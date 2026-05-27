#include <bitset>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
using namespace std;


// 首先这题最重要的就是键值对怎么表示？
// 感觉用pair<string, string> 表示 key: value 就可以
// 静态表和动态表，动态表用deque就可以，动态表要维护固定长度的deque
// 霍夫曼解码？暂时放弃

int s, d;
typedef pair<string, string> kv;
vector<kv> static_table;
deque<kv> dynamic_table;
// 处理huffman tree的方法：递归建树，再dfs遍历得到路径匹配
// 既然题里面给出了0,1也就是内部节点/叶子节点，一定利用起来
string str;
int idx;
unordered_map<string, char> huffman_code;

struct TreeNode{
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    char ch;
};

TreeNode* build(){
    // 注意到了么，这就是递归下降啊！
    // 有一个标记，作为token的类型！
    auto node = new TreeNode();
    if(str[idx] == '0'){
        idx++;
        node->left = build();
        node->right = build();
    }
    else if(str[idx] == '1'){
        node->ch = str[++idx];
        idx++;
    }
    return node;
}

void print_tree(TreeNode* node){
    if(node->left == nullptr && node->right == nullptr){
        cout << '1' << node->ch;
    }
    else{
        cout << '0';
        print_tree(node->left);
        print_tree(node->right);
    }
    // cout << endl;
}

void dfs(TreeNode* node, string prefix){
    if(node->left == nullptr){
        huffman_code.insert({prefix, node->ch});
    }
    else{
        dfs(node->left, prefix+"0");
        dfs(node->right, prefix+"1");
    }
}

void ref_table(int i){
    if(i <= s)
        cout <<  static_table[i-1].first + ": " + static_table[i-1].second << endl;
    else{
        cout << dynamic_table[i-s-1].first + ": " + dynamic_table[i-s-1].second << endl;
    }
}

string ref_table_key(int i){
    if(i <= s)
        return static_table[i-1].first;
    else{
        return dynamic_table[i-s-1].first;
    }
}

string hex_2_binary(string s){
    // 把16进制的huffman编码的字符串转换成二进制
    // s结尾表示填充0的次数，记得最后截断，只返回有效的二进制串
    int truncate = s.back()-'0';
    string output;
    for(int i = 1; i < s.length()-2; i++){
        // 从H后第一个字母遍历，先把16进制转换成2进制数字
        // 再创建一个bitset<4>(x),二进制容器，调用tostring
        int n = stoi(string(1,s[i]), nullptr, 16);
        output+= bitset<4>(n).to_string();
    }
    // cout << output << endl;
    output = output.substr(0, output.length()-truncate);
    // cout << output << endl;
    return output;
}

string decode_huffman(string s){
    if(s.length() == 0) return "";
    if(s.length() >= 2 && s[0] == 'H' && s[1] == 'H') return s.substr(1);
    if(s[0] != 'H') return s;
    // 以H开头，要进行huffman解码
    // 思路还是比较清晰的，我们动态检查前缀prefix是否在huffman_code里，是的话就解码
    // 但是首先要把s从16进制转换成2进制
    s = hex_2_binary(s);
    string output, prefix;
    for(int i = 0; i < s.length(); i++){
        // cout << prefix << endl;
        prefix += s[i];
        if(huffman_code.count(prefix)){
            output += huffman_code[prefix];
            prefix = "";
        }
    }
    // cout << output << endl;
    return output;
}

void dynamic_insert(kv p){
    if(dynamic_table.size() == d) dynamic_table.pop_back();
    dynamic_table.push_front(p);
}

int main(){
    cin >> s >> d;
    for(int i = 0; i < s; i++){
        string key, value;
        cin >> key >> value;
        static_table.push_back({key, value});
    }
    cin >> str;
    auto node = build();
    dfs(node, "");
    // for(auto p: huffman_code){
    //     cout << p.first << ":" << p.second << endl;
    // };
    int n, op, index;
    string key, value;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> op;
        if(op == 1){
            // 表格引用
            cin >> index;
            ref_table(index);
        }
        else{
            // 字面量
            cin >> index;
            if(index == 0){
                // 用字符串作为key
                cin >> key;
                key = decode_huffman(key);
            }else{
                key = ref_table_key(index);
            }
            cin >> value;
            value = decode_huffman(value);
            // cout << "test" << key << ": " << value << endl;
            if(op == 2){
                dynamic_insert({key, value});
            }
            cout << key << ": " << value << endl;
        }
    }
}