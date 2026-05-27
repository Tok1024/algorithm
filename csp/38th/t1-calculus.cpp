#include <iostream>
using namespace std;

int b, c;

int f(int x){
    return x*x + b * x + c;
}

int sum(int l, int r){
    int res = 0;
    for(int i = l; i <= r; i++){
        if(i%2) continue;
        res += f(i);
    }
    return res * 2;
}

int main(){
    int l, r;
    cin >> b >> c >> l >> r;
    cout << sum(l, r) << endl;
}