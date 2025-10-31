#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

constexpr i64 mod = 998244353;
// 矩阵快速幂的式子一般是递推式，关键在于构建关系矩阵

int L; // 矩阵的大小，记得初始化
struct mul
{
    i64 v[50][50];
    void clear() { memset(v, 0, sizeof(v)); }
    void reset()
    {
        clear();
        for (int i = 0; i <= L; i++)
        {
            v[i][i] = 1; // 单位矩阵，相当与1
        }
    }
    mul friend operator*(const mul &a, const mul &b) // 重载运算符
    {
        mul ret;
        ret.clear();
        for (int i = 0; i < L; i++)
        {
            for (int k = 0; k < L; k++)
            {
                for (int j = 0; j < L; j++)
                {
                    ret.v[i][j] += a.v[i][k] * b.v[k][j] % mod;
                    ret.v[i][j] %= mod;
                }
            }
        }
        return ret;
    } // 矩阵乘法
};

inline mul fpow(mul base, i64 k)
{ // k个base矩阵相乘
    mul ret;
    ret.reset(); // ret为初始矩阵
    while (k)
    {
        if (k & 1)
            ret = ret * base;
        base = base * base;
        k >>= 1;
    }
    return ret;
} // 快速幂

mul res;
mul pow2[31];

void solve()
{
    int N;
    cin >> N;

    mul ans;
    ans.clear();
    ans.v[0][0] = 1;
    for(int i=30;i>=0;i--)
    {
        if((N>>i&1)==0) continue;
        vector<i64>now(L);
        for(int j=0;j<L;j++)
        {
            for(int k=0;k<L;k++)
            {
                now[j]=(now[j] + ans.v[0][k]*pow2[i].v[k][j]%mod)%mod;
            }
        }
        for(int j=0;j<L;j++) ans.v[0][j]=now[j];
    }
    cout<<ans.v[0][48]<<"\n";
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    res.clear();
    L = 49;
    auto get = [&](int x, int y)
    {
        return x * 7 + y;
    };
    for (int i = 0; i < L; i++)
    {
        int x = i / 7, y = i % 7;
        res.v[get(x, y)][get(x, y)] = 50;
        if (x - 1 >= 0)
        {
            res.v[get(x - 1, y)][get(x, y)] = 1;
        }
        if (y - 1 >= 0)
        {
            res.v[get(x, y - 1)][get(x, y)] = 1;
        }
        if (x == 6 && y == 6)
        {
            res.v[i][i] = 52;
        }
        else if (x == 6 || y == 6)
        {
            res.v[i][i] = 51;
        }
    }
    for(int i=0;i<=30;i++)
    {
        pow2[i]=fpow(res,(1<<i));
    }
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}