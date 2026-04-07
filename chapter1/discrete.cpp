#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

/* 离散化
1.题目：
假定有一个无限长的数轴，数轴上每个坐标上的数都是 0
现在，我们首先进行 n 次操作，每次操作将某一位置 x 上的数加 c
接下来，进行 m 次询问，每个询问包含两个整数 l 和 r
你需要求出在区间 [l,r] 之间的所有数的和。
2.思路
这个题问区间和，首先肯定是想到了前缀和。
但是仔细看看，数组无限长，我们要开一个无限大的数组？肯定不可能。
但是仔细想想，虽然数轴无限长，但是操作数量有限，询问次数也是有限的。
我们就收集所有的坐标，把坐标值映射到数组a中，然后对这个数组计算前缀和即可
*/

typedef pair<int, int> PII; // 先类型，再别名
const int N = 3e5+10;
int a[N], s[N]; // 映射的数组以及前缀和数组
vector<PII> adds, querys;
vector<int> alls; // 全部的坐标，因为不确定个数，需要是一个vector

// 给出坐标值 x，找出在新的数组a里面的坐标(1-based)
int find(int x){
    // lower_bound 返回的是第一个 <= x的元素的迭代器
    return lower_bound(alls.begin(), alls.end(), x) - alls.begin() + 1;
}

int main(){
    int n, m, l, r, x, c;
    cin >> n >> m;
    // 1. add操作
    while(n--){
        cin >> x >> c;
        adds.push_back({x, c});
        alls.push_back(x);
    }

    // 2. 查询操作
    for(int i = 0; i < m; i++){
        cin >> l >> r;
        querys.push_back({l, r});
        alls.push_back(l);
        alls.push_back(r);
    }

    // 3. 给alls排序去重
    sort(alls.begin(), alls.end());
    //  unique把有序重复元素移到末尾，返回重复区的起点，而erase消除他们
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    // 4. 执行add
    for(auto add: adds){
        a[find(add.first)] += add.second;
    }

    // 5. 计算前缀和
    for(int i = 1; i <= alls.size(); i++) s[i] = s[i-1] + a[i];

    // 6. 输出
    for(auto q: querys){
        int l = q.first, r = q.second;
        cout << s[find(r)] - s[find(l)-1] << endl;
    }
}