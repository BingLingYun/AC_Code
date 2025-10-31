#include<bits/stdc++.h>

using namespace std;

typedef long long i64;

int main()
{
    int n;
    cin >> n;
    map<string,int>mp;
    auto check = [&] (string s,string t)
    {
        int res1,res2,res3;
        if(mp.find(s)!=mp.end())
        {
            res1=mp[s];
        }
        else
        {
            cout<<"? "<<s<<endl;
            cin>>res1;
            mp[s]=res1;
        }
        if(mp.find(t)!=mp.end())
        {
            res2=mp[t];
        }
        else
        {
            cout<<"? "<<t<<endl;
            cin>>res2;
        }
        string h="";
        for(int i=0;i<n;i++)
        {
            if(s[i]=='1' || t[i]=='1') h+='1';
            else h+='0';
        }
        if(mp.find(h)!=mp.end())
        {
            res3=mp[h];
        }
        else
        {
            cout<<"? "<<h<<endl;
            cin>>res3;
        }
        return (res1+res2 != res3);
    };
    string C="1";
    for(int i=1;i<n;i++) C += '0';
    for(int i=1;i<n;i++)
    {
        string h="";
        vector<int>vec;
        for(int j=0;j<n;j++)
        {
            if(C[j]=='1') h+='0';
            else h+='1',vec.push_back(j);
        }
        int l=0,r=vec.size()-1,res=-1;
        while(l<=r)
        {
            int mid=l+r>>1;
            string now="";
            for(int j=0;j<=vec[mid];j++) now+=h[j];
            for(int j=vec[mid]+1;j<n;j++) now+='0';
            if(check(C,now)) res=mid,r=mid-1;
            else l=mid+1;
        }
        if(res==-1)
        {
            cout<<"! 0"<<endl;
            return 0;
        }
        C[vec[res]]='1';
    }
    cout<<"! 1"<<endl;
    return 0;
}