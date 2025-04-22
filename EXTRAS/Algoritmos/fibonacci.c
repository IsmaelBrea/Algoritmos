#include <stdio.h>

int fib1(int x)
{
    if (x < 2)
        return (x);
    else
        return ((fib1(x - 1) + fib1(x - 2)));
}

int fib2(int x)
{
    int i = 1, j = 0, k;

    for (k = 1; k <= x; k++)
    {
        j = i + j;
        i = j - i;
    }
    return j;
}

int fib3(int x)
{
    int j = 0, k = 0, t = 0;
    int i = 1, h = 1;

    while (x > 0)
    {
        if (x % 2 == 1)
        {
            t = j * h;
            j = i * h + j * k + t;
            i = i * k + t;
        }
        t = h * h;
        h = 2 * k * h + t;
        k = k * k + t;
        x = x / 2;
    }
    return j;
}

void test(int max)
{
    int i;

    printf("|  i  | fib1 | fib2 | fib3 |\n");
    for (i = 0; i <= max; i++)
        printf("|%5d|%6d|%6d|%6d|\n", i, fib1(i), fib2(i), fib3(i));
}

int main()
{
    test(25);
    return 0;
}