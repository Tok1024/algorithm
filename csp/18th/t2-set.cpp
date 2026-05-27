#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef long long ll;

int main(){
    set<pair<ll, ll>> points;
    int n;
    vector<int> cnt(5, 0);;
    ll x, y;
    cin >> n;
    for(int i =0; i < n; i++){
        cin >> x >> y;
        points.insert({x, y});
    }
    for(auto p: points){
        int x = p.first, y = p.second;
        if(points.count({x-1, y}) && points.count({x+1, y}) &&
        points.count({x, y-1}) && points.count({x, y+1})){
            int score = 0;
            if(points.count({x-1, y-1})) score++;
            if(points.count({x-1, y+1})) score++;
            if(points.count({x+1, y-1})) score++;
            if(points.count({x+1, y+1})) score++;
            cnt[score]++;
        }
    }
    for(int x: cnt){
        cout << x << endl;
    }
}