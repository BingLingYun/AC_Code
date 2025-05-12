#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

void solve()
{
    string s;cin>>s;s=" "+s;
    int n=s.size()-1;
    vector<pii>vec;
    for(int i=1;i<=n;i++)
    {
        int r=i;
        while(r<n && s[r+1]==s[r]) r++;
        int op;
        if(s[i]=='L') op=0;
        else op=1;
        vec.push_back({op,r-i+1});
        i=r;
    }
    int q;cin>>q;
    while(q--)
    {
        string t;cin>>t;t=" "+t;
        vector<pii>now;
        int m=t.size()-1;
        for(int i=1;i<=m;i++)
        {
            int r=i;
            while(r<m && t[r+1]==t[r]) r++;
            int op;
            if(t[i]=='L') op=0;
            else op=1;
            now.push_back({op,r-i+1});
            i=r;
        }
        int flag=1;
        int l=0;
        for(int i=0;i<now.size();i++)
        {
            auto [op,val]=now[i];
            while(l<vec.size() && val>0)
            {
                auto [op1,val1]=vec[l];
                if(op!=op1)
                {
                    l++;
                }
                else
                {
                    val-=val1;
                    l++;
                }
            }
            if(val>0)
            {
                flag=0;break;
            }
        }
        if(vec[0].first==0)
        {
            if(now[0].first!=0) flag=0;
        }
        if(vec.back().first==1)
        {
            if(now.back().first!=1) flag=0;
        }
        cout<<(flag ? "YES":"NO")<<"\n";
    }
}
int main()
{
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}