#include <iostream>
#include <stack>
using namespace std;


// 单调栈
// 问题：求数组元素 a[i] 左侧最近最小的元素
// 朴素方法：双重循环遍历
// 聪明方法：利用大小关系的传递性
// 如果 a[i] 把 a[j] 淘汰了，那么未来任何元素都不需要再考虑 a[j]
// 可以对每个 a[i] 维护一个stack并动态更新
// 爽点：栈中元素形成一个链式单调结构，并且这个关系是传递闭包的

const int N = 1e5;
int a[N];
int b[N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);

    stack<int> s;

    for(int i = 0; i < n; i++){
        // 1. 计算左侧最小元素
        while(!s.empty() && s.top() >= a[i]) s.pop();

        // 2. 记录答案
        if(s.empty()) b[i] = -1;
        else b[i] = s.top();

        // 3. 入栈
        s.push(a[i]);
    }

    for(int i = 0; i < n; i++) cout << b[i] << ' ';
    cout << endl;

}