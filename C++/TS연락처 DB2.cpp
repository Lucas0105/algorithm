
//user.cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_N			(5)
#define MAX_L			(8)

#include <string>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;


struct Log {
	Log(char* name, char* tel) {
		strcpy(this->name, name);
		strcpy(this->tel, tel);
		removed = false;
	}
	char name[10];
	char tel[10];
	bool removed;
};

unordered_map<string, int> infoHmap;
unordered_map<string, vector<int>> logHmap;
vector<Log> logInfo;
int idx;


struct Result
{
	int size;
	char mNameList[MAX_N][MAX_L + 1];
	char mTelephoneList[MAX_N][MAX_L + 1];
};

void init()
{
	infoHmap.clear();
	logHmap.clear();
	logInfo.clear();
	idx = 0;

	return;
}

void addLog(string data, int targetIdx) {
	for (int i = 1; i <= data.length(); i++) {
		logHmap[data.substr(0, i)].push_back(targetIdx);
	}
}

void add(char mName[], char mTelephone[])
{
	Log log(mName, mTelephone);

	logInfo.push_back(log);
	infoHmap[mName] = idx;
	infoHmap[mTelephone] = idx;

	addLog(mName, idx);
	
	addLog(mTelephone, idx);


	idx++;
	return;
}

void remove(char mStr[])
{

	if (infoHmap.count(mStr)) {
		int targetIdx = infoHmap[mStr];
		logInfo[targetIdx].removed = true;
	}

	return;
}

void call(char mTelephone[])
{
	if (infoHmap.count(mTelephone)) {
		int targetIdx = infoHmap[mTelephone];
		string name = logInfo[targetIdx].name;
		addLog(name, targetIdx);
		addLog(mTelephone, targetIdx);
	}
	else {
		Log log((char*)"", mTelephone);
		logInfo.push_back(log);
		infoHmap[mTelephone] = idx;
		addLog(mTelephone, idx++);
	}


	return;
}

Result search(char mStr[])
{
	Result ret;
	ret.size = 0;

	auto v = logHmap[mStr];

	for (int i = v.size() - 1; i>= 0 ; i--) {
		int it = v[i];
		if (ret.size == 5)
			break;

		if (logInfo[it].removed == true)
			continue;

		string name = logInfo[it].name;
		string tel = logInfo[it].tel;

		bool check = false;
		for (int j = 0; j < ret.size; j++) {
			if (name != "" && name == ret.mNameList[j]) {
				check = true;
				break;
			}
			if (tel == ret.mTelephoneList[j]) {
				check = true;
				break;
			}
		}

		if (check)
			continue;

		strcpy(ret.mNameList[ret.size], name.c_str());
		strcpy(ret.mTelephoneList[ret.size], tel.c_str());

		ret.size++;
	}


	return ret;
}