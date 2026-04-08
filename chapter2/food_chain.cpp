#include <iostream>
using namespace std;

/* 食物链
题目：
动物王国中有三类动物 A,B,C
，这三类动物的食物链构成了有趣的环形。
A 吃 B，B 吃 C，C 吃 A
现有 N 个动物，以 1∼N 编号。
每个动物都是 A,B,C 中的一种，但是我们并不知道它到底是哪一种。
有人用两种说法对这 N 个动物所构成的食物链关系进行描述：
第一种说法是 1 X Y，表示 X 和 Y 是同类。
第二种说法是 2 X Y，表示 X 吃 Y
此人对 N 个动物，用上述两种说法，一句接一句地说出 K 句话，这 K 句话有的是真的，有的是假的。

当一句话满足下列三条之一时，这句话就是假话，否则就是真话。
当前的话与前面的某些真的话冲突，就是假话；
当前的话中 X 或 Y 比 N 大，就是假话；
当前的话表示 X 吃 X，就是假话。
你的任务是根据给定的 N 和 K 句话，输出假话的总数。

思路：
这个题看上去很抽象，实际上是让我们检查关系是否成立，这就让我想起了并查集
但是并查集只能检查连通性
所以我们就需要维护每个节点与根节点的关系

如何表示关系？
我们用0, 1, 2表示A，B，C
就有0->1->2->0...... 的模运算关系
代码里用d[x]维护a->root的关系，b->root的关系
那么如果a和b的root相同，
定义关系 (type[y] - type[x]) mod 3 就可以将关系通过root传递
1就是吃，2就是被吃，0就是同类

我们用d[]表示x到根节点的距离（真正的距离），然后只需要判断这个距离的模就可以判断关系
*/

const int N = 1e5;
// d: x到root节点的距离
// 显然距离可以相加
int p[N], d[N];

int find(int x){
    if(p[x] != x) {
        int root = find(p[x]);
        d[x] += d[p[x]]; // 把父节点的关系传递下来, 路径压缩
        p[x] = root;
    }
    return p[x];
}

int relation(int x, int y){
    return ((x - y) % 3 + 3) % 3;
}

int main(){
    int n, k, D, x, y, cnt=0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
            p[i] = i;
            d[i] = 0;
    }

    while(k--){
        cin >> D >> x >> y;
        if((D == 2 && x == y) || x > n || y > n) {
            cnt++; continue;
        }

        int px = find(x), py = find(y);
        if(px == py){
            // 这两个节点已经比较过了(在同一棵树上)，我们判断一下关系是否成立
            if(D == 1 && relation(d[x], d[y])) cnt++; // x == y
            if(D == 2 && relation(d[x], d[y])-1) cnt++; // x eat y
        }
        else{
            // 没比较过，那只能当真啦
            p[px] = py;
            // d[px] = d[y] - d[x] + relation
            // 挂载a的树到b上，使得a和b的关系成立
            // 为了满足 d[px] + d[x] = d[y], 也就是x，y等价
            if(D == 1) d[px] = d[y] - d[x]; // x, y等价
            else d[px] = d[y] + 1 - d[x]; // x eat y
        }
    }
    cout << cnt << endl;
}