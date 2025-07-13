#include <vector>
#include <queue>
#include <unordered_map>
#include <string.h>

#define MAX_N 305
#define INF 1e9

using namespace std;

struct RoadData {
	int roadIdx, city, cost;
};

vector<RoadData> adj[MAX_N];
unordered_map<int, int> hMap;
int idx;
bool removeIdx[3500];
//user.cpp

int getMapIdx(int id) {
	if (hMap.count(id))
		return hMap[id];
	else {
		hMap[id] = idx++;
		return hMap[id];
	}
}


void add(int mId, int sCity, int eCity, int mToll) {
	int idx = getMapIdx(mId);
	removeIdx[idx] = false;
	adj[sCity].push_back({ idx, eCity, mToll });
	return;
}

void init(int N, int K, int mId[], int sCity[], int eCity[], int mToll[]) {
	idx = 0;
	hMap.clear();

	for (int i = 0; i < N; i++) {
		adj[i].clear();
		removeIdx[i] = false;
	}
	for (int i = 0; i < K; i++) {
		add(mId[i], sCity[i], eCity[i], mToll[i]);
	}
	return;
}

void remove(int mId) {
	int idx = getMapIdx(mId);
	removeIdx[idx] = true;

	return;
}

struct Data {
	int dist, idx, discount;

	bool operator < (const Data &r) const {
		if (dist == r.dist) {
			return discount > r.discount;
		}
		return dist > r.dist;
	}
};

int cost(int M, int sCity, int eCity) {
	
	priority_queue<Data> pq;
	pq.push({ 0, sCity, 0 });

	int dist[11][MAX_N];

	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j < MAX_N; j++)
		{
			dist[i][j] = INF;
		} 
	}

	while (!pq.empty()) {
		int curIdx = pq.top().idx;
		int curDist = pq.top().dist;
		int curDisc = pq.top().discount;
		pq.pop();

		if (curIdx == eCity) {
			continue;
		}

		for (auto nextData : adj[curIdx]) {
			int nextCost = nextData.cost;
			int nextIdx = nextData.city;
			int nextRoad = nextData.roadIdx;

			if (removeIdx[nextRoad])
				continue;

			if (nextCost + curDist < dist[curDisc][nextIdx]) {
				dist[curDisc][nextIdx] = nextCost + curDist;
				pq.push({ dist[curDisc][nextIdx], nextIdx, curDisc });
			}

			// discount
			if (M > curDisc) {
				int dicNextCost = nextCost / 2;

				if (dicNextCost + curDist < dist[curDisc + 1][nextIdx]) {
					dist[curDisc + 1][nextIdx] = dicNextCost + curDist;
					pq.push({ dist[curDisc + 1][nextIdx], nextIdx, curDisc + 1 });
				}
			}

		}
	}

	int result = INF;

	for (int i = 0; i <= 10; i++) {
		result = min(result, dist[i][eCity]);
	}

	if (result == INF)
		result = -1;

	return result;
}