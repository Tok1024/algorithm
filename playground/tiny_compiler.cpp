#include <cctype>
#include <cstddef>
#include <iostream>
#include <memory>
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

string format_char(char c) {
    return string("'") + c + "'";
}

[[noreturn]] void fail(const string& msg){
    throw runtime_error("Parse error : " + msg);
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
    int value = 0;
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
                    case '+': tokens.push_back(Token{TokenKind::Plus}); break;
                    case '-': tokens.push_back(Token{TokenKind::Minus}); break;
                    case '*': tokens.push_back(Token{TokenKind::Star}); break;
                    case '/': tokens.push_back(Token{TokenKind::Slash}); break;
                    case '(': tokens.push_back(Token{TokenKind::LParen}); break;
                    case ')': tokens.push_back(Token{TokenKind::RParen}); break;
                    default: throw runtime_error("invalid character");
                };
                pos ++;
            }

        }
        return tokens;
    }

};

struct Expr{
    virtual void print() const = 0; // 纯虚函数
    virtual int eval() const = 0;
};

struct BinaryExpr: Expr{
    unique_ptr<Expr> l, r;
    char op;
    // unique 指针不能拷贝复制，必须 move
    BinaryExpr(char op, unique_ptr<Expr> left, unique_ptr<Expr> right): 
    op(op), l(std::move(left)), r(std::move(right)) {};
    void print() const override{
        cout << '(';
        l->print();
        cout << ' ' <<  op << ' ';
        r->print();
        cout << ')';
    };
    int eval() const override{
        int res = 0, a = l->eval(), b = r->eval();
        switch(op){
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/': res = a / b; break;
        }
        return res;
    }
};

struct NumberExpr: Expr{
    int val;
    NumberExpr(int x): val(x){};
    void print() const override{
        cout << val;
    };
    int eval() const override{
        return val;
    }
};

class Parser{
private:
    vector<Token> tokens;
    int pos;
public:

    Parser(const vector<Token>& toks): tokens(toks), pos(0){};

    // 查看但不移动指针
    const Token& peek(){
        return tokens[pos];
    }

    // 检查是否匹配 t
    bool match(TokenKind t){
        if(tokens[pos].kind == t){
            pos++;
            return true;
        }
        return false;
    }

    // 确定是 t，不匹配就报错
    void expect(TokenKind t){
        if(tokens[pos].kind == t){
            pos++;
        }
        else{
            string msg = "token type not match, expect:" + to_string(t) + ", got" + to_string(tokens[pos].kind);
            fail(msg);
        }
    }

    unique_ptr<Expr> parse(){
        return parse_expr();
    }

    unique_ptr<Expr> parse_expr(){
        unique_ptr<Expr> res = parse_term();

        if(pos >= (int)tokens.size()) return res;
        auto t = tokens[pos];

        while(t.kind == TokenKind::Plus || t.kind == TokenKind::Minus){
            pos++;
            auto b = parse_term();

            if(t.kind == TokenKind::Plus){
                res = make_unique<BinaryExpr>(
                    '+', std::move(res), std::move(b)
                );
            }
            else if(t.kind == TokenKind::Minus){
                res = make_unique<BinaryExpr>(
                    '-', std::move(res), std::move(b)
                );
            }

            if(pos >= tokens.size()) break;
            t  = tokens[pos];
        }

        return res;
    }

    unique_ptr<Expr> parse_number(){
        if(peek().kind != TokenKind::Number) throw runtime_error("not a number");
        int val = peek().value;
        pos++;
        return make_unique<NumberExpr>(val);
    }

    unique_ptr<Expr> parse_factor(){
        if(pos >= tokens.size()) fail("expected factor: number or (");
        auto token = tokens[pos];
        unique_ptr<Expr> res;
        if(match(TokenKind::LParen)){
            res = parse_expr();
            expect(TokenKind::RParen);
        }
        else{
            res = parse_number();
        }
        return res;
    }

    unique_ptr<Expr> parse_term(){
        unique_ptr<Expr> res = parse_factor();

        if(pos >= (int)tokens.size()) return res;
        auto t = tokens[pos];
        if(t.kind == TokenKind::Plus || t.kind == TokenKind::Minus || t.kind == TokenKind::RParen) return res;

        while(t.kind == TokenKind::Slash || t.kind == TokenKind::Star){
            pos++;
            auto b = parse_factor();

            if(t.kind == TokenKind::Star){
                res = make_unique<BinaryExpr>(
                    '*', std::move(res), std::move(b)
                );
            }
            else if(t.kind == TokenKind::Slash){
                if(b->eval() == 0) fail("devide by zero");
                res = make_unique<BinaryExpr>(
                    '/', std::move(res), std::move(b)
                );
            }

            if(pos >= tokens.size()) break;
            t  = tokens[pos];
        }

        return res;

    }

    void print_ast(const unique_ptr<Expr>& root){
        root->print();
    }

};

int main(){
    string s;
    getline(cin, s);
    Lexer lex(s);
    auto tokens = lex.tokenize();

    for(auto& t: tokens){
        cout << "{ kind: " << to_string(t.kind) << ", value: " << t.value << " }" << endl;
    }

    Parser pas(tokens);
    auto root = pas.parse();
    cout << root->eval() << endl;
    root->print();
}