#include <iostream>
#include <unordered_map>
using namespace std;

/**
 * @brief 八数码问题
 * 每个string 如 s = "123x45678" 是一个状态
 * 询问从状态a到b最少经过几步交换
 * 这个题如果是二维数组就很好理解,但是字符串的话就要知道一些字符串操作了
 * 1. s.find('x') = 3; 0索引
 * 2. s+b = sb 字符串拼接
 * 3. 二维坐标和一维下标互转 x = k / 3, y = k % 3, k = 3*x + y
 */

string s, target = "12345678x";
queue<string> q;
unordered_map<string, int> mp; //记录每个字符串的步数，以及是否访问过
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};


int bfs(){
    q.push(s);
    mp[s] = 0;
    while(!q.empty()){
        string m = q.front();
        // 需要在入栈的时候检查，否则第一个string不就检查不到了吗
        if(m == target) return mp[m];
        int k = m.find('x');
        int x = k / 3, y = k % 3;
        q.pop();
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            string temp = m;

            if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3){
                // 看看命中了没，命中了就溜
                swap(temp[nx*3 + ny], temp[k]);

                //没命中继续搜
                if(!mp.count(temp)){
                    q.push(temp);
                    mp[temp] = mp[m] + 1;
                }
            }
        }
    }
    return -1;
}

int main(){
    string c;
    for(int i = 0; i < 9; i++){
        cin >> c;
        s += c;
    }
    cout << bfs() << endl;
}
