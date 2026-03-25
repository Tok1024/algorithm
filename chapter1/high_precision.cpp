#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6+10;

bool cmp(vector<int> &A, vector<int> &B)
{
    if (A.size() != B.size()) return A.size() > B.size();

    for (int i = A.size() - 1; i >= 0; i--)
    {
        if (A[i] != B[i]) return A[i] > B[i];
    }

    return true; // A >= B
}

//规定A长于B
vector<int> add(vector<int> &A, vector<int> &B){
    if(A.size() < B.size()) return add(B, A);

    vector<int> ans;
    int t = 0;
    for(int i = 0; i < A.size(); i++){
        t += A[i];
        if(i < B.size()) t += B[i];
        ans.push_back(t % 10);
        t /= 10;
    }
    //最后一个进位给忘了，汗
    if(t != 0) ans.push_back(t);
    return ans;
}

// 依旧规定于A长于B，由于AB都是正整数，那么A大于B
vector<int> sub(vector<int> &A, vector<int> &B){
    //减法不要在函数内部调用cmp，否则会出现无限递归啊（二者相等时）
    // if(cmp(B, A)) return sub(B, A);

    vector<int> ans;
    int t = 0;
    for(int i = 0; i < A.size(); i++){
        t += A[i];
        if(i < B.size()) t -= B[i];
        // 减法的情况下，每个进位只可能是0/1
        if(t < 0) {
            ans.push_back(10 + t);
            t = -1;
        }
        else{
            ans.push_back(t);
            t = 0;
        }

    }
    // 重要！！去除前导0,要在sub里进行
    // for(int i = ans.size() - 1; ans[i] == 0; i--){
    //     ans.pop_back();
    // } 不对，如果答案真的是0,那就会被排除啊
    while(ans.size() > 1 && ans.back() == 0) ans.pop_back();
    return ans;
}

vector<int> mul(vector<int> &A, int b){
    vector<int> ans;
    int t = 0;
    for(int i = 0; i < A.size() || t; i++){
        t += b * A[i];
        ans.push_back(t % 10);
        t /= 10;
    }

    // 依旧别忘了去除前导0
    while(ans.size() > 1 && ans.back() == 0) ans.pop_back();
    return ans;
}

// 懒得写了，就当我会了吧
vector<int> div(vector<int> &A, int b, int &r)
{
    vector<int> C;
    r = 0; //余数

    for (int i = A.size() - 1; i >= 0; i--)
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }

    reverse(C.begin(), C.end());

    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}


int main(){
    string a, b;
    int c, r;
    cin >> a >> c;
    vector<int> A, B;
    for(int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    // for(int i = b.size() - 1; i >= 0; i--)
    //     B.push_back(b[i] - '0');

    // vector<int> ans = add(A, B);

    // vector<int> ans;
    
    // if(cmp(A, B)) {
    //     ans = sub(A, B);
    // }
    // else{
    //     cout << "-";
    //     ans = sub(B, A);
    // }

    vector<int> ans = div(A, c, r);

    for(int i = ans.size() - 1; i >= 0; i--)cout << ans[i];
    cout << endl;
    cout << r << endl;
}