#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    i64 n,A,B;cin>>n>>A>>B;
    vector<i64>a(2*n+1);
    for(int i=1;i<=n+n;i++) cin>>a[i];
    sort(a.begin()+1,a.end());
    vector<vector<i64>>vec;
    for(int i=1;i<=n+n;i++)
    {
        int j=i;
        while(j+1 <= 2*n && a[j+1]-a[j]<=A) j++;
        vector<i64>now;
        for(int k=i;k<=j;k++) now.push_back(a[k]);
        int len=j-i+1;
        if(len&1)
        {
            cout<<-1<<"\n";
            return;
        }
        vec.push_back(now);
        i=j;
    }
    // for(auto v:vec)
    // {
    //     for(auto x:v)
    //     {
    //         cout<<x<<" ";
    //     }
    //     cout<<"\n";
    int ans=0;
    auto check = [&] (vector<i64> now)
    {
        // for(auto x:now) cout<<x<<" ";
        // cout<<"\n";
        vector<vector<i64>>seg;
        for(int i=0;i<now.size();i++)
        {
            int j=i;
            while(j+1 < (int)now.size() && now[j+1]-now[j]<=B) j++;
            vector<i64>cc;
            for(int k=i;k<=j;k++) cc.push_back(now[k]);
            seg.push_back(cc);
            i=j;
        }
        // cout<<seg.size()<<"\n";
        // for(auto x:seg)
        // {
        //     for(auto y:x) cout<<y<<" ";cout<<"\n";
        // }
        for(int i=0;i<seg.size();i++)
        {
            if(seg[i].size() %2 ==0)
            {
                ans+=seg[i].size()/2;
                continue;
            }
            int j;
            for(int k=i+1;k<seg.size();k++)
            {
                if(seg[k].size()%2==1)
                {
                    j=k;break;
                }
            }
            int lst=i;
            vector<int>ok;
            for(int k=i+1;k<j;k++)
            {
                if(seg[k][0]-seg[lst].back()<=A && seg[k+1][0]-seg[lst].back()>A)
                {
                    ok.push_back(k);
                    lst=k;
                }
            }
            int res=0;
            for(int k=i;k<=j;k++) res+=seg[k].size();
            ans+=res/2-ok.size()-1;
            i=j;
        }
    };
    for(auto v:vec)
    {
        check(v);
    }
    cout<<ans<<"\n";
}
int main()
{
    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}