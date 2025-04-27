
//user.cpp
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define MAX_WIDTH 500
#define MAX_HEIGHT 1501

int mN, mW, mH;

struct Tank {
    int ID, minH;
    int stickNum[MAX_HEIGHT];
    int mLen[MAX_WIDTH];
    int mSha[MAX_WIDTH];
    vector<int> posList[64];
    unordered_map<int, int> codeHash;

    void init(int mId, int* mLengths, int* mShapes) {
        ID = mId;
        minH = 1500;
        codeHash.clear();

        for (int i = 0; i <= mH; i++) {
            stickNum[i] = 0;
        }

        for (int i = 0; i < mW; i++) {
            mLen[i] = mLengths[i];
            mSha[i] = mShapes[i];
            int h = mLen[i];
            stickNum[h] += 1;
            minH = min(h, minH);
        }

        for (int i = 0; i < 64; i++) {
            posList[i] = vector<int>();
        }


        for (int i = 0; i < mW - 2; i++) {
            int code = (mShapes[i] << 4) + (mShapes[i + 1] << 2) + mShapes[i + 2];
            posList[code].push_back(i);
            codeHash[i] = code;
        }

    }

    int isAble(int mLengths[], int wIdx) {
        if (mLen[wIdx] >= mLen[wIdx + 1] + mLengths[1] || mLen[wIdx] + mLengths[0] <= mLen[wIdx + 1]) {
            return 0;
        }

        if (mLen[wIdx + 1] >= mLen[wIdx + 2] + mLengths[2] || mLen[wIdx + 1] + mLengths[1] <= mLen[wIdx + 2]) {
            return 0;
        }

        if (mLen[wIdx] + mLengths[0] > mH || mLen[wIdx + 1] + mLengths[1] > mH || mLen[wIdx + 2] + mLengths[2] > mH) {
            return 0;
        }

        return 1;
    }
    bool operator < (const Tank& r) const {
        return ID < r.ID;
    }
}tank[20];

struct Result {
    int ID;
    int height;
    int used;
};

void init(int N, int mWidth, int mHeight, int mIDs[], int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH])
{
    mN = N;
    mW = mWidth;
    mH = mHeight;

    for (int i = 0; i < N; i++) {
        tank[i].init(mIDs[i], mLengths[i], mUpShapes[i]);
    }

    sort(tank, tank + N);
}

int checkStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
    int code = (mDownShapes[0] << 4) + (mDownShapes[1] << 2) + mDownShapes[2];
    int result = 0;
    for (int i = 0; i < mN; i++) {
        vector<int> target = tank[i].posList[code];

        for (int wIdx : target) {
            result += tank[i].isAble(mLengths, wIdx);
        }
    }

    return result;
}

int addStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{

    int code = (mDownShapes[0] << 4) + (mDownShapes[1] << 2) + mDownShapes[2];
    int result = 0;
    for (int i = 0; i < mN; i++) {
        vector<int> target = tank[i].posList[code];

        for (int wIdx : target) {
            result = tank[i].isAble(mLengths, wIdx);

            // Add
            if (result > 0) {
                int startIdx = max(0, wIdx - 2);
                int endIdx = min(mW - 3, wIdx + 2);

                for (int j = wIdx; j < wIdx + 3; j++) {
                    tank[i].stickNum[tank[i].mLen[j]] -= 1;

                    tank[i].mLen[j] += mLengths[j - wIdx];

                    tank[i].stickNum[tank[i].mLen[j]] += 1;

                    tank[i].mSha[j] = mUpShapes[j - wIdx];
                }

                for (int j = startIdx; j <= endIdx; j++) {
                    int curCode = tank[i].codeHash[j];

                    auto it = lower_bound(tank[i].posList[curCode].begin(), tank[i].posList[curCode].end(), j);
                    tank[i].posList[curCode].erase(it);

                    int newCode = (tank[i].mSha[j] << 4) + (tank[i].mSha[j + 1] << 2) + tank[i].mSha[j + 2];
                    it = lower_bound(tank[i].posList[newCode].begin(), tank[i].posList[newCode].end(), j);
                    tank[i].posList[newCode].insert(it, j);
                    tank[i].codeHash[j] = newCode;
                }

                result = tank[i].ID * 1000 + wIdx + 1;

                return result;
            }
        }
    }

    return result;
}

Result pourIn(int mWater)
{
    Result ret;
    ret.ID = ret.height = ret.used = 0;

    for (int i = 0; i < mN; i++) {
        Tank curT = tank[i];
        int usedWater = 0;
        int minH = curT.minH;
        while (curT.stickNum[minH] == 0) {
            minH++;
        }
        int stickSum = 0;
        for (minH; minH < mH; minH++) {
            stickSum += curT.stickNum[minH];
            if (stickSum + usedWater > mWater) {
                break;
            }
            usedWater += stickSum;
        }

        if (usedWater == 0)
            continue;

        if (minH > ret.height) {
            ret.ID = curT.ID;
            ret.height = minH;
            ret.used = usedWater;
        }
        else if (minH == ret.height && usedWater > ret.used) {
            ret.ID = curT.ID;
            ret.height = minH;
            ret.used = usedWater;
        }
    }

    return ret;
}
