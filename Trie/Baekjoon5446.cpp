#include <iostream>
#include <vector>

using namespace std;

struct Node {
	bool readOnly, removed;
	int chr[63];
};

vector<Node> buf;
int bcnt = 0;
int t, res, N, M;
string inputData[1005];
string inputOne;

void init() {
	bcnt = 0;
	res = 0;
	buf.clear();
	buf.push_back({ 0 });
}

int getIdx(char s) {
	int intS = s;

	if (intS == 46)
		intS = 0;
	else if (intS <= 57)
		intS -= 47;
	else if (intS <= 90)
		intS -= 54;
	else
		intS -= 60;

	return intS;
}

void push(string s) {
	int cur = 0;
	for (int i = 0; i < s.size(); i++) {
		int idx = getIdx(s[i]);
		if (buf[cur].chr[idx] == 0) {
			buf.push_back({ 0 });
			buf[cur].chr[idx] = ++bcnt;
		}
		cur = buf[cur].chr[idx];
	}
}

void mark(string s) {
	int cur = 0;
	for (int i = 0; i < s.size(); i++) {
		int idx = getIdx(s[i]);
		if (buf[cur].chr[idx] == 0) {
			buf.push_back({ 0 });
			buf[cur].chr[idx] = ++bcnt;
		}
		cur = buf[cur].chr[idx];
		buf[cur].readOnly = true;
	}
}

int deleteFile(string s) {
	int cur = 0;
	for (int i = 0; i < s.size(); i++) {
		int idx = getIdx(s[i]);

		cur = buf[cur].chr[idx];

		if (buf[cur].removed)
			return 0;

		if (!buf[cur].readOnly && !buf[cur].removed) {
			buf[cur].removed = true;
			return 1;
		}
	}

	return 1;
}

int main() {
	// .46              0
	// 0~9: 48~57 10°³  1~10
	// A~Z: 65 90 26°³ 11~36
	// a~z: 97~122  26°³  37~62

	cin >> t;

	for (int i = 0; i < t; i++) {
		init();

		cin >> N;

		for (int j = 0; j < N; j++) {
			cin >> inputData[j];
			push(inputData[j]);
		}

		cin >> M;

		for (int j = 0; j < M; j++) {
			string readOnlyStr;
			cin >> readOnlyStr;
			mark(readOnlyStr);
		}

		if (M == 0)
			cout << 1 << "\n";
		else {
			for (int j = 0; j < N; j++)
				res += deleteFile(inputData[j]);

			cout << res << "\n";

		}
	}
}