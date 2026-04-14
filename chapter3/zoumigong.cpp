#include <iostream>
#include <queue>
using namespace std;

const int N = 110;
int g[N][N], d[N][N];
int n, m;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
typedef pair<int, int> PII;
queue<PII> q;

bool check(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0;
}

// int bfs(){
//     // 起点
//     q.push({0, 0});
    // memset(d, -1, sizeof d);
    // d[0][0] = 0; // 初始化为-1, 防止将起点距离为0以为是未访问
//     // 搜索
//     while(!q.empty()){
//         PII point = q.front();
//         q.pop();
//         for(int i = 0; i < 4; i++){
//             int x = point.first + dx[i];
//             int y = point.second + dy[i];
//             if(check(x, y) && d[x][y] == -1){ // 必须要求以前未访问，否则会无限循环！
//                 d[x][y] = d[point.first][point.second] + 1;
//                 q.push({x, y});
//             }
//         }
//     }
//     return d[n-1][m-1];
// }

// 法2:每次弹出所有点（可拓展性差一点）
int bfs(){
    // 起点
    q.push({0, 0});
    int dist = 0;
    // 初始化d
    memset(d, -1, sizeof d);
    d[0][0] = 0; // 初始化为-1, 防止将起点距离为0以为是未访问
    // 搜索
    while(!q.empty()){
        int len = q.size();
        dist++; // 每次遍历一层，dist++
        for(int i = 0; i < len; i++){
            PII point = q.front();
            q.pop();
            for(int i = 0; i < 4; i++){
                int x = point.first + dx[i];
                int y = point.second + dy[i];
                if(check(x, y) && d[x][y] == -1){ // 必须要求以前未访问，否则会无限循环！
                    d[x][y] = dist; // 不好知道从哪个点来的
                    q.push({x, y});
                }
            }
        }
    }
    return d[n-1][m-1];
}


int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &g[i][j]);
        }
    }
    cout << bfs() << endl;
}