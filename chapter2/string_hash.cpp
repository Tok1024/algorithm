#include <cstddef>
#include <iostream>
using namespace std;

/* 给定一个长度为 n 的字符串，再给定 m
个询问，每个询问包含四个整数 l1,r1,l2,r2
，请你判断 [l1,r1] 和 [l2,r2]
这两个区间所包含的字符串子串是否完全相同。
这个题的暴力做法是遍历两遍，复杂度就是O(mn)，但是每次可能会比较相同的部分
而聪明的做法就是给每个位置的字符一个数字然后加起来，形成一个字符串的hashcode
然后要判断子串，就是比较子数组的和，自然的想法就是比较前缀和是否相等
*/

string s;

typedef unsigned long long ULL;
const int N = 1e5+10, P = 131;// 字符串hash的P常选用131
ULL h[N], p[N]; // h: hashcode of substring of len i, p: p^i

ULL sub_hash(int l, int r){
    // h[r] - h[l-1] * p[len]
    return h[r] - h[l-1] * p[r - l + 1]; // 带权重对齐次方，得到真正子串的hashcode
}

bool check(int l1, int r1, int l2, int r2){
    // return a[r1] - a[l1-1] == a[r2] - a[l2-1]; 应该带权重减，而不是直接减！
    ULL left = sub_hash(l1, r1);
    ULL right = sub_hash(l2, r2);
    return left == right;
}

int main(){
    int n, m;
    cin >> n >> m >> s;
    p[0] = 1;
    // 计算每个位置的hashcode类前缀和
    for(int i = 1; i <= s.size(); i++){
        h[i] = h[i-1] * P + s[i-1]; // 一定要区分索引的模式, 1 or 0
        p[i] = p[i-1] * P;
    }

    int l1, r1, l2, r2;
    while(m --){
        cin >> l1 >> r1 >> l2 >> r2;
        if(check(l1, r1, l2, r2)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

}