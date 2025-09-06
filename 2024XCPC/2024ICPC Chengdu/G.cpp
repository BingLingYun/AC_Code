#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
#define all(x) x.begin(),x.end()
using namespace std;

constexpr i64 mod=998244353;


int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);

    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    set<int>st;
    for(int i=1;i<n;i++)
    {
        int x=a[i],y=a[i+1];
        st.insert(x);
        st.insert(y);
        st.insert(x^y);
        st.insert(x&y);
        st.insert(x|y);
        st.insert(0);
        st.insert(x&(x^y));
        st.insert(y&(x^y));
    }
    cout<<st.size()<<"\n";
    return 0; 
}
