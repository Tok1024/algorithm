#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

// 给定一个表达式，其中运算符仅包含 +,-,*,/
// 可能包含括号，请你求出表达式的最终值。

// 思路：这道题有两个方法
// 1. 简单但巧妙，双栈法
// 如果当前运算符优先级 ≤ 栈顶运算符 → 先算栈顶
// 按这样的顺序就可以构建出 AST

// 2. 递归下降，写 expr，term，factor的分析函数，然后相互调用

stack<char> op;
stack<int> num;
unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

void eval(){
    int b = num.top(); num.pop();
    int a = num.top(); num.pop();
    char c = op.top(); op.pop();
    int res;
    switch (c) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
    }
    num.push(res);
}

bool is_digit(char c){
    return c >= '0' && c <= '9';
}

int main(){
    string exp;
    cin >> exp;
    for(int i = 0; i < exp.size(); i++){
        char c = exp[i];
        if(is_digit(c)) {
            // num.push(c-'0'); 这是错的，有可能有1000这样的多位数字
            int x = 0, j;
            for(j = i ; j < exp.size() && is_digit(exp[j]); j++){
                x = 10 * x + (exp[j] - '0');
            }
            i = j - 1;
            num.push(x);
        }
        else if(c == '(') op.push(c);
        else if(c == ')'){
            while(!op.empty() && op.top() != '(') eval();
            op.pop();
        }
        else{
            while(!op.empty() && pr[op.top()] >= pr[c]) eval();
            op.push(c);
        }
    }
    while(!op.empty()) eval();
    cout << num.top() << endl;
}