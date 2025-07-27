// user.cpp
#include <vector>
#include <queue>
#include <string.h>

constexpr int MAX_LIFE = 1000005;
constexpr int LM = 1000000 * 4 + 5;

using namespace std;
using pii = pair<int, int>;

struct Bact {
	int life, htime;
}bact[30005];

priority_queue<pii, vector<pii>, greater<>>lpq;
priority_queue<pii, vector<pii>, greater<>>tpq;

int tree[LM];
int idCnt;

struct Segment {
	void update(int node, int s, int e, int target, int diff) {
		if (s == e) {
			tree[node] += diff;
			return;
		}

		int left = node * 2, right = left + 1, mId = (s + e) / 2;

		if (target <= mId) update(left, s, mId, target, diff);
		else update(right, mId + 1, e, target, diff);

		tree[node] = tree[left] + tree[right];
	}

	int cntQuery(int node, int ts, int te, int qs, int qe) {
		if (qs > te || qe < ts)return 0;
		if (qs <= ts && qe >= te)return tree[node];

		int left = node * 2, right = left + 1, mId = (ts + te) / 2;

		int leftV = cntQuery(left, ts, mId, qs, qe);
		int rightV = cntQuery(right, mId + 1, te, qs, qe);

		return leftV + rightV;
	}
}segm;

void update(int T) {
	while (tpq.size()) {
		int t = tpq.top().first;
		int id = tpq.top().second;
		if (t > T) return;
		tpq.pop();

		int& life = bact[id].life;
		int htime = bact[id].htime;

		segm.update(1, 1, MAX_LIFE, life, -1);
		life /= 2;

		if (life >= 100) {
			tpq.push({ t + htime, id });
			lpq.push({ life, id });
			segm.update(1, 1, MAX_LIFE, life, 1);
		}
	}
}

void init()
{
	lpq = {};
	tpq = {};
	for (int i = 0; i < LM; i++) tree[i] = 0;
}

void addBacteria(int tStamp, int mID, int mLifeSpan, int mHalfTime)
{
	idCnt = mID;
	bact[mID] = { mLifeSpan, mHalfTime };
	lpq.push({ mLifeSpan, mID });
	tpq.push({ tStamp + mHalfTime, mID });
	segm.update(1, 1, MAX_LIFE, mLifeSpan, 1);
}

int getMinLifeSpan(int tStamp)
{
	update(tStamp);

	while (lpq.size()) {
		int id = lpq.top().second;
		if (bact[id].life >= 100) return id;
		lpq.pop();
	}
	return -1;
}

int getCount(int tStamp, int mMinSpan, int mMaxSpan)
{
	update(tStamp);
	int res = segm.cntQuery(1, 1, MAX_LIFE, mMinSpan, mMaxSpan);

	return res;
}
