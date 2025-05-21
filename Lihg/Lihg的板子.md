# Lihg模板

[TOC]

## 小技巧

```c++
hypot(x,y)=sqrt(x*x,y*y)//求斜边
    
__builtin_popcount()//求二进制中‘1’的个数

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());//生成64位的随机数

d(A,B)=max(|x1-x2|,|y1-y2|)=|(x1+y1)/2-(x2+y2)/2|+|(x1-y1)/2-(x2-y2)/2|//切比雪夫距离转曼哈顿
```

## 封装模板

### 取模板子

```c++
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = i64(1E18) + 9;

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 998244353;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1000000007;
using Z = MInt<P>;

```

### 高精度

```c++
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define endl '\n'
typedef long long ll;

const int base = 1000000000;
const int base_digits = 9; // 分解为九个数位一个数字
struct bigint {
    vector<int> a;
    int sign;

    bigint() : sign(1) {}
    bigint operator-() const {
        bigint res = *this;
        res.sign = -sign;
        return res;
    }
    bigint(long long v) {
        *this = v;
    }
    bigint(const string &s) {
        read(s);
    }
    void operator=(const bigint &v) {
        sign = v.sign;
        a = v.a;
    }
    void operator=(long long v) {
        a.clear();
        sign = 1;
        if (v < 0) sign = -1, v = -v;
        for (; v > 0; v = v / base) {
            a.push_back(v % base);
        }
    }

    // 基础加减乘除
    bigint operator+(const bigint &v) const {
        if (sign == v.sign) {
            bigint res = v;
            for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int)res.a.size()) {
                    res.a.push_back(0);
                }
                res.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry) {
                    res.a[i] -= base;
                }
            }
            return res;
        }
        return *this - (-v);
    }
    bigint operator-(const bigint &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                bigint res = *this;
                for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry) {
                        res.a[i] += base;
                    }
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
    void operator*=(int v) {
        check(v);
        for (int i = 0, carry = 0; i < (int)a.size() || carry; ++i) {
            if (i == (int)a.size()) {
                a.push_back(0);
            }
            long long cur = a[i] * (long long)v + carry;
            carry = (int)(cur / base);
            a[i] = (int)(cur % base);
        }
        trim();
    }
    void operator/=(int v) {
        check(v);
        for (int i = (int)a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long)base;
            a[i] = (int)(cur / v);
            rem = (int)(cur % v);
        }
        trim();
    }
    int operator%(int v) const {
        if (v < 0) {
            v = -v;
        }
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i) {
            m = (a[i] + m * (long long)base) % v;
        }
        return m * sign;
    }

    void operator+=(const bigint &v) {
        *this = *this + v;
    }
    void operator-=(const bigint &v) {
        *this = *this - v;
    }
    bigint operator*(int v) const {
        bigint res = *this;
        res *= v;
        return res;
    }
    bigint operator/(int v) const {
        bigint res = *this;
        res /= v;
        return res;
    }
    void operator%=(const int &v) {
        *this = *this % v;
    }

    bool operator<(const bigint &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
        return false;
    }
    bool operator>(const bigint &v) const {
        return v < *this;
    }
    bool operator<=(const bigint &v) const {
        return !(v < *this);
    }
    bool operator>=(const bigint &v) const {
        return !(*this < v);
    }
    bool operator==(const bigint &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const bigint &v) const {
        return *this < v || v < *this;
    }

    bigint abs() const {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    }
    void check(int v) { // 检查输入的是否为负数
        if (v < 0) {
            sign = -sign;
            v = -v;
        }
    }
    void trim() { // 去除前导零
        while (!a.empty() && !a.back()) a.pop_back();
        if (a.empty()) sign = 1;
    }
    bool isZero() const { // 判断是否等于零
        return a.empty() || (a.size() == 1 && !a[0]);
    }
    friend bigint gcd(const bigint &a, const bigint &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend bigint lcm(const bigint &a, const bigint &b) {
        return a / gcd(a, b) * b;
    }
    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++) x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream &operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
    friend ostream &operator<<(ostream &stream, const bigint &v) {
        if (v.sign == -1) stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }

    /* 大整数乘除大整数部分 */
    typedef vector<long long> vll;
    bigint operator*(const bigint &v) const { // 大整数乘大整数
        vector<int> a6 = convert_base(this->a, base_digits, 6);
        vector<int> b6 = convert_base(v.a, base_digits, 6);
        vll a(a6.begin(), a6.end());
        vll b(b6.begin(), b6.end());
        while (a.size() < b.size()) a.push_back(0);
        while (b.size() < a.size()) b.push_back(0);
        while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
        vll c = karatsubaMultiply(a, b);
        bigint res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int)c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int)(cur % 1000000));
            carry = (int)(cur / 1000000);
        }
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
    friend pair<bigint, bigint> divmod(const bigint &a1,
                                       const bigint &b1) { // 大整数除大整数，同时返回答案与余数
        int norm = base / (b1.a.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.a.resize(a.a.size());
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long)base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) r += b, --d;
            q.a[i] = d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int)p.size(); i++) p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back((int)(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int)cur);
        while (!res.empty() && !res.back()) res.pop_back();
        return res;
    }
    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    res[i + j] += a[i] * b[j];
                }
            }
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++) a2[i] += a1[i];
        for (int i = 0; i < k; i++) b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int)a1b1.size(); i++) r[i] -= a1b1[i];
        for (int i = 0; i < (int)a2b2.size(); i++) r[i] -= a2b2[i];

        for (int i = 0; i < (int)r.size(); i++) res[i + k] += r[i];
        for (int i = 0; i < (int)a1b1.size(); i++) res[i] += a1b1[i];
        for (int i = 0; i < (int)a2b2.size(); i++) res[i + n] += a2b2[i];
        return res;
    }

    void operator*=(const bigint &v) {
        *this = *this * v;
    }
    bigint operator/(const bigint &v) const {
        return divmod(*this, v).first;
    }
    void operator/=(const bigint &v) {
        *this = *this / v;
    }
    bigint operator%(const bigint &v) const {
        return divmod(*this, v).second;
    }
    void operator%=(const bigint &v) {
        *this = *this % v;
    }
};

int main()
{
    bigint a, b;
    cin >> a >> b;
    cout << a+b << endl;
    return 0;
}

```

## 数论

### 欧几里得算法

```c++
i64 exgcd(i64 a,i64 b,i64 &x,i64 &y)//扩展欧几里得算法
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    i64 xx,yy;
    i64 Gcd=exgcd(b,a%b,xx,yy);
    x=yy;
    y=xx-(a/b)*yy;
    return Gcd;
}
//求的是ax+by=gcd(a,b)的一组整数解x,y
//b/=g,a/=g
//通解为x1=x0+bt,y1=y0-at，t为整数
i64 cal(i64 a,i64 b,i64 c)//计算最小正整数解
{
    i64 x,y;
    i64 gcd=exgcd(a,b,x,y);
    if(c%gcd) return -1;//无解
    b/=gcd;if(b<0) b=-b;
    x=x*(c/gcd)%b;
    if(x<=0) x+=b;
    return x;
}
```

### 线性筛

```c++
// 线性筛质数
int st[maxn];
vector<int> prime;
void getPrime(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
        {
            prime.push_back(i);
        }
        for (auto j : prime)
        {
            if (i * j > n)
                break;
            st[i * j] = 1;
        }
    }
}


//Pollard_Rho筛分解质因数
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
i64 quick_pow(i64 x, i64 y, i64 p) // 快速幂
{  
    i64 ans = 1;
    while (y) 
    {
        if (y & 1) ans = (int128)ans * x % p;
        x = (int128)x * x % p;
        y >>= 1;
    }
    return ans;
}
bool Miller_Rabin(i64 p) // 判断素数
{  
    if (p < 2) return false;

    i64 d = p - 1, r = 0;
    while (!(d & 1)) {
        r++;
        d >>= 1;
    }
    int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (auto a : prime) {
        if (p == a)  return true;
        i64 x = quick_pow(a, d, p);
        if (x == 1 || x == p - 1)  continue;

        for (int i = 0; i < r - 1; i++) {
            x = int128(x) * x % p;
            if (x == p - 1) break;
        }
        if (x != p - 1) {
            return false;
        }
    }
    return true;
}

i64 Pollard_Rho(i64 x) 
{
    i64 s = 0, t = 0;
    i64 c = (i64)(rng()) % (x - 1) + 1;
    i64 val = 1;
    for (int goal = 1; ; goal <<= 1, s = t, val = 1) 
    {
        for (int step = 1; step <= goal; step++) 
        {
            t = (int128(t) * t + c) % x;
            val = int128(val) * abs(t - s) % x;
            if (step % 127 == 0) {
                i64 g = gcd(val, x);
                if (g > 1) {
                    return g;
                }
            }
        }
        i64 g = gcd(val, x);
        if (g > 1) {
            return g;
        }
    }
}
unordered_map<i64, int> getprimes(i64 x) {
    unordered_map<i64, int> p;
    function<void(i64)> get = [&](i64 x) {
        if (x < 2) {
            return;
        }
        if (Miller_Rabin(x)) {
            p[x]++;
            return;
        }
        i64 mx = Pollard_Rho(x);
        get(x / mx);
        get(mx);
    };
    get(x);
    return p;
}
vector<i64> getfac(i64 x) 
{
    vector<i64> fac;
    auto primes = getprimes(x);
    vector<pair<i64, int>> tmp(primes.begin(), primes.end());
    int SIZE = tmp.size();
    function<void(int, i64)> dfs = [&](int id, i64 x) {
        if (id == SIZE) {
            fac.push_back(x);
            return;
        }
        i64 p = 1;
        for (int i = 0; i <= tmp[id].second; i++) {
            if (i != 0) {
                p *= tmp[id].first;
            }
            dfs(id + 1, x * p);
        }
    };
    dfs(0, 1);
    return fac;
}
```

