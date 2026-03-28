#include <iostream>
#include <utility>
using namespace std;

int main(){
    int n, a, b;
    cin >> n;
    vector<pair<int, int>> pairs;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        pairs.push_back({a, b});
    }

    // 给 pairs 排序
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b){
        return a.first < b.first;
    });

    // 哨兵初始化，使得第一个区间自动触发 cnt++
    int cnt = 0, start, end = -2e9;
    for(auto &seg: pairs){
        if(seg.first > end){
            cnt ++;
            start = seg.first;
            end = seg.second;
        }
        else end = max(end, seg.second);
    }

    cout << cnt << endl;

}