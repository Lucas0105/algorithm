#include <string>
#include<cstring>
#include <unordered_map>
#include <set>

using namespace std;

struct Stock {
	int PRICE, CODE, BIZCODE, TYPE;

	bool operator < (const Stock& r) const {
		if (PRICE == r.PRICE)
			return CODE < r.CODE;
		return PRICE < r.PRICE;
	}

};

unordered_map<int, Stock> stockMap;
set<Stock> stockSet[6];

void init() {
	stockMap.clear();
	for (int i = 0; i < 6; i++) {
		stockSet[i] = set<Stock>();
	}
	return;
}

int add(char mStockInfo[]) {
	
	char* context = NULL;
	char* ptr = strtok_s(mStockInfo, ",", &context);

	int tbIdx = 0;
	int process = 0;

	Stock newStock;

	while (ptr) {
		string key = "";
		string value = "";

		int i = 1;
		while (ptr[i] != ']') {
			key += ptr[i];
			i++;
		}

		i+= 3;
		while (ptr[i] != '}') {
			value += ptr[i];
			i++;
		}

		if (key[0] == 'S') {
			process++;
			newStock.CODE = stoi(value);
		}
		else if (key[0] == 'B') {
			process++;
			newStock.BIZCODE = stoi(value) - 1;
		}
		else if (key[0] == 'T') {
			process++;

			if (value[0] == 'c') {
				newStock.TYPE = 0;
			}
			else if (value[0] == 'p') {
				newStock.TYPE = 3;
			}

		}
		else if (key[0] == 'P') {
			process++;
			newStock.PRICE = stoi(value);
		}

		if (process == 4) {
			process = 0;
			tbIdx = newStock.TYPE + newStock.BIZCODE;
			stockSet[tbIdx].insert(newStock);
			stockMap[newStock.CODE] = newStock;
			newStock = *new Stock;
		}
		ptr = strtok_s(NULL, ",", &context);
	}
	
	Stock result = *stockSet[tbIdx].rbegin();
	return result.CODE;
}

int remove(int mStockCode) {
	if (stockMap.count(mStockCode) == 0)
		return -1;
	Stock target = stockMap[mStockCode];
 	stockMap.erase(mStockCode);

	int tbIdx = target.TYPE + target.BIZCODE;
	int price = target.PRICE;
	stockSet[tbIdx].erase(target);

	if (stockSet[tbIdx].empty())
		return -1;

	return stockSet[tbIdx].begin() -> CODE;
}

int search(char mCondition[]) {
	string s = mCondition;
	bool bcode[3] = {}, type[2] = {};

	int price = stoi(s.substr(s.find("PR") + 8));
	
	// BIZCODE
	for (int i = s.find("B") + 10; s[i] != '}'; i++) {
		if (s[i] != ',') {
			bcode[s[i] - '1'] = 1;
		}
	}

	// TYPE
	for (int i = s.find("T") + 7; s[i] != '}'; i++) {
		if (s[i] == 'c') type[0] = 1;
		if (s[i] == 'p') type[1] = 1;
	}

	int resPrice = 1e9;
	int resCode = -1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if (bcode[i] && type[j]) {
				int key = i + j * 3;
				auto it = stockSet[key].lower_bound({ price, 0 });

				if (it == stockSet[key].end()) continue;

				if (resPrice > it->PRICE) {
					resPrice = it->PRICE;
					resCode = it->CODE;
				}
				else if (resPrice == it->PRICE && resCode > it->CODE) {
					resCode = it->CODE;
				}
			}

		}
	}
	return resCode;
}