### 整除分块

求$$ sum = \sum n/i$$，1-n

```c++
i64 sum=0;
for(int l=1;l<=n;l++)
{
    int d=n/l,r=n/d;
    sum+=(r-l+1)*d;
    l=r;
}
```

### long long 取模

```c++
i64 get(i64 x,i64 y,i64 m)
{
    x%=m,y%=m;
    i64 d=((long double)x*y/m);
    d=x*y-d*m;
    if(d>=m) d-=m;
    if(d<0) d+=m;
    return d;
}
```

### 卡特兰数

![image-20250218172145779](C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20250218172145779.png)

![image-20250218172219076](C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20250218172219076.png)

### 矩阵快速幂

```c++
//矩阵快速幂的式子一般是递推式，关键在于构建关系矩阵
i64 kpow(i64 x,i64 y)
{
    i64 res=0;
    for(;y>0;y>>=1)
    {
        if(y&1) res=(res+x)%mod;
        x=(x+x)%mod;
    }
    return res;
}//龟速乘，计算x*y

int L;//矩阵的大小，记得初始化
struct mul{
    i64 v[105][105];
    void clear(){ memset(v,0,sizeof(v)); }
    void reset()
    {
        clear();
        for(int i=1;i<=L;i++)
        {
            v[i][i]=1;//单位矩阵，相当与1
        }
    }
    mul friend operator * (const mul &a, const mul &b)//重载运算符
    {
        mul ret;ret.clear();
        for(int i=1;i<=L;i++)
        {
            for(int k=1;k<=L;k++)
            {
                for(int j=1;j<=L;j++)
                {
                    ret.v[i][j]+=kpow(a.v[i][k]%mod,b.v[k][j]%mod)%mod;
                    ret.v[i][j]%=mod;
                }
            }
        }
        return ret;
    }//矩阵乘法
};

inline mul fpow(mul base,i64 k)
{//k个base矩阵相乘
    mul ret;ret.reset();//ret为初始矩阵
    while(k)
    {
        if(k&1) ret=ret*base;
        base=base*base;
        k>>=1;
    }
    return ret;
}//快速幂
```

### 组合数

```c++
i64 fpow(i64 x,i64 y)
{
    i64 ans=1;
    for(;y>0;y>>=1)
    {
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
    }
    return ans;
}
struct Combi{
    vector<i64>fac,inv;int n;
    Combi(){}
    Combi(int n)
    {
        init(n);
    }
    void init(int n)
    {
        this->n=n;
        fac.resize(n+1,0);
        inv.resize(n+1,0);
    }
    void init_C()
    {
        fac[0]=1;
        for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
        inv[n]=fpow(fac[n],mod-2);
        for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    }
    i64 C (i64 x,i64 y)
    {
        if(x<y) return 0ll;
        return (fac[x]*inv[y]%mod*inv[x-y]%mod);
    }
};
```

### Lucas定理

![image-20240428145833213](C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20240428145833213.png)

```c++
int n,m,p;cin>>n>>m>>p;
vector<i64>fac(p+1);fac[0]=1;
for(int i=1;i<=p;i++) fac[i]=fac[i-1]*i%p; 
auto C = [&](int x,int y)
{
    if(y>x)return 0ll;
    return ((fac[x]*fpow(fac[y],p-2,p))%p*fpow(fac[x-y],p-2,p)%p);

};
function<i64(int,int)> lucas = [&] (int x,int y)
{
    if(y==0) return 1ll;
    return C(x%p,y%p)*lucas(x/p,y/p)%p;
};
```



### 欧拉函数

------

$\sum_{d|n} \phi(d) = n$

```c++
int st[maxn], phi[maxn];
vector<int> prime;
void getPrime(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
        {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (auto j : prime)
        {
            if (i * j > n)
                break;
            st[i * j] = 1;
            if (i % j == 0)
            {
                phi[i * j] = phi[i] * j;
                break;
            }
            phi[i * j] = phi[i] * phi[j];
        }
    }
}
```



### CRT

------

<img src="C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20250429185132818.png" alt="image-20250429185132818" style="zoom: 50%;" /><img src="C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20250429191218340.png" alt="image-20250429191218340" style="zoom:50%;" />

```c++
i64 exgcd(i64 a,i64 b,i64 &x,i64 &y)//扩展欧几里得算法
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    i64 xx,yy;
    i64 Gcd=exgcd(b,a%b,xx,yy);
    x=yy;
    y=xx-(a/b)*yy;
    return Gcd;
}
i64 CRT(int n,vector<i64>mo,vector<i64>yu)
{
    i64 M=1,ans=0;
    for(int i=1;i<=n;i++) M=M*mo[i];
    for(int i=1;i<=n;i++)
    {
        i64 Mi=M/mo[i],inv,y;
        exgcd(Mi,mo[i],inv,y);
        inv = inv % mo[i];
        ans= (ans+yu[i]*Mi*inv)%M;
    }
    return (ans+M)%M;
}
```



## 基础数据结构/算法思想

### 单调栈

```c++
vector<int>r(n+1,n+1),q(n+1);
int top=0;
for(int i=1;i<=n;i++)
{
    while(top && a[q[top]] < a[i]) r[q[top]]=i,top--;
    q[++top]=i;
}//在右侧找到第一个大于当前值的下标
```



### ST表

```c++
//st表用以计算可重复贡献性问题,可以求区间最大（小）值问题，区间求最大公约数问题
//f[i][j]表示区间[i,i+2^j -1]
struct ST{
    vector<vector<int>>f;
    int n;
    ST(){}
    ST(int n)
    {
        init(n);
    }
    void init(int n)
    {
        this->n=n;
        f.resize(n+1,vector<int>(31,0));
    }
    int quiry(int l,int r)
    {
        int ln=(int)(log(r-l+1)/log(2));
        return (max(f[l][ln],f[r-(1<<ln)+1][ln]));
    }
    void build(vector<int>a)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][0]=a[i];
        }
        int len=(int)(log(n)/log(2));
        for(int j=1;j<=len;j++)
        {
            for(int i=1;i<=n-(1<<j)+1;i++)
            {
                f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
            }
        }
    }
};

//二维st表-维持左上角为(i,j),右下角为(i+2^k-1,j+2^k-1)的正方形
struct ST_2D
{
    vector<vector<vector<i64>>>st;
    int n,m;
    ST_2D(int N,int M)
    {
        n=N,m=M;
        int k=log(min(n,m))/log(2);
        st=vector<vector<vector<i64>>>(n+1,vector<vector<i64>>(m+1,vector<i64>(k+1)));
    }
    void build(vector<vector<i64>>sum)
    {
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) st[i][j][0]=sum[i][j];
        int t=(int)(log(min(n,m))/log(2));
        for(int k = 1;k <= t;k++)
        {
            for(int i = 1;i + (1<<k)-1 <= n;i++)
            {
                for(int j = 1;j + (1<<k)-1 <= m;j++)
                {
                    i64 t1 = st[i][j][k-1];
                    i64 t2 = st[i+(1<<(k-1))][j][k-1];
                    i64 t3 = st[i][j+(1<<(k-1))][k-1];
                    i64 t4 = st[i+(1<<k-1)][j+(1<<k-1)][k-1];
                    st[i][j][k] = max({t1,t2,t3,t4});
                }
            }
        }
    }
    i64 query(int r1,int c1,int r2,int c2)//遍历，可能被宽度为1的长方形卡掉
    {
        int k1=log2(r2-r1+1);
        int k2=log2(c2-c1+1);
        if(k1==k2) return max({st[r1][c1][k1],st[r2-(1<<k1)+1][c1][k1],st[r1][c2-(1<<k1)+1][k1],st[r2-(1<<k1)+1][c2-(1<<k1)+1][k1]});
        if(k1<k2)
        {
            i64 mx=0;
            for(int i=c1;i<=c2-(1<<k1)+1;i+=(1<<k1)) mx=max(mx,max(st[r1][i][k1],st[r2-(1<<k1)+1][i][k1]));
            mx=max(mx,max(st[r1][c2-(1<<k1)+1][k1],st[r2-(1<<k1)+1][c2-(1<<k1)+1][k1]));
            return mx;
        }
        i64 mx=0;
        for(int i=r1;i<=r2-(1<<k2)+1;i+=(1<<k2)) mx=max(mx,max(st[i][c1][k2],st[i][c2-(1<<k2)+1][k2]));
        mx=max(mx,max(st[r2-(1<<k2)+1][c1][k2],st[r2-(1<<k2)+1][c2-(1<<k2)+1][k2]));
        return mx;
    }
};

//二维st表-维持左上角为(i,j),右下角为(i+2^k-1,j+2^h-1)的矩形
struct RMQ_2D{
    vector<vector<vector<vector<i64>>>>st;
    int n,m;
    RMQ_2D(int N,int M)
    {
        n=N,m=M;
        int k1=log(n)/log(2);
        int k2=log(m)/log(2);
        st=vector<vector<vector<vector<i64>>>>(n+1,vector<vector<vector<i64>>>(m+1,vector<vector<i64>>(k1+1,vector<i64>(k2+1))));
    }
    void build(vector<vector<i64>>sum)
    {
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) st[i][j][0][0]=sum[i][j];
        int t=(int)(log(max(n,m))/log(2));
        for(int i=0;i<=t;i++)
        {
            for(int j=0;j<=t;j++)
            {
                if(i==0 && j==0) continue;
                for(int row=1;row+(1<<i)-1 <=n ;row++)
                {
                    for(int col=1;col+(1<<j)-1 <=m;col++)
                    {
                        if(i) st[row][col][i][j]=max(st[row][col][i-1][j],st[row+(1<<(i-1))][col][i-1][j]);
                        else st[row][col][i][j]  = max(st[row][col][i][j-1],st[row][col+(1<<(j-1))][i][j-1]);
                    }
                }
            }
        }
    }
    i64 query(int x1,int y1,int x2,int y2)
    {
        int k1 = log(double(x2 - x1 + 1)) / log(2.0);
        int k2 = log(double(y2 - y1 + 1)) / log(2.0);
        i64 m1 = st[x1][y1][k1][k2];
        i64 m2 = st[x2 - (1<<k1) + 1][y1][k1][k2];
        i64 m3 = st[x1][y2 - (1<<k2) + 1][k1][k2];
        i64 m4 = st[x2 - (1<<k1) + 1][y2 - (1<<k2) + 1 ][k1][k2];
        i64 mx = max(max(m1,m2),max(m3,m4));
        return mx;
    }
};
```



