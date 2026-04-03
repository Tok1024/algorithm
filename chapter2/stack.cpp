#include <iostream>
using namespace std;

const int N = 1e5;
struct stk{
    int a[N];
    int top = 0;

    void push(int x){
        a[top++] = x;
    }

    int query(){
        return a[top-1];
    }

    void pop(){
        top--;
    }

    bool empty(){
        return top == 0;
    }
};

int main(){
    int m, x;
    string op;
    stk s;
    cin >> m;
    while(m--){
        cin >> op;
        if(op == "push"){
            cin >> x;
            s.push(x);
        }
        else if(op == "pop") s.pop();
        else if(op == "empty"){
            if (s.empty()) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        else if(op == "query") cout << s.query() << endl;
    }
}