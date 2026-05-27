#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<string, string> table;
unordered_set<string> indirect;

string get_value(string s){
    if(table.count(s)) return table[s];
    else return "";
}

// string eval(string s){
//     string res;
//     int i = 0;
//     while(i < s.length() && s[i] == ' ')i++;
//     for(; i < s.length(); i++){
//         if(s[i] == '$'){
//             i++;
//             string var;
//             while(i < s.length() && s[i] != ' '){
//                 var += s[i++];
//             }
//             // cout << "var:" << var << " value: " << get_value(var) << endl;
//             res += get_value(var);
//         }
//         else if(s[i] == ' '){
//             while(i < s.length() && s[i]==' ') i++;
//             i--;
//         }
//         else{
//             while(i < s.length() && s[i] != ' '){
//                 res += s[i++];
//             }
//         }
//     }
//     // cout << "input: "<< s << " output: " << res << endl;
//     return res;
// }

// 对于变量，仅仅eval，getvalue是不够的，必须递归的获取值，直到不存在变量
// 同时需要避免出现环路，否则会死循环
string eval_var(const string& s, unordered_set<string>& visiting){

}


string expand(const string& s) {
    string res;
    int i = 0;
    int n = s.size();
    while (i < n && s[i] == ' ') i++;
    while (i < n) {
        if (s[i] == '$') {
            i++;
            string var;
            while (i < n && s[i] != ' ') {
                var += s[i];
                i++;
            }
            res += get_value(var);
        } else {
            res += s[i];
            i++;
        }
    }
    return res;
}

int main(){
    int n, op;
    string var, value;
    cin >> n;
    while(n--){
        cin >> op;
        if(op == 1){
        // 直接插入变量
        cin >> var;
        getline(cin, value);
        // cout << value << endl;
        string content = eval(value);
        table[var] = content;
        }else if (op == 2) {
            // 间接插入变量
            cin >> var; getline(cin, value);
            table[var] = value;
            indirect.insert(var);
        }else {
            // 打印
            cin >> var;
            if(indirect.count(var)){
                cout << eval(get_value(var)).length() << endl;
            }else{
                cout << get_value(var).length() << endl;
            }
        }
    }
}