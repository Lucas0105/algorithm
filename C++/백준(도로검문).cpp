#include <iostream>
#include <vector>
#include <queue>


#define INF 10000000

using namespace std;

int N, M;
vector<pair<int, int>> adj[1001];
vector<int> parent;


int road1, road2 = 0;
bool first = true;

int dijk()
{
    vector<int> dist(N + 1, INF);
    dist[1] = 0;

    priority_queue <pair<int, int>, vector<pair<int, int>>, less<>> pq;
    pq.push({ 0, 1 });

    while (!pq.empty())
    {
        int cost = pq.top().first;
        int cur = pq.top().second;
        pq.pop();


        if (dist[cur] < cost)
            continue;

        for (auto next : adj[cur])
        {
            int nextCost = next.first;
            int nextPos = next.second;

            if ((nextPos == road1 && cur == road2) || (nextPos == road2 && cur == road1))
                continue;

            int tmpCost = cost + nextCost;
            if (tmpCost < dist[nextPos])
            {
                dist[nextPos] = tmpCost;

                pq.push({ tmpCost, nextPos });
                if(first)
                    parent[nextPos] = cur;
            }
        }

    }
    if (dist[N] == INF)
        return -1;
    else
        return dist[N];
}


int main()
{
    FILE* stream;
    freopen_s(&stream, "도로검문.txt", "r", stdin);

    cin >> N >> M;
    parent.resize(1001, -1);

    for (int i = 0; i < M; i++)
    {
        int a, b, v;
        cin >> a >> b >> v;

        adj[a].push_back({ v, b });
        adj[b].push_back({ v, a });
    }

    int init = dijk();

    first = false;
    
    int result = -1;
    for (int i = 1; i <= N; i++)
    {
        if (parent[i] == -1)
            continue;

        road1 = i;
        road2 = parent[i];

        int obstructCost = dijk();

        if (obstructCost == -1)
        {
            result = -1;
            break;
        }

        if (obstructCost - init > result)
            result = obstructCost - init;
    }

    cout << result;

    return 0;
}
