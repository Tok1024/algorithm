#include <iostream>
using namespace std;

const int N = 1e5+10;
int a[N], cnt[N];



int main(){
    int n, ans = 0;
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);

    // 双指针算法
    for(int i = 0, j = 0; i < n; i++){
        // 1. 扩展右边界，维护区间
        cnt[a[i]]++;

        // 2. 维护左边界, 得到一个合法的区间
        // 这里唯一需要检查的就是新加入的元素a[i]是否满足不重复！
        while(j <= i && cnt[a[i]] > 1) {
            cnt[a[j]]--;
            j++;
        }

        // 3. 更新答案
        ans = max(ans, i - j + 1);
    }
    cout << ans << endl;
}