### Trie

```c++
//字典树，用于实现字符串快速检索的多叉树结构
//也可用于搜索最大的异或对，生成二进制书进行检索
//在进行大量字符串的前面连续个数匹配时，可以考虑使用tire
struct Trie{
    vector<vector<int>>trie;int tot=1;
    vector<int>end;
    Trie(int N)
    {
        trie=vector<vector<int>>(N+10,vector<int>(26));
        end=vector<int>(N+10);
    }
    void insert(string s)//插入
    {
        int len=s.size(),p=1;
        for(int k=0;k<len;k++)
        {
            int ch=s[k]-'a';
            if(trie[p][ch] == 0) trie[p][ch]= ++tot;
            p=trie[p][ch];
        }
        end[p]=1;
    }
    int search(string s)//寻找
    {
        int len=s.size(),p=1;
        for(int k=0;k<len;k++)
        {
            int ch=s[k]-'a';
            p=trie[p][ch];
            if(p==0) return 0;
        }
        return end[p];
    }
};
```



### DSU

```c++
struct DSU{
	vector<int>fa,siz;
	DSU(int N){
		fa=vector<int>(N+1);
		iota(fa.begin(),fa.end(),0);
		siz=vector<int>(N+1,1);
	}
	int find(int x)
	{
		return (fa[x]==x ? x : fa[x]=find(fa[x]));
	}
	void unite(int x,int y)
	{
		x=find(x);y=find(y);
		if(x!=y)
		{
			if(siz[x]<siz[y]) swap(x,y);
			fa[y]=x;
			siz[x]+=siz[y];
			siz[y]=0;
		}
	}
	int getsiz(int x)
	{
		return siz[find(x)];
	}
};
unionfind UF(n);

//带权并查集
struct unionfind{
    vector<int>f;
    vector<i64>val;
    unionfind(int n)
    {
        f=vector<int>(n+1);
        iota(f.begin(),f.end(),0);
        val=vector<i64>(n+1,0);
    }
    int find(int x)//查找并计算路径和
    {
        if(x != f[x])
        {
            int t=find(f[x]);
            val[x]+=val[f[x]];
            f[x]=t;
        }
        return f[x];
    }
    void merge(int x,int y,i64 s)//x->y有一条长度为s的线段
    {
        int fx=find(x),fy=find(y);
        if(fx != fy)
        {
            f[fx]=fy;
            val[fx]=s-val[x]+val[y];//矢量和加减，具有方向
        }
    }
    i64 ask(int x,int y)//查询x->y的值
    {
        return val[x]-val[y];
    }
};
```

### 树状数组

```c++
struct BIT{
    vector<int>a;int n;
    BIT(){}
    BIT (int n)
    {
        this->n=n;
        init(n);
    }
    void init(int n)
    {
        a.resize(n+1,0);
    }
    void add(int x,int v)
    {
        for(int i=x;i<=n;i+=(i&(-i))) a[i]+=v;
    }
    int ask(int x)
    {
        int res=0;
        for(int i=x;i>0;i-=(i&(-i))) res+=a[i];
        return res;
    }
    int ask(int l,int r)
    {
        return ask(r)-ask(l-1);
    }
    int query(i64 x)//查询1...pos的和小于x的最大值
    {
        i64 h=ceil(log2(n)),pos=0,t=0;
        for(int j=h;j>=0;j--)//从大到小
        {
            if(pos + (1<<j) <=n && t + a[pos+(1<<j)] <= x)
            {
                pos+=(1<<j);
                t+=a[pos];
            }
        }
        return pos;
    }
};

//单点修改+区间最值
struct BIT{
    vector<double>a,h;int n;
    BIT (int N)
    {
        a=vector<double>(N+10,0);
        h=vector<double>(N+10,0);
    	n=N+5;
    }
    int lowbit(int x)
    {
        return x&(-x);
    }
    void change(int x,double v)
    {
        a[x]=v;
    }
    void update(int x)
    {
        int lx, i;
        while (x <= n)
        {
            h[x] = a[x];
            lx = lowbit(x);
            for (i=1; i<lx; i<<=1)
            {
                h[x] = max(h[x], h[x-i]);
            }
            x += lowbit(x);
        }	
    }
    double ask(int x,int y)
    {
        if(x>y) return 0;
        double ans = 0;
        while (y >= x)
        {
            ans = max(a[y], ans);
            y --;
            for (; y-lowbit(y) >= x; y -= lowbit(y))
            {
                ans = max(h[y], ans);
            }
        }
        return ans;
    }
};
```



### 线段树

------

#### 基础线段树

------

```c++
//区间加减+求区间最值
struct Info{
	i64 add,mn;
};
Info operator + (Info a,Info b)
{
    Info c;c.add=0;
    c.mn=min(a.mn,b.mn);
    return c;
}
struct SegmentTree{
    vector<Info>info;
    SegmentTree(int n)
    {
        init(n);
	}
    void init(int n)
    {
        info.resize(n<<2);
    }
    void pushup(int u)
    {
        info[u]=info[u<<1]+info[u<<1|1];
    }
    void build(int u,int l,int r)//建树
    {
        if(l==r)
        {
            info[u].mn=info[u].add=0;
            return;
        }
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
  		pushup(u);
    }
    void pushdown(int u)//标记下移
    {
        info[u<<1].mn=info[u<<1].mn+info[u].add;
        info[u<<1|1].mn=info[u<<1|1].mn+info[u].add;
        info[u<<1].add=info[u<<1].add+info[u].add;
        info[u<<1|1].add=info[u<<1|1].add+info[u].add;
        info[u].add=0;
    }
    void modify(int u,int l,int r,int x,int y,i64 k)//当前区间与目的区间
    {
        if(r<x || l>y) return;
        if(x<=l && r<=y)
        {
            info[u].add+=k;info[u].mn+=k;
            return;
        }
        pushdown(u);
        int mid=l+r>>1;
        if(x<=mid) modify(u<<1,l,mid,x,y,k);
        if(y>mid) modify(u<<1|1,mid+1,r,x,y,k);
        pushup(u);
    }
    Info quiry(int u,int l,int r,int x,int y)
    {
        if(x<=l && r<=y)
        {
            return info[u];
        }
        pushdown(u);
        int mid=l+r>>1;
        if(y<=mid) return quiry(u<<1,l,mid,x,y);
        else if(x>mid) return quiry(u<<1|1,mid+1,r,x,y);
        return quiry(u<<1,l,mid,x,y)+quiry(u<<1|1,mid+1,r,x,y);
    }
};

//单点修改+求区间和
struct Info{
	i64 add,val;
};
Info operator + (Info a,Info b)
{
    Info c;c.add=0;
    c.val=a.val+b.val;
    return c;
}
struct SegmentTree{
    vector<Info>info;
    SegmentTree(int n)
    {
        info=vector<Info>(n<<2);
	}
    void pushup(int u)
    {
        info[u]=info[u<<1]+info[u<<1|1];
    }
    void build(int u,int l,int r)//建树
    {
        if(l==r)
        {
            info[u].val=info[u].add=0;
            return;
        }
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
  		pushup(u);
    }
    void pushdown(int u,int l,int r)//标记下移
    {   
        int mid=l+r>>1;
        info[u<<1].add+=info[u].add;
        info[u<<1|1].add+=info[u].add;
        info[u<<1].val+=info[u].add*(mid-l+1);
        info[u<<1|1].val+=info[u].add*(r-mid);
        info[u].add=0;
    }
    void modify(int u,int l,int r,int x,int y,i64 k)//当前区间与目的区间
    {
        if(r<x || l>y) return;
        if(x<=l && r<=y)
        {
            info[u].add+=k;info[u].val+=k*(r-l+1);
            return;
        }
        pushdown(u,l,r);
        int mid=l+r>>1;
        if(x<=mid) modify(u<<1,l,mid,x,y,k);
        if(y>mid) modify(u<<1|1,mid+1,r,x,y,k);
        pushup(u);
    }
    i64 quiry(int u,int l,int r,int x,int y)
    {
        if(l>y || r<x) return 0;
        if(x<=l && r<=y)
        {
            return info[u].val;
        }
        pushdown(u,l,r);
        int mid=l+r>>1;
        return quiry(u<<1,l,mid,x,y)+quiry(u<<1|1,mid+1,r,x,y);
    }
};
```



