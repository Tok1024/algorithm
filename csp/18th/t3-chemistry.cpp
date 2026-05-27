#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <cctype>

using namespace std;

// ========================================================
// 1. 核心单体化学式解析
// ========================================================
map<string, int> parse_formula(string s) {
    stack<map<string, int>> stk;
    stk.push({}); // 最外层

    int i = 0, n = s.length();
    while (i < n) {
        if (s[i] == '(') {
            stk.push({});
            i++;
        }
        else if (s[i] == ')') {
            // 一个term的结束, 我们找coef
            int coef = 0, j = i+1;
            while(j < s.length() && isdigit(s[j])){
                coef = coef * 10 + (s[j++] - '0');
            }
            auto cur_layer = stk.top();
            stk.pop();
            if(coef==0) coef=1;
            // 有括号的后coef至少是1
            for(auto& m: cur_layer){
                // 把当前层，加到新的top
                stk.top()[m.first] += m.second * coef;
            }
            i = j;
        }
        else if (isupper(s[i])) {
            // 是一个元素
            string ele = "";
            ele += s[i];
            int j = i+1;
            while(j < s.length() && islower(s[j])){
                ele += s[j++];
            }
            int coef = 0;
            while(j < s.length() && isdigit(s[j])){
                coef = coef * 10 + (s[j++] - '0');
            }
            if(coef==0) coef=1;
            stk.top()[ele] += coef;
            i = j;
        }
    }
    return stk.top();
}

// ========================================================
// 2. 解析方程的单侧（处理 "+" 连接的多个化学式及其前导系数）
// ========================================================
map<string, int> parse_side(string side) {
    map<string, int> total_res;
    int start = 0, n = side.length();
    
    // 按 '+' 切分出每一个独立的项（例如 "2H2" 和 "O2"）
    for (int i = 0; i <= n; i++) {
        if (i == n || side[i] == '+') {
            string expr = side.substr(start, i - start);
            
            // 提取前导总系数（如 "2H2" 中的 '2'）
            int coef = 0;
            int j = 0;
            while (j < expr.length() && isdigit(expr[j])) {
                coef = coef * 10 + (expr[j] - '0');
                j++;
            }
            if (coef == 0) coef = 1; // 没写系数默认为 1
            
            // 剩余部分是纯化学式（如 "H2"）
            string formula = expr.substr(j);
            
            // 解析纯化学式，并乘上总系数累加到该侧的总账本中
            auto f_map = parse_formula(formula);
            for (auto& p : f_map) {
                total_res[p.first] += p.second * coef;
            }
            
            start = i + 1; // 移动指针跳过 '+'
        }
    }
    return total_res;
}

// ========================================================
// 3. 主函数：处理输入输出
// ========================================================
int main() {
    // 提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    string line;
    getline(cin, line); // 🔥 关键一步：吃掉读入 n 之后残留在行尾的换行符！

    while (n--) {
        getline(cin, line);

        // 寻找 '=' 将方程式切分为左、右两边
        size_t eq_pos = line.find('=');
        string left_side = line.substr(0, eq_pos);
        string right_side = line.substr(eq_pos + 1);

        // 分别计算两边的原子总数
        map<string, int> left_map = parse_side(left_side);
        map<string, int> right_map = parse_side(right_side);

        // map 之间可以直接使用 == 运算符比较，它会同时比较 key 和 value 是否完全一致
        if (left_map == right_map) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }

    return 0;
}