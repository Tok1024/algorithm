#include <iostream>
#include <vector>
using namespace std;

int k, n, idx;
vector<string> a;
bool ok = true;

string parse_pair();
string parse_type();

string parse_type(){
    if(idx >= n) {
        ok = false;
        return "";
    }
    if(a[idx] == "int"){
        idx++;
        return "int";
    }
    if(a[idx] == "pair") return parse_pair();

    ok = false;
    return "";
}

string parse_pair(){
    // 这里实际上就是在检测 FIRST 集
    if(idx >= n || a[idx++] != "pair"){
        ok = false;
        return "";
    }

    string left = parse_type();
    if(!ok) return "";

    string right = parse_type();
    if(!ok) return "";

    return "pair<" + left +", "+ right+">";
}



int main(){
    string s;
    cin >> k;
    while(k--)
    {
        idx = 0;
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        string ans = parse_pair();
        if(ok && idx == n) cout << ans << endl;
        else cout << "Error!" << endl;
    }
}