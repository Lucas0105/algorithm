#include <iostream>
#include<queue>
#include<vector>
#include<math.h>

using namespace std;

class Pos {
public:
	int x, y;

public:
	Pos(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

vector<Pos> island[10000];
int islandIdx = 0;

int land[100][100];
bool visitedIsland[100][100];
int N;

queue<Pos> que;

int dRow[] = {-1, 0, 1, 0};
int dCol[] = { 0, 1, 0, -1 };


void islandBFS(Pos node, int islandIdx) {
	que.push(node);

	while (!que.empty()) {
		Pos curNode = que.front();
		que.pop();

		if (visitedIsland[curNode.x][curNode.y])
			continue;
		visitedIsland[curNode.x][curNode.y] = true;

		bool isOutSide = false;
		for (int i = 0; i < 4; i++) {
			int newR = curNode.x + dRow[i];
			int newC = curNode.y + dCol[i];

			if (newR < 0 || newR >= N || newC < 0 || newC >= N) {
				continue;
			}

			if (land[newR][newC] == 1 && !visitedIsland[newR][newC]) {
				que.push(Pos(newR, newC));
			}

			if (land[newR][newC] == 0) {
				isOutSide = true;
			}
		}
		if(isOutSide)
			island[islandIdx].push_back(curNode);
	}
}
int islandClac() {
	int result = 10000;

	for (int i = 0; i < islandIdx; i++) {
		for (int j = i + 1; j < islandIdx; j++) {

			for (int m = 0; m < island[i].size(); m++) {
				for (int n = 0; n < island[j].size(); n++) {
					int dist = abs(island[i][m].x - island[j][n].x) + abs(island[i][m].y - island[j][n].y) - 1;

					if (dist == 1)
						return 1;
					result = min(result, dist);
				}
			}
		}
	}

	return result;
}
int main() {
	cin >> N;
	Pos test = Pos(1, 2);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> land[i][j];
		}
	}

	// =============island BFS================
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visitedIsland[i][j])
				continue;
			if(land[i][j] == 1)
				islandBFS(Pos(i, j), islandIdx++);
		}
	}

	// ============ island Calc================
	int res = islandClac();

	cout << res;
}

