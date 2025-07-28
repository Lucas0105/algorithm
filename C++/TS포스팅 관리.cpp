#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

constexpr int LM = 110005;				// 포스팅 최대 개수
constexpr int LV = 8;					// 버킷 크기 레벨 (2의 거듭제곱 지수)
constexpr int BUCKET_SZ = 1 << LV;		// 버킷 크기
constexpr int MAX_BUCKET = 450;			// 버킷 최대 개수 (포스팅 최대 개수 / 버킷 크기)
constexpr int MASK = BUCKET_SZ - 1;

unordered_map<string, int> hashTagMap;	// hashTag -> ID

int DB[5][5][LM];						// [hashTag1][hashTag2][포스팅]
int blocks[5][5][MAX_BUCKET];

int idCnt;								// 포스팅 개수 (새로운 ID)
unordered_map<int, int> idMap;			// 포스팅 ID -> 새로운 ID (오래된 순으로 부여)

struct Posting {
	int mID;				// 포스팅의 mID
	int M;					// hashTag 개수
	char hashTags[5][10];	// hashTag 리스트
} postingList[LM];

void updatePosting(int newID, int dCnt) {
	// 포스팅 정보 가져오기
	int M = postingList[newID].M;
	char(*hashTags)[10] = postingList[newID].hashTags;

	if (M == 1) {									// hashTag가 1개인 경우
		auto res = hashTagMap.insert({ hashTags[0], hashTagMap.size() });
		int tagID = res.first->second;				// hashTag의 ID 가져오기
		// 포스팅 업데이트
		DB[tagID][tagID][newID] += dCnt;
		blocks[tagID][tagID][newID >> LV] += dCnt;
	}
	else {										// hashTag가 여러개인 경우
		// 모든 (hashTag1, hashTag2)의 경우의 수에 대해서 포스팅 저장
		for (int a = 0; a < M; ++a) {
			auto res1 = hashTagMap.insert({ hashTags[a], hashTagMap.size() });
			int tagID1 = res1.first->second;	// hashTag1의 ID 가져오기
			for (int b = 0; b < M; ++b) {
				auto res2 = hashTagMap.insert({ hashTags[b], hashTagMap.size() });
				int tagID2 = res2.first->second;	// hashTag2의 ID 가져오기
				if (tagID1 > tagID2) continue;

				// 포스팅 업데이트
				DB[tagID1][tagID2][newID] += dCnt;
				blocks[tagID1][tagID2][newID >> LV] += dCnt;
			}
		}
	}
}

void init(int N, int mPostingIDs[], int mHashTagNum[], char mHashTags[][5][10])
{
	// 변수 초기화
	memset(DB, 0, sizeof(DB));
	memset(blocks, 0, sizeof(blocks));
	idCnt = 0;
	idMap.clear();
	hashTagMap.clear();

	// 초기 포스팅 정보 입력 받기
	for (int i = N - 1; i >= 0; --i) {				// 오래된 순으로 포스팅 저장
		idMap[mPostingIDs[i]] = ++idCnt;			// 포스팅에 새로운 ID 부여 (오래된 순)

		// 새로운 포스팅 정보 저장
		postingList[idCnt].mID = mPostingIDs[i];
		postingList[idCnt].M = mHashTagNum[i];
		for (int j = 0; j < mHashTagNum[i]; ++j)
			memcpy(postingList[idCnt].hashTags[j], mHashTags[i][j], sizeof(mHashTags[i][j]));

		// 새로운 포스팅 업데이트
		updatePosting(idCnt, 1);
	}
}

void addPosting(int mID, int mHashTagNum, char mHashTags[][10])
{
	// 포스팅에 새로운 ID 부여
	idMap[mID] = ++idCnt;

	// 새로운 포스팅 정보 저장 및 업데이트
	postingList[idCnt].mID = mID;
	postingList[idCnt].M = mHashTagNum;
	for (int i = 0; i < mHashTagNum; ++i)
		memcpy(postingList[idCnt].hashTags[i], mHashTags[i], sizeof(mHashTags[i]));

	updatePosting(idCnt, 1);
}

void removePosting(int mID)
{
	updatePosting(idMap[mID], -1);
}


int findPostingList(int M, char mKeyWords[][10], int mPageNum, int mAnsIDs[])
{
	int fID = 1, rID = idCnt;
	int startNum = (mPageNum - 1) * 10 + 1;			// mPageNum까지의 포스팅 개수 +1
	int cnt = 0;									// 검색 한 포스팅 개수
	int ans = 0;									// mPageNum의 포스팅 개수

	// 첫번째 hashTag의 ID 가져오기
	if (hashTagMap.find(mKeyWords[0]) == hashTagMap.end()) return 0;
	int tagID0 = hashTagMap[mKeyWords[0]], tagID1 = tagID0;

	if (M > 1) {		// hashTag가 2개인 경우
		// 두번째 hashTag의 ID 가져오기
		if (hashTagMap.find(mKeyWords[1]) == hashTagMap.end()) return 0;
		tagID1 = hashTagMap[mKeyWords[1]];

		// tagID1이 더 커야함
		if (tagID0 > tagID1) swap(tagID0, tagID1);
	}

	int* A = DB[tagID0][tagID1];
	int* B = blocks[tagID0][tagID1];

	// 낱개 부분의 포스팅 확인
	while (fID <= rID && ((rID + 1) & MASK)) {
		int val = A[rID];
		if (val) {
			cnt += val;
			if (cnt >= startNum) {
				mAnsIDs[ans++] = postingList[rID].mID;
				if (ans >= 10) return ans;
			}
		}
		rID--;
	}

	// 온전한 block 부분의 포스팅 확인
	while (fID <= rID) {
		if ((cnt + B[rID >> LV]) >= startNum) break;		// 해당 버킷을 포함하면 개수를 넘는 경우
		cnt += B[rID >> LV];
		rID -= BUCKET_SZ;
	}

	// 다시 낱개로 포스팅 확인하기
	while (fID <= rID) {
		int val = A[rID];
		if (val) {
			cnt += val;
			if (cnt >= startNum) {
				mAnsIDs[ans++] = postingList[rID].mID;
				if (ans >= 10) return ans;
			}
		}
		rID--;
	}

	return ans;
}
