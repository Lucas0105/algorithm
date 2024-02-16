#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

list<int> li;
int pos, value;

void insert() {
    cin >> pos >> value;
    pos ? li.push_back(value) : li.push_front(value);
}

void erase() {
    cin >> pos >> value;
    int cnt = 0;

    if (pos)
    {
        for (list<int>::iterator it = li.end(); it != li.begin();)
        {
            --it;
            if (*it >= value) {
                it = li.erase(it);
                cnt++;

                if (cnt >= 3)
                    break;
            }
        }
    }
    else 
    {
        for (auto it = li.begin(); it != li.end();)
        {
            if (*it >= value) {
                it = li.erase(it);
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
        for (list<int>::reverse_iterator it = li.rbegin(); it != li.rend(); ++it)
        {
            cout << *it << ' ';
        }

    }
    else
    {
        for (int x : li)
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
            li.sort(comp);
        }
        if (cmd == 4) print();
    }
    return 0;
}
