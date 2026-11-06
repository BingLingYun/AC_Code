#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    vector dir(n + 1, vector<int>(m + 1));
    if (n % 2 == 0)
    {
        for (int i = 2; i <= n; i++)
            dir[i][1] = 0;
        dir[1][1] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 2; j <= m; j++)
            {
                if (i % 2 == 1)
                {
                    dir[i][j] = 1;
                    if (j == m)
                        dir[i][j] = 2;
                }
                else
                {
                    dir[i][j] = 3;
                    if (j == 2)
                        dir[i][j] = 2;
                }
            }
        }
        dir[n][2] = 3;
    }
    else if (m % 2 == 0)
    {
        for (int i = 2; i <= m; i++)
            dir[1][i] = 3;
        dir[1][1] = 2;
        for (int j = 1; j <= m; j++)
        {
            for (int i = 2; i <= n; i++)
            {
                if (j % 2 == 1)
                {
                    dir[i][j] = 2;
                    if (i == n)
                        dir[i][j] = 1;
                }
                else
                {
                    dir[i][j] = 0;
                    if (i == 2)
                        dir[i][j] = 1;
                }
            }
        }
        dir[2][m] = 0;
    }
    else
    {
        for (int i = 1; i <= n - 2; i++)
        {
            for (int j = 3; j <= m; j++)
            {
                if (j % 2 == 1)
                {
                    dir[i][j] = 0;
                    if (i == 1)
                        dir[i][j] = 3;
                }
                else
                {
                    dir[i][j] = 2;
                    if (i == n - 2)
                        dir[i][j] = 3;
                }
            }
        }
        dir[1][2] = 3;
        int nx = 1, ny = 1;
        for (int i = 1; i <= (n - 1) / 2 - 1; i++)
        {
            dir[nx][ny] = 2;
            nx++;
            dir[nx][ny] = 1;
            ny++;
            dir[nx][ny] = 2;
            nx++;
            dir[nx][ny] = 3;
            ny--;
        }
        dir[nx][ny] = 2;
        nx++;
        dir[nx][ny] = 2;
        nx++;
        for (int i = 1; i <= ((m - 1) / 2) - 1; i++)
        {
            dir[nx][ny] = 1;
            ny++;
            dir[nx][ny] = 0;
            nx--;
            dir[nx][ny] = 1;
            ny++;
            dir[nx][ny] = 2;
            nx++;
        }
        dir[nx][ny] = 1;
        dir[n][m - 1] = 0;
        dir[n - 1][m - 1] = 1;
        dir[n - 1][m] = 0;
        dir[n][m] = 0;
    }
    auto print = [&](int &x, int &y)
    {
        if (dir[x][y] == 0)
        {
            cout << "U";
            x--;
        }
        else if (dir[x][y] == 1)
        {
            cout << "R";
            y++;
        }
        else if (dir[x][y] == 2)
        {
            cout << "D";
            x++;
        }
        else
        {
            cout << "L";
            y--;
        }
    };
    if (n % 2 == 0 || m % 2 == 0)
    {
        for (int i = 1; i <= n * m - 1; i++)
        {
            int x, y;
            cin >> x >> y;
            while (1)
            {
                print(r, c);
                if (r == x && c == y)
                    break;
            }
            cout << endl;
        }
    }
    else
    {
        for (int i = 1; i <= n * m - 1; i++)
        {
            int x, y;
            cin >> x >> y;
            if (x == n && y == m)
            {
                dir[n][m - 1] = 1;
            }
            while (1)
            {
                print(r, c);
                if (r == x && c == y)
                    break;
            }
            cout << endl;
            if (x == n && y == m)
            {
                dir[n][m - 1] = 0;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout << fixed << setprecision(15);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}