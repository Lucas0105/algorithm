// user.cpp
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

#define pii pair<int, int>
#define LM 505
#define INF 2e9

using namespace std;

int N, tab[LM][LM];
vector<pii> adj[LM];
vector<pii> prr;

void addRoad(int mRoadA, int mRoadB, int mLen)
{
    adj[mRoadA].push_back({ mRoadB, mLen });
    adj[mRoadB].push_back({ mRoadA, mLen});
}

void init(int N, int K, int mRoadAs[], int mRoadBs[], int mLens[])
{
    ::N = N;
    for (int i = 1; i <= N; i++) {
        adj[i].clear();
    }

    for (int i = 0; i < K; i++) {
        addRoad(mRoadAs[i], mRoadBs[i], mLens[i]);
    }

}

int dist[LM];
int arr[10], M;
int used[LM], ucnt;

int dijkstra(int mStart) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
    }

    dist[mStart] = 0;
    priority_queue<pii, vector<pii>, greater<pii>>pq;

    pq.push({ 0, mStart });
    ++ucnt;


    while (!pq.empty()) {
        int curBus = pq.top().second;
        int curLen = dist[curBus];
        pq.pop();

        if (used[curBus] == ucnt)
            continue;
        used[curBus] = ucnt;

        for (auto nextNode : adj[curBus]) {
            int nextLen = nextNode.second + curLen;
            int nextBus = nextNode.first;

            if (dist[nextBus] > nextLen) {
                dist[nextBus] = nextLen;

                if (nextBus == arr[0] || nextBus == arr[M])
                    continue;
                pq.push({nextLen, nextBus});
            }
        }

    }

    for (int i = 0; i <= M; i++) {
        if (dist[arr[i]] == INF) return 0;
    }

    for (int i = 0; i <= M; i++) {
        tab[mStart][arr[i]] = tab[arr[i]][mStart] = dist[arr[i]];

        prr.push_back({ mStart, arr[i] });
    }

    return 1;
}

int ret, visited[10];
void dfs(int lev, int u, int dist) {
    if (lev == M) {
        if (tab[u][arr[M]])
                ret = min(ret, dist + tab[u][arr[M]]);
        return;
    }

    for (int i = 1; i < M; i++) {
        int v = arr[i];
        if (visited[i] == 0 && tab[u][v]) {
            visited[i] = 1;
            dfs(lev + 1, v, dist + tab[u][v]);
            visited[i] = 0;
        }
    }
}

int findPath(int mStart, int mEnd, int M, int mStops[])
{
    ret = INF;
    int i;

    for (i = 0; i < M; i++) arr[i + 1] = mStops[i];
    arr[0] = mStart, arr[++M] = mEnd;
    ::M = M;

    for (i = 1; i < M && dijkstra(arr[i]); i++);

    if (i == M) {
        dfs(1, arr[0], 0);
    }

    for (auto item : prr) {
        tab[item.first][item.second] = 0;
        tab[item.second][item.first] = 0;
    }

    prr.clear();

    return ret < INF ? ret : -1;
}
