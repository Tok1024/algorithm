#include <iostream>
#include <vector>
using namespace std;

int main(){
    int m, n;
    cin >> m >> n;
    vector<int> dp(n+1);
    vector<int> capacity(m), value(m);
    for(int i = 0; i < m; i++){
        cin >> capacity[i] >> value[i];
    }

    // 一定是外层物品，内层容积
    for(int i = 0; i < m; i++){
        for(int j = n; j >= capacity[i]; --j){
            dp[j] = max(dp[j], dp[j-capacity[i]] + value[i]);
        }
    }
    cout << dp[n] << endl;
}