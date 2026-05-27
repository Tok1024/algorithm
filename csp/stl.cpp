/**
 * @file csp_ultimate_api_summary.cpp
 * @brief CCF-CSP 考试常用 API 终极大汇总（完整版·含所有高频模板）
 * @note 使用 C++17 或以上标准编译，推荐直接当“刷题工具箱”使用
 */
#include <iostream>          // cout、cin、ios
#include <sstream>           // stringstream
#include <string>            // string、stoi、to_string、find、substr
#include <vector>            // vector
#include <algorithm>         // sort、unique、lower_bound、upper_bound、max
#include <iterator>          // distance
#include <unordered_map>     // unordered_map
#include <unordered_set>     // unordered_set
#include <queue>             // queue、priority_queue
#include <deque>             // deque
#include <functional>        // function、greater、multiplies
#include <numeric>           // gcd、lcm、accumulate、iota
#include <iomanip>           // fixed、setprecision
#include <utility>           // pair
using namespace std;

// ==================== 常用常量 & 类型定义 ====================
using ll = long long;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;
const double EPS = 1e-9;

// ==========================================
// 场景 1：输入输出优化与字符串整行解析
// ==========================================
void scenario_io_and_string() {
    cout << "--- 场景 1：输入输出与字符串解析 ---\n";
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string input_line = "1024 Tok algorithm 403 99";
    cout << "原字符串: " << input_line << "\n";
    stringstream ss(input_line);
    string word;
    int num;
    ss >> num >> word;
    cout << "解析出的整数: " << num << ", 字符串: " << word << "\n";
    string s_num = "12345";
    int converted_int = stoi(s_num);
    string back_to_str = to_string(6789);
    string email = "csp@ccf.org.cn";
    size_t pos = email.find("@");
    if (pos != string::npos) {
        string username = email.substr(0, pos);
        cout << "用户名: " << username << "\n";
    }
}

// ==========================================
// 场景 2：去重、排序与离散化
// ==========================================
struct Point {
    int x, y;
};
void scenario_sort_and_unique() {
    cout << "\n--- 场景 2：排序、去重与二分查找 ---\n";
    vector<int> nums = {5, 2, 8, 2, 5, 1, 9, 8};
    sort(nums.begin(), nums.end());
    auto it = unique(nums.begin(), nums.end());
    nums.erase(it, nums.end());
    cout << "去重后的数组: ";
    for (int x : nums) cout << x << " ";
    cout << "\n";
    auto lb = lower_bound(nums.begin(), nums.end(), 5);
    auto ub = upper_bound(nums.begin(), nums.end(), 5);
    cout << "第一个 >= 5 的位置下标: " << distance(nums.begin(), lb) << "\n";
    cout << "第一个 > 5 的数字是: " << *ub << "\n";
    vector<Point> points = {{1, 5}, {2, 3}, {1, 2}};
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y > b.y;
    });
}

// ==========================================
// 场景 3：频次统计与无序去重（Map & Set）
// ==========================================
void scenario_map_set() {
    cout << "\n--- 场景 3：Map 与 Set 的快查与计数 ---\n";
    unordered_map<string, int> counts;
    counts["apple"]++;
    counts["banana"]++;
    counts["apple"]++;
    if (counts.count("apple")) {
        cout << "apple 出现了 " << counts["apple"] << " 次\n";
    }
    unordered_set<int> visited;
    visited.insert(10);
    visited.insert(20);
    if (visited.find(10) != visited.end()) {
        cout << "10 已经被访问过了\n";
    }
}

// ==========================================
// 场景 4：堆与优先队列（Priority Queue）
// ==========================================
void scenario_priority_queue() {
    cout << "\n--- 场景 4：优先队列（堆） ---\n";
    priority_queue<int> max_heap;
    max_heap.push(10); max_heap.push(30); max_heap.push(20);
    cout << "大顶堆堆顶（最大值）: " << max_heap.top() << "\n";
    priority_queue<int, vector<int>, greater<int>> min_heap;
    min_heap.push(10); min_heap.push(30); min_heap.push(20);
    cout << "小顶堆堆顶（最小值）: " << min_heap.top() << "\n";
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> node_heap;
    node_heap.push({5, 1}); node_heap.push({2, 2});
    cout << "最近的节点是: " << node_heap.top().second << "，距离为: " << node_heap.top().first << "\n";
}

