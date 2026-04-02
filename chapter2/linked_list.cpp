#include <iostream>
using namespace std;

/*
这个题比较阴间
要求可以删除第 k 个插入的数后面的一个数；
但这对于普通链表来说是做不到的
我们无法知道链表的节点是第几个插入的，因为会删减，增改
所以不如直接用数组去模拟链表
最关键的地方在于：我们直接按照插入顺序放进数组，但是使用 next, val 来记录链表的信息 
* */
const int N = 1e6+10;
struct linked_list{
    // 索引 idx 本身就是插入的顺序，val 和 next 额外记录
    int val[N], next[N];
    int head = -1, idx = 0; // 链表的入口

    // 头插
    void push_front(int x){
        val[idx] = x;
        next[idx] = head;
        head = idx++;
    }

    // 删除第k个插入的元素之后的一个元素
    void del_k(int k){
        if (!k) head = next[head];
        else if(next[k-1] != -1) next[k-1] = next[next[k-1]];
    }

    // 在第 k 个数后面插入x
    void insert_k(int k, int x){
        val[idx] = x;
        next[idx] = next[k-1];
        next[k-1] = idx++;
    }

    void print_list(){
        for(int p = head; p != -1; p = next[p]){
            cout << val[p] << ' ';
        }
        cout << endl;
    }

};


int main(){
    int m, k, x;
    linked_list list;
    char c;
    cin >> m;
    while(m --){
        cin >> c;
        switch(c){
            case 'H': {
                cin >> x;
                list.push_front(x);
                break;
            };
            case 'D': {
                cin >> k;
                list.del_k(k);
                break;
            }
            case 'I':{
                cin >> k >> x;
                list.insert_k(k, x);
                break;
            }
        }
    }
    list.print_list();
}
