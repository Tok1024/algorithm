#include <iostream>
using namespace std;

// 递归下降法计算表达式求值
// 输入：1000*(3+5)
// 文法：
// expr → term (+|-) term 加减块
// term → factor (*|/) factor 乘除块
// factor → number | (expr) 原子

// 基于以上问题实现一个小型的编译器
// 可以构建 AST，并基于AST求值

string expr;
int idx = 0; // 全局指针
bool ok = true; // 全局状态管理

int panic(){
    ok = false;
    cout << "114514" << endl;
    return -114514;
}

bool is_digit(char c) {
    return c <= '9' && c >= '0';
}

void match(char c){
    if(expr[idx] != c){
        panic();
    }
    else idx++;
}

int parse_expr();
int parse_term();
int parse_factor();
int parse_number(){
    int i = idx, x = 0;
    if(!is_digit(expr[i])) return panic();
    while(i < expr.size() && is_digit(expr[i])){
        x = x * 10 + (expr[i] - '0');
        i++;
    }
    idx = i;
    return x;
}

int parse_factor(){
    // 查看first集
    char c = expr[idx];
    int res;
    if(c == '('){
        match('(');

        res = parse_expr();
        if(!ok) return panic();

        match(')');
        if(!ok) return panic();
    }
    else if(is_digit(c)){
        res = parse_number();
        if(!ok) return panic();
    }
    else{
        ok = false;
        return 0;
    }
    return res;
}

int parse_term(){
    int res, b;

    res = parse_factor();
    if(!ok) return panic();

    // char c = expr[idx++]; 这里可能直接就结束了，不一定要继续parse
    char c = expr[idx];
    if(idx == expr.size() || c == '+' || c == '-' || c == ')') return res;

    while(c == '*' || c == '/'){
        idx++;
        b = parse_factor();
        if(!ok) return panic();

        if(c == '*') res *= b;
        else if(c == '/') res /= b;
        else return panic();
        c = expr[idx];
    }
    // else return panic();
    return res;
}

int parse_expr(){
    int b, res;

    res = parse_term();
    if(!ok) return panic();

    // char c = expr[idx++]; 这里可能直接就结束了，不一定要继续parse

    char c = expr[idx];
    if(idx == expr.size()) return res;

    while(c == '+' || c == '-'){
        idx++;
        b = parse_term();
        if(!ok) return panic();

        if(c == '+') res += b;
        else if(c == '-') res -= b;
        else return panic();
        c = expr[idx];
    }

    return res;
}

int main(){
    cin >> expr;
    int res = parse_expr();
    cout << res << endl;
}