#include <bits/stdc++.h>
using namespace std;


void solve()
{
    int n, m;
    cin >> n >> m;
    vector a(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)
    {
        string s;cin>>s;s=" "+s;
        for(int j=1;j<=m;j++)
        {
            if(s[j]=='W') a[i][j]=0;
            else a[i][j]=1;
        }
    }
    auto check = [&](vector<vector<int>>g,int op)
    {
        int sx=1,sy=m,ex=1,ey=m;
        vector<vector<char>>ans;
        while(1)
        {
            if(sx==n || ey==1) break;
            vector<char>ch;
            int x=1,y=1;
            g[x][y]^=1;
            while(x<sx) ch.push_back('D'),x++,g[x][y]^=1;
            while(y<sy-1) ch.push_back('R'),y++,g[x][y]^=1;
            while(y!=ey) 
            {
                if(g[x][y+1]==op) 
                {
                    ch.push_back('D');
                    ch.push_back('R');
                    g[x+1][y]^=1;g[x+1][y+1]^=1;
                }
                else
                {
                    ch.push_back('R');
                    ch.push_back('D');
                    g[x][y+1]^=1;g[x+1][y+1]^=1;
                }
                x+=1,y+=1;
            }
            while(x<n) ch.push_back('D'),x++,g[x][y]^=1;
            while(y<m) ch.push_back('R'),y++,g[x][y]^=1;
            ans.push_back(ch);
            if(sy==2) sx+=1;
            else sy-=1;
            if(ex==n-1) ey-=1;
            else ex+=1;
            if(sx==n || ey==1) break;
        }

        int flag=1;
        for(int i=1;i<=n;i++)
        {
            if(g[i][1]!=op) flag=0;
        }
        for(int i=1;i<=m;i++)
        {
            if(g[n][i]!=op) flag=0;
        }
        if(flag)
        {
            return ans;
        }

        vector<char>ch;
        for(int i=1;i<n;i++) 
        {
            ch.push_back('D');
        }
        for(int i=1;i<m;i++)
        {
            ch.push_back('R');
        }
        ans.push_back(ch);
        flag=1;
        for(int i=1;i<=n;i++)
        {
            if(g[i][1]==op) flag=0;
        }
        for(int i=1;i<=m;i++)
        {
            if(g[n][i]==op) flag=0;
        }
        if(flag) return ans;
        else
        {
            ans.clear();
            ans.push_back({'#'});
            return ans;
        }
    };
    set<vector<char>>st;
    auto h1=check(a,0);
    // cout<<h1.size()<<"\n";
    // return;
    if(h1.empty() || h1[0][0]!='#')
    {
        for(auto v:h1)
        {
            if(st.find(v)!=st.end())
            {
                st.erase(v);
            }
            else st.insert(v);
        }
    }
    else
    {
        auto h2=check(a,1);
        if(h2.empty() || h2[0][0]!='#')
        {
            for(auto v:h2)
            {
                if(st.find(v)!=st.end())
                {
                    st.erase(v);
                }
                else st.insert(v);
            }
        }
        else
        {
            cout<<"NO"<<"\n";
            return;
        }
    }
    cout<<"YES"<<"\n";
    cout<<st.size()<<"\n";
    for(auto x:st) 
    {
        for(auto y:x) cout<<y;
        cout<<"\n";
    }
}
int main()
{
    int t;cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}