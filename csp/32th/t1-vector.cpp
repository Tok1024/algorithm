#include <iostream>
using namespace std;

// 给向量x找出一个向量
// 使得这个向量的每一维度都大于他

const int N = 1010, M = 10;
int n, m;
int vectors[N][M];

// x > y
bool check(int x, int y){
    for(int i = 0; i < m; i++){
        if (vectors[x][i] <= vectors[y][i]){
            return false;
        }
    }
    return true;
}

int father(int i){
    for(int j = 1; j <= n; j++){
        if(j == i) continue;
        if(check(j, i)) return j;
    }
    return 0;
}

int main(){
    cin >> n >> m;
    for(int i = 1;  i <= n; i++){
        for(int j = 0; j < m; j++){
            cin >> vectors[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        cout << father(i) << endl;
    }
}