#include<iostream>

using namespace std;

int N;
long tileArr[31];

long rec(int target) {
	if (tileArr[target] != 0)
		return tileArr[target];

	tileArr[target] = rec(target - 2) * tileArr[2];
	
	for (int i = target - 4; i >= 0; i -= 2) {
		tileArr[target] += tileArr[i] * 2;
	}

	
	return tileArr[target];

}

int main() {
	cin >> N;

	if (N % 2 == 1) {
		cout << 0;
		return 0;
	}
	else if (N == 2) {
		cout << 3;
		return 0;
	}

	tileArr[0] = 1;
	tileArr[2] = 3;

	rec(N);

	cout << tileArr[N];

}