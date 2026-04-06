#include <iostream>
#include <vector>
using namespace std;

/* 模拟哈希表
实现哈希表有两种方法
1. 拉链法：每个bucket是一个链表 <- STL unordered_map/set
2. 开放寻址法：冲突就往后放
*/

const int N = 10003, M = 10010; // 数据范围是 [1, 1e5],那我们就开这个数字开始的最大质数

struct HashTable{
    int idx = 0; // 链表的索引
    vector<int> h = vector<int>(N, -1); // 存索引的主hash表，N由hash function决定，尽量选质数
    vector<int> e = vector<int>(M); // 每个bucket里的链表， M由元素个数决定
    vector<int> ne = vector<int>(M);
    int hashcode(int x){
        return (x % N + N) % N; // 处理负数的模，也是正数
    }

    bool query(int x){
        int hcode = hashcode(x);
        int p = h[hcode];
        while(p != -1){
            if(e[p] == x) return true;
            p = ne[p];
        }
        return false;
    }

    void insert(int x){
        if(query(x)) return;
        int hcode = hashcode(x);
        e[idx] = x;
        ne[idx] = h[hcode];
        h[hcode] = idx;
        idx++;
    }
};

int main(){
    int x, m;
    string s;
    HashTable h;
    cin >> m;
    while(m--){
        cin >> s >> x;
        if(s == "I"){
            h.insert(x);
        }
        else if(s == "Q"){
            if(h.query(x)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}