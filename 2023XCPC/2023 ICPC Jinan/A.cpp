#include<bits/stdc++.h>

#define i64 long long
#define pii pair<int,int>
#define pll pair<i64,i64>
#define int128 __int128_t
#define ull unsigned long long
using namespace std;

constexpr i64 mod=998244353;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(15);
    
    int t;cin>>t;
    while(t--)
    {
        string s;cin>>s;
        s=" "+s;
        int n=s.size()-1;
        vector<int>l(n+1),r(n+1);
        string t=s;
        vector<pii>vec;
        for(int i=1;i<=n;i++)
        {
            if(s[i]=='(' || s[i]==')')
            {
                if(!vec.empty())
                {
                    if(vec.back().second == 0)
                    {
                        int pos=vec.back().first;
                        vec.pop_back();
                        t[pos]='(';
                        t[i]=')';
                        l[pos]=i;
                        r[i]=pos;
                    }
                    else
                    {
                        vec.push_back({i,0});
                    }
                }
                else vec.push_back({i,0});
            }
            else
            {
                if(!vec.empty())
                {
                    if(vec.back().second == 1)
                    {
                        int pos=vec.back().first;
                        vec.pop_back();
                        t[pos]='[';
                        t[i]=']';
                        l[pos]=i;
                        r[i]=pos;
                    }
                    else
                    {
                        vec.push_back({i,1});
                    }
                }
                else vec.push_back({i,1});
            }
        }
        int flag=0;
        for(int i=2;i<n;i++) 
        {
            if(t[i]==')' && t[i+1]=='(' || t[i]==']' && t[i+1]=='[')
            {
                flag=1;
            }
            if(t[i]==')')
            {
                int R=l[i+1];
                if(R+1<=n && R>i && t[R+1]=='(') flag=1;
            }
            if(t[i]==']')
            {
                int R=l[i+1];
                if(R+1<=n && R>i && t[R+1]=='[') flag=1;
            }
        }
        cout<<(flag ? "No" : "Yes")<<"\n";
    }
    return 0; 
}
