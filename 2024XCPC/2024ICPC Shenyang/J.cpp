#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    
    string ans1,ans2;
    int cnt1=0,cnt2=0;
    for(int i=1;i<=8;i++)
    {
        string t;cin>>t;
        int res;cin>>res;
        if(i<=4)
        {
            if(res>cnt1)
            {
                ans1=t;
                cnt1=res;
            }
        }
        else
        {
            if(res>cnt2)
            {
                ans2=t;
                cnt2=res;
            }
        }
    }
    if(cnt1<cnt2)
    {
        swap(ans1,ans2);
    }
    cout<<ans1<<" "<<"beats"<<" "<<ans2<<"\n";
    return 0;
}