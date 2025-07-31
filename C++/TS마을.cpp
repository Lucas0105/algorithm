// user.cpp
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

constexpr int BLM = 101;
constexpr int IDLM = 25005;
int L, R;
struct Data {
	int mid, r, c, tid;
	list<int>::iterator it;
	bool isNeighber(Data& t) {
		return abs(r - t.r) + abs(c - t.c) <= L;
	}
}house[IDLM];

vector<int> block[BLM][BLM];
int N;

int idCnt;
int tree[IDLM], minID[IDLM];
unordered_map<int, int> renumHtab;
unordered_map<int, list<int>> town;

int Find(int r) {
	return tree[r] = r == tree[r] ? r : Find(tree[r]);
}

void init(int L, int R) {
	for(int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) {
			block[i][j].clear();
		}
	renumHtab.clear(), town.clear();
	idCnt = 0;
	::L = L, ::R = R;
	N = R / L + 1;
}

int add(int mId, int mX, int mY) {
	int id = renumHtab[mId] = ++idCnt;
	house[id] = { mId, --mY, --mX, id };
	minID[id] = mId;
	tree[id] = id;
	house[id].it = town[id].insert(town[id].begin(), id);
	list<int>& a = town[id];
	int gr = mY / L, gc = mX / L;
	for (int i = gr - 1; i <= gr + 1; i++) if (i >= 0 && i < N) {
		for (int j = gc - 1; j <= gc + 1; j++) if (j >= 0 && j < N) {
			for (auto b : block[i][j]) {
				if (house[b].mid && house[id].isNeighber(house[b])) {
					int rid = Find(house[b].tid);
					if (rid == id) continue;
					a.splice(a.begin(), town[rid]);
					town.erase(rid);
					tree[rid] = id;
					minID[id] = min(minID[id], minID[rid]);
				}
			}
		}
	}
	block[gr][gc].push_back(id);
	
	return (int)town[id].size();
}

int remove(int mId) {
	if (renumHtab.count(mId) == 0) return -1;
	int id = renumHtab[mId], tid = Find(house[id].tid);
	renumHtab.erase(mId);
	house[id].mid = 0;
	list<int>& a = town[tid];
	a.erase(house[id].it);
	if (a.empty()) {
		town.erase(tid);
		return 0;
	}
	if (minID[tid] == mId) {
		minID[tid] = house[*a.begin()].mid;
		for (int k : a) minID[tid] = min(minID[tid], house[k].mid);
	}
	return a.size();
}

int check(int mId) {
	if (renumHtab.count(mId) == 0) return -1;
	int id = renumHtab[mId];
	int tid = Find(house[id].tid);
	return minID[tid];
}

int count() {
	return town.size();
}
