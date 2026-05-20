#include <iostream>
using namespace std;

bool check(int x){
    int one = 0, zero = 0, t = x;
    while(t){
        if(t & 1) one++;
        else zero++;
        t = t >> 1;
    }
    return x != 0 && one == zero;
}

int main(){
    int n, t, cnt = 0;
    cin >> n;
    while(n --){
        cin >> t;
        if(check(t)) cnt++;
    }
    cout << cnt;
}