#include<iostream>
using namespace std;

int main(){
    double n, mid;
    cin >> n;
    double l = 0, r = n;
    while(r - l > 1e-6){
        mid = (l + r) / 2;
        if (mid * mid > n) r = mid;
        else l = mid;
    }
    cout << l;
}