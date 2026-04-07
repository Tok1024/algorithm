#include <iostream>
using namespace std;

/* 并查集
并查集disjoint set是一种用于判断集合/图的连通性的数据结构
支持
- isConnected() 判断两个图是否连接
- connect(a, b) 连接两个图

而并查集关键的操作是
- find(a) 顺着叶节点向上找到根节点

并查集维护一个数组 p ，idx对应唯一的节点，数组值p[idx]是父节点的idx，形成了一棵树
只有根节点的数组值等于自身 p[x] = x
*/
const int MAX_SIZE = 1e5;
struct DisjointSet{
    int size = 0;
    int p[MAX_SIZE]; // 简单版本的并查集，只存储1-n的数字

    int find(int x){
        if (p[x] != x) p[x] = find(p[x]); // 递归向上 + 路径压缩
        return p[x];
    }

    void range(int n){
        for(int i = 0; i < n; i++) p[i] = i;
        size = n;
    }

    bool isConnected(int a, int b){
        return find(a) == find(b);
    }

    void connect(int a, int b){
        p[find(a)] = find(b); // 把a的祖宗节点挂到b的祖宗节点下面
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
        if(op == "M"){
            cin >> a >> b;
            ds.connect(a, b);
        }
        else if(op == "Q"){
            cin >> a >> b;
            if(ds.isConnected(a, b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
}