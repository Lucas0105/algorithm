// user.cpp

#include <vector>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;
constexpr int LM = 6005;
constexpr int HLM = 30005;
int N;

struct Hole {
	int r, c, closed, del;
	int L, R;

	void init(int nr, int nc) {
		{
			r = nr, c = nc, closed = 0, del = 0;
			L = r + c, R = N + r - c;
		}
	}

	int operator-(const Hole& t) const {
		if (r == t.r) return abs(c - t.c) * 10;
		if (c == t.c) return abs(r - t.r) * 10;
		return abs(r - t.r) * 14;
	}

	bool operator<(const Hole& t) const {
		return r != t.r ? r < t.r : c < t.c;
	}
}hole[HLM];

pii leftRange[LM];
pii rightRange[LM];
vector<int> leftList[LM];
vector<int> rightList[LM];

vector<int> hori[LM];
vector<int> vert[LM];
vector<int> leftRoad[LM];
vector<int> rightRoad[LM];

void init(int N)
{
	::N = N;

	for (int i = 0; i <= LM; i++) {
		leftRange[i] = { 0, 0 };
		rightRange[i] = { 0, 0 };
		leftList[i].clear();
		rightList[i].clear();

		hori[i].clear();
		vert[i].clear();
		leftRoad[i].clear();
		rightRoad[i].clear();
	}
}

void addDiagonal(int mARow, int mACol, int mBRow, int mBCol)
{
	if (mARow + mACol == mBRow + mBCol) {
		int L = mARow + mACol;
		int st = N + mARow - mACol;
		int ed = N + mBRow - mBCol;
		if (st > ed) swap(st, ed);
		leftRange[L] = { st, ed };
		for (auto id : leftList[L]) {
			if (st <= hole[id].R && hole[id].R <= ed) {
				leftRoad[L].push_back(id);
			}
		}
	}
	else {
		int R = N + mARow - mACol;
		int st = mARow + mACol;
		int ed = mBRow + mBCol;
		if (st > ed) swap(st, ed);
		rightRange[R] = { st, ed };
		for (auto id : rightList[R]) {
			if (st <= hole[id].L && hole[id].L <= ed) {
				rightRoad[R].push_back(id);
			}
		}
	}
}

void addHole(int mRow, int mCol, int mID)
{
	hole[mID].init(mRow, mCol);
	hori[mRow].push_back(mID);
	vert[mCol].push_back(mID);

	int L = mRow + mCol, R = N + mRow - mCol;
	leftList[L].push_back(mID);
	rightList[R].push_back(mID);
	if (leftRange[L].first <= R && R <= leftRange[L].second) {
		leftRoad[L].push_back(mID);
	}
	if (rightRange[R].first <= L && L <= rightRange[R].second) {
		rightRoad[R].push_back(mID);
	}
}

void eraseHole(int mRow, int mCol)
{
	int id = -1;
	for (auto i : hori[mRow]) if (hole[i].c == mCol) {
		id = i; break;
	}
	if (id < 0) return;
	hole[id].del = 1;
}

int holeID, holeDist;
void search(vector<int>& vec) {
	for (auto id : vec) {
		if (hole[id].del) continue;
		if (hole[id].closed) continue;
		int dist = hole[0] - hole[id];
		if (holeDist > dist) holeID = id, holeDist = dist;
		else if (holeDist == dist && hole[id] < hole[holeID]) {
			holeID = id;
		}
	}
}

int hitMarble(int mRow, int mCol, int mK)
{
	vector<int> closedHoleList;
	int retID = -1;
	hole[0].init(mRow, mCol);
	auto& tg = hole[0];
	for (int i = 0; i < mK; i++) {
		int L = tg.r + tg.c, R = N + tg.r - tg.c;
		holeID = -1, holeDist = 1e9;
		search(hori[tg.r]);
		search(vert[tg.c]);
		if (leftRange[L].first <= R && R <= leftRange[L].second) {
			search(leftRoad[L]);
		}
		if (rightRange[R].first <= L && L <= rightRange[R].second) {
			search(rightRoad[R]);
		}
		if (holeID < 0) break;
		closedHoleList.push_back(holeID);
		hole[holeID].closed = 1;
		tg = hole[holeID];
		retID = holeID;
	}
	for (auto id : closedHoleList)
		hole[id].closed = 0;
	return retID;
}
