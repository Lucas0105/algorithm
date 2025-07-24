
//user.cpp

#include <unordered_map>
#include <vector>

constexpr int MAXN = 305;
constexpr int MAXK = 1705;

using namespace std;
using pii = pair<int, int>;

vector<pii> adj[MAXN];

unordered_map<int, pii> roads;

int visited[MAXN], vCnt;
int minC, maxC;
int dst;

void add(int mId, int sCity, int eCity, int mCost) {
	roads[mId] = { sCity, eCity };
	adj[sCity].push_back({ eCity, mCost });
	return;
}


void init(int N, int K, int mId[], int sCity[], int eCity[], int mCost[]) {
	roads.clear(); vCnt = 0;
	for (int i = 0; i < MAXN; i++)adj[i].clear();
	for (int i = 0; i < K; i++)add(mId[i], sCity[i], eCity[i], mCost[i]);
}

void remove(int mId) {
	int sCity = roads[mId].first;
	int eCity = roads[mId].second;
	for (int idx = 0; idx < adj[sCity].size(); idx++) {
		if (adj[sCity][idx].first == eCity) {
			adj[sCity].erase(adj[sCity].begin() + idx);
			return;
		}
	}
	return;
}

bool dfs(int city) {
	if (city == dst) return true;
	if (visited[city] == vCnt) return false;
	visited[city] = vCnt;

	for (auto& p : adj[city]) {
		if (visited[p.first] == vCnt) continue;
		if (p.second < minC || p.second > maxC) continue;
		if (dfs(p.first)) return true;
	}
	return false;
}


bool isOk(int minDiff, int sCity) {
	for (minC = 1; minC <= 500 - minDiff; minC++) {
		vCnt++;
		maxC = minC + minDiff;

		if (dfs(sCity)) return true;
	}

	return false;
}

int cost(int sCity, int eCity) {
	int low = 0, high = 500;
	dst = eCity;
	
	while (low <= high) {
		int mid = (low + high) / 2;
		if (isOk(mid, sCity)) high = mid - 1;
		else low = mid + 1;
	}

	if (low >= 500) return -1;
	return low;

	return 0;
}