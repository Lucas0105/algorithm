//user.cpp
#include <deque>
#include <stack>

using namespace std;

deque<int> m1;
deque<int> m2;

int hashNum[1000];

void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000]) {
    m1.clear();
    m2.clear();

    for (int i = 0; i < 1000; i++) {
        hashNum[i] = 0;
    }

    for (int i = 0; i < mCnt1; i++) {
        m1.push_back(mDigitList1[i]);
    }

    for (int i = 0; i < mCnt1-2; i++) {
        int tmp = mDigitList1[i] * 100 + mDigitList1[i + 1] * 10 + mDigitList1[i + 2];
        hashNum[tmp] += 1;
    }

    for (int i = 0; i < mCnt2; i++) {
        m2.push_back(mDigitList2[i]);
    }

    for (int i = 0; i < mCnt2-2; i++) {
        int tmp = mDigitList2[i] * 100 + mDigitList2[i + 1] * 10 + mDigitList2[i + 2];
        hashNum[tmp] += 1;
    }
}

void append(int mDir, int mNum1, int mNum2) {
    if (mDir == 0) {
        int size = 0;

        while (mNum1 != 0) {
            int tmp = mNum1 % 10;
            m1.push_front(tmp);
            mNum1 /= 10;
            size++;
        }

        for (int i = 0; i < size; i++) {
            int hashIdx = m1[i] * 100 + m1[i + 1] * 10 + m1[i + 2];
            hashNum[hashIdx] += 1;
        }

        size = 0;
        while (mNum2 != 0) {
            int tmp = mNum2 % 10;
            m2.push_front(tmp);
            mNum2 /= 10;
            size++;
        }

        for (int i = 0; i < size; i++) {
            int hashIdx = m2[i] * 100 + m2[i + 1] * 10 + m2[i + 2];
            hashNum[hashIdx] += 1;
        }

    }
    else {
        int size = 0;
        stack<int> st;

        while (mNum1 != 0) {
            int tmp = mNum1 % 10;
            st.push(tmp);
            mNum1 /= 10;
            size++;
        }

        while (!st.empty()) {
            m1.push_back(st.top());
            st.pop();
        }

        for (int i = m1.size() - size - 2; i < m1.size() - 2; i++) {
            int hashIdx = m1[i] * 100 + m1[i + 1] * 10 + m1[i + 2];
            hashNum[hashIdx] += 1;
        }

        size = 0;
        while (mNum2 != 0) {
            int tmp = mNum2 % 10;
            st.push(tmp);
            mNum2 /= 10;
            size++;
        }

        while (!st.empty()) {
            m2.push_back(st.top());
            st.pop();
        }

        for (int i = m2.size() - size - 2; i < m2.size() - 2; i++) {
            int hashIdx = m2[i] * 100 + m2[i + 1] * 10 + m2[i + 2];
            hashNum[hashIdx] += 1;
        }
    }
}

int countNum(int mNum) {
    int result = hashNum[mNum];

    int a1 = m1[m1.size() - 1] * 100 + m2[0] * 10 + m2[1];
    int a2 = m1[m1.size() - 2] * 100 + m1[m1.size() - 1] * 10 + m2[0];

    if (mNum == a1)
        result += 1;

    if (mNum == a2)
        result += 1;

    return result;
}