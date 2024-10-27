#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int LN = 4000 * 1000;

struct Node {
	bool isEnd;
	int chr[26];
};

Node Colors[LN];
unordered_set<string> Teams;

int C, N, Q;
int colorCnt;
string str;

void pushStr(string s, Node buf[], int& bcnt) {
	int cur = 0;
	for (char c : s) {
		int idx = c - 'a';
		if (buf[cur].chr[idx] == 0) {
			buf[cur].chr[idx] = ++bcnt;
		}
		cur = buf[cur].chr[idx];
	}
	buf[cur].isEnd = true;
}

bool query(string s, Node buf[]) {
	int cur = 0;
	int strIdx = 0;
	for (char c : s) {
		int idx = c - 'a';

		if (buf[cur].isEnd) {
			string tmp = s.substr(strIdx);
			if (Teams.count(tmp))
				return true;
		}

		if (buf[cur].chr[idx] == 0) {
			return false;
		}
		cur = buf[cur].chr[idx];

		strIdx++;
	}

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> C >> N;

	for (int i = 0; i < C; i++) {
		cin >> str;
		pushStr(str, Colors, colorCnt);
	}

	for (int i = 0; i < N; i++) {
		cin >> str;
		Teams.insert(str);
	}

	cin >> Q;

	for (int i = 0; i < Q; i++) {
		cin >> str;
		bool res = query(str, Colors);
		if (res) {
			cout << "Yes" << "\n";
		}
		else {
			cout << "No" << "\n";
		}

	}

	return 0;
}