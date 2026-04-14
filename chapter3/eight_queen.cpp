#include <iostream>
using namespace std;

/**
 * @brief 八皇后问题
 * 每一行只能有一个皇后
 * 这是一个在每层做出选择的dfs问题
 * 限制条件：每行，每列，每个对角线只有一个皇后
 * 对角线的表示 dg[2*N], udg[2*N], 其中 位于同一对角线的
 * x，y分别满足 x+y，和 x - y + n相等
 */

const int N = 10;

int n;
char g[N][N];
bool col[N], dg[2*N], udg[2*N];

// 规定深度u每次从0开始，到达n代表选择结束(n+1次)
// 这里我们遍历每一行
void dfs(int u){
    // base case
    if(u == n){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++) printf("%c", g[i][j]);
            puts("");
        }
        puts("");
        return;
    }
    // 对当前行可能的列进行选择
    for(int v = 0; v < n; v++){
        if(!col[v] && !dg[u+v] && !udg[u-v+n]){
            col[v] = dg[u+v] = udg[u-v+n] = true;
            g[u][v] = 'Q';
            dfs(u+1);
            g[u][v] = '.';
            col[v] = dg[u+v] = udg[u-v+n] = false;
        }
    }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g[i][j] = '.';
    dfs(0);
}