#### 树套树

------

```c++
//树套数求二维区间最值
void cmx(int &a,int b) { a=max(a,b); }
void cmn(int &a,int b) { a=min(a,b); }
struct node_y{
    int l,r;
    int res[4],tag[4];
};
struct tree_y{
    vector<node_y>tr;
    void push_up(int u)
    {
        for(int i=0;i<4;i++)
        {
            if(i<2) tr[u].res[i]=max(tr[u<<1].res[i],tr[u<<1|1].res[i]);
            else tr[u].res[i]=min(tr[u<<1].res[i],tr[u<<1|1].res[i]);
        }
    }
    void push_down(int u)
    {
        for(int i=0;i<4;i++)
        {
            if(i<2)
            {
                if(tr[u].tag[i]>0)
                {
                    cmx(tr[u<<1].res[i],tr[u].tag[i]);
                    cmx(tr[u<<1].tag[i],tr[u].tag[i]);
                    cmx(tr[u<<1|1].res[i],tr[u].tag[i]);
                    cmx(tr[u<<1|1].tag[i],tr[u].tag[i]);
                    tr[u].tag[i]=0;
                }
            }
            else
            {
                if(tr[u].tag[i]<2001)
                {
                    cmn(tr[u<<1].res[i],tr[u].tag[i]);
                    cmn(tr[u<<1].tag[i],tr[u].tag[i]);
                    cmn(tr[u<<1|1].res[i],tr[u].tag[i]);
                    cmn(tr[u<<1|1].tag[i],tr[u].tag[i]);
                    tr[u].tag[i]=2001;
                }
            }
        }
        
    }
    void build(int u,int l,int r)
    {
        tr[u].l=l,tr[u].r=r;
        for(int i=0;i<4;i++)
        {
            if(i<2) tr[u].res[i]=tr[u].tag[i]=0;
            else tr[u].res[i]=tr[u].tag[i]=2001;
        }
        if(l==r) return;
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
    }
    void update(int u, int l, int r, int val,int id)
    {
        if(tr[u].l >= l && tr[u].r <= r)
        {
            if(id<2) cmx(tr[u].res[id],val),cmx(tr[u].tag[id],val);
            else cmn(tr[u].res[id],val),cmn(tr[u].tag[id],val);
            return;
        }
        push_down(u);
        int mid =tr[u].l + tr[u].r >> 1;
        if(r <= mid) update(u<<1, l, r, val,id);
        else if(l > mid) update(u<<1|1, l, r, val,id);
        else update(u<<1, l, mid, val,id), update(u<<1|1, mid + 1, r, val,id);
        push_up(u);
    }
    int query(int u, int l, int r,int id)
    {
        if(tr[u].l >= l && tr[u].r <= r) return tr[u].res[id];  
        push_down(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(id<2)
        {
            if(r <= mid) return query(u<<1, l, r,id);
            else if(l > mid) return query(u<<1|1, l, r,id);
            else return max(query(u<<1, l, mid,id), query(u<<1|1, mid + 1, r,id));
        }
        else
        {
            if(r <= mid) return query(u<<1, l, r,id);
            else if(l > mid) return query(u<<1|1, l, r,id);
            else return min(query(u<<1, l, mid,id), query(u<<1|1, mid + 1, r,id));
        }
    }
};

struct node_x
{
    int l, r;
    tree_y lazy_tag;
    tree_y tr;
};
struct tree_x{
    int m;
    vector<node_x>tree;
    tree_x(int N,int M)
    {
        tree=vector<node_x>(N<<2);
        m=M;
    }
    void build(int now, int l, int r)
    {
        tree[now].l = l; tree[now].r = r;
        tree[now].tr.tr.resize(m<<2);tree[now].lazy_tag.tr.resize(m<<2);
        tree[now].tr.build(1, 1, m); tree[now].lazy_tag.build(1, 1, m);
        if(tree[now].l == tree[now].r) return ;
        int mid = (l + r) >> 1;
        build(now<<1, l, mid); build(now<<1|1, mid + 1, r);
    }
    void update(int now, int l1, int r1, int l2, int r2, int val,int id)
    {
        tree[now].tr.update(1, l2, r2, val,id);
        if(tree[now].l >= l1 && tree[now].r <= r1)
        {
            tree[now].lazy_tag.update(1, l2, r2, val,id);
            return ;
        }
        int mid = (tree[now].l + tree[now].r) >> 1;
        if(r1 <= mid) update(now<<1, l1, r1, l2, r2, val,id);
        else if(l1 > mid) update(now<<1|1, l1, r1, l2, r2, val,id);
        else update(now<<1, l1, mid, l2, r2, val,id), update(now<<1|1, mid + 1, r1, l2, r2, val,id);
    }
    int query(int now, int l1, int r1, int l2, int r2,int id)
    {
        if(tree[now].l >= l1 && tree[now].r <= r1) return tree[now].tr.query(1, l2, r2,id);
        int mid = (tree[now].l + tree[now].r) >> 1;
        int res = tree[now].lazy_tag.query(1, l2, r2,id);
        if(id<2)
        {
            if(r1 <= mid) return max(res, query(now<<1, l1, r1, l2, r2,id));
            else if(l1 > mid) return max(res, query(now<<1|1, l1, r1, l2, r2,id));
            else return max(res, max(query(now<<1, l1, mid, l2, r2,id), query(now<<1|1, mid + 1, r1, l2, r2,id)));
        }
        else
        {
            if(r1 <= mid) return min(res, query(now<<1, l1, r1, l2, r2,id));
            else if(l1 > mid) return min(res, query(now<<1|1, l1, r1, l2, r2,id));
            else return min(res, min(query(now<<1, l1, mid, l2, r2,id), query(now<<1|1, mid + 1, r1, l2, r2,id)));
        }
    }
};
```



#### 可持久化线段树

------

```c++
//权值线段树，通过前缀和得到区间的线段树的值，再在权值上进行操作求值
//求区间第k小的值
struct Segtree
{
    vector<int> sum, rt, ls, rs;
    int tot = 0;
    Segtree() {}
    Segtree(int n)
    {
        init(n);
    }
    void init(int n)
    {
        int maxn = (n << 5) + 10;
        sum.resize(maxn);
        rt.resize(maxn);
        ls.resize(maxn);
        rs.resize(maxn);
    }
    int build(int l, int r) // 建树
    {
        int root = ++tot;
        if (l == r)
            return root;
        int mid = l + r >> 1;
        ls[root] = build(l, mid);
        rs[root] = build(mid + 1, r);
        return root; // 返回该子树的根节点
    }
    int update(int k, int l, int r, int root) // 插入操作
    {
        int dir = ++tot;
        ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
        if (l == r)
            return dir;
        int mid = l + r >> 1;
        if (k <= mid)
            ls[dir] = update(k, l, mid, ls[dir]);
        else
            rs[dir] = update(k, mid + 1, r, rs[dir]);
        return dir;
    }
    int query(int u, int v, int l, int r, int k)// 查询操作
    { 
        int mid = l + r >> 1,
            x = sum[ls[v]] - sum[ls[u]]; // 通过区间减法得到左儿子中所存储的数值个数
        if (l == r)
            return l;
        if (k <= x) // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
            return query(ls[u], ls[v], l, mid, k);
        else // 否则说明在右儿子中
            return query(rs[u], rs[v], mid + 1, r, k - x);
    }
};
```



### 对顶堆求中位数

```c++
multiset<int>S,T;
void eval()
{
    if(S.size())
    {
        auto itr=S.end();itr--;
        T.insert(*itr);S.erase(itr);
    }
    while(S.size()<T.size())
    {
        S.insert(*T.begin());
        T.erase(T.begin());
    }
}
int val()
{
    auto itr=S.end();itr--;
    if(S.size()==T.size()+1)  return (*itr);
    else return (*itr + *T.begin())/2;
}
void erase(int x)
{
    if(S.empty())
    {
        T.erase(T.lower_bound(x))
	}
    else
    {
        auto itr=S.end();itr--;
        if(*itr<x) T.erase(T.lower_bound(x));
        else S.erase(S.lower_bound(x));
    }
}
```



## 数据结构

### 笛卡尔树

------

![image-20250503003959084](C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20250503003959084.png)



O($n$)复杂度利用单调栈

```c++
//小根
vector<int>stk(n+1),ls(n+1),rs(n+1),w(n+1);
for (int i = 1; i <= n; i++) 
{
    int k = top;  // top 表示操作前的栈顶，k 表示当前栈顶
    while (k > 0 && w[stk[k]] > w[i]) k--;  // 维护右链上的节点
    if (k) rs[stk[k]] = i;  // 栈顶元素.右儿子 := 当前元素
    if (k < top) ls[i] = stk[k + 1];  // 当前元素.左儿子 := 上一个被弹出的元素
    stk[++k] = i;                     // 当前元素入栈
    top = k;
}
```



O($nlog_n$)复杂度利用ST表和分治

