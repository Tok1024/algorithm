#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

const int Z = 401;
int n;
char g[Z][Z], temp[Z][Z];

void global_rotate_right(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // 顺时针旋转的公式- 先对称 - 再把列反转
            temp[j][n-1-i] = g[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            g[i][j] = temp[i][j];
        }
    }
}

void local_rotate_left(int u, int v, int l){
    int x1 = u, x2 = u+l, y1 = v, y2 = v+l;
    for(int i = x1; i < x2; i++){
        for(int j = y1; j < y2; j++){
            temp[i][j] = g[i][j];
        }
    }
    for(int i = x1; i < x2; i++){
        for(int j = y1; j < y2; j++){
            // 逆时针旋转的公式- 先对称 - 再把行反转
            temp[x2+x1-1-j][i] = g[i][j];
        }
    }
    for(int i = x1; i < x2; i++){
        for(int j = y1; j < y2; j++){
            g[i][j] = temp[i][j];
        }
    }
}

void flip_up_down(int x1, int x2, int y1, int y2){
    for(int i = x1; i <= x2; i++){
        for(int j = y1; j <= y2; j++){
            // 上下翻转的公式- 行反转
            temp[x2-i+x1][j] = g[i][j];
        }
    }
    for(int i = x1; i <= x2; i++){
        for(int j = y1; j <= y2; j++){
            g[i][j] = temp[i][j];
        }
    }
}

void flip_left_right(int x1, int x2, int y1, int y2){
    for(int i = x1; i <= x2; i++){
        for(int j = y1; j <= y2; j++){
            // 左右翻转的公式- 列反转
            temp[i][y2+y1-j] = g[i][j];
        }
    }
    for(int i = x1; i <= x2; i++){
        for(int j = y1; j <= y2; j++){
            g[i][j] = temp[i][j];
        }
    }
}

void decode_rotate(int u, int v, int l, int d, int r){
    // 1. 整体顺时针旋转90度r次
    for(int i = 0; i < r; i++){
        global_rotate_right();
    }
    // 2. 局部逆时针旋转d度
    int rotate_cnt = d / 90;
    u--,v--;
    while(rotate_cnt--){
        local_rotate_left(u, v, l);
    }
}

void decode_flip(int u, int d, int l, int r, int o){
    // 翻转的逆操作就是自身
    u--,d--,l--,r--;
    if(o==-1) flip_left_right(u, d, l, r);
    else flip_up_down(u, d, l, r);
}

void print_graph(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << g[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int find_width(){
    bool flag = false;
    for (int j = n-1; j >= 0; j--){
        for(int i = 0; i < n; i++){
            if(g[i][j]!='?'){
                flag = true;
                break;
            }
        }
        if(flag) return j+1;
    }
    return 0;
}

int find_height(){
    bool flag = false;
    for (int i = n-1; i >= 0; i--){
        for(int j = 0; j < n; j++){
            if(g[i][j]!='?'){
                flag = true;
                break;
            }
        }
        if(flag) return i+1;
    }
    return 0;
}


int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> g[i][j];
        }
    }
    int k, x, len;
    cin >> k >> len;
    vector<vector<int>> operations(len);
    for(auto& operation: operations){
        for(int i = 0; i < 6; i++){
            cin >> x;
            operation.push_back(x);
        }
    }
    // 我们要倒馆，也就是反向操作才能decode
    for(auto it = operations.rbegin(); it != operations.rend(); ++it){
        auto operation = *it;
        if(operation[0] == 1){
            decode_rotate(operation[1], operation[2], operation[3], operation[4], operation[5]);
        }else{
            decode_flip(operation[1], operation[2], operation[3], operation[4], operation[5]);
        }
    }
    int w = find_width(), h = find_height();
    cout << h << ' ' << w << endl;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            cout << g[i][j];
        }
        cout << endl;
    }
    cout << endl;
}