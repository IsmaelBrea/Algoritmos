#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int sumaSubMax1(int v[], int tam)
{
    int i, j;
    int sumaMax = 0, estaSuma = 0;

    for (i = 0; i < tam; i++)
    {
        estaSuma = 0;
        for (j = i; j < tam; j++)
        {
            estaSuma += v[j];
            if (estaSuma > sumaMax)
                sumaMax = estaSuma;
        }
    }
    return sumaMax;
}

int sumaSubMax2(int v[], int tam)
{
    int i;
    int sumaMax = 0, estaSuma = 0;

    for (i = 0; i < tam; i++)
    {
        estaSuma += v[i];
        if (estaSuma > sumaMax)
            sumaMax = estaSuma;
        else if (estaSuma < 0)
            estaSuma = 0;
    }
    return sumaMax;
}

void inicializar_semilla()
{
    srand(time(NULL));
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
    printf("] ");
}

void check()
{
    int i;
    int v[6][5] = {{-9, 2, -5, -4, 6}, {4, 0, 9, 2, 5}, {-2, -1, -9, -7, -1}, {9, -2, 1, -7, -8}, {15, -2, -5, -4, 16}, {7, -5, 6, 7, -7}};

    printf("\tsecuencia\t| sumasubMax1 | sumasubMax2 |\n");
    for (i = 0; i < 6; i++)
    {
        print_vector(v[i], 5);
        printf("| %11d | %11d |\n", sumaSubMax1(v[i], 5), sumaSubMax2(v[i], 5));
    }
}

void test(int tam)
{
    int i;
    int v[tam];

    check();
    printf("\n\t\t\t\t\t    | sumasubMax1 | sumasubMax2 |\n");
    for (i = 0; i <= tam; i++)
    {
        aleatorio(v, tam);
        print_vector(v, tam);
        printf("| %11d | %11d |\n", sumaSubMax1(v, tam), sumaSubMax2(v, tam));
    }
}

int main()
{
    inicializar_semilla();
    test(10);
    return 0;
}