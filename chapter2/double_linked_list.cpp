#include <iostream>
using namespace std;

const int N = 1e5;

struct double_linked_list{
    int val[N], l[N], r[N];
    int head = 0, tail = 1, idx = 2;

    double_linked_list(){
        init();
    }

    void init(){
        idx = 2;
        l[head] = tail;
        r[head] = tail;
        l[tail] = head;
        r[tail] = head;
    }
    // 1. L x, 表示在链表的最左端插入数X
    // 2. R x, 表示在链表的最右端插入数X
    // 3. D k, 表示将第k个插入的数删除
    // 4. IL k x, 表示在第k个插入的数左侧插入一个数
    // 5. IR K ×, 表示在第k个插入的数右侧插入一个数

    void push_front(int x){
        val[idx] = x;
        r[idx] = r[head];
        l[r[head]] = idx;
        l[idx] = head;
        r[head] = idx;
        idx++;
    }

    void push_back(int x){
        val[idx] = x;
        r[idx] = tail;
        r[l[tail]] = idx;
        l[idx] = l[tail];
        l[tail] = idx;
        idx++;
    }

    void del_k(int k){
        k = k + 1;
        r[l[k]] = r[k];
        l[r[k]] = l[k];
    }

    void insert_left(int k, int x){
        k = k + 1;
        val[idx] = x;
        r[idx] = k;
        l[idx] = l[k];
        r[l[k]] = idx;
        l[k] = idx;
        idx++;
    }

    void insert_right(int k, int x){
        k = k + 1;
        val[idx] = x;
        l[idx] = k;
        r[idx] = r[k];
        l[r[k]] = idx;
        r[k] = idx;
        idx++;
    }

    void print_list(){
        for(int p = r[head]; p != tail; p = r[p]){
            cout << val[p] << ' ';
        }
        cout << endl;
    }

};

int main(){
    int m, k, x;
    double_linked_list list;
    string s;
    cin >> m;
    while(m --){
        cin >> s;
        if(s == "L"){
            cin >> x;
            list.push_front(x);
        }
        else if(s == "R"){
            cin >> x;
            list.push_back(x);
        }
        else if(s == "D"){
            cin >> k;
            list.del_k(k);
        }
        else if(s == "IL"){
            cin >> k >> x;
            list.insert_left(k, x);
        }
        else if(s == "IR"){
            cin >> k >> x;
            list.insert_right(k, x);
        }
    }
    list.print_list();
}