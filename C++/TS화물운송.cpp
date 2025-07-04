// user.cpp
#include <queue>
#include <vector>
#include <string.h>

//          limit, id
#define pii pair<int, int>

using namespace std;

vector<pii> adj[1000];

int N;

void init(int N, int K, int sCity[], int eCity[], int mLimit[]) {
	::N = N;

	for (int i = 0; i < N; i++) {
		adj[i] = vector<pii>();
	}

	for (int i = 0; i < K; i++) {
		int sId = sCity[i];
		int eId = eCity[i];
		int limit = mLimit[i];
		adj[sId].push_back({ limit, eId });
	}

	return;
}

void add(int sCity, int eCity, int mLimit) {
	adj[sCity].push_back({ mLimit, eCity });
	return;
}

bool visited[1000];
int dist[1000];


int dijkstra(int sCity, int eCity) {
	memset(visited, false, sizeof(bool) * N);
	memset(dist, 0, sizeof(int) * N);

	priority_queue<pii> pq;
	pq.push({ 30000, sCity});
	
	int result = 30000;

	while (!pq.empty()) {
		int limit = pq.top().first;
		int sId = pq.top().second;
		pq.pop();

		if (visited[sId])
			continue;
		visited[sId] = true;
		result = min(result, limit);

		if (sId == eCity) {
			return result;
		}

		for (auto next : adj[sId]) {
			int eLimit = next.first;
			int eId = next.second;

			if (visited[eId])
				continue;

			if (dist[eId] < eLimit) {
				dist[eId] = eLimit;
				pq.push({ eLimit, eId });
			}
		}
	}

	return -1;
}

int calculate(int sCity, int eCity) {
	int result = dijkstra(sCity, eCity);
	return result;
}
