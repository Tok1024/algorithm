#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1010;
struct Task{
    int t, a, b, type;
    double ratio;
};


int main(){
    int n, m;
    double total_time = 0.0, res = 0.0;
    cin >> n >> m;
    vector<Task> flex, normal;
    for(int i = 0; i < n; i++){
        int o, t, a, b;
        cin >> o >> t >> a >> b;
        if(o == 0){
            flex.push_back({t, a, b, o, b / (1.0 * a)});
        }else{
            normal.push_back({t, a, b, o, b / (1.0 * a)});
        }
        total_time += t;
    }

    // 我们把DP和贪心都转化成收益最大的问题

    // 1. 预处理DP数组
    vector<double> dp(m+1, 0.0);
    for(const auto& t: normal){
        for(int j = m; j >= t.a; --j){
            // 选 or 不选
            // 0/1 背包不能选多次，要倒序遍历
            dp[j] = max(dp[j - t.a] + t.b, dp[j]);
            // 这是从二维压缩过来的
            // 原本是 dp[i-1][j]，这是一个滚动更新，代表对于第i个任务，
        }
    }


    // 2. 贪心问题
    // 升序排列的比较器
    sort(flex.begin(), flex.end(), [](Task& x, Task& y){
        return x.ratio > y.ratio;
    });

    vector<double> gain_flex(m+1);
    for(int c = 1; c <= m; c++){
        double max_gain = 0.0;
        int remain = c;
        for(auto t: flex){
            if(remain >= t.a){
                // c -= t.a;
                max_gain += t.b;
                remain -= t.a;
            }
            else{
                max_gain += remain * t.ratio;
                break;
            }
        }
        gain_flex[c] = max_gain;
    }

    double max_gain = 0.0;

    for(int x = 0; x <= m; x++){
        max_gain = max(max_gain, dp[x] + gain_flex[m-x]);
    }
    res = total_time - max_gain;
    printf("%.6f\n", res);
}