#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

void solve()
{
    int n;cin>>n;
    int cnt=0;
    int x,y;
    for(int i=2;i<=n;i+=2)
    {
        cout<<"? "<<i-1<<" "<<i<<endl;
        int op;cin>>op;
        if(op==1)
        {
            cnt++;
            x=i-1,y=i;
        }
    }
    if(cnt>=2)
    {
        cout<<"! 1"<<endl;
        return;
    }
    if(cnt==0)
    {
        int cc=0;
        for(int i=1;i<=3;i++)
        {
            cout<<"? "<<i<<" "<<n<<endl;
            int op;cin>>op;
            cc+=op;
        }
        if(cc==3)
        {
            cout<<"! 2"<<endl;
        }
        else
        {
            cout<<"! 1"<<endl;
        }
    }
    else
    {
        int a=0,b=0;
        for(int i=1;i<=n;i++)
        {
            if(i!=x && i!=y)
            {
                if(!a) a=i;
                else
                {
                    b=i;break;
                }
            }
        }
        int op1,op2;
        cout<<"? "<<a<<" "<<x<<endl;
        cin>>op1;
        cout<<"? "<<a<<" "<<y<<endl;
        cin>>op2;
        if(op1==0 && op2==0)
        {
            cout<<"! 1"<<endl;
            return;
        }
        if(op1==1)
        {
            cout<<"? "<<b<<" "<<x<<endl;
            int cc;cin>>cc;
            if(cc==1)
            {
                cout<<"! 2"<<endl;
            }
            else
            {
                cout<<"! 1"<<endl;
            }
            return;
        }
        if(op2==1)
        {
            cout<<"? "<<b<<" "<<y<<endl;
            int cc;cin>>cc;
            if(cc==1)
            {
                cout<<"! 2"<<endl;
            }
            else
            {
                cout<<"! 1"<<endl;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<fixed<<setprecision(15);

    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}