#include <iostream>
using namespace std;

/* trie
 * trie 是一种高效存储字符串的数据结构
 * 他把字符串当作一个n叉树，每个节点最多有n个子节点，代表字符串里的一个字母
 * 依旧用 idx 标识每个节点，然后使用 son[N][26] 标识节点的可能的子节点
 * 而 cnt[N] 表示以该节点结尾的字符串数量
 * */

const int N = 1e5+10;
int son[N][26], cnt[N], idx;
// 这个 idx 已经用的非常多了，就是对每个链式节点维护一个自增的标识，可以互相通过idx查找
// 有一个哨兵节点，也就是cnt[0] 既表示根节点，又等于0, 因为根节点不可能是结尾（根本没字符）

void insert(char str[]){
    int p = 0; // 从根节点开始爬树
    for(int i = 0; str[i]; i++){
        int u = str[i] - 'a';
        if(son[p][u] == 0) son[p][u] = ++idx; // 不存在就创造一个节点
        p = son[p][u];
    }
    cnt[p]++;
}

int query(char str[]){
    int p = 0; // 从根节点开始搜
    for(int i = 0; str[i]; i++){
        int u = str[i] - 'a';
        if(son[p][u] == 0) return 0;
        p = son[p][u];
    }
    return cnt[p];
}


int main(){
    int n;
    scanf("%d", &n);
    while(n --){
        char str[N], op[2];
        scanf("%s%s", op, str);
        if(op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }
}