#include <iostream>
using namespace std;

/* 并查集
在并查集的基础上记录每个集合的大小
*/
const int MAX_SIZE = 1e5;
struct DisjointSet{
    int p[MAX_SIZE], size[MAX_SIZE]; // 简单版本的并查集，只存储1-n的数字

    int find(int x){
        if (p[x] != x) p[x] = find(p[x]); // 递归向上 + 路径压缩
        return p[x];
    }

    void range(int n){
        for(int i = 1; i <= n; i++) {
            p[i] = i;
            size[i] = 1;
        }
    }

    bool isConnected(int a, int b){
        return find(a) == find(b);
    }

    void connect(int a, int b){
        int pa = p[a], pb = p[b]; // 需要先判断是否是同一棵树
        if(pa == pb) return;
        size[pb] += size[pa];
        p[pa] = find(pb); // 把a的祖宗节点挂到b的祖宗节点下面
    }

    int count(int x){
        return size[find(x)];
    }

};

int main(){
    DisjointSet ds;
    string op;
    int a, b, n, m;
    cin >> n >> m;
    ds.range(n);
    while(m--){
        cin >> op;
        if(op == "C"){
            cin >> a >> b;
            ds.connect(a, b);
        }
        else if(op == "Q1"){
            cin >> a >> b;
            if(ds.isConnected(a, b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
        else if(op == "Q2"){
            cin >> a;
            cout << ds.count(a) << endl;
        }
    }
}