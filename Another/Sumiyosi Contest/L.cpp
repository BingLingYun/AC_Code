#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> x(n+1);
    for(int i=1; i<n; i++) {
        cin >> x[i];
    }
    for(int i=2; i<=n; i++) {
        cout << 1 << " " << i << endl;
    }
    int a=2, b=3;
    for(int i=n; i<=m; i++) {
        cout << a << " " << b << endl;
        b ++;
        if(b == n+1) {
            a ++;
            b = a+1;
        }
    }
    return 0;
}