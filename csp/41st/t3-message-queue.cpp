#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct FreeBlock{
    long long l, r, len;
    // 重载 <, 配合set的lower_bound，找出最优的block
    // cpp的set是红黑树，有顺序, 要给出排序(重载），或者声明的时候给比较器
    // bool operator<(const FreeBlock& other) const {
    //     if(len != other.len) return len < other.len;
    //     return l < other.l;
    // }
    FreeBlock(long long l, long long len){
        this->l = l;
        this->len = len;
        this->r = l + len - 1;
    }
};

struct BySize{
    bool operator()(const FreeBlock& a, const FreeBlock& b) const {
        if(a.len != b.len) return a.len < b.len;
        return a.l < b.l; // 比较器要求的都是小于关系
    }
};

struct ByAddr{
    bool operator()(const FreeBlock& a, const FreeBlock& b) const {
        return a.l < b.l;
    }
};

const long long MAX_ADDR = 1e18;
FreeBlock initial_block = FreeBlock(0, MAX_ADDR);
// 为了实现删除，我们需要能同时通过大小（找到空闲块）和地址（合并地址）操作
// set<FreeBlock> memory = {FreeBlock(0, MAX_ADDR)};
set<FreeBlock, BySize> free_by_size = {initial_block};
set<FreeBlock, ByAddr> free_by_addr = {initial_block};

struct Interface{
    long long size, start, idx, end;
    bool is_empty;
    int next_idx(){
        if(is_empty) {
            is_empty = false;
            return start;
        }
        else if(idx != end) return idx+1;
        return start;
    }
    Interface(long long l, long long length){
        this->idx = 0;
        this->start = l;
        this->size = length;
        this->end = this->start+ this->size - 1;
        this->is_empty = true;
    }
};

struct Process{
    vector<Interface> queue;
};

void handle_send(Process& p){
    long long sum = 0;
    for(auto& iterface: p.queue){
        long long idx = iterface.next_idx();
        sum += idx;
        iterface.idx = idx;
    }
    cout << sum << endl;
}

void handle_new(Process& p, int length){
    FreeBlock target = FreeBlock(0, length);
    auto best_block = free_by_size.lower_bound(target);
    if(best_block == free_by_size.end()){ // 正确的判空姿势
        // cout << "no space left" << endl;
        return;
    }
    // 这一块分配 length 给 p，剩余部分拆分
    // 1. 分配
    Interface t = Interface(best_block->l, length);
    p.queue.push_back(t);

    // 2. 重组磁盘块
    // 如果还剩下内存，插入回去
    if (best_block->len > length){
        free_by_size.insert(FreeBlock(best_block->l + length, best_block->len - length));
        free_by_addr.insert(FreeBlock(best_block->l + length, best_block->len - length));
    }
    cout << best_block->l << endl;
    FreeBlock temp = *best_block; // 先把里面的数据安全地备份出来
    free_by_addr.erase(temp);
    free_by_size.erase(temp);
};

void free_memory(long long a, long long b){
    // 在memory中释放 [a, b] 这段内存
    FreeBlock newBlock(a, b-a+1);
    // 如果能合并，那么一定是右边界等于 a-1 或 左边界等于 b+1
    // 1. 查查左边有没有
    auto it = free_by_addr.lower_bound(FreeBlock(a, 0));
    if(it != free_by_addr.end()){
        --it; // 我们需要的是a的上一块
        if(it->r == a - 1){
            // 可以合并！
            // 先删除再合并
            newBlock.l = it->l;
            newBlock.len += it->len;
            FreeBlock temp = *it; // 先把里面的数据安全地备份出来
            free_by_addr.erase(temp);
            free_by_size.erase(temp);// 这里索引不一样！不能传相同的迭代器, 传对象
        }
    }

    // 2. 查查右边
    auto it_r = free_by_addr.lower_bound(FreeBlock(b, 0));
    if(it_r != free_by_addr.end()){
        if(it_r->l == b+1){
            newBlock.r = it_r->r;
            newBlock.len += it_r->len;
            FreeBlock temp = *it_r; // 先把里面的数据安全地备份出来
            free_by_addr.erase(temp);
            free_by_size.erase(temp);
        }
    }

    // 3. 添加
    free_by_addr.insert(newBlock);
    free_by_size.insert(newBlock);
}

void handle_delete(Process& p, int i){
    auto& q = p.queue;
    if(i < 0 || i >= q.size()) return;

    // 直接用vector的erase就可以按索引删元素
    int start = q[i].start, end = q[i].end;
    q.erase(q.begin()+i);

    // 释放内存空间
    free_memory(start, end);

}

int main(){
    int n, q;
    cin >> n >> q;
    vector<Process> processes(n);
    while(q--){
        string op;
        cin >> op;
        int p, l, i;
        if(op == "new"){
            cin >> p >> l;
            handle_new(processes[p-1], l);
        }
        else if(op == "send"){
            cin >> p;
            handle_send(processes[p-1]);
        }
        else if(op == "delete"){
            cin >> p >> i;
            handle_delete(processes[p-1], i-1);
        }
    }
}