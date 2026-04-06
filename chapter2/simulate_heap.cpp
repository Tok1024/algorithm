#include <iostream>
using namespace std;

/*
问题：能否在堆操作中，追踪第 k 个插入的元素？
联想到模拟链表那道题，这个题显然需要我们用数组p[idx]去追踪每一个插入的元素
也就是先维护每一个节点插入的idx，idx->heap索引->heap值
比如删除第k个idx节点，就需要pointer->heap索引的映射，记作 ph
而交换堆节点，需要从heap->pointer的映射，记作hp
其余思路和堆一致
*/

const int N = 1e5+10;

// 数组模拟的最小堆，可以追踪第k个插入节点
struct MinHeap{
    int h[N], ph[N], hp[N]; // h是实际的heap数组，而ph，hp是pointer到heap的双向映射，必须保持一致
    int size = 0, idx = 0;

    int parent(int k) {return k / 2;}
    int lchild(int k) {return k * 2;}
    int rchild(int k) {return k * 2 + 1;}

    // 交换heap的两个节点的值，以及它们对idx的指针
    // 因为如果这两个节点交换了，我们希望用原来的idx找到他们，而非新的idx
    void heap_swap(int a, int b){ // a, b is the index of h
        // 这里一开始需要交换的是a，b对应的 p->h 的指针
        // 因为后面要交换这个反向指针，需要在还正确的时候先交换
        swap(ph[hp[a]], ph[hp[b]]);
        swap(hp[a], hp[b]); // 交换a和b对应的 h -> p 反向映射
        swap(h[a], h[b]); // 最后交换 a, b对应的堆节点的值
    }

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
            heap_swap(p, t);
            p = t;
        }
    }

    void up(int k){
        int p = k;
        while(p > 1 && h[parent(p)] > h[p]){
            heap_swap(parent(p), p);
            p = parent(p);
        }
    }

    void insert(int x){
        ph[++idx] = ++size;
        hp[size] = idx;
        h[size] = x;
        up(size);
    }

    int top() {return h[1];}

    void pop(){
        if(size == 0) return;
        heap_swap(1, size); // 这里的交换节点在下移的过程也需要保持映射
        ph[hp[size]] = -1; // 交换过后，hp[size] 恰好指向 根节点 或者即将被删除的节点的idx
        size--;
        down(1);
    }

    // 删除第k个插入的元素
    void pop_k(int k){
        int pos = ph[k];
        // 这里为什么不能像普通的堆一样，仅仅赋值 h[ph[k]] = h[size--]?
        // 这样只是把末尾的值搬了过来，但是末尾的指针丢失了！
        // 必须依旧使用 heap swap
        heap_swap(pos, size); // 这个交换代表完全交换树节点，包括ph和hp的两个指针
        // 所以交换之后，两个指针也变了，我们需要从被交换到末尾的节点去找到k
        ph[hp[size]] = -1;
        size--;
        up(pos); down(pos);
    }

    // 修改第k个插入的元素
    void update(int k, int x){
        if(ph[k] == -1) return;
        int pos = ph[k];
        h[pos] = x;
        up(pos);
        down(pos);
    }

};

int main(){
    MinHeap pq;
    string op;
    int k, x;
    int n;
    cin >> n;
    while(n --){
        cin >> op;
        if(op == "I"){
            cin >> x;
            pq.insert(x);
        }
        else if (op == "PM") cout << pq.top() << endl;
        else if (op == "DM") pq.pop();
        else if (op == "D") {
            cin >> k;
            pq.pop_k(k);
        }
        else if (op == "C") {
            cin >> k >> x;
            pq.update(k, x);
        }
    }
}