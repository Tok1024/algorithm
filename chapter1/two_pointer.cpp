#include <iostream>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    int n = s.size();
    for(int i = 0; i < n; i++){
        int j = i;
        while(j < n && s[j] != ' ') j++;
        cout << s.substr(i, j-i) << endl;;
        while(j < n && s[j] == ' ') j++;
        i = j-1;
    }
}