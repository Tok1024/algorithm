#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// 递归下降法计算表达式求值
// 输入：1000*(3+5)
// 文法：
// expr → term (+|-) term 加减块
// term → factor (*|/) factor 乘除块
// factor → number | (expr) 原子

string expr;
size_t idx = 0; // 全局指针

string format_char(char c) {
    return string("'") + c + "'";
}

[[noreturn]] void fail(const string& msg){
    string got = (idx < expr.size()) ? format_char(expr[idx]) : string("EOF");
    throw runtime_error("Parse error at pos " + to_string(idx) + ": " + msg + ", got " + got);
}

bool is_digit(char c) {
    return c <= '9' && c >= '0';
}

void match(char c){
    if(idx >= expr.size()) fail("expected " + format_char(c));
    if(expr[idx] != c) fail("expected " + format_char(c));
    else idx++;
}

int parse_expr();
int parse_term();
int parse_factor();
int parse_number(){
    size_t i = idx;
    int x = 0;
    if(i >= expr.size()) fail("expected number");
    if(!is_digit(expr[i])) fail("expected number");
    while(i < expr.size() && is_digit(expr[i])){
        x = x * 10 + (expr[i] - '0');
        i++;
    }
    idx = i;
    return x;
}

int parse_factor(){
    // 查看first集
    if(idx >= expr.size()) fail("expected factor: number or '('");
    char c = expr[idx];
    int res;
    if(c == '('){
        match('(');

        res = parse_expr();
        match(')');
    }
    else if(is_digit(c)){
        res = parse_number();
    }
    else{
        fail("expected factor: number or '('");
    }
    return res;
}

int parse_term(){
    int res, b;

    res = parse_factor();

    // char c = expr[idx++]; 这里可能直接就结束了，不一定要继续parse
    if(idx >= expr.size()) return res;
    char c = expr[idx];
    if(c == '+' || c == '-' || c == ')') return res;

    while(c == '*' || c == '/'){
        idx++;
        b = parse_factor();

        if(c == '*') res *= b;
        else if(c == '/') {
            if(b == 0) fail("division by zero");
            res /= b;
        }

        if(idx >= expr.size()) break;
        c = expr[idx];
    }
    return res;
}

int parse_expr(){
    int b, res;

    res = parse_term();

    // char c = expr[idx++]; 这里可能直接就结束了，不一定要继续parse
    if(idx >= expr.size()) return res;
    char c = expr[idx];

    while(c == '+' || c == '-'){
        idx++;
        b = parse_term();

        if(c == '+') res += b;
        else if(c == '-') res -= b;

        if(idx >= expr.size()) break;
        c = expr[idx];
    }

    return res;
}

int main(){
    try {
        cin >> expr;
        int res = parse_expr();
        if(idx != expr.size()) fail("unexpected trailing tokens");
        cout << res << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}