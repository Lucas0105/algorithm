#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> v;
int pos, value;

void insert() {
    cin >> pos >> value;
    if (pos)
        v.push_back(value);
    else
        v.insert(v.begin(), value);
}

void erase() {
    cin >> pos >> value;
    int cnt = 0;

    if (pos)
    {
        for (vector<int>::iterator it = v.end(); it != v.begin();)
        {
            --it;
            if (*it >= value) {
                it = v.erase(it);
                cnt++;

                if (cnt >= 3)
                    break;
            }
        }
    }
    else 
    {
        for (auto it = v.begin(); it != v.end();)
        {
            if (*it >= value) {
                it = v.erase(it);
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
        for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
        {
            cout << *it << ' ';
        }

    }
    else
    {
        for (int x : v)
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
            sort(v.begin(), v.end(), comp);
        }
        if (cmd == 4) print();
    }
    return 0;
}
