// user.cpp
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

const int psize = 100;

int PN, N;
vector<pii>blank[20005];
int rowMax[20005];
int pageMax[205];

struct Word {
    int r, c, len;

    void erase() {
        auto& v = blank[r];
        int i = lower_bound(v.begin(), v.end(), pii{ c, 0 }) - v.begin();

        if (i < v.size() && c + len == v[i].first) {
            v[i] = { c, len + v[i].second };
        }
        else {
            v.insert(v.begin() + i, { c, len });
        }

        if (i && v[i - 1].first + v[i - 1].second == c) {
            v[i - 1].second += v[i].second;
            v.erase(v.begin() + i);
            i--;
        }

        rowMax[r] = max(rowMax[r], v[i].second);
        pageMax[r / psize] = max(pageMax[r / psize], v[i].second);

        r = -1;
    }
}word[55005];

void init(int N, int M)
{
    ::N = N;
    PN = (N - 1) / psize + 1;
    for (int i = 0; i < N; i++) {
        rowMax[i] = M;
        pageMax[i / psize] = M;
        blank[i] = { {0, M} };
    }
    fill(word, word + 55001, Word{ -1 });
}

int writeWord(int mId, int mLen)
{
    for (int p = 0; p < PN; p++) {
        if (pageMax[p] < mLen) continue;

        int sr = p * psize;
        int er = min(sr + psize, N);

        for (int r = sr; r < er; r++) {
            if (rowMax[r] < mLen) continue;

            auto& v = blank[r];
            for (int i = 0; i < v.size(); i++) {
                if (v[i].second < mLen) continue;

                int c = v[i].first;
                word[mId] = { r, c, mLen };

                v[i] = { c + mLen, v[i].second - mLen };
                if (v[i].second == 0) v.erase(v.begin() + i);

                int maxLen = 0;
                for (auto p : v) maxLen = max(maxLen, p.second);
                rowMax[r] = maxLen;


                for (int j = sr; j < er; j++) {
                    maxLen = max(maxLen, rowMax[j]);
                }
                pageMax[p] = maxLen;

                return r;
            }
        }
    }
    return -1;
}

int eraseWord(int mId)
{
    int res = word[mId].r;
    if (res != -1) word[mId].erase();
    return res;
}

