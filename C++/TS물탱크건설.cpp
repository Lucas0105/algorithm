//user.cpp
#include <vector>
#include <string>
using namespace std;

vector<int> waterBox[60000];

int waterHeight[50000];

void init(int N, int mHeight[])
{
    for (int i = 0; i < 60000; i++) {
        waterBox[i].clear();
    }

    for (int i = 1; i < N - 3; i++) {
        int minH = mHeight[i];
        int maxH = mHeight[i];

        for (int j = i; j < i + 5; j++) {
            if (abs(maxH - mHeight[j]) >= 5 || abs(minH - mHeight[j]) >= 5) {
                break;
            }
            maxH = max(maxH, mHeight[j]);
            minH = min(minH, mHeight[j]);
            if (j >= i + 2) {
                int newMin = minH - 1;
                int targetM = 0;
                for (int k = i; k <= j; k++) {
                    targetM = targetM * 10 + (mHeight[k] - newMin);
                }
                waterBox[targetM].push_back(i);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        waterHeight[i] = mHeight[i];
    }
}

int countPosition(int mLen, int mTank[])
{
    int maxH = 0;
    for (int i = 0; i < mLen; i++) {
        maxH = max(mTank[i], maxH);
    }
    maxH += 1;

    int targetNum = 0;
    for (int i = 0; i < mLen; i++) {
        targetNum = targetNum * 10 + maxH - mTank[i];
    }

    int res = waterBox[targetNum].size();

    return res;
}

int calc(int water, int s, int m, int e) {
    int maxH = min(waterHeight[s], waterHeight[e]);

    int curH = waterHeight[m];
    int sIdx = m;
    int eIdx = m;

    int ret = 0;

    while (curH < maxH) {
        while (waterHeight[sIdx] == curH) sIdx--;
        while (waterHeight[eIdx] == curH) eIdx++;

        int nextH = min(waterHeight[sIdx], waterHeight[eIdx]);

        int hLen = nextH - curH;
        int wLen = eIdx - sIdx - 1;
        int usedWater = min(hLen, water / wLen) * wLen;


        ret += usedWater;
        water -= usedWater;
        if (water < wLen) break;
        curH = nextH;

    }

    return ret;
}

int buildAndPourOut(int mLen, int mTank[], int mWater)
{
    int maxH = 0;
    for (int i = 0; i < mLen; i++) {
        maxH = max(mTank[i], maxH);
    }
    maxH += 1;

    int targetNum = 0;
    for (int i = 0; i < mLen; i++) {
        targetNum = targetNum * 10 + maxH - mTank[i];
    }

    vector<int> &targetVec = waterBox[targetNum];

    if (targetVec.size() == 0)
        return 0;

    int ans = 0, s, m, e;
    for (int i = 0; i < targetVec.size(); i++) {
        int qs = targetVec[i];
        int qe = qs + mLen - 1;
        waterHeight[qs] += mTank[0], waterHeight[qe] += mTank[mLen - 1];
        // 왼쪽으로 이동
        if (waterHeight[qs] > waterHeight[qs - 1]) {
            for (m = qs; waterHeight[m] >= waterHeight[m - 1]; )m--;
            for (s = m; waterHeight[s] <= waterHeight[s - 1];)s--;
            int ret = calc(mWater, s, m, qs);
            ans = max(ans, ret);
        }

        // 오른쪽으로 이동
        if (waterHeight[qe] > waterHeight[qe + 1]) {
            for (m = qe; waterHeight[m] >= waterHeight[m + 1]; )m++;
            for (e = m; waterHeight[e] <= waterHeight[e + 1];)e++;
            int ret = calc(mWater, qe, m, e);
            ans = max(ans, ret);
        }

        waterHeight[qs] -= mTank[0], waterHeight[qe] -= mTank[mLen - 1];
    }
    return ans;
}
