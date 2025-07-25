//user.cpp
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int mat[55][55];

void init(int N, int E, int sCity[], int eCity[], int mTime[]) {
	::N = N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			if (i != j) mat[i][j] = 1e9;
	}

	for (int i = 0; i < E; i++) {
		mat[sCity[i]][eCity[i]] = mTime[i];
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
			}
		}
	}

	return;
}

void add(int sCity, int eCity, int mTime) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			mat[i][j] = min(mat[i][j], mat[i][sCity] + mTime + mat[eCity][j]);
		}
	}
	return;
}

int M;
int* S, * E;
int minCost;
bool visit[55];

void dfs(int c, int pos, int cost) {
	if (cost >= minCost) return;

	if (c > M) {
		minCost = cost;
		return;
	}

	for (int i = 0; i < M; i++) {
		if (visit[i]) continue;
		visit[i] = 1;
		dfs(c + 1, E[i], cost + mat[pos][S[i]] + mat[S[i]][E[i]]);
		visit[i] = 0;
	}
}

int deliver(int mPos, int M, int mSender[], int mReceiver[]) {
	minCost = 1e9;
	::M = M, S = mSender, E = mReceiver;
	memset(visit, 0, sizeof(visit));
	dfs(1, mPos, 0);
	return minCost;
}