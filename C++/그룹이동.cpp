#include <iostream>
#include <vector>
#include <list>
#define MAX_X 200001

using namespace std;

int Q, x;
char gid, gid1, gid2;
list<int> li[10];
vector<list<int>::iterator> itList(MAX_X);

void add()
{
    cin >> x >> gid;
    gid -='A';

    itList[x] = li[gid].insert(li[gid].end(), x);
}

void remove()
{
    cin >> x;
    *itList[x] = 0;
}

void move()
{
    cin >> gid1 >> gid2;
    gid1 -= 'A'; gid2 -= 'A';

    li[gid2].splice(li[gid2].begin(), li[gid1]);

}

void get()
{
    cin >> gid;
    gid -= 'A';
    int result = MAX_X;
    for (auto it = li[gid].begin(); it != li[gid].end();)
    {
        if (*it == 0)
            it = li[gid].erase(it);
        else
        {
            if (result > *it)
                result = *it;

            ++it;
        }

    }

    if (result == MAX_X)
        cout << -1;
    else
        cout << result;
    cout << "\n";
}

int main()
{
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        string command;
        cin >> command;

        if (command == "add")
            add();
        else if (command == "remove")
            remove();
        else if (command == "move")
            move();
        else if (command == "get")
            get();
        
    }

    return 0;
}
