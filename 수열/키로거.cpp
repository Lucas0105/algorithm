#include <iostream>
#include <list>

using namespace std;

list<char> keyList;

int main()
{
    FILE* stream;
    freopen_s(&stream, "키로거.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        string tmp;
        cin >> tmp;
        keyList.clear();
        list<char>::iterator it = keyList.end();

        for (int j = 0; j < tmp.size(); j++)
        {
            if (tmp[j] == '<')
            {
                if (it != keyList.begin())
                    --it;
            }
            else if (tmp[j] == '>')
            {
                if (it != keyList.end())
                    ++it;
            }
            else if (tmp[j] == '-')
            {
                if (it != keyList.begin())
                    keyList.erase(prev(it, 1));
            }
            else {
                keyList.insert(it, tmp[j]);
                
            }

        }
        for (auto it = keyList.begin(); it != keyList.end(); ++it)
        {
            cout << *it;
        }
        cout << "\n";

    }

    return 0;
}