```c++
//大根
struct ST{
    vector<vector<pii>>f;
    int n;
    ST(){}
    ST(int n)
    {
        init(n);
    }
    void init(int n)
    {
        this->n=n;
        f.resize(n+1,vector<pii>(31));
    }
    pii quiry(int l,int r)
    {
        int ln=(int)(log(r-l+1)/log(2));
        if(f[l][ln].first < f[r-(1<<ln)+1][ln].first) return f[r-(1<<ln)+1][ln];
        else return f[l][ln];
    }
    void build(vector<int>a)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][0].first=a[i];
            f[i][0].second=i;
        }
        int len=(int)(log(n)/log(2));
        for(int j=1;j<=len;j++)
        {
            for(int i=1;i<=n-(1<<j)+1;i++)
            {
                if(f[i][j-1].first < f[i+(1<<(j-1))][j-1].first) f[i][j]=f[i+(1<<(j-1))][j-1];
                else f[i][j]=f[i][j-1];
            }
        }
    }
};
int main()
{
    int n;cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    ST rmq(n);rmq.build(a);
    vector<vector<int>>g(n+1);
    function<int(int,int)> build = [&] (int l,int r)
    {
        if(l==r) return l;
        auto val=rmq.quiry(l,r);
        int pos=val.second;
        if(pos>l) g[pos].push_back(build(l,pos-1));
        if(pos<r) g[pos].push_back(build(pos+1,r));
        return pos;
    };
    int root = build(1,n);
}
```



### 线性基

------

**用处**

- 快速查询一个数是否可以被一堆数异或出来
- 快速查询一堆数可以异或出来的最大/最小值
- 快速查询一堆数可以异或出来的第k大值性质

**性质**

- 原数列里的任何一个数都可以通过线性基里的数异或表示出来
- 线性基里任意一个子集的异或和都不为0
- 一个数列可能有多个线性基，但是线性基里数的数量一定唯一，而且是满足性质一的基础上最少的

```c++
struct Linear_basis
{
    vector<i64>d;
    int tot=0,n=0;
    Linear_basis()
    {
        d=vector<i64>(61);
    }
    void insert(i64 x)//插入线性基
    {
        n++;
        for(int i=60;i>=0;i--)
        {
            if(x&(1ll<<i))
            {
                if(!d[i])
                {
                    d[i]=x;tot++;
                    break;
                }
                else x^=d[i];
            }
        }
    }
    bool check(i64 x)//判断能否通过原数列异或得到一个数x
    {
        for(int i=60;i>=0;i--)
            if(x&(1ll<<i))
                if(!d[i])return false;
                else x^=d[i];
        return true;
    }
    i64 qmax()//最大异或和
    {
        i64 res=0;
        for(int i=60;i>=0;i--)
            res=max(res,res^d[i]);
        return res;
    }
    i64 qmin()//最小异或和
    {
        if(tot<n) return 0;
        for(int i=0;i<=60;i++)
            if(d[i])return d[i];
    }
    i64 k_th(i64 k)//查询第k小异或和
    {
        if(k==1&&tot<n) return 0;//tot为线性基个数，特判可以异或出0
        if(tot<n) k--;
        for(int i=1;i<=60;i++)
        {
            for(int j=1;j<=i;j++)
            {
                if(d[i] & (1ll<<(j-1)) ) d[i]^=d[j-1];
            }
        }
        i64 ans=0;
        for(int i=0;i<=60;i++)
        {
            if(d[i]!=0)
            {
                if(k%2==1) ans^=d[i];
                k/=2;
            }
        }
        return ans;
    }
};
```



## **图论**

### 网络流

------

#### Dinic

```c++
//最大流
const int N=3005,M=5005,INF=0x3f3f3f3f;
struct MF
{
    struct edge
    {
        int v, c, nxt;
    } edges[M << 1];

    int s, t, idx=0;
    int d[N], cur[N], head[N];

    MF(int s,int t)
    {
        this->s=s;
        this->t=t;
        memset(head,-1,sizeof(head));
    }
    void addedge(int u, int v, int c)
    {
        edges[idx] = {v, c, head[u]};
        head[u] = idx++;

        edges[idx] = {u, 0, head[v]};
        head[v] = idx++;
    }

    bool bfs() // 多路增广，分层搜索优化
    {
        memset(d, 0, sizeof(d));
        queue<int> q;
        q.emplace(s), d[s] = 1;
        while (q.size())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = edges[i].nxt)
            {
                int v = edges[i].v;
                if (!d[v] && edges[i].c)
                {
                    d[v] = d[u] + 1;
                    q.emplace(v);
                    if (v == t) return true;
                }
            }
        }
        return false;
    }

    int dfs(int u, int limit)
    {
        if (u == t) return limit;
        int ret = 0;
        for (int& i = cur[u]; ~i && limit > 0 ; i = edges[i].nxt)//limit > 0 余量优化
        {//弧优化
            int v = edges[i].v;
            if (d[v] == d[u] + 1 && edges[i].c)
            {
                i64 incf = dfs(v, min(limit, edges[i].c));
                if (!incf) d[v] = 0; //剪枝优化
                edges[i].c -= incf, edges[i ^ 1].c += incf, ret += incf, limit -= incf;
            }
        }
        return ret;
    }

    int dinic()
    {
        int ret = 0;
        while (bfs())
        {
            memcpy(cur, head, sizeof(head)), ret += dfs(s, INF);
        }
        return ret;
    }
};
```



#### MCMF

```c++
//最小费用最大流
//基于dinic改进的spfa实现
const int N=5005,M=50005,INF=0x3f3f3f3f;
struct edge{
    int v,nxt,cap,cost;
}edges[M<<1];
int dis[N],cur[N],head[N],vis[N];
i64 ret=0;
int tot=1;
void addedge(int u,int v,int w,int c)
{
    edges[++tot]={v,head[u],w,c};
    head[u]=tot;

    edges[++tot]={u,head[v],0,-c};
    head[v]=tot;
}
bool spfa(int s,int t)
{
    memset(dis,0x3f,sizeof(dis));
    memcpy(cur,head,sizeof(head));
    queue<int>q;
    q.push(s);dis[s]=0,vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();vis[u]=0;
        for(int i=head[u];i;i=edges[i].nxt)
        {
            int v=edges[i].v;
            if(edges[i].cap && dis[v] > dis[u] + edges[i].cost)
            {
                dis[v] = dis[u] + edges[i].cost;
                if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
    }
    return dis[t]!= INF;
}
int dfs(int u, int t,int flow)
{
    if (u == t) return flow;
    vis[u]=1;
    int ans=0;
    for (int &i = cur[u]; i && ans < flow ; i = edges[i].nxt)
    {
        int v = edges[i].v;
        if (!vis[v]  && edges[i].cap && dis[v] == dis[u] + edges[i].cost)
        {
            int x=dfs(v,t,min(edges[i].cap,flow-ans));
            if(x)
            {
                ret += x*edges[i].cost; edges[i].cap-=x;edges[i^1].cap+=x;ans+=x;
            }
        }
    }
    vis[u]=0;
    return ans;
}
int mcmf(int s,int t)
{
    int ans=0;
    while(spfa(s,t))
    {
        int x;
        while((x = dfs(s,t,INF))) ans+=x;
    }
    return ans;
}

//另一种写法
const i64 N=305,M=50005;
const i64 LLINF=1e18;
i64 n,m,s,t,head[N],tot=1;
i64 dis[N],prevv[N],preve[N];
bool vis[N];
struct Edge{
	i64 to,nxt,val,cost;
}e[M];
void add_edge(int x,int y,int z,int cost){
	e[++tot] = {y,head[x],z,cost};
	head[x]=tot;

	e[++tot] = {x,head[y],0,-cost};
	head[y]=tot;
}
bool SPFA(){
	for(int i=s;i<=t;++i) dis[i]=LLINF;
	memset(vis,0,sizeof(vis));
	queue<int>q;
	q.push(s),dis[s]=0,vis[s]=true;
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(e[i].val && dis[y]>dis[x]+e[i].cost){
				prevv[y]=x,preve[y]=i;
				dis[y]=dis[x]+e[i].cost;
				if(!vis[y]){
					q.push(y);
					vis[y]=true;
				}
			}
		}
	}
	return dis[t]!=LLINF;
}
i64 cost,maxflow;
void Dinic()
{
	while(SPFA())
    {
		i64 res=LLINF;
		for(int i=t;i!=s;i=prevv[i]) res=min(res,e[preve[i]].val);
		for(int i=t;i!=s;i=prevv[i]){
			e[preve[i]].val-=res;
			e[preve[i]^1].val+=res;
		}
        maxflow+=res;
		cost+=res*dis[t];
	}
}
```

#### 封装模板

```c++
//求最大流
template<class T>
struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    int n;
    std::vector<_Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
    std::vector<bool> minCut() {
        std::vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }
    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};MaxFlow<int>g(2*n+2);

//dijkstra求最小费用最大流
namespace mcmf {
	using pr = std::pair<i64, int>;
	const int N = 5005, M = 100005;
	struct edge {
		int to, nxt, v; i64 f;
	} e[M << 1];
	int h[N], num = 1;
	void link(int x, int y, int v, i64 f) {
		e[++num] = {y, h[x], v, f}, h[x] = num;
		e[++num] = {x, h[y], 0, -f}, h[y] = num;
	}
	i64 d[N], dis[N];
	int vis[N], fr[N];
	bool dijkstra(int s, int t) { // 正常题目不需要 dijk
		std::priority_queue<pr, std::vector<pr>, std::greater<pr>> Q;
		for(int i = s;i <= t;++i) dis[i] = d[i], d[i] = 1e18, vis[i] = fr[i] = 0; // CHECK
        //从最小点到最大点进行更新
		for(Q.emplace(d[s] = 0, s);!Q.empty();) {
			int x = Q.top().second; Q.pop();
			if(vis[x]) continue;
			vis[x] = 1;
			for(int i = h[x];i;i = e[i].nxt) {
				const i64 v = e[i].f + dis[x] - dis[e[i].to];
				if(e[i].v && d[e[i].to] > d[x] + v) {
					fr[e[i].to] = i;
					Q.emplace(d[e[i].to] = d[x] + v, e[i].to);
				}
			}
		}
		for(int i = s;i <= t;++i) d[i] += dis[i]; // CHECK
		return d[t] < 1e17;
	}
	std::pair<i64, i64> EK(int s, int t) {
		i64 f = 0, c = 0;
		for(;dijkstra(s, t);) { // 正常可以用 spfa
			i64 fl = 1e18;
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) fl = std::min<i64>(e[i].v, fl);
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) e[i].v -= fl, e[i ^ 1].v += fl;
			f += fl, c += fl * d[t];
		}
		return std::make_pair(f, c);
	}
}
```



