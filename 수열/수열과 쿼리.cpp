
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

vector<int> v;

vector<int>::iterator find(int x)
{
	return find(v.begin(), v.end(), x);
}

void insert(int x)
{
	if (find(x) == v.end())
		v.push_back(x);
}

void erase(int x)
{
	auto it = find(x);
	if (it != v.end())
		v.erase(it);
}

void update(int x, int y)
{
	auto itX = find(x);
	auto itY = find(y);

	if (itX != v.end() && itY == v.end())
		*itX = y;
}

void front(int c)
{
	if (v.empty())
		cout << "empty" << "\n";
	else
	{
		int vSize = c;
		if (c > v.size())
			vSize = v.size();

		nth_element(v.begin(), v.begin() + vSize - 1, v.end());

		cout << v[vSize - 1] << "\n";
	}
}

void back(int c)
{
	if (v.empty())
		cout << "empty" << "\n";
	else
	{
		int vSize = c;
		if (c > v.size())
			vSize = v.size();

		nth_element(v.begin(), v.begin() + vSize - 1, v.end(), greater<int>{});

		cout << v[vSize - 1] << "\n";
	}
}

int main()
{
    FILE* stream;
    freopen_s(&stream, "수열과 커리.txt", "r", stdin);
	int tc, q, x, y;
	string cmd;
	cin >> tc;
	while (tc--) {
		cin >> q;
		v.clear();
		while (q--) {
			cin >> cmd >> x;
			if (cmd == "insert") insert(x);
			if (cmd == "erase") erase(x);
			if (cmd == "update") {
				cin >> y;
				update(x, y);
			}
			if (cmd == "front") front(x);
			if (cmd == "back") back(x);
		}
	}
	return 0;
}
