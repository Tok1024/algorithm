#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> a;

// 一定要引用传递！不然会超时的
bool check_sort(vector<int>& s, vector<int>& t){
    if(s.size() != t.size()) return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    for(int i = 0; i < s.size(); i++){
        if(s[i] != t[i]) return false;
    }
    return true;
}

bool check_xor(vector<int>& s, vector<int>& t){
    int s_xor = 0;
    for(int x: s){
        s_xor ^= a[x];
    }
    int t_xor = 0;
    for(int x: t){
        t_xor ^= a[x];
    }
    return s_xor == t_xor;
}

int main(){
    int n, m, len;
    cin >> n >> m;
    a.resize(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    vector<vector<int>> all_s, all_t;

    for(int k = 0; k < m; k++){
        cin >> len;
        vector<int> t(len);
        for(int i = 0; i < len; i++){
            cin >> t[i];
        }
        all_s.push_back(t);
    }
    for(int k = 0; k < m; k++){
        cin >> len;
        vector<int> t(len);
        for(int i = 0; i < len; i++){
            cin >> t[i];
        }
        all_t.push_back(t);
    }
    for(int i = 0; i < all_s.size(); i++){
        if(check_sort(all_s[i], all_t[i])==check_xor(all_s[i], all_t[i])) cout << "correct" << endl;
        else cout << "wrong" << endl;
    }
}
