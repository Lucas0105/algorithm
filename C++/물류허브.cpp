// *** user.cpp ***
#include<vector>
#include<queue>
#include<unordered_map>
#include<iostream>
#define pii pair<int, int>

using namespace std;

const int LM = 605; // 도시의 개수
const int INF = int(1e9);


struct comp {
    bool operator() (const pii& l, const pii& r) const {
        return l.second > r.second;
    }
};

vector<pii> Graph[LM];
vector<pii> rGraph[LM];
priority_queue<pii, vector<pii>, comp> pq;
unordered_map<int, int> cityHash;
int cityArray[LM];
int hashIdx = 1;


int getHash(int value) {
    if (cityHash.count(value) > 0)
        return cityHash[value];
    else {
        cityHash[value] = hashIdx;
        return hashIdx++;
    }
}

int dijkstra(int s, vector<pii> G[]) {
    int visited[LM];
    int dist[LM];
    for (int i = 0; i < LM; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[s] = 0;
    pq.push({ s, 0 });

    while (!pq.empty()) {
        pii d = pq.top();
        pq.pop();
        int node = d.first;
        int value = d.second;

        if (visited[node])
            continue;
        visited[node] = 1;

        for (pii nextNode : G[node]) {
            if (dist[nextNode.first] > nextNode.second + value) {
                dist[nextNode.first] = nextNode.second + value;
                pq.push({ nextNode.first, dist[nextNode.first] });
            }
        }
    }

    int result = 0;

    for (int i = 1; i < hashIdx; i++) {
        result += dist[i];
    }

    return result;
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
    hashIdx = 1;

    for (int i = 0; i < LM; i++) {
        Graph[i].clear();
        rGraph[i].clear();
        cityArray[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        int sIdx = getHash(sCity[i]);
        int eIdx = getHash(eCity[i]);
        cityArray[sIdx] = sCity[i];
        cityArray[eIdx] = eCity[i];

        Graph[sIdx].push_back({ eIdx, mCost[i] });
        rGraph[eIdx].push_back({ sIdx, mCost[i] });
    }

    return hashIdx - 1;
}

void add(int sCity, int eCity, int mCost) {
    int sIdx = getHash(sCity);
    int eIdx = getHash(eCity);

    Graph[sIdx].push_back({ eIdx, mCost });
    rGraph[eIdx].push_back({ sIdx, mCost });
}

int cost(int mHub) {
    int start = getHash(mHub);
    int result = 0;

    result += dijkstra(start, Graph);
    result += dijkstra(start, rGraph);


    return result;
}
