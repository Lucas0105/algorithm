
//user.cpp

#include<vector>
#include<queue>
using namespace std;
using pii = pair<int, int>;
const int INF = 1e9;

int N;
enum { WALK, BIKE, TAXI };

vector<pii> adj[105];
bool bike[105];
int C[105][505][3];

struct Data {
	int spot, cost, time, type;
	bool operator < (const Data& r) const {
		if (cost != r.cost) return cost > r.cost;
		return time > r.time;
	}
};
priority_queue<Data> pq;


void init(int N)
{
	::N = N;
	for (int i = 1; i <= N; i++) {
		bike[i] = 0;
		adj[i].clear();
	}
}

void addRoad(int K, int mSpotA[], int mSpotB[], int mDis[])
{
	for (int i = 0; i < K; i++) {
		adj[mSpotA[i]].push_back({ mSpotB[i], mDis[i] });
		adj[mSpotB[i]].push_back({ mSpotA[i], mDis[i] });
	}
}
int maxTime;

void push(int spot, int cost, int time, int type) {
	if (time > maxTime) return;
	if (C[spot][time][type] <= cost)return;
	pq.push({ spot, cost, time, type });
	C[spot][time][type] = cost;
}

void addBikeRent(int mSpot)
{
	bike[mSpot] = 1;
}

int getMinMoney(int mStartSpot, int mEndSpot, int mMaxTime)
{
	::maxTime = mMaxTime;
	pq = {};
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= maxTime; j++) {
			C[i][j][0] = C[i][j][1] = C[i][j][2] = INF;
		}
	}

	pq.push({ mStartSpot, 0, 0, WALK });
	C[mStartSpot][0][WALK] = 0;

	while (pq.size()) {
		Data d = pq.top();
		int spot = d.spot, cost = d.cost, time = d.time, type = d.type;
		pq.pop();
		if (C[spot][time][type] != cost) continue;

		if (spot == mEndSpot && !(type == BIKE && !bike[spot]))
			return cost;

		for (pii p : adj[spot]) {
			int nspot = p.first;
			int dist = p.second;

			if (type == WALK) {
				push(nspot, cost, time + dist * 17, WALK);								// walk->walk
				if (bike[spot]) push(nspot, cost + dist * 4, time + dist * 4, BIKE);	// walk->bike
				push(nspot, cost + dist * 19, time + dist + 7, TAXI);
			}
			else if (type == TAXI) {
				push(nspot, cost, time + dist * 17, WALK);
				if (bike[spot])push(nspot, cost + dist * 4, time + dist * 4, BIKE);
				push(nspot, cost + dist * 19, time + dist, TAXI);

			}
			else if (type == BIKE) {
				push(nspot, cost + dist * 4, time + dist * 4, BIKE);
				if (bike[spot]) {
					push(nspot, cost, time + dist * 17, WALK);
					push(nspot, cost + dist * 19, time + dist + 7, TAXI);
				}
			}
		}
	}

	return -1;
}