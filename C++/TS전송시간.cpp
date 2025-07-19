// user.cpp

#include <vector>
#include<queue>
#include<algorithm>

using namespace std;
using pii = pair<int, int>;

const int INF = 1e9;

int N, M;
vector<pii> gAdj[30050];
vector<pii> lAdj[305][50];

int dist[30050];
priority_queue<pii> pq;

int dijkstra(vector<pii> adj[], int s, int e, int n = 30) {
	fill(dist + 1, dist + 1 + n, INF);
	dist[s] = 0;
	pq = {};
	pq.push({ 0, s });

	while (pq.size()) {
		int cur = pq.top().second;
		int minDist = -pq.top().first;
		pq.pop();
		if (dist[cur] != minDist) continue;
		if (cur == e) return minDist;

		for (pii p : adj[cur]) {
			int next = p.first, cost = p.second;
			if (dist[next] > dist[cur] + cost) {
				dist[next] = dist[cur] + cost;
				pq.push({ -dist[next], next });
			}
		}
	}

	return 0;
}

void addEdge(vector<pii> adj[], int a, int b, int c) {
	adj[a].push_back({ b, c });
	adj[b].push_back({ a, c });
}

void removeEdge(vector<pii>adj[], int a, int b) {
	for (int i = 0; i < adj[a].size(); i++) {
		if (adj[a][i].first == b) {
			adj[a].erase(adj[a].begin() + i);
			break;
		}
	}

	for (int i = 0; i < adj[b].size(); i++) {
		if (adj[b][i].first == a) {
			adj[b].erase(adj[b].begin() + i);
			break;
		}
	}
}

void update(int gid) {
	for (int i = 1; i <= 3; i++) {
		int a = i, b = (i % 3) + 1;
		int dist = dijkstra(lAdj[gid], a, b);

		if (dist) {
			a += gid * 100;
			b += gid * 100;
			removeEdge(gAdj, a, b);
			addEdge(gAdj, a, b, dist);
		}
	}
}

void init(int N, int K, int mNodeA[], int mNodeB[], int mTime[])
{
	M = N * 100 + 30;
	for (int i = 1; i <= M; i++) gAdj[i].clear();
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= 30; j++) lAdj[i][j].clear();

	for (int i = 0; i < K; i++) {
		int aid = mNodeA[i] / 100;
		int bid = mNodeB[i] / 100;
		if (aid == bid)
			addEdge(lAdj[aid], mNodeA[i] % 100, mNodeB[i] % 100, mTime[i]);
		else
			addEdge(gAdj, mNodeA[i], mNodeB[i], mTime[i]);
	}

	for (int i = 1; i <= N; i++) update(i);
}


void addLine(int mNodeA, int mNodeB, int mTime)
{
	int aid = mNodeA / 100, bid = mNodeB / 100;
	if (aid == bid) {
		addEdge(lAdj[aid], mNodeA % 100, mNodeB % 100, mTime);
		update(aid);
	}
	else {
		addEdge(gAdj, mNodeA, mNodeB, mTime);
	}
}

void removeLine(int mNodeA, int mNodeB)
{
	int aid = mNodeA / 100, bid = mNodeB / 100;
	if(aid == bid) {
		removeEdge(lAdj[aid], mNodeA % 100, mNodeB % 100);
		update(aid);
	}
	else {
		removeEdge(gAdj, mNodeA, mNodeB);
	}
}

int checkTime(int mNodeA, int mNodeB)
{
	return dijkstra(gAdj, mNodeA, mNodeB, M);
}
