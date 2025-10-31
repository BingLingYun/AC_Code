#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

i64 dfs(i64 x)
{
    if(x==0) return 1ll;
    if(x%3==0)
    {
        return dfs(x/3)+1;
    }
    else
    {
        i64 yu = x%3;
        return dfs(x-yu)+yu;
    }
}
void solve()
{
    i64 l,r;cin>>l>>r;
    int ans=0;
    ans=max(dfs(l),dfs(r));
    vector<int>R,L;
    while(r) R.push_back(r%3),r/=3;
    while(l) L.push_back(l%3),l/=3;
    if(R.size()!=L.size())
    {
        ans=max(ans,3*(int)(R.size()-1));
        reverse(R.begin(),R.end());
        int len=R.size();
        int res=0;
        for(int i=0;i<R.size();i++)
        {
            if(i==0)
            {
                if(R[i]==2)
                {
                    ans=max(ans,1+2*(len-1)+len);
                }
            }
            else
            {
                if(R[i]>0)
                {
                    ans=max(ans,res+R[i]-1+(len-i-1)*2+len);
                }
            }
            res+=R[i];
        }
        ans=max(ans,res);
    }
    else
    {
        reverse(R.begin(),R.end());
        reverse(L.begin(),L.end());
        int res=0,len=R.size();
        for(int i=0;i<len;i++)
        {
            if(R[i]>L[i])
            {
                ans=max(ans,res+R[i]-1+(len-i-1)*2+len);
            }
            res+=R[i];
        }
    }
    cout<<ans<<"\n";
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);

    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
//长度差为>=1的话，全2以及len确定找最大
//长度相同和差1一致