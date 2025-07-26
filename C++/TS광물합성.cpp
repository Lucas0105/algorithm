// user.cpp
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAX_M = 3505;
constexpr int INF = 1 << 20;

vector<int>entry[2][3];

int shipFee;
int idCnt;
struct Matrial {
	int mId, type, cost, content;

	void erase(int id) {
		auto& tg = entry[mId][type];
		auto it = find(tg.begin(), tg.end(), id);
		*it = tg.back();
		tg.pop_back();
	}
}matrials[MAX_M];

struct Result {
	int mCost;
	int mContent;
};

void init(int mShipFee) {
	matrials[0] = { 0, 0, INF, 0 };
	idCnt = 0;
	shipFee = mShipFee;
	for (int i = 0; i < 3; i++) {
		entry[0][i].clear(); entry[1][i].clear();
	}
}

int gather(int mMineId, int mType, int mCost, int mContent) {
	matrials[++idCnt] = { mMineId, mType, mCost, mContent };
	entry[mMineId][mType].push_back(idCnt);
	return entry[mMineId][mType].size();
}

Result mix(int mBudget) {
	Result result = { 0, 0 };
	int low = 0, height = 1000000;
	int i, j;
	int ansCost = INF, ansContent = 0, ans[3] = { 0 };

	while (low <= height) {
		int mContent = (low + height) / 2;
		int candi[2][3] = { 0 };

		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 3; j++) {
				for (auto id : entry[i][j]) {
					if (matrials[id].content < mContent) continue;
					if (matrials[candi[i][j]].cost > matrials[id].cost) {
						candi[i][j] = id;
					}
				}
			}
		}

		auto& A = candi[0];
		auto& B = candi[1];
		int aCost = matrials[A[0]].cost + matrials[A[1]].cost + matrials[A[2]].cost + shipFee;
		int bCost = matrials[B[0]].cost + matrials[B[1]].cost + matrials[B[2]].cost + shipFee;

		int twoShipFee = shipFee * 2; int t[3] = { 0 }, tCost = twoShipFee;
		for (int i = 0; i < 3; i++) {
			if (matrials[A[i]].cost < matrials[B[i]].cost) t[i] = A[i];
			else t[i] = B[i];
			tCost += matrials[t[i]].cost;
		}

		if (tCost > aCost) {
			tCost = aCost;
			for (int i = 0; i < 3; i++) {
				t[i] = A[i];
			}
		}

		if (tCost > bCost) {
			tCost = bCost;
			for (int i = 0; i < 3; i++) {
				t[i] = B[i];
			}
		}

		if (tCost <= mBudget) {
			ansCost = tCost;
			ansContent = mContent;
			for (int i = 0; i < 3; i++) {
				ans[i] = t[i];
			}
			low = mContent + 1;
		}
		else {
			height = mContent - 1;
		}
	}

	if (ansCost < INF) {
		result = { ansCost, ansContent };
		for (i = 0; i < 3; i++) {
			matrials[ans[i]].erase(ans[i]);
		}
	}

	return result;
}
