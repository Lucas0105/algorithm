#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX_N 10001
#define MAX_K 21
#define INF 10000000000
using namespace std;

struct Road {
    long long cost;
    int node;
    int limitK;

    bool operator()(Road a, Road b)
    {
        return a.cost > b.cost;
    }
};


vector<Road> Graph[MAX_N];
int N, M, K;
long long minDist[MAX_K][MAX_N];

void dijk()
{
    for (int i = 0; i < MAX_K; i++)
    {
        fill(minDist[i], minDist[i] + N + 1, INF);
    }
    minDist[K][1] = 0;
    priority_queue<Road, vector<Road>, Road> pq;
    pq.push({ 0, 1, K });

    while (!pq.empty())
    {
        int limit_k = pq.top().limitK;
        int node = pq.top().node;
        long long cost = pq.top().cost;
        pq.pop();

        if (minDist[limit_k][node] < cost)
            continue;

        for (int i = 0; i < Graph[node].size(); i++)
        {
            int nextNode = Graph[node][i].node;
            long long nextCost = Graph[node][i].cost;

            if (minDist[limit_k][nextNode] > cost + nextCost)
            {
                minDist[limit_k][nextNode] = cost + nextCost;
                pq.push({ minDist[limit_k][nextNode], nextNode, limit_k });
            }

            if (limit_k > 0)
            {
                if (minDist[limit_k - 1][nextNode] > cost)
                {
                    minDist[limit_k - 1][nextNode] = cost;
                    pq.push({ minDist[limit_k - 1][nextNode], nextNode, limit_k - 1 });
                }
            }
        }

    }

}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;

    for (int i = 0; i < M; i++)
    {
        int s, e, v;
        cin >> s >> e >> v;

        Graph[s].push_back({ v, e });
        Graph[e].push_back({ v, s });
    }

    dijk();

    long long result = INF;
    for (int i = 0; i < K; i++)
    {
        result = result > minDist[i][N] ? minDist[i][N] : result;
    }
    cout << result;

    return 0;
}
