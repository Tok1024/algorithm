#include<iostream>
using namespace std;

/*
单调队列
- 问题类型：滑动窗口求区间内的最大值
- 基本思想：和单调栈一样，利用单调性的传递性。如果a[i] <= a[j] 且 i < j, 
            那么a[i] 对于j以及之后的元素都没用，因为直接选择 a[j]了，谁要你 a[i]
- 数据结构：为什么要用deque？单调栈问题里，每个元素的下一个最大是一个因果全局的（想想transformer的因果掩码）
            而单调队列里，元素会过期呀，所以过期元素要出队，需要两头操作，所以要用deque!\
*           而且单调栈里要求的是最近，而这道题要求的是最大，所以要用队列！
*/

const int N = 1e5;
int a[N], wind_max[N], wind_min[N];

int main(){
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);

    deque<int> dq_max, dq_min;
    // ? 枚举起点还是终点，我觉得还是终点把，方便添加元素
    for(int i = 0; i < n; i++){ // 这是在枚举终点哦
        // 1. 清理过期元素
        while(i >= k && !dq_max.empty() && dq_max.front() <= i - k) dq_max.pop_front();
        while(i >= k && !dq_min.empty() && dq_min.front() <= i - k) dq_min.pop_front();

        // 2. 删除被 a[i] 淘汰的元素
        while(!dq_max.empty() && a[i] >= a[dq_max.back()]) dq_max.pop_back();
        while(!dq_min.empty() && a[i] <= a[dq_min.back()]) dq_min.pop_back();

        // 3. 入队, 无论如何都要入队
        dq_max.push_back(i);
        dq_min.push_back(i);

        // 4. 记录答案
        wind_max[i] = a[dq_max.front()];
        wind_min[i] = a[dq_min.front()];
    }
    for(int i = 0; i < n; i++) printf("%d ", wind_max[i]);
    printf("\n");
    for(int i = 0; i < n; i++) printf("%d ", wind_min[i]);
    printf("\n");
}