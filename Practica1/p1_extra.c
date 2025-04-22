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

int fib4(int n)                 // Memoización
{ // Complejidad O(n)
    if (n <= 1)
        return n;

    int *memo = (int *)malloc((n + 1) * sizeof(int)); // Crear el arreglo memo
    memo[0] = 0;
    memo[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        memo[i] = memo[i - 1] + memo[i - 2];
    }

    int result = memo[n]; // Guardar el resultado final
    free(memo);           // Liberar memoria
    return result;
}

int fib5(int n) {          // Programación dinámica bottom up
// Complejidad O(n)
    if (n < 2) {
        return n;  // Casos base
    }

    int *fib = (int *)malloc((n + 1) * sizeof(int));
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int result = fib[n];
    free(fib);  // Liberamos la memoria usada
    return result;
}


int fib6(int n) {
    double phi = (1 + sqrt(5)) / 2;  // Número áureo
    double psi = (1 - sqrt(5)) / 2;  // Número áureo conjugado

    return round((pow(phi, n) - pow(psi, n)) / sqrt(5));
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

void medir_tiemposFib4()
{
    int n, i;
    double cota1, cota2, cota3;
    int repeticiones = 100000;
    bool promedio = false;
    double tiempoInicio, tiempoFin, tiempoTotal, tiempoPromedio;

    printf("\n\t  n\t      t(microS)\t    t(n)/n^0.8\t "
           "   t(n)/n      t(n)/n*log(n)\n\n");

    for (n = 1000; n <= 10000000; n = n * 10)
    {
        tiempoInicio = microsegundos();
        fib4(n);
        tiempoFin = microsegundos();
        tiempoTotal = tiempoFin - tiempoInicio;

        if (tiempoTotal < 500)
        {
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++)
            {
                fib4(n);
            }
            tiempoFin = microsegundos();
            tiempoPromedio = (tiempoFin - tiempoInicio) / repeticiones;
        }
        else
        {
            promedio = false;
        }

        if (promedio)
        {
            cota1 = tiempoPromedio / pow(n, 0.8);  // Cota subestimada O(n^0.8)
            cota2 = tiempoPromedio / n;            // Cota ajustada O(n)
            cota3 = tiempoPromedio / (n * log(n)); // Cota sobreestimada O(n log(n))
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoPromedio, cota1, cota2, cota3);
        }
        else
        {
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

void medir_tiemposFib5()
{
    int n, i;
    double cota1, cota2, cota3;
    int repeticiones = 100000;
    bool promedio = false;
    double tiempoInicio, tiempoFin, tiempoTotal, tiempoPromedio;

    printf("\n\t  n\t      t(microS)\t    t(n)/n^0.8\t "
           "   t(n)/n      t(n)/n*log(n)\n\n");

    for (n = 1000; n <= 10000000; n = n * 10)
    {
        tiempoInicio = microsegundos();
        fib5(n);
        tiempoFin = microsegundos();
        tiempoTotal = tiempoFin - tiempoInicio;

        if (tiempoTotal < 500)
        {
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++)
            {
                fib5(n);
            }
            tiempoFin = microsegundos();
            tiempoPromedio = (tiempoFin - tiempoInicio) / repeticiones;
        }
        else
        {
            promedio = false;
        }

        if (promedio)
        {
            cota1 = tiempoPromedio / pow(n, 0.8);  // Cota subestimada O(n^0.8)
            cota2 = tiempoPromedio / n;            // Cota ajustada O(n)
            cota3 = tiempoPromedio / (n * log(n)); // Cota sobreestimada O(n log(n))
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoPromedio, cota1, cota2, cota3);
        }
        else
        {
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

void medir_tiemposFib6()
{
    int n, i;
    double cota1, cota2, cota3;
    int repeticiones = 100000;
    bool promedio = false;
    double tiempoInicio, tiempoFin, tiempoTotal, tiempoPromedio;
    printf("\n\t  n\t      t(microS)\t    t(n)/n^0.8\t "
           "   t(n)/n      t(n)/n*log(n)\n\n");

    for (n = 1000; n <= 10000000; n = n * 10)
    {
        // Mide el tiempo de la función fib6
        tiempoInicio = microsegundos();
        fib6(n);  // Llamada a la función fib6 para medir tiempos
        tiempoFin = microsegundos();
        tiempoTotal = tiempoFin - tiempoInicio;

        if (tiempoTotal < 500)
        {
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++)
            {
                fib6(n);
            }
            tiempoFin = microsegundos();
            tiempoPromedio = (tiempoFin - tiempoInicio) / repeticiones;
        }
        else
        {
            promedio = false;
        }

        // Ajustamos las cotas a O(1) para reflejar que el tiempo es constante
        if (promedio)
        {
            // Debido a que fib6 es O(1), esperamos que las cotas se mantengan constantes
            cota1 = tiempoPromedio / 1.0;      // O(1)
            cota2 = tiempoPromedio / 1.0;      // O(1)
            cota3 = tiempoPromedio / 1.0;      // O(1)
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n,
                   tiempoPromedio, cota1, cota2, cota3);
        }
        else
        {
            cota1 = tiempoTotal / 1.0;      // O(1)
            cota2 = tiempoTotal / 1.0;      // O(1)
            cota3 = tiempoTotal / 1.0;      // O(1)
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
    assert(fib4(0) == 0);
    assert(fib5(0) == 0);
    assert(fib6(0) == 0);

    // Caso base: Fibonacci de 1
    assert(fib1(1) == 1);
    assert(fib2(1) == 1);
    assert(fib3(1) == 1);
    assert(fib4(1) == 1);
    assert(fib5(1) == 1);
    assert(fib6(1) == 1);

    // Fibonacci de 5
    assert(fib1(5) == 5);
    assert(fib2(5) == 5);
    assert(fib3(5) == 5);
    assert(fib4(5) == 5);
    assert(fib5(5) == 5);
    assert(fib6(5) == 5);

    // Fibonacci de 10
    assert(fib1(10) == 55);
    assert(fib2(10) == 55);
    assert(fib3(10) == 55);
    assert(fib4(10) == 55);
    assert(fib5(10) == 55);
    assert(fib6(10) == 55);

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

    printf("\n\nFib4");
    medir_tiemposFib4();

    printf("\n\nFib5");
    medir_tiemposFib5();

    printf("\n\nFib6");
    medir_tiemposFib6();


    return 0;
}
