// user.cpp

#include <algorithm>

using namespace std;

constexpr int LM = (200000 * 4) + 5;
constexpr int INF = 1e9;
int N = 0;
int subscriber[200005];

struct SegTree {
	int tree[LM][3];

	void init(int node, int s, int e) {
		if (s == e) {
			tree[node][0] = tree[node][1] = tree[node][2] = subscriber[s];
			return;
		}

		int left = node * 2, right = left + 1, mid = (s + e) / 2;
		init(left, s, mid);
		init(right, mid + 1, e);
		tree[node][0] = tree[left][0] + tree[right][0];
		tree[node][1] = max(tree[left][1], tree[right][1]);
		tree[node][2] = min(tree[left][2], tree[right][2]);
	}

	void update(int node, int s, int e, int target) {
		if (s == e) {
			tree[node][0] = tree[node][1] = tree[node][2] = subscriber[target];
			return;
		}

		int left = node * 2, right = left + 1, mid = (s + e) / 2;

		if (target <= mid) update(left, s, mid, target);
		else update(right, mid + 1, e, target);

		tree[node][0] = tree[left][0] + tree[right][0];
		tree[node][1] = max(tree[left][1], tree[right][1]);
		tree[node][2] = min(tree[left][2], tree[right][2]);
	}

	int queryCnt(int node, int ts, int te, int qs, int qe) {
		if (qs > te || qe < ts) return 0;
		if (qs <= ts && qe >= te) return tree[node][0];

		int left = node * 2, right = left + 1, mid = (ts + te) / 2;
		int leftSum = queryCnt(left, ts, mid, qs, qe);
		int rightSum = queryCnt(right, mid + 1, te, qs, qe);
		return leftSum + rightSum;
	}

	int queryMax(int node, int ts, int te, int qs, int qe) {
		if (qs > te || qe < ts) return 0;
		if (qs <= ts && qe >= te) return tree[node][1];

		int left = node * 2, right = left + 1, mid = (ts + te) / 2;
		int leftV = queryMax(left, ts, mid, qs, qe);
		int rightV = queryMax(right, mid + 1, te, qs, qe);
		return max(leftV, rightV);
	}

	int queryMin(int node, int ts, int te, int qs, int qe) {
		if (qs > te || qe < ts) return INF;
		if (qs <= ts && qe >= te) return tree[node][2];

		int left = node * 2, right = left + 1, mid = (ts + te) / 2;
		int leftV = queryMin(left, ts, mid, qs, qe);
		int rightV = queryMin(right, mid + 1, te, qs, qe);
		return min(leftV, rightV);
	}
}segTree;

void init(int N, int mSubscriber[]) {
	::N = N;
	for (int i = 1; i <= N; i++) {
		subscriber[i] = mSubscriber[i - 1];
	}
	segTree.init(1, 1, N);
	return;
}

int subscribe(int mId, int mNum) {
	subscriber[mId] += mNum;
	segTree.update(1, 1, N, mId);
	return subscriber[mId];
}

int unsubscribe(int mId, int mNum) {
	subscriber[mId] -= mNum;
	segTree.update(1, 1, N, mId);
	return subscriber[mId];
}

int count(int sId, int eId) {
	int res = segTree.queryCnt(1, 1, N, sId, eId);
	return res;
}

int calculate(int sId, int eId) {
	int maxV = segTree.queryMax(1, 1, N, sId, eId);
	int minV = segTree.queryMin(1, 1, N, sId, eId);
	int res = maxV - minV;
	return res;
}
