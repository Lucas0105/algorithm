#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, S, E;

vector<pair<int, int>> lineV;
int dp[101] = { 1, };
int main()
{
    cin >> N;
    
    for(int i = 0; i < N; i++){
        cin >> S >> E;
        lineV.push_back({S, E});
    }
    
    sort(lineV.begin(), lineV.end());
    
    for(int i = 0; i < N; i++){
        int curV = 0;
        for(int j = 0; j < i; j++){
            if(lineV[i].second > lineV[j].second) {
                curV = max(curV, dp[j]);
            }
        }
        dp[i] = curV + 1;
    }
    
    int maxV = 0;
    
    for(int i = 0; i < N; i++){
        maxV = max(maxV, dp[i]);
    }
    
    cout << N - maxV;

    return 0;
}
