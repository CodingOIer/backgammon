#include <algorithm>
#include <cstdio>
#include <random>
#include <tuple>
std::mt19937 rnd(std::random_device{}());
constexpr int n = 5;
constexpr int MaxN = 25;
constexpr int MaxCallStack = 4;
constexpr int MaxRandomPoint = 30;
int block[MaxN][MaxN];
inline int make(int gx, int gy)
{
    int res = 0;
    res += std::min(gx, n - gx + 1) * 3 + std::min(gy, n - gy + 1) * 3;
    res += rnd() % 11 + -5;
    return res;
}
inline bool checkLine(int x, int y)
{
    int last = block[x][y];
    if (block[x][y] == 0)
    {
        return false;
    }
    for (int k = 1; k < 5; k++)
    {
        if (last != block[x][y + k])
        {
            return false;
        }
    }
    return true;
}
inline bool checkRow(int x, int y)
{
    int last = block[x][y];
    if (block[x][y] == 0)
    {
        return false;
    }
    for (int k = 1; k < 5; k++)
    {
        if (last != block[x + k][y])
        {
            return false;
        }
    }
    return true;
}
inline bool checkInc(int x, int y)
{
    int last = block[x][y];
    if (block[x][y] == 0)
    {
        return false;
    }
    for (int k = 1; k < 5; k++)
    {
        if (last != block[x + k][y + k])
        {
            return false;
        }
    }
    return true;
}
inline void check(int &p, int who)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (checkLine(i, j))
            {
                if (who == block[i][j])
                {
                    p += 1000;
                }
                else
                {
                    p -= 1000;
                }
            }
            if (checkRow(i, j))
            {
                if (who == block[i][j])
                {
                    p += 1000;
                }
                else
                {
                    p -= 1000;
                }
            }
            if (checkInc(i, j))
            {
                if (who == block[i][j])
                {
                    p += 1000;
                }
                else
                {
                    p -= 1000;
                }
            }
        }
    }
}
int calc(int who, int stack)
{
    int app = 0;
    check(app, who);
    if (stack > MaxCallStack)
    {
        return app;
    }
    int rx = 0, ry = 0;
    int best = 0x3f3f3f3f;
    for (int cnt = 1; cnt <= MaxRandomPoint; cnt++)
    {
        int gx, gy;
        gx = 0;
        gy = 0;
        for (; (gx == 0 && gy == 0) || block[gx][gy] != 0;)
        {
            gx = rnd() % n + 1;
            gy = rnd() % n + 1;
        }
        block[gx][gy] = who;
        int res = -calc(3 - who, stack + 1) + make(gx, gy) + app;
        block[gx][gy] = 0;
        best = std::min(res, best);
    }
    return best;
}
std::pair<int, int> next(int who)
{
    int best = 0x3f3f3f3f;
    int rx = 0, ry = 0;
    for (int gx = 1; gx <= n; gx++)
    {
        for (int gy = 1; gy <= n; gy++)
        {
            if (block[gx][gy] != 0)
            {
                continue;
            }
            block[gx][gy] = who;
            int res = -calc(3 - who, 1) + make(gx, gy);
            block[gx][gy] = 0;
            if (res < best)
            {
                best = res;
                rx = gx;
                ry = gy;
            }
        }
    }
    return {rx, ry};
}
inline void print()
{
    printf("+");
    for (int i = 1; i <= n; i++)
    {
        printf("-");
    }
    printf("+\n");
    for (int i = 1; i <= n; i++)
    {
        printf("|");
        for (int j = 1; j <= n; j++)
        {
            printf("%c", block[i][j] == 0 ? ' ' : (block[i][j] == 1 ? '#' : '@'));
        }
        printf("|\n");
    }
    printf("+");
    for (int i = 1; i <= n; i++)
    {
        printf("-");
    }
    printf("+\n");
}
inline void get(int who)
{
    auto res = next(who);
    block[res.first][res.second] = who;
}
int main()
{
    block[1][1] = 1;
    block[1][2] = 1;
    block[1][3] = 1;
    block[1][4] = 1;
    auto res = next(2);
    printf("%d %d\n", res.first, res.second);
    /* for (int i = 1; i <= n; i++)
    {
        // system("cls");
        print();
        int x, y;
        scanf("%d%d", &x, &y);
        block[x][y] = 1;
        // system("cls");
        print();
        get(2);
    } */
    return 0;
}