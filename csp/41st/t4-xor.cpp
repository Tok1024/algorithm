#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
const int N = 5e5+10;
typedef unsigned long long ULL;
ULL a[N];

vector<int> convert_to_basek(ULL x){
    vector<int> res;
    while(x){
        res.push_back(x % k);
        x /= k;
    }
    // reverse(res.begin(), res.end());
    return res;
}


ULL vec_2_num(vector<int>& x){
    ULL res = 0, m = 1;
    // 区分高位到低位和低位到高位的累加方式
    for(int i: x){
        res += i * m;
        m *= k;
    }
    return res;
}

ULL xor_basek(ULL a, ULL b){
    auto x = convert_to_basek(a);
    auto y = convert_to_basek(b);
    int min_len = min(x.size(), y.size());
    vector<int> res;
    for(int i = 0; i < min_len; i++){
        res.push_back((x[i] + y[i])%k);
    }
    auto left = x.size() > y.size()? x : y;
    for(int i = min_len; i < left.size(); i++){
        res.push_back(left[i]);
    }
    // reverse(res.begin(), res.end());
    return vec_2_num(res);
}

ULL f(ULL n){
    if(n == 0){
        return 0;
    }
    else return xor_basek(n, f(n-1));
}


void xor_k(int l, int r, ULL v){
    for(int i = l; i <= r; i++){
        a[i] = xor_basek(a[i], v);
    }
}

ULL query(int l, int r){
    ULL res = 0;
    for(int i = l; i <= r; i++){
        res = xor_basek(res, f(a[i]));
    }
    return res;
}

int main(){
    cin >> n >> m >> k;
    int t, l, r;
    ULL v;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    while(m--){
        cin >> t;
        if(t==1){
            cin >> l >> r >> v;
            xor_k(l, r, v);
        }
        else if(t==2){
            cin >> l >> r;
            cout << query(l, r) << endl;
        }
    }
}