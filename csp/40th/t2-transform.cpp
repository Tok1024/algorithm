#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int N = (1 << 9);
vector<int> k;

int f(int x, int k){
    return ((x*x + k*k) % 8) ^ k;
}

int g(int x, int k){
    int mask_c = 7, mask_b = 7 << 3, mask_a = 7 << 6;
    int a = (x & mask_a) >> 6;
    int b = (x & mask_b) >> 3;
    int c = (x & mask_c);
    int res = (b << 6) + ((c ^ f(b, k)) << 3) + a ^ (f(c, k));
    return res;
}

int f_transform(int input){
    int res = input;
    for(int i = 0; i < k.size(); i++){
        res = g(res, k[i]);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    k.resize(m);
    vector<int> outputs(n);
    for(int i = 0; i < m; i++){
        cin >> k[i];
    }
    for(int i = 0; i < n; i++){
        cin >> outputs[i];
    }
    // 1. 暴力枚举 1-2^9, 找出输入
    // for(int x: outputs){
    // 然后发现这里计算的transform都是一样的呀！那就预计算（打表）出来吧
    //     for(int i = 0; i < N; i++){
    //         if(f_transform(i) == x){
    //             cout << i << ' ';
    //             break;
    //         }
    //     }
    // }
    map<int, int> mapping;
    for(int i = 0; i < N; i++){
        mapping[f_transform(i)] = i;
    }
    for(int x: outputs){
        cout << mapping[x] << ' ';
    }
    cout << "\n";
}
