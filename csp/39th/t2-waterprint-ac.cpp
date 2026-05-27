#include <bits/stdc++.h>
using namespace std;

const int N = 210;

int n, L;
int g[N][N];
bool pattern[5][9];   // true 表示期待白色，false 表示期待黑色
set<int> notAns;      // 还没有被证明是答案的 k

pair<int, int> getRange(int x, int y)
{
    int minWhite = L;   // k 的上界
    int maxBlack = -1;  // k 的下界

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int val = g[x + i][y + j];

            if (pattern[i][j])
            {
                // 这个位置要求是白色
                // val >= k，所以 k <= val
                minWhite = min(minWhite, val);
            }
            else
            {
                // 这个位置要求是黑色
                // val < k，所以 k >= val + 1
                maxBlack = max(maxBlack, val + 1);
            }
        }
    }

    return {maxBlack, minWhite};
}

int main()
{
    cin >> n >> L;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> g[i][j];
        }
    }

    // 一开始所有 k 都还不是答案
    for (int k = 0; k < L; k++)
    {
        notAns.insert(k);
    }

    // 初始化水印模板，默认全是白色
    memset(pattern, true, sizeof pattern);

    // 把指定位置改成黑色
    pattern[1][1] = pattern[1][2] = pattern[1][4] = pattern[1][5] = pattern[1][7] = false;
    pattern[2][1] = pattern[2][2] = pattern[2][8] = false;
    pattern[3][1] = pattern[3][2] = pattern[3][3] = pattern[3][4] = pattern[3][7] = pattern[3][8] = false;
    pattern[4][7] = pattern[4][8] = false;

    // 枚举每一个 5 × 9 的区域
    for (int x = 0; x <= n - 5; x++)
    {
        for (int y = 0; y <= n - 9; y++)
        {
            auto range = getRange(x, y);

            int blackK = range.first;
            int whiteK = range.second;

            // 无解
            if (blackK > whiteK) continue;

            // 这个区域在 [blackK, whiteK] 内的 k 都能匹配水印
            // 所以这些 k 是答案，从 notAns 里删掉
            auto l = notAns.lower_bound(blackK);
            auto r = notAns.lower_bound(whiteK + 1);

            notAns.erase(l, r);
        }
    }

    // 不在 notAns 里的，就是答案
    for (int k = 0; k < L; k++)
    {
        if (!notAns.count(k))
        {
            cout << k << '\n';
        }
    }

    return 0;
}