### Tarjan算法

------

#### 强连通分量

```c++
vector<int>dfn(n+1),low(n+1),s(n+1),in_stack(n+1);
int dfncnt,tp,sc;
vector<int>scc(n+1);  // 结点 i 所在 SCC 的编号
vector<int>sz(n+1);       // 强连通 i 的大小

function<void(int)> tarjan = [&] (int u) 
{
    low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
    for (auto v:g[u]) 
    {
        if (!dfn[v]) 
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } 
        else if (in_stack[v]) 
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) 
    {
        ++sc;
        while (s[tp] != u) 
        {
            scc[s[tp]] = sc;
            sz[sc]++;
            in_stack[s[tp]] = 0;
            --tp;
        }
        scc[s[tp]] = sc;
        sz[sc]++;
        in_stack[s[tp]] = 0;
        --tp;
    }
};
```



#### 割点与点双

```c++
int n,m;cin>>n>>m;
vector<vector<int>>g(n+1);
for(int i=1;i<=m;i++)
{
    int u,v;cin>>u>>v;
    g[u].push_back(v);
    g[v].push_back(u);
}
int num=0,top=0,cnt=0;
vector<int>dfn(n+1),low(n+1),sta(n+1),cut(n+1);
vector<vector<int>>dcc(n+1);
function<void(int,int)> tarjan = [&] (int u,int root)
{
    dfn[u]=low[u]=++num;
    sta[++top]=u;
    if(u==root && g[u].size()==0)
    {
        dcc[++cnt].push_back(u);
        return;
    }
    int flag=0;
    for(auto v:g[u])
    {
        if(!dfn[v])
        {
            tarjan(v,root);
            low[u]=min(low[u],low[v]);
            if(low[v] >= dfn[u])
            {
                flag++;
                if(u!=root || flag>1)
                {
                    cut[u]=1;//割点
                }
                cnt++;
                int z;
                do{
                    z=sta[top--];
                    dcc[cnt].push_back(z);
                }while(z!=v);
                dcc[cnt].push_back(u);//点双连通分量
            }
        }
        else
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
};
for(int i=1;i<=n;i++)
{
    if(!dfn[i]) tarjan(i,i);
}
cout<<cnt<<"\n";
for(int i=1;i<=cnt;i++)
{
    for(auto j:dcc[i]) cout<<j<<" ";cout<<"\n";
}

//桥边
vector<int>father(n+1),low(n+1),dfn(n+1),isbridge(n+1);
int dfs_clock=0,cnt_bridge=0;
function<void(int,int)> tarjan = [&] (int u, int fa) 
{
    father[u] = fa;
    low[u] = dfn[u] = ++dfs_clock;
    for (auto v:g[u]) 
    {
        if (!dfn[v]) 
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) 
            {
                isbridge[v] = true;
                ++cnt_bridge;
            }
        } 
        else if (dfn[v] < dfn[u] && v != fa) 
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
};
for(int i=1;i<=n;i++)
{
    if(!dfn[i]) tarjan(i,0);
}
```



### 最短路

------

#### Bellman-Ford 算法

Bellman-Ford 算法是一种基于松弛（relax）操作的最短路算法，

可以求出有负权的图的最短路，并可以对最短路不存在的情况进行判断。

```c++
auto bellmanford = [&] (int s)
{
    vector<int>dis(n+1,1e9);
    dis[s]=0;
    int flag;
    for(int i=1;i<=n;i++)
    {
        flag=0;// 判断一轮循环过程中是否发生松弛操作
        for(int u=1;u<=n;u++)
        {
            if(dis[u]==1e9) continue;
            // 无穷大与常数加减仍然为无穷大
            // 因此最短路长度为 inf 的点引出的边不可能发生松弛操作
            for(auto x:g[u])
            {
                int v=x.first,w=x.second;
                if(dis[v] > dis[u] + w)
                {
                    dis[v]=dis[u]+w;
                    flag=1;
                }
            }
        }
        // 没有可以松弛的边时就停止算法
        if(!flag) break;
    }
    // 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
    return flag;
};


//队列优化：SPFA
auto spfa = [&] (int s)
{
    vector<int>dis(n+1,1e9),vis(n+1,0),cnt(n+1);
    dis[s]=0,vis[s]=1;
    queue<int>q;q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop(),vis[u]=0;
        for(auto x:g[u])
        {
            int v=x.first,w=x.second;
            if(dis[v] > dis[u]+w)
            {
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;// 记录最短路经过的边数
                if(cnt[v] >= n) return false;
                // 在不经过负环的情况下，最短路至多经过 n - 1 条边
                // 因此如果经过了多于 n 条边，一定说明经过了负环
                if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
    }
    return true;    
};
```



#### Dijkstra 算法

------

一种求解 **非负权图** 上单源最短路径的算法

在稀疏图中![m = O(n)](data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7)，[m = O(n)]，使用二叉堆实现的 Dijkstra 算法较 Bellman-Ford 算法具有较大的效率优势；

而在稠密图中![m = O(n^2)](data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7)，m = O(n^2)，这时候使用暴力做法较二叉堆实现更优。

```c++
struct node {
  int dis, u;

  bool operator>(const node& a) const { return dis > a.dis; }
};

auto dijkstra = [&] (int s)
{
    vector<int>dis(n+1,1e9),vis(n+1,0);
    priority_queue<pii,vector<pii>,greater<pii> > q;
    dis[s]=0;q.push({0,s});
    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto x:g[u])
        {
            int v=x.first,w=x.second;
            if(dis[v] > dis[u]+w)
            {
                dis[v]=dis[u]+w;
                q.push({dis[v],v});
            }
        }
    }
    return dis;
};
```



## 树

### 树的基础

------

#### 树的直径

```c++
//树形dp可以在存在负权边的情况下求解出树的直径。
//记录每个节点作为子树的根时，向下延伸的最长路径长度d1与次长路径（与最长路径无公共边）长度d2
//直径是每一个点的 d1 + d2 的最大值。
vector<vector<pii>> g(n+1);
vector<int>d1(n+1),d2(n+1);
for (int i = 1; i < n; i++) 
{
    int u,v,w; cin >> u >> v >> w;
    g[u].push_back({v,w}),g[v].push_back({u,w});
}
int d=0;
function<void(int,int)> dfs = [&] (int u,int fa)
{
    d1[u] = d2[u] = 0;
    for (auto [v,w] : g[u]) 
    {
        if (v == fa) continue;
        dfs(v, u);
        int t = d1[v] + w;
        if (t > d1[u]) d2[u] = d1[u], d1[u] = t;
        else if (t > d2[u]) d2[u] = t;
    }
    d = max(d, d1[u] + d2[u]);
};
```



#### 树的重心

```c++
//计算节点所有子树中最大的子树节点数，值最小的点就是这棵树的重心
//一棵树的重心最多有两个，并且相邻
vector<int>siz(n+1),weight(n+1),centroid(2);
vector<vector<int>>g(n+1);
function<void(int,int)>  GetCentroid = [&] (int u, int fa) 
{  
    siz[u] = 1;
    weight[u] = 0;
    for (auto v:g[u]) 
    {
        if (v==fa) continue;
        GetCentroid(v,u);
        siz[u] += siz[v];
        weight[u] = max(weight[u], siz[v]);

    }
    weight[u] = max(weight[u], n - siz[u]);
    if (weight[u] <= n / 2) {
        centroid[centroid[0] != 0] = u;
    }
};
```



### LCA

------

#### 倍增算法

```c++
//倍增算法是经典的LCA算法，通过预处理fa[x][i]数组，fa[x][i]表示点 x 的第 2^i 个祖先。
//fa[x][i]数组可以通过 dfs 预处理出来。

vector f(n+1,vector<int>(31));
vector<int>dep(n+1);
function<void(int,int)> dfs = [&] (int u,int fa)
{
    f[u][0]=fa;dep[u]=dep[fa]+1;
    for(int i=1;i<=30;i++)
    {
        f[u][i]=f[f[u][i-1]][i-1];
    }
    for(int v:g[u])
    {
        if(v==fa) continue;
        dfs(v,u);
    }
};dfs(1,0);

auto LCA = [&](int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    int temp=dep[y]-dep[x];
    for(int j=0;temp;j++,temp>>=1)
    {
        if(temp&1) y=f[y][j];
    }
    if(y==x) return x;

    for(int i=30;i>=0 && x!=y ;i--)
    {
        if(f[x][i]!=f[y][i])
        {
            x=f[x][i],y=f[y][i];
        }
    }
    return f[x][0];
};
```



#### 欧拉序求LCA

