#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool is_prime(int x){
    for(int i = 2; i <= sqrt(x); i++){
        if(x % i == 0) return false;
    }
    return true;
}

long long query(long long n, int k){
    long long res = 1;
    for(int i = 2; i*i <= n; i++){
        // 这里不用检查i是不是素数
        // 因为我们从小到大遍历，后面的合数的因子在意开始早就除尽了，所以一定值能被质数整除
        if(n%i != 0) continue;
        // 可以整除
        int t = 0;
        while(n && ((n % i) == 0)){
            n /= i;
            t++;
        }
        if(t >= k) res *= pow(i, t);
    }
    return res;
}

int main(){
    int q, k;
    long long n;
    cin >> q;
    while(q--){
        cin >> n >> k;
        cout << query(n, k) << endl;
    }
}