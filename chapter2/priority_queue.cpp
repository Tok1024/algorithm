#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5+10;

struct MinHeap{
    int h[N];
    int size = 0;

    int parent(int k) {return k / 2;}
    int lchild(int k) {return k * 2;}
    int rchild(int k) {return k * 2 + 1;}

    // version1: 向下传递需要比较左右儿子，但是你也不想在while里比较一百个条件把
    // 建议直接while(True) + break
    // void down(int k){
    //     int p = k;
    //     // 每次调用数组前，一定要检查索引的范围
    //     while(p <= size &&
    //         ((lchild(p) <= size && h[lchild(p)] < h[p]) || 
    //         (rchild(p) <= size && h[rchild(p)] < h[p]))){
    //         if(h[lchild(p)] < h[p]) {
    //             swap(h[lchild(p)], h[p]);
    //             p = lchild(p);
    //         }
    //         else {
    //             swap(h[rchild(p)], h[p]);
    //             p = rchild(p);
    //         }
    //     }
    // }


    // version2: while true + break, 以及down时需要选择左右节点里较小的那个
    // 这里使用一个t去动态比较三者
    void down(int k){
        int p = k;
        while(true){
            int t = p; // t 记录当前节点 p，左右子节点三个节点里的最小值
            if(lchild(p) <= size && h[lchild(p)] < h[t]) t = lchild(p);
            // 这里千万不能用else-if，不然没法判断三者的大小
            if (rchild(p) <= size && h[rchild(p)] < h[t]) t = rchild(p);
            if(t == p) break;
            swap(h[p], h[t]);
            p = t;
        }
    }

    void down_recursion(int k)//调整函数
    {
        //t记录最小点的编号
        int t = k;

        //有左儿子，并且左儿子比t节点的值小，更新t
        if(lchild(k) <= size && h[lchild(k)] < h[t]) t = lchild(k);
        if(rchild(k) <= size && h[rchild(k)] < h[t]) t = rchild(k);

        if(t != k){
            swap(h[t], h[k]);
            down_recursion(t);
        }
    }

    void up(int k){
        int p = k;
        while(p > 1 && h[parent(p)] > h[p]){
            swap(h[parent(p)], h[p]);
            p = parent(p);
        }
    }

    void insert(int x){
        h[++size] = x;
        up(size);
    }

    int top() {return h[1];}

    void pop(){
        if(size == 0) return;
        h[1] = h[size--];
        down_recursion(1);
    }

    // 删除第k个元素
    void pop_k(int k){
        if(size < k) return;
        h[k] = h[size--];
        up(k); down(k);
    }

    // 修改第k个元素
    void update(int k, int x){
        h[k] = x;
        up(k);
        down(k);
    }

    void from_vector(vector<int> nums){
        size = nums.size();
        for(int i = 0; i < size; i++) h[i+1] = nums[i];
        for(int i = size / 2; i >= 1; i--) down(i);
    }

    void sort(){
        for(int i = size / 2; i >= 1; i--) down(i);
    }


};

int main(){
    MinHeap pq;
    int m, n;
    cin >> n >> m;
    pq.size = n;
    for(int i = 1; i <= n; i++) {
        cin >> pq.h[i];
    }
    pq.sort();
    while(m--){
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << endl;
}