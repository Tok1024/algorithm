#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


const int N = 1e5;
struct que{
    int data[N];
    int front = 0, back = 0; //左闭右开，数据范围是 [front, back）

    void push(int x){
        data[back++] = x;
    }

    bool empty(){
        return front == back;
    }

    void pop(){
        if(empty()){
            string msg = "queue is empty, can't pop";
            throw runtime_error(msg);
        }
        front++;
    }

    int query(){
        if(empty()) return 404;
        return data[front];
    }

    void print(){
        for(int i = front; i < back; i++){
            cout << data[i] << ' ';
        }
        cout << endl;
    }
};

int main(){
    que q;
    string op; int x, m;
    cin >> m;
    while(m--){
        cin >> op;
        if(op == "push"){
            cin >> x;
            q.push(x);
        }
        else if (op == "pop") {
            q.pop();
        }
        else if (op == "empty") {
            if(q.empty()) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        else if(op == "query"){
            cout << q.query() << endl;
        }
        else if(op == "print"){
            q.print();
        }
    }
}