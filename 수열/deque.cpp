#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

deque<int> dq;
int pos, value;

void insert() {
    cin >> pos >> value;
    if (pos)
        dq.push_back(value);
    else
        dq.insert(dq.begin(), value);
}

void erase() {
    cin >> pos >> value;
    int cnt = 0;

    if (pos)
    {
        for (deque<int>::iterator it = dq.end(); it != dq.begin();)
        {
            --it;
            if (*it >= value) {
                it = dq.erase(it);
                cnt++;

                if (cnt >= 3)
                    break;
            }
        }
    }
    else 
    {
        for (auto it = dq.begin(); it != dq.end();)
        {
            if (*it >= value) {
                it = dq.erase(it);
                cnt++;
                if (cnt >= 3)
                    break;
            }
            else
                ++it;
        }
    }
}

void print() {
    cin >> pos;
    if (pos)
    {
        for (deque<int>::reverse_iterator it = dq.rbegin(); it != dq.rend(); ++it)
        {
            cout << *it << ' ';
        }

    }
    else
    {
        for (int x : dq)
        {
            cout << x << ' ';
        }
    }

    cout << "\n";
}

bool comp(int l, int r) {
    int absl = abs(value - l);
    int absr = abs(value - r);
    if (absl != absr)
        return absl < absr;
    return l < r;
}

int main() {
    FILE* stream;
    freopen_s( &stream, "수열.txt", "r", stdin);
    int q, cmd;
    cin >> q;
    while (q--) {
        cin >> cmd;
        if (cmd == 1) insert();
        if (cmd == 2) erase();
        if (cmd == 3) {
            cin >> value;
            sort(dq.begin(), dq.end(), comp);
        }
        if (cmd == 4) print();
    }
    return 0;
}