// ==========================================
// 场景 5：位运算与常用数学内建函数
// ==========================================
void scenario_math_and_bits() {
    cout << "\n--- 场景 5：位运算与数学 API ---\n";
    int g = std::gcd(12, 18);
    int l = std::lcm(12, 18);
    cout << "12 和 18 的最大公约数: " << g << ", 最小公倍数: " << l << "\n";
    unsigned int status = 0b10110;
    cout << "10110 中 1 的个数: " << __builtin_popcount(status) << "\n";
    cout << "10110 末尾有几个 0: " << __builtin_ctz(status) << "\n";
    cout << "绝对值: " << abs(-50) << "\n";
    cout << "多个数求最值: " << max({1, 5, 3, 9, 2}) << "\n";
}

// ==========================================
// 场景 6：队列、栈、双端队列（BFS + 单调队列）
// ==========================================
void scenario_queue_deque() {
    cout << "\n--- 场景 6：queue / stack / deque ---\n";
    queue<int> q;
    q.push(1); q.push(2);
    cout << "BFS 队头: " << q.front() << "\n";
    deque<int> dq;
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> maxWin;
    for (int i = 0; i < arr.size(); ++i) {
        while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() == i - 3) dq.pop_front();
        if (i >= 2) maxWin.push_back(arr[dq.front()]);
    }
    cout << "窗口最大值: ";
    for (int x : maxWin) cout << x << " ";
    cout << "\n";
}

// ==========================================
// 场景 7：并查集（Union-Find）
// ==========================================
struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) ++rank[rx];
        return true;
    }
};
void scenario_dsu() {
    cout << "\n--- 场景 7：并查集 ---\n";
    UnionFind uf(10);
    uf.unite(1, 2);
    uf.unite(2, 3);
    cout << "1 和 3 是否连通: " << (uf.find(1) == uf.find(3) ? "是" : "否") << "\n";
}

// ==========================================
// 场景 8：DFS / BFS 模板
// ==========================================
void scenario_search() {
    cout << "\n--- 场景 8：BFS & DFS 模板 ---\n";
    vector<vector<int>> g = {{1,2}, {0,2}, {0,1,3}, {2}};
    vector<bool> vis(4, false);
    // BFS
    queue<int> q;
    q.push(0); vis[0] = true;
    cout << "BFS 遍历: ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
    // DFS
    function<void(int)> dfs = [&](int u) {
        vis[u] = true;
        cout << u << " ";
        for (int v : g[u]) if (!vis[v]) dfs(v);
    };
    fill(vis.begin(), vis.end(), false);
    cout << "DFS 遍历: ";
    dfs(0);
    cout << "\n";
}

// ==========================================
// 场景 9：排列生成 & 数值算法
// ==========================================
void scenario_permute_numeric() {
    cout << "\n--- 场景 9：next_permutation & accumulate ---\n";
    vector<int> a = {1, 2, 3};
    cout << "所有排列: \n";
    do {
        for (int x : a) cout << x << " ";
        cout << "\n";
    } while (next_permutation(a.begin(), a.end()));
    vector<int> nums = {1, 2, 3, 4, 5};
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int prod = accumulate(nums.begin(), nums.end(), 1, multiplies<int>());
    cout << "累加和: " << sum << ", 累乘积: " << prod << "\n";
}

// ==========================================
// 场景 10：EOF、多组输入、浮点输出、离散化完整版
// ==========================================
void scenario_misc() {
    cout << "\n--- 场景 10：EOF / 浮点 / 离散化完整版 ---\n";
    cout << "浮点精确输出示例: " << fixed << setprecision(10) << 3.1415926535 << "\n";
    vector<int> coords = {100, 20, 100, 50, 20};
    vector<int> sorted = coords;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    auto get_rank = [&](int x) {
        return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;
    };
    cout << "100 的离散化秩: " << get_rank(100) << "\n";
}

int main() {
    scenario_io_and_string();
    scenario_sort_and_unique();
    scenario_map_set();
    scenario_priority_queue();
    scenario_math_and_bits();
    scenario_queue_deque();
    scenario_dsu();
    scenario_search();
    scenario_permute_numeric();
    scenario_misc();

    cout << "\n=== CSP 常用 API 大汇总（完整版）结束 ===\n";
    cout << "提示：把上面所有 scenario_* 函数直接复制到你的刷题模板里即可！\n";
    cout << "祝你 CSP 每次都高分通过！🚀\n";
    return 0;
}