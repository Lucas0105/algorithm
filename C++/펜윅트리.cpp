#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
vector<long long> tree;
vector<long long> origin;

long long sumNum(long long idx)
{
    long long ans = 0;
    while (idx > 0)
    {
        ans += tree[idx];
        idx -= (idx & -idx);
    }

    return ans;
}

void update(long long idx, long long num)
{
    while (idx < tree.size())
    {
        tree[idx] += num;
        idx += (idx & -idx);
    }
}

int main()
{
    FILE* stream;
    freopen_s(&stream, "구간합구하기.txt", "r", stdin);
   
    cin >> N >> M >> K;

    tree.resize(N + 1, 0);
    origin.resize(N + 1, 0);

    for (int i = 1; i <= N; i++)
    {
        cin >> origin[i];
        update(i, origin[i]);
    }

    for (int i = 0; i < M + K; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        if (a == 1)
        {
            update(b, c - origin[b]);
            origin[b] = c;
        }
        else if (a == 2)
        {
            cout << sumNum(c) - sumNum(b - 1) << "\n";
        }
    }

    return 0;
}
