// user.cpp
#include <set>
#include <queue>
#include <list>
#include <algorithm>

#define MAX_BOX 10005

using namespace std;

int gH, gW, minH;

struct Box {
    int left, right, upDown1, upDown2;
    list<int> nearBox;
} boxArr[MAX_BOX];

struct BoxOperator {
    bool operator() (const int l, const int r) const {
        return boxArr[l].left < boxArr[r].left;
    }
};

set<int, BoxOperator> boxSet[1005];

void init(int mH, int mW)
{
    gW = mW, gH = mH, minH = mH;

    for (int i = 0; i <= mH; i++)
        boxSet[i].clear();

    boxArr[0] = { 0, mW, -1, -1 };
    boxSet[mH].insert(0);
}


int dropBox(int mId, int mLen, int mExitA, int mExitB, int mCol)
{
    boxArr[mId] = { mCol, mCol + mLen - 1, mCol + mExitA, mCol + mExitB };

    for (int i = minH; i <= gH; i++) {
        auto it = boxSet[i].lower_bound(mId);
        
        if (it != boxSet[i].begin())
            it = prev(it);

        for (; it != boxSet[i].end(); it++) {
            Box target = boxArr[*it];

            // 겹치지 않으면 아래로 이동
            if (target.left > boxArr[mId].right)
                break;

            //겹치는지 않겹치는지 확인
            if (target.left <= boxArr[mId].right && target.right >= boxArr[mId].left) {
                int newH = i - 1;
                auto insertIt = boxSet[newH].insert(mId).first;

                minH = min(minH, newH);

                // 왼쪽, 오른쪽, 아래쪽 겹치는지 확인
                // 왼쪽
                if (insertIt != boxSet[newH].begin()) {
                    auto leftIt = prev(insertIt);
                    if (boxArr[*leftIt].right + 1 == boxArr[mId].left) {
                        boxArr[mId].nearBox.push_back(*leftIt);
                        boxArr[*leftIt].nearBox.push_back(mId);
                    }
                }
                
                // 오른쪽
                auto rightIt = next(insertIt);
                if (rightIt != boxSet[newH].end()) {
                    if (boxArr[*rightIt].left - 1 == boxArr[mId].right) {
                        boxArr[mId].nearBox.push_back(*rightIt);
                        boxArr[*rightIt].nearBox.push_back(mId);
                    }
                }

                // 아래쪽 겹치는지 확인
                while (it != boxSet[i].end()) {
                    Box *bottomTarget = &boxArr[*it];

                    if (bottomTarget->left > boxArr[mId].right) {
                        break;
                    }

                    // 아래 박스에서 위 박스 확인
                    if ((boxArr[mId].left <= bottomTarget->upDown1 && bottomTarget->upDown1 <= boxArr[mId].right) 
                        || boxArr[mId].left <= bottomTarget->upDown2 && bottomTarget->upDown2 <= boxArr[mId].right) {
                        bottomTarget->nearBox.push_back(mId);
                    }

                    // 위 박스에서 아래 박스 확인
                    if ((bottomTarget->left <= boxArr[mId].upDown1 && boxArr[mId].upDown1 <= bottomTarget->right)
                        || bottomTarget->left <= boxArr[mId].upDown2 && boxArr[mId].upDown2 <= bottomTarget->right) {
                        boxArr[mId].nearBox.push_back(*it);
                    }

                    it = next(it);
                }

                // 웅덩이의 행
                return newH;
            }
        }
    }


    return 0;
}

int explore(int mIdA, int mIdB)
{
    int visited[MAX_BOX] = {};
    visited[mIdA] = 1;
    visited[0] = 1;

    queue<int> q;
    q.push(mIdA);

    while (!q.empty()) {
        int nodeId = q.front();
        q.pop();

        if (nodeId == mIdB)
            break;

        Box node = boxArr[nodeId];



        for (auto id : node.nearBox) {
            if (visited[id])
                continue;

            visited[id] += visited[nodeId] + 1;
            q.push(id);
        }
    }

    return visited[mIdB] - 1;
}
