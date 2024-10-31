#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int LM = 100000;
int bcnt, N;
string str;
string dict[LM];

struct Node {
	int pathCnt;
	int chr[26];
	bool isEnd;
};

vector<Node> buf;

void init() {
	buf.clear();
	bcnt = 0;
	buf.push_back({ 0 });
}

void push(string s) {
	int cur = 0;
	for (int i = 0; i < s.size(); i++) {
		int idx = s[i] - 'a';
		if (buf[cur].chr[idx] == 0) {
			buf[cur].chr[idx] = ++bcnt;
			buf.push_back({ 0 });
		}

		cur = buf[cur].chr[idx];
	}

	buf[cur].isEnd = true;
}

int query(string s) {
	int cur = 0;
	int res = 1;
	int cnt = 0;

	cur = buf[cur].chr[s[0] - 'a'];
	int i = 1;
	for (i = 1; i < s.size(); i++) {
		int idx = s[i] - 'a';
		cnt = 0;


		for (int j = 0; j < 26; j++) {
			if (buf[cur].chr[j] != 0)
				cnt++;
		}

		if (cnt > 1 || buf[cur].isEnd)
			res++;

		cur = buf[cur].chr[idx];


	}


	return res;
}

int main() {
	while (cin >> N) {
		init();
		double res = 0;
		for (int i = 0; i < N; i++) {
			cin >> dict[i];
			push(dict[i]);
		}

		for (int i = 0; i < N; i++) {
			res += query(dict[i]);
		}

		cout.precision(2);
		cout << fixed << res / N << "\n";
	}

}