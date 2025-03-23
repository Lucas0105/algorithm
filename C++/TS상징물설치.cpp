// user.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT			(100)
#define CMD_ADD_BEAM		(200)
#define CMD_REQUIRE_SINGLE	(300)
#define CMD_REQUIRE_TWIN	(400)

#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;

class Gidung {

	public:
		Gidung() {
			firstStick[0] = 0; firstStick[1] = -1;
			secondStick[0] = 0; secondStick[1] = -1;
			thirdStick[0] = 0; thirdStick[1] = -1;
		}

		int firstStick[2];
		int secondStick[2];
		int thirdStick[2];

		Gidung gidungMemCpy() {
			Gidung g2;
			g2.firstStick[0] = firstStick[0]; g2.firstStick[1] = firstStick[1];
			g2.secondStick[0] = secondStick[0]; g2.secondStick[1] = secondStick[1];
			g2.thirdStick[0] = thirdStick[0]; g2.thirdStick[1] = thirdStick[1];

			return g2;
		}

		int getLongStic() {
			int MaxStick = max(firstStick[0], secondStick[0]);
			MaxStick = max(MaxStick, thirdStick[0]);

			return MaxStick;
		}
		
};

unordered_map<int, int> hMap;
vector<int> sticks;
vector<Gidung> gidungList[300000];
int hIdx = 0;
int stIdx = 0;

int getHashValue(int originValue, bool check = false) {
	if (hMap.count(originValue)) {
		return hMap[originValue];
	}
	else {
		// Data 유무 파악
		if (check) {
			return -1;
		}
		hMap[originValue] = hIdx++;
		return hMap[originValue];
	}
}


void init()
{
	hIdx = 0;
	stIdx = 0;
	hMap.clear();
	sticks.clear();
	for (int i = 0; i < 300000; i++) {
		gidungList[i].clear();
	}
	return;
}

void addBeam(int mLength)
{
	Gidung gidung;
	gidung.firstStick[0] = mLength;
	gidung.firstStick[1] = stIdx;
	int idx = getHashValue(mLength);

	gidungList[idx].push_back(gidung);

	for (int i = 0; i < sticks.size(); i++) {
		Gidung gidung2 = gidung.gidungMemCpy();

		gidung2.secondStick[0] = sticks[i];
		gidung2.secondStick[1] = i;

		int secondSum = mLength + sticks[i];
		idx = getHashValue(secondSum);

		gidungList[idx].push_back(gidung2);
		for (int j = i + 1; j < sticks.size(); j++) {
			Gidung gidung3 = gidung2.gidungMemCpy();

			gidung3.thirdStick[0] = sticks[j];
			gidung3.thirdStick[1] = j;

			int thirdSum = secondSum + sticks[j];
			idx = getHashValue(thirdSum);

			gidungList[idx].push_back(gidung3);
		}
	}

	sticks.push_back(mLength);
	stIdx++;

	return;
}

int requireSingle(int mHeight)
{
	int minStick = 1000000000;

	int idx = getHashValue(mHeight, true);

	if (idx == -1) {
		return -1;
	}
	auto gidungVec = gidungList[idx];

	for (auto it = gidungVec.begin(); it != gidungVec.end(); it++) {
		int maxStick = it->getLongStic();
		minStick = min(maxStick, minStick);
	}
	return minStick;
}

int requireTwin(int mHeight)
{
	int minStick = 1000000000;

	int idx = getHashValue(mHeight, true);

	if (idx == -1) {
		return -1;
	}
	auto gidungVec = gidungList[idx];

	int check = false;
	for (auto it = gidungVec.begin(); it != gidungVec.end(); it++) {
		bool midCheck = false;
		int maxStick = it->getLongStic();
		for (auto it2 = it + 1; it2 != gidungVec.end(); it2++) {
			if (it->firstStick[1] != -1 and (it->firstStick[1] == it2->firstStick[1] or it->firstStick[1] == it2->secondStick[1] or it->firstStick[1] == it2->thirdStick[1])) {
				continue;
			}

			if (it->secondStick[1] != -1 and (it->secondStick[1] == it2->firstStick[1] or it->secondStick[1] == it2->secondStick[1] or it->secondStick[1] == it2->thirdStick[1])) {
				continue;
			}

			if (it->thirdStick[1] != -1 and (it->thirdStick[1] == it2->firstStick[1] or it->thirdStick[1] == it2->secondStick[1] or it->thirdStick[1] == it2->thirdStick[1])) {
				continue;
			}

			int maxStick2 = it2->getLongStic();
			maxStick2 = max(maxStick, maxStick2);

			minStick = min(maxStick2, minStick);

			midCheck = true;
			check = true;
		}

	}

	if (!check)
		return -1;
	return minStick;
}


// main.cpp

extern void init();
extern void addBeam(int mLength);
extern int requireSingle(int mHeight);
extern int requireTwin(int mHeight);

static bool run()
{
	int Q;
	int mLength, mHeight;

	int ret = -1, ans;

	scanf("%d", &Q);

	bool okay = false;

	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			init();
			okay = true;
			break;
		case CMD_ADD_BEAM:
			scanf("%d", &mLength);
			addBeam(mLength);
			break;
		case CMD_REQUIRE_SINGLE:
			scanf("%d", &mHeight);
			ret = requireSingle(mHeight);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_REQUIRE_TWIN:
			scanf("%d", &mHeight);
			ret = requireTwin(mHeight);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		default:
			okay = false;
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int TC, MARK;

	scanf("%d %d", &TC, &MARK);
	for (int tc = 1; tc <= TC; ++tc)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}