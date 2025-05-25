// user.cpp
#include <unordered_map>
#include <queue>
#include <list>
#define MAX 201

using namespace std;

int idIdx;
unordered_map<int, int> idMap;

struct Train {
	int idIdx, sId, eId, step;
	list<int> trainList;

	bool isStation(int t) {
		if(t < sId || t > eId)
			return false;
		int result = (t - sId) % step;

		if (result == 0)
			return true;
		return false;
	}
	
	bool setCrossTrain(Train& t) {
		int lt = sId, rt = t.sId;
		
		if (sId > t.eId || eId < t.sId)
			return false;

		while (lt <= eId && rt <= t.eId) {
			if (lt == rt) {
				trainList.push_back(t.idIdx);
				t.trainList.push_back(idIdx);
				return true;
			}

			if (lt > rt) {
				rt += t.step;
			}
			else {
				lt += step;
			}
		}

		return false;
	}
}train[MAX];

void add(int mId, int sId, int eId, int mInterval) {
	train[idIdx] = Train({ idIdx, sId, eId, mInterval });
	
	for (int i = 0; i < idIdx; i++) {
		if (train[i].step == -1)
			continue;
		train[i].setCrossTrain(train[idIdx]);
	}
	idMap[mId] = idIdx;

	idIdx++;
	return;
}

void init(int N, int K, int mId[], int sId[], int eId[], int mInterval[]) {
	idIdx = 0;
	for (int i = 0; i < K; i++) {
		add(mId[i], sId[i], eId[i], mInterval[i]);
	}
	return;
}

void remove(int mId) {
	int id = idMap[mId];

	train[id].step = -1;

	return;
}

int calculate(int sId, int eId) {
	int visited[MAX] = {};
	queue<int> q;

	for (int i = 0; i < idIdx; i++) {
		if (train[i].step == -1)
			continue;

		if (train[i].isStation(sId)) {
			q.push(i);
			visited[i] = 1;
		}
	}

	while (!q.empty()) {
		int idx = q.front();
		q.pop();

		if (train[idx].isStation(eId)) {
			return visited[idx] - 1;
		}

		for (int newIdx : train[idx].trainList) {
			if (visited[newIdx])
				continue;

			if (train[newIdx].step == -1)
				continue;

			visited[newIdx] = visited[idx] + 1;
			q.push(newIdx);
		}
	}
	
	return -1;
}
