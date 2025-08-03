// user.cpp
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
using pii = pair<int, int>;
constexpr int MAXN = 15;
constexpr int MAXO = 15005;

struct Order {
	vector<int> doneList;
	int cntFood;
	int cancel;
}orders[MAXO];

struct Kitchen {
	queue<int> orderList;
	int doneTime;
}kitchen[MAXN];

int N;
int* cookingTimeList;

int cntOrder;
int idCnt;
unordered_map<int, int> idMap;

void cooking(int mTime) {
	for (int i = 0; i < N; i++) {
		if (kitchen[i].doneTime == 0) continue;

		while (!kitchen[i].orderList.empty()) {
			int old = kitchen[i].orderList.front();

			while (orders[old].cancel) {
				kitchen[i].orderList.pop();
				if (kitchen[i].orderList.empty())break;
				old = kitchen[i].orderList.front();
			}

			if (kitchen[i].orderList.empty()) {
				kitchen[i].doneTime = 0;
				break;
			}

			if (mTime < kitchen[i].doneTime) break;

			kitchen[i].orderList.pop();

			orders[old].doneList.push_back(i);

			if (orders[old].cntFood == orders[old].doneList.size()) {
				--cntOrder;
			}

			kitchen[i].doneTime += cookingTimeList[i];
		}

		if (kitchen[i].orderList.empty()) kitchen[i].doneTime = 0;
	}
}

void init(int N, int mCookingTimeList[])
{
	for (int i = 0; i < MAXO; i++) {
		orders[i].doneList.clear();
		orders[i].cancel = 0;
	}

	for (int i = 0; i < MAXN; i++) {
		kitchen[i].orderList = {};
		kitchen[i].doneTime = 0;
	}

	::N = N;
	idCnt = cntOrder = 0;
	idMap.clear();
	cookingTimeList = mCookingTimeList;
}

int order(int mTime, int mID, int M, int mDishes[])
{
	cooking(mTime);

	idMap[mID] = ++idCnt;

	orders[idCnt].cntFood = M;
	for (int i = 0; i < M; i++) {
		int n = mDishes[i] - 1;
		kitchen[n].orderList.push(idCnt); 
		if (kitchen[n].doneTime == 0) kitchen[n].doneTime = mTime + cookingTimeList[n];
	}

	return ++cntOrder;
}

int cancel(int mTime, int mID)
{
	cooking(mTime);

	int old = idMap[mID];
	orders[old].cancel = 1;
	for (auto n : orders[old].doneList) {
		if (kitchen[n].doneTime == 0) continue;

		int _old = kitchen[n].orderList.front();
		kitchen[n].orderList.pop();

		while (orders[_old].cancel && !kitchen[n].orderList.empty()) {
			_old = kitchen[n].orderList.front();
			kitchen[n].orderList.pop();
		}

		if (orders[_old].cancel) {
			kitchen[n].doneTime = 0;
			continue;
		}

		orders[_old].doneList.push_back(n);

		if (orders[_old].cntFood == orders[_old].doneList.size()) {
			--cntOrder;
		}
	}


	return --cntOrder;
}

int getStatus(int mTime, int mID)
{
	cooking(mTime);

	int old = idMap[mID];

	if (orders[old].cancel) return -1;

	return orders[old].cntFood - orders[old].doneList.size();
}
