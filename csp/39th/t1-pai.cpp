#include <iostream>
using namespace std;

int main(){
    int n, a, m = 0;
    double x, y;
    cin >> n >> a;
    for(int i = 0; i < n; i++){
        cin >> x >> y;
        if(x*x + y*y <= a*a) m++;
    }
    printf("%.6f\n", 4.0*m / n);
}