```c++
//得到欧拉序之后，两点第一次出现的位置之间的深度最小的点就是LCA
//求区间深度最小值利用st表

//a数组表示欧拉序列，p数组表示各个值第一次出现的位置
vector<int>dep(n+1,0),a(2*n+1),p(n+1);
int tim=0;
function<void(int,int)> dfs = [&] (int u,int fa)
{
    dep[u]=dep[fa]+1;
    a[++tim]=u;p[u]=tim;
    for(auto v:g[u]) if(v!=fa)
    {
        dfs(v,u);
        a[++tim]=u;
    }
};dfs(1,0);

vector<vector<pii>>f(cnt+1,vector<pii>(31));
for(int i=1;i<=cnt;i++)
{
    f[i][0]={dep[a[i]],a[i]};
}
int len=(int)(log(cnt)/log(2));
for(int j=1;j<=len;j++)
{
    for(int i=1;i<=cnt-(1<<j)+1;i++)
    {
        f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    }
}
auto quiry = [&] (int l,int r)
{
    l=p[l],r=p[r];
    if(l>r) swap(l,r);
    int ln=(int)(log(r-l+1)/log(2));
    return (min(f[l][ln],f[r-(1<<ln)+1][ln]));
};
```



### Dsu on tree

------

遍历一个节点u：

- 遍历所有轻儿子，计算答案，但是不保留遍历之后的影响
- 遍历重儿子，保留遍历之后的影响
- 再次遍历所有轻儿子，加入这些节点的贡献

```c++
//https://codeforces.com/contest/600/problem/E
//解决树上离线问题
int main()
{
    int n;cin>>n;
    vector<i64>col(n+1),siz(n+1),son(n+1),ans(n+1),cnt(n+1);
    i64 mx=0,sum=0,Son=0;
    for(int i=1;i<=n;i++) cin>>col[i];
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;i++)
    {
        int x,y;cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    function<void(int,int)> dfs1 =[&] (int x,int fa)
    {
        siz[x]+=1;
        for(auto y:g[x])
        {
            if(y==fa) continue;
            dfs1(y,x);
            siz[x]+=siz[y];
            if(siz[y]>siz[son[x]]) son[x]=y;////轻重链剖分
        }
    };dfs1(1,0);
    
    function<void(int,int,int)> add = [&] (int x,int fa,int val)
    {
        cnt[col[x]]+=val;
        if(cnt[col[x]]>mx)
        {
            mx=cnt[col[x]];sum=col[x];
        }
        else if(cnt[col[x]]==mx) sum+=col[x];
        for(auto y:g[x])
        {
            if(y==fa || y==Son) continue;
            add(y,x,val);
        }
    };
    function<void(int,int,int)> dfs2 = [&] (int x,int fa,int op)
    {
        for(auto y:g[x]) if(y!=fa)
        {
            if(y!=son[x]) dfs2(y,x,0);
        }//暴力统计轻边的贡献，op = 0表示递归完成后消除对该点的影响
        
        if(son[x]) dfs2(son[x],x,1),Son=son[x];//统计重儿子的贡献，不消除影响

        add(x,fa,1);Son=0;//暴力统计所有轻儿子的贡献

        ans[x]=sum;//更新答案
        if(!op) add(x,fa,-1),sum=0,mx=0;//如果需要删除贡献的话就删掉
    };
    dfs2(1,0,0);
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
    return 0;   
}
```



### 虚树

------

#### 二次排序 + LCA

```c++
//将关键点按 DFS 序排序
//遍历一遍，任意两个相邻的关键点求一下 LCA，并且判重
//然后根据原树中的祖先后代关系建树

vector<int>dfn(n+1),dep(n+1);int tot=0;
vector<vector<int>>f(n+1,vector<int>(31));
function<void(int,int)> dfs1 = [&] (int u,int fa)
{   
    f[u][0]=fa;dep[u]=dep[fa]+1;
    dfn[u]=++tot;
    for(int i=1;i<=30;i++)
    {
        f[u][i]=f[f[u][i-1]][i-1];
    }
    for(auto v:g[u]) if(v!=fa)
    {
        dfs1(v,u);
    }
};dfs1(1,0);

auto LCA = [&](int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    int temp=dep[y]-dep[x];
    for(int j=0;temp;j++,temp>>=1)
    {
        if(temp&1) y=f[y][j];
    }
    if(y==x) return x;

    for(int i=30;i>=0 && x!=y ;i--)
    {
        if(f[x][i]!=f[y][i])
        {
            x=f[x][i],y=f[y][i];
        }
    }
    return f[x][0];
};

vector<vector<int>>e(n+1);//虚树
auto buildvt = [&] (vector<int>h)
{
    auto cmp = [&] (int x,int y){
        return dfn[x]<dfn[y];
    };//按照dfn序进行排序
    sort(h.begin(),h.end(),cmp);
    int m=h.size();
    for(int i=1;i<m;i++) h.push_back(LCA(h[i-1],h[i]));//加入相邻两个数的lca
    h.push_back(1);
    sort(h.begin(),h.end(),cmp);
    h.erase(unique(h.begin(),h.end()),h.end());
    m=h.size();
    for(int i=1;i<m;i++)
    {
        int lc=LCA(h[i-1],h[i]);
        e[lc].push_back(h[i]);
    }//将lca(x,y)与y进行连边
    return h;
};
for(int i=1;i<=n;i++) if(!col[i].empty())
{
    vector<int> v=buildvt(col[i]);
    for(auto x:v) e[x].clear();
}
```



### 珂朵莉树

------

**什么是珂朵莉树？**

> 珂朵莉树是一种以近乎暴力的形式存储区间信息的一个数据结构。方式是通过set存放若干个用结构体表示的区间，每个区间的元素都是相同的

**珂朵莉树的用途？**

> 只要是涉及到区间赋值操作的题，就可以用珂朵莉树处理几乎任何关于区间信息的询问

**什么情况下可以用珂朵莉树而不被卡？**

> 珂朵莉树是一种优美的暴力，他的优美是建立在区间的合并操作上，即区间赋值，那么如果构造出一组数据使得其几乎不含区间赋值操作，那珂朵莉树就会被轻易的卡掉。所以珂朵莉树要求题目必须存在区间赋值操作，且数据有高度的随机性

```c++
struct ran{
    int l,r;
    mutable i64 v;//在进行操作时往往需要修改v的值，一般使用&，在结构体中使用mutable变量
    ran(int L,int R=-1,i64 V=0){
        l=L,r=R,v=V;
    }
    bool operator < (const ran &x)const{ // 重载运算符，用于set的排序
        return l < x.l;//按区间的左端点大小进行排序
    }
};//珂朵莉树通过节点来存储区间，用结构体
set<ran>st;

auto split(int pos)//查找pos所在区间
{
    auto it=st.lower_bound(ran(pos));
    if(it!=st.end() && it->l==pos) return it;
    it--;
    int l=it->l;
    int r=it->r;
    i64 v=it->v;
    st.erase(it);
    st.insert(ran(l,pos-1,v));//分成[l,pos-1]和[pos,r]两个区间
    return st.insert(ran(pos,r,v)).first;
    //set的insert函数插入成功有返回值，会返回一个pair<set ::iterator , bool>,第一个值是插入的元素的迭代器
}

void emerge(int l,int r,int x)//区间赋值，合并区间
{
    auto itr=split(r+1);auto itl=split(l);
    //先取右侧，在取左侧，否侧会因为顺序相反而是第一个的元素地址删除，造成RE
    st.erase(itl,itr);//set函数删除连续的区间，左闭右开
    st.insert(ran(l,r,x));
}
```



### Kruskal重构树

------

- Kruskal 重构树就是基于 Kruskal 的最小生成树算法在无向图中得出的树所构造而成的树

- 把最小生成树上的边从小到大取出来，这条边为 x 与 y 连边，那么我们新建节点 now，将 now 连向 *x*,*y*，将now的点权设为这条边的边权，x 与 y 之间不连边。



```c++
//二叉树
//原节点是Kruskal重构树的叶子节点
//原图中两个点间所有路径上的边最大权值的最小值 = 最小生成树上两点简单路径的边最大权值 = Kruskal 重构树上两点 LCA 的点权
void Ex_Kruskal()
{
    int cnt=n;
    sort(edge.begin(),edge.end());
    for(int i=0;i<m;i++)
    {
        auto [u,v,w]=edge[i];
        int fx=find(u),fy=find(v);
        if(fx!=fy)
        {
            cnt++;
            weight[cnt]=w;
            fa[fx]=cnt,fa[fy]=cnt;
            lch[cnt]=fx,rch[cnt]=fy;
		}
	}
}
```



### Prufer序列

------

对树建立 Prufer 序列,每次选择一个编号最小的叶结点并删掉它，然后在序列中记录下它连接到的那个结点。重复n-2次后就只剩下两个结点。

