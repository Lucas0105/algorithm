// user.cpp
#include <queue>

#define INF 1 << 20;

using namespace std;

int arr[520][520];

int idx, mN;
char* mStr;

int dR[] = { 0, -1, 0, 1 };
int dC[] = { -1, 0, 1, 0 };

void decode(int sR, int sC, int h) {
	int baseH = h;
	h /= 2;
	char c = mStr[idx++];

	if (c == '(') {
		decode(sR, sC, h);		decode(sR, sC + h, h);
		decode(sR + h, sC, h);	decode(sR + h, sC + h, h);
		idx++;
	}
	else if (c == '0' || c == '1') {
		for (int i = sR; i < sR + baseH; i++) {
			for (int j = sC; j < sC + baseH; j++) {
				arr[i][j] = c - '0';
			}
		}
	}

}

void init(int N, int L, char mCode[])
{
	idx = 0, mN = N;
	mStr = mCode;

	for (int i = 0; i <= N + 1; i++) {
		arr[0][i] = INF; arr[i][N + 1] = INF;
		arr[N + 1][i] = INF; arr[i][0] = INF;
	}

	decode(1, 1, N);
	return;
}

void encodeRec(int sR, int sC, int h) {
	// h 만큼 타일이 같은지 확인
	int startTile = arr[sR][sC];
	bool isMatch = true;

	for (int i = sR; i < sR + h; i++) {
		for (int j = sC; j < sC + h; j++) {
			if (startTile != arr[i][j]) {
				isMatch = false;
			}
		}
		if (!isMatch)
			break;
	}

	if (isMatch) {
		mStr[idx++] = '0' + startTile;
	}
	else {
		h /= 2;
		mStr[idx++] = '(';
		encodeRec(sR, sC, h);				encodeRec(sR, sC + h, h);
		encodeRec(sR + h, sC, h);			encodeRec(sR + h, sC + h, h);
		mStr[idx++] = ')';
	}
}

int encode(char mCode[])
{
	idx = 0;
	mStr = mCode;
	
	encodeRec(1, 1, mN);

	return idx;
}

void makeDot(int mR, int mC, int mSize, int mColor)
{
	mR += 1; mC += 1;
	int j;
	int w = 0;
	for (int i = mR - mSize + 1; i <= mN && i < mR + mSize; i++) {

		if (i > 0) {
			for (j = mC - w; j <= mC + w; j++) {
				if (j < 1 || j > mN) continue;
				arr[i][j] = mColor;
			}
		}
			

		if (i < mR) {
			w += 1;
		}
		else {
			w -= 1;
		}
	}

	return;
}

void paint(int mR, int mC, int mColor)
{
	mR += 1; mC += 1;

	if (arr[mR][mC] == mColor) return;

	int tgColor = arr[mR][mC];
	queue <pair<int, int>> q;

	arr[mR][mC] = mColor;
	q.push({ mR, mC });

	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int newR = r + dR[i];
			int newC = c + dC[i];

			if (arr[newR][newC] == tgColor) {
				arr[newR][newC] = mColor;
				q.push({ newR, newC });
			}

		}
	}
	
	return;
}

int getColor(int mR, int mC)
{
	return arr[mR + 1][mC + 1];
}
