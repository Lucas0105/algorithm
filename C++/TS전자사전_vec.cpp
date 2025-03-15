
//user.cpp
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#define MAX_L				(8)

using namespace std;

struct RESULT
{
	int success;
	char word[MAX_L + 1];
};

vector<string> alphaVec[26];

void init(int N, char mWordList[][MAX_L + 1])
{	
	for (int i = 0; i < 26; i++) alphaVec[i].clear();
	for (int i = 0; i < N; i++) {
		int startChar = mWordList[i][0] - 'a';
		alphaVec[startChar].push_back(mWordList[i]);
	}

	for (int i = 0; i < 26; i++) {
		sort(alphaVec[i].begin(), alphaVec[i].end());
	}

	return;
}

int add(char mWord[])
{
	int startChar = mWord[0] - 'a';
	auto target = lower_bound(alphaVec[startChar].begin(), alphaVec[startChar].end(), mWord);

	if (target == alphaVec[startChar].end() || *target != mWord) {
		alphaVec[startChar].insert(target, mWord);
		return 1;
	}
	else {
		return 0;
	}
}

int erase(char mWord[])
{
	int startChar = mWord[0] - 'a';
	auto target = lower_bound(alphaVec[startChar].begin(), alphaVec[startChar].end(), mWord);

	if (target == alphaVec[startChar].end() || *target != mWord) {
		return 0;
	}
	else {
		alphaVec[startChar].erase(target);
		return 1;
	}
}

RESULT find(char mInitial, int mIndex)
{
	RESULT res;

	int stIndex = mInitial - 'a';
	
	if (alphaVec[stIndex].size() < mIndex) {
		res.success = 0;
	}
	else {
		res.success = 1;
		strcpy_s(res.word, alphaVec[stIndex][mIndex-1].c_str());
	}

	return res;
}

int getIndex(char mWord[])
{
	int stIdx = mWord[0] - 'a';
	int curIdx = 0;

	auto target = lower_bound(alphaVec[stIdx].begin(), alphaVec[stIdx].end(), mWord);

	if (target == alphaVec[stIdx].end() || *target != mWord) {
		return 0;
	}
	else {
		curIdx += target - alphaVec[stIdx].begin() + 1;
	}

	for (int i = 0; i < stIdx; i++) {
		curIdx += alphaVec[i].size();
	}


	return curIdx;
}