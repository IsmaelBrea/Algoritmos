#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void ord_ins(int v[], int n)
{
    int i, x, j;

    for (i = 0; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void inicializar_semilla()
{
    srand(time(NULL));
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
}

void aleatorio(int v[], int n)
{ /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void print_vector(int v[], int n)
{
    int i;
    printf("  [");
    for (i = 0; i < n; i++)
    {
        printf("%3d", v[i]);
        if (i != n - 1)
            printf(",");
    }
    printf("]\n");
}

void test(int tam)
{
    int v[tam];

    printf(" 1. Vector ascendente:\n");
    ascendente(v, tam);
    print_vector(v, tam);
    ord_ins(v, tam);
    print_vector(v, tam);

    printf(" 2. Vector descendente:\n");
    descendente(v, tam);
    print_vector(v, tam);
    ord_ins(v, tam);
    print_vector(v, tam);

    printf(" 3. Vector aleatorio:\n");
    aleatorio(v, tam);
    print_vector(v, tam);
    ord_ins(v, tam);
    print_vector(v, tam);
}

int main()
{
    inicializar_semilla();
    test(10);
    return 0;
}