#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1010;
int g[N][N];
int score[5];
int n;
vector<int> all_x, all_y;

void count_score(int i, int j){
    int s = 0;
    if(i > 0 && j > 0 && g[i-1][j-1] == 1) s++;
    if(i > 0 && j < N-1 && g[i-1][j+1] == 1) s++;
    if(i < N-1 && j > 0 && g[i+1][j-1] == 1) s++;
    if(i < N-1 && j < N-1 && g[i+1][j+1] == 1) s++;

    score[s]++;
}

int main(){
    memset(score, 0, sizeof(score));
    // 把x，y离散化
    int x, y;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x >> y;
        all_x.push_back(x);
        all_y.push_back(y);
    }
    // 1. 排序+去重
    vector<int> sorted_x = all_x;
    vector<int> sorted_y = all_y;
    sort(sorted_x.begin(), sorted_x.end());
    sorted_x.erase(unique(sorted_x.begin(), sorted_x.end()), sorted_x.end());
    sorted_y.erase(unique(sorted_y.begin(), sorted_y.end()), sorted_x.end());

    // 2. get_rank 把原始坐标映射到新的数组索引
    auto get_rank_x = [&](const int x) -> int{
        return lower_bound(sorted_x.begin(), sorted_x.end(), x) - sorted_x.begin() + 1;
    };
    auto get_rank_y = [&](const int y) -> int{
        return lower_bound(sorted_y.begin(), sorted_y.end(), x) - sorted_y.begin() + 1;
    };

    for(int i = 0; i < all_x.size(); i++){
        int new_x = get_rank_x(all_x[i]), new_y = get_rank_y(all_y[i]);
        g[new_x][new_y] = 1;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i > 0 && j > 0 && i < N-1 && j < N-1 &&
                g[i-1][j] == 1 && g[i+1][j] == 1 && g[i][j-1] == 1 && g[i][j+1] == 1){
                    count_score(i, j);
                }
        }
    }
    for(int i = 0; i < 5; i++){
        cout << score[i] << endl;
    }
}