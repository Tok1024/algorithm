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
// expr → term ('+' | '-' term)* 加减块
// term → factor ( '*' | '/' factor)* 乘除块
// factor → number | (expr) | '-' factor原子

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
    size_t pos;
public:
    Lexer(string& input): s(input), pos(0){};

    vector<Token> tokenize(){
        vector<Token> tokens;
        while(pos < s.size()){
            char c = s[pos];
            if(isspace(c)){
                pos++;
                continue;
            }
            // while(pos < (int(s.size())) && isspace(s[pos])) pos++;
            c = s[pos];
            if(isdigit(c)){
                int x = 0;
                while(pos < s.size() && isdigit(s[pos])){
                    x = 10*x + s[pos]-'0';
                    pos++;
                    // c = s[++pos]; 不要写s[++i]这种！很容易越界
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
        tokens.push_back(Token{TokenKind::Eof});
        return tokens;
    }

};

struct Expr{
    virtual void print() const = 0; // 纯虚函数
    virtual int eval() const = 0;
    virtual ~Expr() = default; // OOP 的习惯，抽象类一定要写虚析构函数，动态绑定子类的析构函数进行销毁
};

struct UnaryExpr: Expr{
    char op;
    unique_ptr<Expr> node;
    UnaryExpr(char op, unique_ptr<Expr> nd): op(op), node(std::move(nd)) {};

    void print() const override{
        cout << "( - ";
        node->print();
        cout << " )";
    }

    int eval() const override{
        return - node->eval();
    };

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
    size_t pos;
public:

    Parser(const vector<Token>& toks): tokens(toks), pos(0){};

    // 查看但不移动指针
    const Token& peek() const {
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
        auto root = parse_expr();
        expect(TokenKind::Eof);
        return root;
    }

    unique_ptr<Expr> parse_expr(){
        unique_ptr<Expr> res = parse_term();

        if(pos >= tokens.size()) return res;
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
        unique_ptr<Expr> res;
        if(match(TokenKind::LParen)){
            res = parse_expr();
            expect(TokenKind::RParen);
        }
        else if(match(TokenKind::Minus)){
            res = parse_factor();
            res = make_unique<UnaryExpr>(
                '-', std::move(res)
            );
        }
        else{
            res = parse_number();
        }
        return res;
    }

    unique_ptr<Expr> parse_term(){
        unique_ptr<Expr> res = parse_factor();

        if(pos >= tokens.size()) return res;
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

    // for(auto& t: tokens){
    //     cout << "{ kind: " << to_string(t.kind) << ", value: " << t.value << " }" << endl;
    // }

    Parser pas(tokens);
    auto root = pas.parse();
    cout << root->eval() << endl;
    root->print();
}