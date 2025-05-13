//user.cpp
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

// rank, id
using pii = pair<int, int>;

#define MAX_RESULT 3

struct Result {
    int ids[MAX_RESULT];
};

// id, category, rank
set<int> prodSet[6][6];

// id, rank index, category
unordered_map<int ,pii> prodMap;
int R[6][6];

void init() {
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++) {
            prodSet[i][j] = set<int>();
            R[i][j] = j;
        }
    prodMap.clear();
}

int getRankIdx(int cate, int rnk) {
    for (int i = 1; i <= 5; i++) {
        if (R[cate][i] == rnk) return i;
    }
}

int add(int mGoodsID, int mCategory, int mRank) {
    int rIdx = getRankIdx(mCategory, mRank);
    prodMap[mGoodsID] = { rIdx, mCategory };
    prodSet[mCategory][rIdx].insert(mGoodsID);

    int res = 0;
    for (int i = 1; i <= 5; i++) {
        res += prodSet[mCategory][i].size();
    }

    return res;
}

int remove(int mGoodsID) {
    int cate = prodMap[mGoodsID].second;
    int rank = prodMap[mGoodsID].first;

    prodMap.erase(mGoodsID);

    prodSet[cate][rank].erase( mGoodsID);

    int res = 0;
    for (int i = 1; i <= 5; i++) {
        res += prodSet[cate][i].size();
    }

    return res;
}

int changeRank(int mGoodsID, int mRank) {
    int cate = prodMap[mGoodsID].second;
    int rank = prodMap[mGoodsID].first;
    int rank2 = getRankIdx(cate, mRank);

    prodMap[mGoodsID].first = rank2;

    auto it = prodSet[cate][rank].find(mGoodsID);
    prodSet[cate][rank].erase(it);
    prodSet[cate][rank2].insert(mGoodsID);

    int res = 0;

    for (int i = 1; i <= 5; i++) {
        int rIdx = getRankIdx(cate, i);
        if (prodSet[cate][rIdx].size() > 0) {
            res = max(*prodSet[cate][rIdx].rbegin(), res);
            break;
        }
    }

    return res;
}

int swapRank(int mCategory, int mRank1, int mRank2) {
    int ran1 = getRankIdx(mCategory, mRank1);
    int ran2 = getRankIdx(mCategory, mRank2);

    int res = prodSet[mCategory][ran1].size() - prodSet[mCategory][ran2].size();
    swap(R[mCategory][ran1], R[mCategory][ran2]);

    return res;
}

int n = 0;
pii candi[20];

void addTopThree(int cate) {
    int c = 0;
    for (int i = 1; i <= 5 && c < 3; i++) {
        int ridx = getRankIdx(cate, i);
        auto& s = prodSet[cate][ridx];
        for (auto it = s.rbegin(); it != s.rend() && c < 3; ++it, ++c)
            candi[n++] = { i, -(*it) };
    }
}

Result getTopRanks() {
    Result res = { {-1, -1, -1} };
    
    n = 0;
    for (int cate = 1; cate <= 5; cate++) addTopThree(cate);

    // 기록된 후보들 중 우선순위 3개 뽑아서 res.ids[]에 기록
    int m = min(3, n);
    partial_sort(candi, candi + m, candi + n);
    for (int i = 0; i < m; i++) res.ids[i] = -candi[i].second;
    return res;
}
