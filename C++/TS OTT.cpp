#include <unordered_map>
#include <set>

using namespace std;
using pii = pair<int, int>;

struct Movie {
    int id, tot, time, genre;

    bool operator < (const Movie &r) const {
        if (tot == r.tot) {
            return time > r.time;
        }
        return tot > r.tot;
    }
};

int time;
int watchTime;
set<Movie> movieSet[6];
set<pii> showMovie[1001];

unordered_map<int, int> score[1001];
unordered_map<int, int> watchTimeMap[1001];
unordered_map<int, Movie> movieMap;
//user.cpp

struct RESULT
{
    int cnt;
    int IDs[5];
};

void init(int N)
{
    for (int i = 1; i < 6; i++)
        movieSet[i].clear();

    for (int i = 1; i <= 1000; i++) {
        showMovie[i].clear();
        score[i].clear();
        watchTimeMap[i].clear();
    }
    movieMap.clear();
    time = 0;
    watchTime = 0;

    return;
}

int add(int mID, int mGenre, int mTotal)
{
    if (movieMap.count(mID) > 0)
        return 0;

    Movie newMovie({ mID, mTotal, time, mGenre });
    movieSet[mGenre].insert(newMovie);
    movieMap[mID] = newMovie;
    time++;
    return 1;
}

int erase(int mID)
{
    if (movieMap.count(mID) == 0)
        return 0;

    Movie target = movieMap[mID];
    movieSet[target.genre].erase(target);
    movieMap.erase(mID);

    return 1;
}

int watch(int uID, int mID, int mRating)
{
    // 삭제됨 혹은 원래 없음
    if (movieMap.count(mID) == 0)
        return 0;

    Movie target = movieMap[mID];

    // 이미 봄
    if (score[uID].count(mID)> 0) {
        return 0;
    }

    // 봄
    showMovie[uID].insert({ watchTime++, mID });
    score[uID][mID] = mRating;

    movieSet[target.genre].erase(target);
    target.tot += mRating;
    movieSet[target.genre].insert(target);
    movieMap[mID].tot += mRating;

    return 1;
}

RESULT suggest(int uID)
{
    RESULT res;
    res.cnt = 0;

    int movieIdx = 0;
    int movieArray[5];
    
    // 순서대로 5개 영화 추천
    for (auto it = showMovie[uID].rbegin(); it != showMovie[uID].rend() && movieIdx != 5; it++) {
        int id = it->second;
        if (movieMap.count(id)) {
            movieArray[movieIdx] = id;
            movieIdx++;
        }
    }
    
    set<Movie> recomendMovie;

    // 본 영화가 없을 때
    if (movieIdx == 0) {
        for (int i = 1; i <= 5; i++) {
            int idx = 0;
            for (auto it = movieSet[i].begin(); it != movieSet[i].end() && idx != 5; it++) {
                recomendMovie.insert(*it);
                idx++;
            }
        }
    }
    else {
        // 5개 영화 중 최고 평점 영화 선택
        int maxID = movieArray[0];
        for (int i = 1; i < movieIdx; i++) {
            int mID = movieArray[i];
            if (score[uID][maxID] < score[uID][mID]) {
                maxID = mID;
            }
        }
        Movie target = movieMap[maxID];

        int movieSize = 0;
        for (auto it = movieSet[target.genre].begin(); it != movieSet[target.genre].end() && movieSize != 5; it++) {
            if (it->id != maxID && score[uID].count(it->id) == 0) {
                res.IDs[movieSize] = it->id;
                movieSize++;
            }
        }
        res.cnt = movieSize;

        return res;
    }
    int recSize = recomendMovie.size();
    int movieSize = min(5, recSize);

    if (movieSize == 0)
        return res;

    res.cnt = movieSize;

    auto it = recomendMovie.begin();
    for (int i = 0; i < movieSize; i++) {
        res.IDs[i] = it->id;
        it = next(it);
    }

    return res;
}