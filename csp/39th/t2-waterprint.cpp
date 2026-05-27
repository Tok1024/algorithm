#include <iostream>
using namespace std;

// 检查图片中的水印
// 一般的想法是用一个数组存图片，一个数组存临时结果，一个数组存目标水印
const int N = 210;
int n, l; // 图片尺寸，灰度值范围
int g[N][N], tmp[N][N];
int target[5][9] = {
    1,1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,1,0,1,
    1,0,0,1,1,1,1,1,0,
    1,0,0,0,0,1,1,0,0,
    1,1,1,1,1,1,1,0,0,
};

void print_graph(int g[N][N]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << g[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool check_waterprint(int x, int y){
    for(int i = x; i <= x+4; i++){
        for(int j = y; j <= y+8; j++){
            if(tmp[i][j] != target[i-x][j-y])
            return false;
        }
    }
    return true;
}

bool check_threshold(int k){
    // 1. 用阈值k处理图像
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(g[i][j] >= k) tmp[i][j] = 1;
            else tmp[i][j] = 0;
        }
    };
    // print_graph(tmp);
    // 2. 遍历整个图像，找子矩阵匹配
    for(int i = 0; i < n-4; i++){
        for(int j = 0; j < n-8; j++){
            if(check_waterprint(i, j)){
                return true;
            }
        }
    }
    return false;
}


int main(){
    cin >> n >> l;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> g[i][j];
        }
    }
    // print_graph(g);
    for(int k = 1; k < l; k++){
        if(check_threshold(k)) cout << k << endl;
    }
    // cout << check_threshold(4) << endl;

}