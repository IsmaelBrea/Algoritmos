// Ismael Brea Arias

// P1 sucesión de Fibonacci

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>
#include <assert.h>

// funciones fib() ---------------------------------------------------------------------------

int fib1(int n)
{ // complejidad O(o**n)
    if (n < 2)
        return n;
    else
        return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n)
{ // complejidad O(n)
    int i = 1, j = 0, k;
    for (k = 1; k <= n; k++)
    {
        j = i + j;
        i = j - i;
    }
    return j;
}

int fib3(int n)
{ // complejidad O(log n)
    int i, j, k, h, t;
    i = 1;
    j = 0;
    k = 0;
    h = 1;
    while (n > 0)
    {
        if ((n % 2) != 0)
        {
            t = j * h;
            j = (i * h) + (j * k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2 * k * h) + t;
        k = (k * k) + t;
        n = n / 2;      // División por 2 en cada iteración → O(log n)
    }
    return j;
}

// TIEMPOS -------------------------------------------------------------

double microsegundos()
{ /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void medir_tiemposFib1()
{
    int n, i;
    double cota1, cota2, cota3;
    int repeticiones = 100000;
    bool promedio = false;
    double tiempoInicio, tiempoFin, tiempoTotal, tiempoPromedio;
    printf("\n\t  n\t     t(microS)      t(n)/1.1^n\t "
           "t(n)/1.61^n\t  t(n)/1.7^n\n\n");
    for (n = 2; n <= 32; n = n * 2){
        tiempoInicio = microsegundos();
        fib1(n);
        tiempoFin = microsegundos();
        tiempoTotal = tiempoFin - tiempoInicio;
        if (tiempoTotal < 500){
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++){
                fib1(n);
            }
            tiempoFin = microsegundos();
            tiempoPromedio = (tiempoFin - tiempoInicio) / repeticiones;
        }else
            promedio = false;

        if (promedio){
            cota1 = tiempoPromedio / pow(1.1, n);                 // Cota subestimada O(φ^n) con φ ≈ 1.4
            cota2 = tiempoPromedio / pow(((1 + sqrt(5)) / 2), n); // Cota ajustada O(φ^n) con φ = (1+√5)/2
            cota3 = tiempoPromedio / pow(1.7, n);                 // Cota sobreestimada O(1.8^n)
            printf("(*)");
            printf("%12d%15.5f%15.6f%15.6f%15.6f\n", n,
                   tiempoPromedio, cota1, cota2, cota3);
        }
        else{
            cota1 = tiempoTotal / pow(1.1, n);                 // Cota subestimada O(φ^n) con φ ≈ 1.1
            cota2 = tiempoTotal / pow(((1 + sqrt(5)) / 2), n); // Cota ajustada O(φ^n) con φ = (1+√5)/2
            cota3 = tiempoTotal / pow(1.7, n);                 // Cota sobreestimada O(1.7^n)
            printf("   %12d%15.5f%15.6f%15.6f%15.6f\n", n,
                   tiempoTotal, cota1, cota2, cota3);
        }
        tiempoTotal = 0;
        tiempoPromedio = 0;
    }
}

// Test para el algoritmo fib2
void medir_tiemposFib2()
{
    int n, i;
    double cota1, cota2, cota3;
    int repeticiones = 100000;
    bool promedio = false;
    double tiempoInicio, tiempoFin, tiempoTotal, tiempoPromedio;
    printf("\n\t  n\t      t(microS)\t    t(n)/n^0.8\t "
           "   t(n)/n      t(n)/n*log(n)\n\n");

    for (n = 1000; n <= 10000000; n = n * 10){
        tiempoInicio = microsegundos();
        fib2(n);
        tiempoFin = microsegundos();
        tiempoTotal = tiempoFin - tiempoInicio;

        if (tiempoTotal < 500){
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++)
            {
                fib2(n);
            }
            tiempoFin = microsegundos();
            tiempoPromedio = (tiempoFin - tiempoInicio) / repeticiones;
        }else
        {
            promedio = false;
        }
        
        if (promedio){
            cota1 = tiempoPromedio / pow(n, 0.8);  // Cota subestimada O(n^0.8)
            cota2 = tiempoPromedio / n;            // Cota ajustada O(n)
            cota3 = tiempoPromedio / (n * log(n)); // Cota sobreestimada O(n log(n))
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoPromedio, cota1, cota2, cota3);
        }
        else{
            cota1 = tiempoTotal / pow(n, 0.8);  // Cota subestimada O(n^0.8)
            cota2 = tiempoTotal / n;            // Cota ajustada O(n)
            cota3 = tiempoTotal / (n * log(n)); // Cota sobreestimada O(n log(n))
            printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoTotal, cota1, cota2, cota3);
        }
        tiempoTotal = 0;
        tiempoPromedio = 0;
    }
}

void medir_tiemposFib3()
{
    int n, i;
    double cota1, cota2, cota3;
    int repeticiones = 100000;
    bool promedio = false;
    double tiempoInicio, tiempoFin, tiempoTotal, tiempoPromedio;
    printf("\n\t  n\t   t(microS)   t(n)/sqrt(log(n))  "
           "t(n)/log(n)\tt(n)/n^0.4\n\n");

    for (n = 1000; n <= 10000000; n = n * 10)
    {
        tiempoInicio = microsegundos();
        fib3(n);
        tiempoFin = microsegundos();
        tiempoTotal = tiempoFin - tiempoInicio;

        if (tiempoTotal < 500)
        {
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++)
            {
                fib3(n);
            }
            tiempoFin = microsegundos();
            tiempoPromedio = (tiempoFin - tiempoInicio) / repeticiones;
        }
        else
            promedio = false;

        if (promedio)
        {
            cota1 = tiempoPromedio / sqrt(log(n)); // Cota subestimada O(sqrt(log(n)))
            cota2 = tiempoPromedio / log(n);       // Cota ajustada O(log(n))
            cota3 = tiempoPromedio / pow(n, 0.4);  // Cota sobreestimada O(n^0.4)
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoPromedio, cota1, cota2, cota3);
        }
        else
        {
            cota1 = tiempoTotal / sqrt(log(n)); // Cota subestimada O(sqrt(log(n)))
            cota2 = tiempoTotal / log(n);       // Cota ajustada O(log(n))
            cota3 = tiempoTotal / pow(n, 0.4);  // Cota sobreestimada O(n^0.4)
            printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoTotal, cota1, cota2, cota3);
        }
        tiempoTotal = 0;
        tiempoPromedio = 0;
    }
}

// TESTS --------------------------------------------------------------
// Función para correr los tests
void run_tests()
{
    // Caso base: Fibonacci de 0
    assert(fib1(0) == 0);
    assert(fib2(0) == 0);
    assert(fib3(0) == 0);

    // Caso base: Fibonacci de 1
    assert(fib1(1) == 1);
    assert(fib2(1) == 1);
    assert(fib3(1) == 1);

    // Fibonacci de 5
    assert(fib1(5) == 5);
    assert(fib2(5) == 5);
    assert(fib3(5) == 5);

    // Fibonacci de 10
    assert(fib1(10) == 55);
    assert(fib2(10) == 55);
    assert(fib3(10) == 55);

    printf("\033[0;32mTodos los tests pasaron correctamente.\033[0m\n");
}

// MAIN -------------------------------------------------------
int main()
{
    run_tests();
    printf("Mediciones:\nFib1");
    medir_tiemposFib1();

    printf("\n\nFib2");
    medir_tiemposFib2();

    printf("\n\nFib3");
    medir_tiemposFib3();

    return 0;
}
