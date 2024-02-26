#include <iostream>
#include <vector>
#include <math.h>
#include <queue>

#define MAX_N 102
#define INF 100000

using namespace std;

struct pairPos
{
    double X, Y;
};


pairPos start, target;
int n;
vector<pairPos> cannon;
vector<double> minTime(MAX_N, INF);
priority_queue <pair<double, int>, vector<pair<double, int>>, less<>> pq;


double GetDistance(pairPos s, pairPos e)
{
    return sqrt(pow(s.X - e.X, 2) + pow(s.Y - e.Y, 2));
}

double GetCannon(pairPos s, pairPos e)
{
    double tmpTime = 2;
    double dist = GetDistance(s, e);
    tmpTime += abs(dist - 50) / 5;

    return tmpTime > dist / 5 ? dist / 5: tmpTime;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> start.X >> start.Y;
    cin >> target.X >> target.Y;
    cin >> n;

    cannon.push_back(start);
    for (int i = 1; i <= n; i++)
    {
        pairPos newCannon;
        cin >> newCannon.X >> newCannon.Y;
        cannon.push_back(newCannon);
    }
    cannon.push_back(target);

    minTime[0] = 0;
    
    for (int i = 1; i <= n + 1; i++)
    {
        minTime[i] = GetDistance(start, cannon[i]) / 5;
        pq.push({ minTime[i], i });
    }

    while (!pq.empty())
    {
        double cost = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (minTime[cur] < cost)
            continue;

        for (int nextNode = 1; nextNode <= n + 1; nextNode++) {
            if (nextNode == cur)
                continue;
            double nextCost = cost + GetCannon(cannon[cur], cannon[nextNode]);
            if (minTime[nextNode] > nextCost) {
                minTime[nextNode] = nextCost;
                pq.push({ minTime[nextNode], nextNode });
            }
        }
        
    }

    cout.precision(8);
    cout << minTime[n + 1];

    return 0;
}
