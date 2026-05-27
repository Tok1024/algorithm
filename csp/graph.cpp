/*
 * 图论综合训练 - 填空版
 * 三道题，每题有 TODO 标注的关键逻辑需要你补全
 * 编译: g++ -O2 -o graph_training graph_training.cpp
 */

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// ============================================================
// 公共数据结构
// ============================================================
const int N = 1005;
const int INF = 1e9;

vector<int> tree_adj[N];           // 树的邻接表（无权）
vector<pair<int,int>> graph_adj[N]; // 图的邻接表（带权）
int a[N];     // 树节点的权值
int par[N];   // 树中每个节点的父节点
int dep[N];   // 树中每个节点的深度

// ============================================================
// 题目一：树上路径 mex 查询
// ============================================================
/*
  给一棵 n 个节点的树，节点 i 的权值为 a[i]，a[] 是 0..n-1 的排列。
  有 q 次查询，每次给 (x, y)，求 x 到 y 路径上所有节点权值构成集合的 mex。
  mex = 集合中没有出现的最小自然数

  输入样例 (task1.txt):
  7
  3 1 0 4 2 6 5
  6
  1 2
  1 3
  2 4
  2 5
  3 6
  3 7
  3
  4 7
  5 6
  4 5

  预期输出:
  2
  4
  0
*/

// 树的 DFS，建好 par[] 和 dep[]
void dfs_tree(int u, int p, int d) {
    par[u] = p;
    dep[u] = d;
    for (int v : tree_adj[u]) {
        if (v == p) continue;
        dfs_tree(v, u, d + 1);
    }
}

// TODO 1: 实现 get_path(x, y)
// 返回 x 到 y 路径上所有节点的 vector
// 思路：两端同时往上爬，爬到 LCA 为止，拼接两段路径
vector<int> get_path(int x, int y) {
    // 你的代码
    vector<int> path_x, path_y;
    while(x != y){
        if(dep[x] >= dep[y]){
            path_x.push_back(x);
            x = par[x];
        }else{
            path_y.push_back(y);
            y = par[y];
        }
    }
    path_x.push_back(x);
    for(int y: path_y) path_x.push_back(y);
    return path_x;
}

// TODO 2: 实现 calc_mex(path)
// 收集路径上所有节点的 a[] 值，求 mex
int calc_mex(vector<int>& path) {
    // 你的代码
    unordered_set<int> vals;
    for(int n: path){
        int w = a[n];
        vals.insert(w);
    }
    int m = 0;
    while(vals.count(m)) m++;
    return m;
}

void solve_task1() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int edges = n - 1;
    for (int i = 0; i < edges; i++) {
        int u, v; cin >> u >> v;
        tree_adj[u].push_back(v);
        tree_adj[v].push_back(u);
    }
    dfs_tree(1, -1, 0);

    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        vector<int> path = get_path(x, y);
        for(int x: path) cout << x << ' ';
        cout << endl;
        cout << calc_mex(path) << "\n";
    }
}

// ============================================================
// 题目二：带权图单源最短路（Dijkstra）
// ============================================================
/*
  给一个 n 个节点、m 条无向带权边的图，从节点 1 出发，求到每个节点的最短路。
  如果不可达输出 -1。

  输入样例 (task2.txt):
  6 8
  1 2 4
  1 3 2
  2 3 1
  2 4 5
  3 4 8
  3 5 10
  4 5 2
  4 6 6
  1

  预期输出（从节点1到1~6的最短路）:
  0 3 2 8 10 14

  解析:
  1->1: 0
  1->2: 1->3->2 = 2+1 = 3
  1->3: 2
  1->4: 1->3->2->4 = 2+1+5 = 8
  1->5: 1->3->2->4->5 = 8+2 = 10
  1->6: 1->3->2->4->6 = 8+6 = 14
*/

// TODO 3: 实现堆优化 Dijkstra
// 返回从 src 出发到所有节点的最短距离数组（不可达为 INF）
// 提示：用 priority_queue<pair<int,int>, vector<...>, greater<>> 小顶堆
//       堆里存 {距离, 节点}
//       每次取出最近的节点，松弛它的邻居
vector<int> dijkstra(int src, int n) {
    vector<int> dist(n + 1, INF);
    // 你的代码
    return dist;
}

void solve_task2() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph_adj[u].push_back({v, w});
        graph_adj[v].push_back({u, w});
    }
    int src; cin >> src;
    vector<int> dist = dijkstra(src, n);
    for (int i = 1; i <= n; i++) {
        cout << (dist[i] == INF ? -1 : dist[i]);
        if (i < n) cout << " ";
    }
    cout << "\n";
}

// ============================================================
// 题目三：并查集 - 动态连通 + 路径权值
// ============================================================
/*
  有 n 个节点，初始互不相连。
  支持两种操作：
    1 u v w  → 连接 u 和 v，边权为 w（保证 u v 原本不连通）
    2 u v    → 查询 u 和 v 是否连通，如果连通输出 "YES"，否则 "NO"

  输入样例 (task3.txt):
  5 7
  1 1 2 3
  1 2 3 5
  2 1 3
  2 1 4
  1 3 4 2
  1 4 5 7
  2 1 5

  预期输出:
  YES
  NO
  YES
*/

int fa[N];

void init_uf(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i;
}

// TODO 4: 实现带路径压缩的 find
int find_uf(int x) {
    // 你的代码
}

// TODO 5: 实现 unite
void unite(int x, int y) {
    // 你的代码
}

bool same(int x, int y) {
    return find_uf(x) == find_uf(y);
}

void solve_task3() {
    int n, q; cin >> n >> q;
    init_uf(n);
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int u, v, w; cin >> u >> v >> w;
            unite(u, v);
        } else {
            int u, v; cin >> u >> v;
            cout << (same(u, v) ? "YES" : "NO") << "\n";
        }
    }
}

// ============================================================
// 主函数 - 分别跑三道题（实际测试时注释掉不用的）
// ============================================================
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    // freopen("inputs/mex.txt", "r", stdin);   // 输入从文件读

    // 选择运行哪道题（注释掉其他两个）
    solve_task1();
    // solve_task2();
    // solve_task3();

    return 0;
}
