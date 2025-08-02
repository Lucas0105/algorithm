//user.cpp
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

constexpr int MAXR = 50005;
constexpr int BUCKET = 100;
constexpr int MAXG = 105;

struct Radio {
	int freq;
	int x, y;
	int pw;
}radioList[MAXR];

int N, Limit;
vector<int> bucket[MAXG][MAXG];

struct Comp {
	bool operator() (const int aId, const int bId) const {
		if (radioList[aId].pw != radioList[bId].pw) return radioList[aId].pw < radioList[bId].pw;
		return aId < bId;
	}
};

pii que[MAXG * MAXG];
int fr, re;
int visited[MAXG][MAXG], vCnt;
int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };

void init(int N, int mLimit)
{
	::N = N;
	Limit = mLimit;
	for (int i = 0; i < MAXG; i++) {
		for (int j = 0; j < MAXG; j++) {
			bucket[i][j].clear();
		}
	}
}

void addRadio(int K, int mID[], int mFreq[], int mY[], int mX[])
{
	for (int i = 0; i < K; i++) {
		int mId = mID[i];
		radioList[mId].freq = mFreq[i];
		radioList[mId].x = mX[i];
		radioList[mId].y = mY[i];

		bucket[mY[i] / BUCKET][mX[i] / BUCKET].push_back(mId);
	}
}

int getMinPower(int mID, int mCount)
{
	int res = 0;

	int mx = radioList[mID].x, my = radioList[mID].y;
	int bx = mx / BUCKET, by = my / BUCKET;
	int freq = radioList[mID].freq;

	vector<int> cands;
	for (int id : bucket[by][bx]) {
		if (id == mID) continue;

		int pw = (abs(radioList[id].x - mx) + abs(radioList[id].y - my)) * 10;
		if (radioList[id].freq != freq) pw += 1000;
		if (Limit < pw) continue;

		radioList[id].pw = pw;
		cands.push_back(id);
	}
	int GN = (N - 1) / BUCKET;
	int LIM = GN * 2;

	fr = re = 0;
	que[re++] = { by, bx };
	visited[by][bx] = ++vCnt;

	while (fr < re) {
		int cy = que[fr].first, cx = que[fr++].second;

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i], nx = cx + dx[i];
			if (ny < 0 || ny > GN || nx < 0 || nx > GN) continue;
			if (visited[ny][nx] == vCnt) continue;

			int diff = abs(by - ny) + abs(bx - nx);
			if (diff > LIM) continue;

			visited[ny][nx] = vCnt;
			que[re++] = { ny, nx };

			for (int id : bucket[ny][nx]) {
				int pw = (abs(radioList[id].x - mx) + abs(radioList[id].y - my)) * 10;
				if (radioList[id].freq != freq) pw += 1000;
				if (Limit < pw) continue;

				radioList[id].pw = pw;
				cands.push_back(id);

				if (cands.size() >= mCount && LIM > diff + 3) LIM = diff + 3;
			}

		}
	}
	
	partial_sort(cands.begin(), cands.begin() + mCount, cands.end(), Comp());

	for (int i = 0; i < mCount; i++) res +=  radioList[cands[i]].pw;

	return res;
}