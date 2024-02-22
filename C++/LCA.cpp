#include <iostream>
#include <vector>
#include <math.h>

#define maxValue 100001

using namespace std;

vector<int> tree[maxValue];
int parent[maxValue][18];
int depth[maxValue];
int N, M;
int MaxLv = floor(log2(maxValue));

void set_tree(int node, int pnode, int lv)
{
    depth[node] = lv;
    parent[node][0] = pnode;

    for (int i = 1; i <= MaxLv; i++)
    {
        int p1 = parent[node][i - 1];
        parent[node][i] = parent[p1][i - 1];
    }

    for (int i = 0; i < tree[node].size(); i++)
    {
        int next = tree[node][i];

        if (next == pnode)
            continue;

        set_tree(next, node, lv + 1);
    }
}

int LCA(int v1, int v2)
{
    if (v1 == 1 || v2 == 1)
        return 1;

    // 하나의 정점을 높은 Depth로 고정
    if (depth[v1] < depth[v2])
        swap(v1, v2);
    
    // depth 일치 시키는 작업
    if (depth[v1] != depth[v2])
    {
        for (int i = MaxLv; i >= 0; i--)
        {
            if (depth[parent[v1][i]] >= depth[v2])
                v1 = parent[v1][i];
        }
    }
        

    if (v1 == v2)
        return v1;

    // 위로 올라가며 찾는 작업
    int res = v1;
    for (int i = MaxLv; i >= 0; i--)
    {
        if (parent[v1][i] != parent[v2][i])
        {
            v1 = parent[v1][i];
            v2 = parent[v2][i];
        }

        res = parent[v1][i];
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    for (int i = 0; i < N-1; i++)
    {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    set_tree(1, 0 , 1);

    cin >> M;


    for (int i = 0; i < M; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        cout << LCA(v1, v2) << "\n";
    }
    

    return 0;
}
