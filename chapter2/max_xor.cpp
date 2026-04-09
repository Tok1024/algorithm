#include <iostream>
using namespace std;

/* 最大异或对
 * 题目：给定 n 个数字，求出一对数字，使得他们的异或值最大
 * 思路：每次循环固定一个数字去搜索另外一个数字，使得异或值最大
 *      其中的优化策略就是对每一个数字的31位（数据范围0-2^21)建立一颗trie树
 *      每次就尽可能沿着01的反方向爬树，使得异或值最大
 * */

const int M = 3e6+10, N = 1e5;
int son[M][2], a[N], idx;

void insert(int x){
    int p = 0;
    for(int i = 30; ~i; i--){ //等价于i >= 0, i=-1时， ~i = 0
        int u = (x >> i) & 1; // 这里可以记一下，右移i 再与1,就是取第i位
        if(!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
}

int query(int x){
    int p = 0, res = 0;
    for(int i = 30; ~i; i--){
        int u = (x >> i) & 1;
        if(son[p][!u]){ // 若另一方向分支存在，则加上这一位的共享，爬向这方向
            p = son[p][!u];
            res += 1 << i;
        }
        else p = son[p][u];
    }
    return res;
}

int main(){
    int n, x;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        insert(a[i]);
    }

    int res = 0;
    for(int i = 0; i < n; i++){
        res = max(res, query(a[i]));
    }
    cout << res << endl;
}