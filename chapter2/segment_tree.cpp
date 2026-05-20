#include <iostream>
using namespace std;

/*线段树
一种高效查询和修改区间和的数据结构
相比于前缀和高速查询O(1)但是慢速修改O(N)
线段树把数组的求和放到了一颗二叉树上
从而使得查询和修改都是O(logN)
*/

const int N = 1e5+10;
int a[N], tree[4*N], lazy[4*N];
int n;

// 递归的构建一棵树
// node: 树节点
// start, end: 树节点的管辖范围
void build(int node, int start, int end){
    if(start == end) tree[node] = a[start];
    else{
        // 多个区间的情况
        int mid = start + (end - start) / 2, lchild = 2 * node, rchild = lchild+1;
        build(lchild, start, mid);
        build(rchild, mid+1, end);
        tree[node] = tree[lchild] + tree[rchild];
    }
    lazy[node] = 0;
}

// 不变量：tree的节点值已经修改过了！因为后续要直接使用
// 这里做的是不修改tree节点，而是把节点的lazy加载传递下去，传递一层！
void push_down(int node, int start, int end){
    int val = lazy[node];
    if(val == 0) return;
    // leaf
    if(start == end){
        tree[node] = 0;
        return;
    }
    else{
        int lchild = 2 * node, rchild = 2 * node + 1;
        int mid = start + (end - start) / 2;
        // tree[node] += (end - start + 1) * val;
        tree[lchild] += (mid - start + 1) * val;
        tree[rchild] += (end - mid) * val;
        lazy[lchild] = val;
        lazy[rchild] = val;
    }
    lazy[node] = 0;
}

// 查询区间 [l, r]的和
// start， end： 由父节点确定的当前节点的管辖范围
int query(int node, int l, int r, int start, int end){
    if(l > r) return 0;
    // 如果不相交，直接返回
    if(r < start || l > end) return 0;
    // 如果当前节点被目标区间完全包含，返回当前节点的和
    if(l <= start && r >= end) return tree[node];
    push_down(node, start, end);
    // 否则要分别对左右子树递归调用
    int mid = start + (end - start) / 2, lchild = 2 * node, rchild = lchild+1;
    return query(lchild, l, r, start, mid) + query(rchild, l, r, mid+1, end);
}

void add(int node, int l, int r, int start, int end, int val){
    // 1. 没重叠
    if(l > end || r < start) return;
    // 2. leaf
    if(start == end) tree[node] += val;
    // 3. 完全包括
    else if(end <= r && start >= l){
        lazy[node] += val;
        tree[node] += (end - start + 1) * val;
    }
    // 4. 不完全包括
    else {
        push_down(node, start, end);
        int mid = start + (end - start) / 2, lchild = 2 * node, rchild = lchild+1;
        add(lchild, l, r, start, mid, val);
        add(rchild, l, r, mid+1, end, val);
        tree[node] = tree[lchild] + tree[rchild];
    }
}

// 给区间 [l, r] + val
void update(int l, int r, int val){
    add(1, l, r, 0, n-1, val);
}

int find(int l, int r){
    return query(1, l, r, 0, n-1);
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    build(1, 0, n-1);
    cout << find(1, 2) << endl;
    update(0, 2, 3);
    cout << find(1, 2) << endl;
}