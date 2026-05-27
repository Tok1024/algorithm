#include <iostream>
#include <vector>
using namespace std;

int check(int x){
    if(x % 7 == 0) return 1;
    while(x){
        int l = x % 10;
        if(l == 7) return 1;
        x /= 10;
    }
    return 0;
}

int main(){
    vector<int> cnt(4, 0);
    int n;
    cin >> n;
    int i = 0, a = 0;
    for(int x = 1; x <= n*2; x++){
        int res = check(x);
        if(!res){
            a++;
        }
        cnt[i] += res;
        i = (i+1) % 4;
        if(a==n) break;
    }
    for(int x: cnt){
        cout << x << endl;
    }
}