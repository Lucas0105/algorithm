// user.cpp
#include <queue>
#include <vector>

using namespace std;

#define pii pair<int, int>
#define MAP_SIZE_MAX	350
#define MAX_ID 205

int  (*dungeon)[MAP_SIZE_MAX];
vector<pii>adj[MAX_ID];
bool isUse[MAX_ID];
pii pos[MAX_ID];
int stamina, mN;
int isVisited[MAP_SIZE_MAX][MAP_SIZE_MAX];

int dr[4] = { 0, -1, 0, 1 };
int dc[4] = { -1, 0, 1, 0 };

void bfs(int sId, int sRow, int sCol) {
	for (int i = 0; i < mN; i++) {
		for (int j = 0; j < mN; j++) {
			isVisited[i][j] = 0;
		}
	}

	isVisited[sRow][sCol] = 1;
	queue <pii> q;
	q.push({ sRow, sCol });

	while (!q.empty()) {
		pii node = q.front();
		int row = node.first, col = node.second;
		q.pop();

		// Gate
		if (dungeon[row][col] < 0 && isVisited[row][col] != 1) {
			int tID = dungeon[row][col] * -1;
			adj[sId].push_back({ tID, isVisited[row][col] - 1});
			adj[tID].push_back({ sId, isVisited[row][col] - 1 });
		}

		if (isVisited[row][col] > stamina)
			continue;

		for (int i = 0; i < 4; i++) {
			int nRow = row + dr[i], nCol = col + dc[i];

			if (nRow < 0 || nRow >= mN || nCol >= mN || nCol < 0)
				continue;

			if (dungeon[nRow][nCol] <= 0 && isVisited[nRow][nCol] == 0) {
				isVisited[nRow][nCol] = isVisited[row][col] + 1;
				q.push({ nRow, nCol });
			}

		}
	}


}

int dijkstra(int sId, int eId) {
	bool isVisited[MAX_ID] = {};
	int dist[MAX_ID] = {};

	for (int i = 1; i < MAX_ID; i++) {
		dist[i] = (int)1e10;
	}
	dist[sId] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> pq = {};
	pq.push({ 0, sId });

	while (!pq.empty()) {
		int currentCost = pq.top().first;
		int currentId = pq.top().second;
		pq.pop();
		int row = pos[currentId].first, col = pos[currentId].second;

		if (isVisited[currentId] )
			continue;

		isVisited[currentId] = true;

		if (currentId == eId) {
			return dist[eId];
		}

		for (auto& nextNode : adj[currentId]) {
			int nextId = nextNode.first, nextDist = nextNode.second;

			if (!isUse[nextId])
				continue;

			if (nextDist + currentCost < dist[nextId]) {
				dist[nextId] = nextDist + currentCost;
				pq.push({ dist[nextId], nextId });
			}
		}
	}

	return -1;
}

void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
	mN = N;
	dungeon = mMap;
	stamina = mMaxStamina;

	for (int i = 1; i < MAX_ID; i++) {
		isUse[i] = false;
		adj[i].clear();
	}

	return;
}

void addGate(int mGateID, int mRow, int mCol)
{
	isUse[mGateID] = true;
	pos[mGateID] = { mRow, mCol };
	int minusId = mGateID * -1;
	dungeon[mRow][mCol] = minusId;

	bfs(mGateID, mRow, mCol);

	return;
}

void removeGate(int mGateID)
{
	isUse[mGateID] = false;
	return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
	int result = dijkstra(mStartGateID, mEndGateID);
	return result;
}