```c++
//在构造完 Prüfer 序列后原树中会剩下两个结点，其中一个一定是编号最大的点 n。
//每个结点在序列中出现的次数是其度数减 1。（没有出现的就是叶结点）

//利用小根堆来建立树的prufer序列
vector<vector<int>> adj;
vector<int> pruefer_code() 
{
    int n = adj.size();
    set<int> leafs;
    vector<int> degree(n);
    vector<bool> killed(n);
    for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size();
        if (degree[i] == 1) leafs.insert(i);
    }

    vector<int> code(n - 2);
    for (int i = 0; i < n - 2; i++) {
        int leaf = *leafs.begin();
        leafs.erase(leafs.begin());
        killed[leaf] = true;
        int v;
        for (int u : adj[leaf])
            if (!killed[u]) v = u;
        code[i] = v;
        if (--degree[v] == 1) leafs.insert(v);
    }
    return code;
}

//根据 Prüfer 序列的性质，我们可以得到原树上每个点的度数。然后你也可以得到编号最小的叶结点，而这个结点一定与 Prüfer 序列的第一个数连接。然后我们同时删掉这两个结点的度数。

//每次我们选择一个度数为 1 的最小的结点编号，与当前枚举到的 Prüfer 序列的点连接，然后同时减掉两个点的度。到最后我们剩下两个度数为 1 的点，其中一个是结点 n。就把它们建立连接。使用堆维护这个过程，在减度数的过程中如果发现度数减到 1 就把这个结点添加到堆中
vector<pair<int, int>> pruefer_decode(vector<int> const& code) 
{
      int n = code.size() + 2;
      vector<int> degree(n, 1);
      for (int i : code) degree[i]++;

      set<int> leaves;
      for (int i = 0; i < n; i++)
        if (degree[i] == 1) leaves.insert(i);

      vector<pair<int, int>> edges;
      for (int v : code) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());

        edges.emplace_back(leaf, v);
        if (--degree[v] == 1) leaves.insert(v);
      }
      edges.emplace_back(*leaves.begin(), n - 1);
      return edges;
}
```



## 字符串

### KMP

```c++
auto kmp = [&] (string s,string t)
{
  	int n=s.size(),m=t.size();
    s=" "+s,t=" "+t;
    vector<int>nxt(m+1,0);
    int j=0;
    for(int i=2;i<=m;i++)
    {
        while(j>0 && t[j+1]!=t[i])
        {
            j=nxt[j];
		}
        if(t[j+1]==t[i]) j++;
        nxt[i]=j;
    }
    j=0;
    vector<int>f(n+1,0);
    for(int i=1;i<=n;i++)
    {
        while(j==m || (j>0 && t[j+1]!=s[i]))
        {
            j=nxt[j];
		}
        if(t[j+1]==s[i]) j++;
        f[i]=j;
	}
    return f;
};

vector<int> kmp(string s)
{//s=s[i]+'#'+s[j]
    int n=s.size();
    vector<int>f(n+1);
    for(int i=1,j=0;i<n;i++)
    {
        while(j && s[i]!=s[j])
        {
            j=f[j];
        }
        j+=(s[i]==s[j]);
        f[i+1]=j;
    }
    return f;
}
//求最短公共前后缀
auto kmp = [&] (string t)
{
    int m=t.size();
    t=" "+t;
    vector<int>nxt(m+1,0);
    for(int i=2,j=0;i<=m;i++)
    {
        while(j>0 && t[j+1]!=t[i])
        {
            j=nxt[j];
        }
        if(t[j+1]==t[i]) j++;
        nxt[i]=j;
    }
    for(int i=2,j=2;i<=m;i++,j=i)
    {
        while(nxt[j]) j=nxt[j];
        if(nxt[i]) nxt[i]=j;
    }
    return nxt;
};
```



### SA

------

![image-20240920141341707](C:\Users\GLH\AppData\Roaming\Typora\typora-user-images\image-20240920141341707.png)

倍增排序时间复杂度为O($\ nlog^2 n$）

```c++
//倍增排序
string s;cin>>s;s=" "+s;
int n=s.size()-1;
vector<int>sa(n+1),rk(2*n+1),oldrk(n+n+1);
for (int i = 1;i <= n; ++i) sa[i] = i, rk[i] = s[i];
for (int w = 1; w < n; w <<= 1) 
{
    sort(sa.begin()+1, sa.end(), [&](int x, int y) {
    	return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
    });
    oldrk=rk;// 由于计算 rk 的时候原来的 rk 会被覆盖，要先复制一份
    for (int p = 0, i = 1; i <= n; ++i) 
    {
        if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) 
        {
        	rk[sa[i]] = p;
        } 
        else 
        {
            rk[sa[i]] = ++p;
        }  // 若两个子串相同，它们对应的 rk 也需要相同，所以要去重
    }
}
```



## DP

### SOS DP

解决子集和问题，$\text{sum}[i] = \sum_{j \subseteq i} a[j]$

常规的O($3^n$)写法

```c++
for(int i=0;i<1<<n;i++) {
    sum[i]=a[0];
    for(int j=i;j;j=(j-1)&i) {
        sum[i]+=a[j];
    }
}
```

sos dp 时间复杂度为O($n2^n$)

```c++
for(int i=0;i<n;i++) {
    for(int j=0;j<1<<n;j++) if(j&(1<<i)) {
        sum[j]+=sum[j^(1<<i)];
    }
}//解决子集和

for(int i=0;i<n;i++) {
    for(int j=(1<<n)-1;~j;j--) if(j&(1<<i)) {
        sum[j^(1<<i)]+=sum[j];
    }
}//维护超集和
```



### Bitset优化01背包

```c++
for(int i=1;i<=n;i++)
	bt |= (bt<<a[i]);

```



## 计算几何

### 凸包

```c++
const double eps=1e-9; 
const double PI=acos(-1.0);
struct Point{
    long double x,y;
    Point(long double x = 0,long double y = 0) : x(x), y(y) {}
    Point &operator+=(const Point &rhs) {
        x += rhs.x; y += rhs.y;
        return *this;
    }
    Point &operator-=(const Point &rhs) {
        x -= rhs.x; y -= rhs.y;
        return *this;
    }
    friend Point operator+(const Point &lhs, const Point &rhs) { //+
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    friend Point operator-(const Point &lhs, const Point &rhs) { //-
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    friend Point operator*(const Point &lhs, double t){ //数乘
        return Point(lhs.x * t, lhs.y * t);
    }
    friend Point operator/(const Point &lhs, double t){ //数乘
        return Point(lhs.x / t, lhs.y / t);
    }
    //叉积可以用来判断rhs在lhs的方向,顺时针<0,逆时针>0
    friend double operator*(const Point &lhs, const Point &rhs){ //叉积 a,b为向量
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }
    friend double operator&(const Point &lhs, const Point &rhs){ //点积 a,b为向量
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    friend bool operator<(const Point &lhs, const Point &rhs){ //点积 a,b为向量
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
    double len() const{ //向量的模
        return sqrt(x * x + y * y);
    }
    void zero(){  //判断是否是0
        if(fabs(x)<=eps) x=0;
        if(fabs(y)<=eps) y=0;
    }
};
Point norm(Point a){ //单位向量
    return a/a.len();
}
long double dis(Point a,Point b){ //两点间距离
    return (a-b).len();
}
double cross(Point a,Point b,Point c){ //叉积 a,b,c为点,b-a,c-a向量叉积
    return (b - a) * (c - a);
}
double dot(Point a,Point b,Point c){ //点积 a,b,c为点,b-a,c-a向量点积
    return (b - a) & (c - a);
}
double angle(Point a,Point b){ //求夹角
    return acos((a & b) / a.len() / b.len());
}
double getarea(Point a,Point b,Point c){//求三角形面积
    return 0.5*abs((b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y));
}
//获取两直线的交点,其中a,b为点,u,v为a和b的方向向量
Point cross(Point a,Point u,Point b,Point v){
    double t = (a - b) * v / (v * u);
    return a + u * t;
}
Point rotate(Point a,double b){ //逆时针转b角
    return Point(a.x*cos(b)-a.y*sin(b),a.x*sin(b)+a.y*cos(b));
}
//判断线段ab与线段cd是否相交 0为不相交,1为相交
bool intersect(Point a,Point b,Point c,Point d){
    if(cross(a , b , c)*cross(a , b , c) > 0) return 0;
    if(cross(c , d , a)*cross(c , d , b) > 0) return 0;
    return 1;
}
pair<Point,Point> midperp(Point a,Point b){ //中垂线,方向a->b逆时针转90度
    return {(a+b)/2,rotate(b-a,PI/2)}; 
}

int n,top,tot;
vector<Point>p(n+1),s(2*n+1);

auto Andrew = [&] ()
{
    top=tot=0;
    sort(p.begin()+1,p.end());//排序
    for(int i=1;i<=n;i++){//下凸包
        while(top>1&&cross(s[top-1],s[top],p[i])<=0) top--;
        s[++top]=p[i];
    }
    int t=top;
    for(int i=n-1;i>=1;i--){//上凸包
        while(top>t&&cross(s[top-1],s[top],p[i])<=0) top--;
        s[++top]=p[i];
    }
    tot=top-1;
}//求凸包
auto gatmax = [&]()
{
    if(tot==1) return 0;
    if(top<4)
    {
        return dis(s[1],s[2]);
    }
    long double mx=0;
    for(int i=1,j=3;i<top;i++)
    {
        while (cross(s[i], s[i + 1], s[j]) <=
               cross(s[i], s[i + 1], s[j % top + 1]))
            j = j % top + 1;
        mx = max(mx, max(dis(s[i + 1], s[j]), dis(s[i], s[j])));
    }
    return mx;
}//凸包直径
```

### 三维直线

```c++
struct Point{
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

// 向量减法
Point operator-(const Point& a, const Point& b)
{
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

// 向量叉积
Point cross(const Point& a, const Point& b) 
{
    return Point(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// 向量点积
double dot(const Point& a, const Point& b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 向量模长
double norm(const Point& a) 
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// 计算两条直线的最近距离
double LineDis(const Point& P1, const Point& P2, const Point& Q1, const Point& Q2) 
{
    Point u = P2 - P1; 
    Point v = Q2 - Q1; 
    Point w = Q1 - P1; 

    Point n = cross(u, v);

    if (norm(n) < 1e-10) // 两条直线平行
    { 
        Point now = cross(w, u);
        return norm(now) / norm(u);
    } 
    else 
    {
        return fabs(dot(w, n)) / norm(n);
    }
}
```

