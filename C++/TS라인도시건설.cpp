#include <set>
#include<map>
#include<math.h>

//user.cpp

using namespace std;

// pos, length
using pii = pair<int ,int>;

struct operation {
    bool operator()(const pii &l, const pii &r) const {
        if (l.second == r.second) {
            return l.first < r.first;
        }
        return l.second > r.second;
    }
};

set<pii, operation> emptyBuilding;
map<int, int> usedBuilding;

void init(int N) {
    emptyBuilding.clear();
    usedBuilding.clear();

    usedBuilding.insert({ N, 0 });
    emptyBuilding.insert({ 0, N });
}

int build(int mLength) {
    auto it = emptyBuilding.begin();

    // 길이 check
    if (it == emptyBuilding.end() || mLength > it->second)
        return -1;

    int mid = it->first + (it->second - 1) / 2;

    // 가운데
    int pos = mid;
    int buildingLen = 1;

    // 둘다 짝수인 경우 => 중앙이 2개
    if (it->second % 2 == 0 && mLength % 2 == 0) {
        buildingLen += 1;
    }

    int leftNum = ceil((mLength - buildingLen) / 2.0);
    pos = pos - leftNum;


    // 사용한 토지 저장
    usedBuilding[pos] = mLength;

    // 양쪽 토지 생성
    // 왼쪽
    if (it->first < pos) {
        emptyBuilding.insert({it->first, pos - it->first});
    }


    // 오른쪽
    int backIdx = pos + mLength;
    if (backIdx < it->first + it->second) {
        emptyBuilding.insert({ backIdx, it -> first + it->second - backIdx});
    }
    
    // 기존 빌딩 삭제
    emptyBuilding.erase(it);

    return pos;
}

int demolish(int mAddr) {
    if (usedBuilding.count(mAddr) == 0)
        return -1;
        
    auto result = usedBuilding.find(mAddr);

    int startAddr = mAddr;
    int buildLen = result->second;

    // 왼쪽 건물 존재 유무 파악
    auto prevIt = prev(result);

    int s = startAddr;
    if(prevIt != usedBuilding.end()){
        s = prevIt->first + prevIt->second;
        emptyBuilding.erase({s, startAddr - s });
    }
    else {
        s = 0;
        emptyBuilding.erase({s, startAddr });
    }

    // 오른쪽 건물 존재 유무 파악
    auto nextIt = next(result);

    int e = nextIt->first;
    emptyBuilding.erase({ result->first + result->second, e - result->first - result->second });

    int ret = result->second;
    usedBuilding.erase(result);
    emptyBuilding.insert({ s, e - s });


    return ret;
}
