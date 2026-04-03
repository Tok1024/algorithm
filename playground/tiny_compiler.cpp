#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctype.h>
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

void match(char c){
    if(idx >= expr.size()) fail("expected " + format_char(c));
    if(expr[idx] != c) fail("expected " + format_char(c));
    else idx++;
}

// 1. 词法分析
enum class TokenKind {
    Number, Plus, Minus, Star, Slash, LParen, RParen, Eof
};

string to_string(TokenKind kind) {
    switch (kind) {
        case TokenKind::Number: return "Number";
        case TokenKind::Plus:   return "Plus";
        case TokenKind::Minus:  return "Minus";
        case TokenKind::Star:   return "Star";
        case TokenKind::Slash:  return "Slash";
        case TokenKind::LParen: return "LParen";
        case TokenKind::RParen: return "RParen";
        case TokenKind::Eof:    return "Eof";
        default: return "Unknown";
    }
}

struct Token{
    TokenKind kind;
    int value;
};

class Lexer{
private:
    string s;
    int pos;
public:
    Lexer(string& input): s(input), pos(0){};

    vector<Token> tokenize(){
        vector<Token> tokens;
        while(pos < (int)s.size()){
            char c = s[pos];
            if(isspace(c)){
                pos++;
                continue;
            }
            // while(pos < (int(s.size())) && isspace(s[pos])) pos++;
            c = s[pos];
            if(isdigit(c)){
                int x = 0;
                while(isdigit(c)){
                    x = 10*x + c-'0';
                    c = s[++pos];
                }
                tokens.push_back(Token{TokenKind::Number, x});
            }
            else{
                switch(c){
                    case '+': tokens.push_back(Token{TokenKind::Plus, 0}); break;
                    case '-': tokens.push_back(Token{TokenKind::Minus, 0}); break;
                    case '*': tokens.push_back(Token{TokenKind::Star, 0}); break;
                    case '/': tokens.push_back(Token{TokenKind::Slash, 0}); break;
                    case '(': tokens.push_back(Token{TokenKind::LParen, 0}); break;
                    case ')': tokens.push_back(Token{TokenKind::RParen, 0}); break;
                    default: throw runtime_error("invalid character");
                };
                pos ++;
            }

        }
        return tokens;
    }

};

int parse_expr();
int parse_term();
int parse_factor();
int parse_number(){
    size_t i = idx;
    int x = 0;
    if(i >= expr.size()) fail("expected number");
    if(!isdigit(expr[i])) fail("expected number");
    while(i < expr.size() && isdigit(expr[i])){
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
    else if(isdigit(c)){
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
    string s;
    getline(cin, s);
    Lexer lex(s);
    auto tokens = lex.tokenize();
    for(auto& token:tokens){
        cout << "{ kind: " << to_string(token.kind) << ", val: " << token.value << "}" << endl;
    }
}