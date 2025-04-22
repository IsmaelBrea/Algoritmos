#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_PRUEBA 100 
#define MAX 32000

//ALGORITMO 1: Ordenación por inserción
void ord_ins(int v[], int n) {
    int i, j, x;
    for (i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}


//ALGORITMO 2: Ordenación rápida (quicksort)
void intercambiar(int v[], int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void ord_rap_aux(int v[], int izq, int der) {
    int x, pivote, i, j;
    if (izq < der) {
        x = rand() % (der - izq + 1) + izq; 
        pivote = v[x];
        intercambiar(v, izq, x); 
        i = izq + 1, j = der;

        while (i <= j) {
            while (i <= der && v[i] < pivote) i++;
            while (j >= izq && v[j] > pivote) j--;

            if (i <= j) {
                intercambiar(v, i, j);
                i++;
                j--;
            }
        }
        intercambiar(v, izq, j); 
        ord_rap_aux(v, izq, j - 1); 
        ord_rap_aux(v, j + 1, der); 
    } else {
        ord_ins(v + izq, der - izq + 1);
    }
}

void ord_rap(int v[], int n) {
    ord_rap_aux(v, 0, n - 1);
}

//ALGORITMO 3: Ordenación shell
void ord_shell(int v[], int n)
{
    bool seguir;
    int i, j, tmp = 0;
    int incremento = n;

    do
    {
        incremento = incremento / 2;
        for (i = incremento; i < n; i++)
        {
            tmp = v[i];
            j = i;
            seguir = true;
            while ((j - incremento >= 0) && seguir)
            {
                if (tmp < v[j - incremento])
                {
                    v[j] = v[j - incremento];
                    j = j - incremento;
                }
                else
                {
                    seguir = false;
                }
            }
            v[j] = tmp;
        }
    } while (incremento > 1);
}

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = (rand() % (2 * n + 1)) - n;
    }
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
}

void descendente(int v[], int n) {
    int i;
    for (i= 0; i < n; i++) {
        v[i] = n - 1 - i;
    }
}

bool esta_ordenado(int v[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return true;
}

void imprimir_vector(int v[], int n) {
    int i;
    for (i = 0; i < n && i < 10; i++) {
        printf("%d", v[i]);
        if (i < n - 1 && i < 9) {
            printf(", ");
        }
    }
    if (n > 10) {
        printf(", ... (%d más)", n - 10);
    }
    printf("\n");
}

void test_ord_inser(int n) {
    int v[MAX_PRUEBA]; 

    printf("Ordenacion por insercion con inicializacion aleatoria\n");
    aleatorio(v, n);
    imprimir_vector(v, n);
    printf("Ordenado? %i\n",esta_ordenado(v,n));
    if (!esta_ordenado(v, n)) {
        ord_ins(v, n);
        imprimir_vector(v, n);
    }
    printf("Ordenado? %i\n\n",esta_ordenado(v,n));

    printf("Ordenacion por insercion con inicializacion descendente\n");
    descendente(v, n);
    imprimir_vector(v, n);
    printf("Ordenado? %i\n",esta_ordenado(v,n));
    if (!esta_ordenado(v, n)) {
        ord_ins(v, n);
        imprimir_vector(v, n);
    }
    printf("Ordenado? %i\n\n",esta_ordenado(v,n));

}

void test_ord_rap(int n) {
    int v[MAX_PRUEBA]; 

    printf("Ordenacion rapida con inicializacion aleatoria\n");
    aleatorio(v, n);
    imprimir_vector(v, n);
    printf("Ordenado? %i\n",esta_ordenado(v,n));
    if (!esta_ordenado(v, n)) {
        ord_rap(v, n);
        imprimir_vector(v, n);
    }
    printf("Ordenado? %i\n\n",esta_ordenado(v,n));


    printf("Ordenacion rapida con inicializacion descendente\n");
    descendente(v, n);
    imprimir_vector(v, n);
    printf("Ordenado? %i\n",esta_ordenado(v,n));
    if (!esta_ordenado(v, n)) {
        ord_rap(v, n);
        imprimir_vector(v, n);
    }
    printf("Ordenado? %i\n\n",esta_ordenado(v,n));

}

void test_ord_shell(int n) {
    int v[MAX_PRUEBA]; 

    printf("Ordenación Shell con inicialización aleatoria\n");
    aleatorio(v, n);
    imprimir_vector(v, n);
    printf("Ordenado? %i\n", esta_ordenado(v, n));
    if (!esta_ordenado(v, n)) {
        ord_shell(v, n);
        imprimir_vector(v, n);
    }
    printf("Ordenado? %i\n\n", esta_ordenado(v, n));

    printf("Ordenación Shell con inicialización descendente\n");
    descendente(v, n);
    imprimir_vector(v, n);
    printf("Ordenado? %i\n", esta_ordenado(v, n));
    if (!esta_ordenado(v, n)) {
        ord_shell(v, n);
        imprimir_vector(v, n);
    }
    printf("Ordenado? %i\n\n", esta_ordenado(v, n));
}


double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void tabla(int n, double t, double sub, double cota, 
           double sobre, bool promedio) {    
    if (promedio) {
        printf("(*)\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / pow(n, sub), t / pow(n, cota), t / pow(n, sobre));
    } else {
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
               n, t, t / pow(n, sub), t / pow(n, cota), t / pow(n, sobre));
    }
}

void medirTiempos(void (*algoritmo) (int*,int), void (*inicializacion) 
    (int*,int), double sub, double cota, double sobre) {

    double tiempoInicio, tiempoFinal, tiempoTotal, tiempoPromedio;
    bool promedio = false;
    int i, repeticiones = 1000, n = 500;
    int v[MAX];

    while (n <= MAX) {
        promedio = false;
        inicializacion(v, n);
        tiempoInicio = microsegundos();
        algoritmo(v, n);
        tiempoFinal = microsegundos();
        tiempoTotal = tiempoFinal - tiempoInicio;

        if (tiempoTotal < 500) {
            promedio = true;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++) {
                inicializacion(v, n);
                algoritmo(v, n);
            }
            tiempoFinal = microsegundos();
            tiempoTotal = tiempoFinal - tiempoInicio;
            tiempoInicio = microsegundos();
            for (i = 0; i < repeticiones; i++) 
                inicializacion(v, n);
            tiempoFinal = microsegundos();
            tiempoTotal = tiempoTotal - (tiempoFinal - tiempoInicio);
            tiempoPromedio = tiempoTotal / repeticiones;
        } else {
            tiempoPromedio = tiempoTotal;
        }
        tabla(n, tiempoPromedio, sub, cota, sobre, promedio);
        n = n * 2;
    }
}

double tiempos(void (*alg)(int v[], int tamanho),
               void (*vector)(int v[], int tamanho), int tamanho, int k)
{
    double t1, t2, t, prima;
    int i;
    int *v;
    v = malloc(tamanho * sizeof(int));
    vector(v, tamanho);

    t1 = microsegundos();
    alg(v, tamanho);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500)
    {
        printf("(*)");
        t1 = microsegundos();
        for (i = 0; i < k; i++)
        {
            vector(v, tamanho);
            alg(v, tamanho);
        }
        t2 = microsegundos();
        prima = t2 - t1;
        t1 = microsegundos();
        for (i = 0; i < k; i++)
        {
            vector(v, tamanho);
        }
        t2 = microsegundos();
        t = t2 - t1;
        t = (prima - t) / k;
    }
    free(v);
    return t;
}

void tiempo_shell()
{
    int k = 1000;
    double tiempo = 0.0;
    int n;
    printf("\nOrdenación por shell:\n");
    printf("\tVector ascendente:\n\t - Cota subestimada (sub): n^(0.8)\n");
    printf("\t - Cota ajustada (aj): n^(1.01)*log2(n)\n");
    printf("\t - Cota sobreestimada (sob): n^(1.2)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_shell, ascendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / (pow(n, 0.8)),
               tiempo / (pow(n, 1.01) * log2(n)), tiempo / (pow(n, 1.2)));
    }
    printf("\n\tVector descendente:\n\t - Cota subestimada (sub): n^(1.0)\n");
    printf("\t - Cota ajustada (aj): n^(1.09)\n");
    printf("\t - Cota sobreestimada (sob): n^(1.3)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_shell, descendente, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / n, tiempo / (pow(n, 1.09)),
               tiempo / (pow(n, 1.3)));
    }
    printf("\n\tVector aleatorio:\n\t - Cota subestimada (sub): n^(1.0)\n");
    printf("\t - Cota ajustada (aj): n^(1.24))\n");
    printf("\t - Cota sobreestimada (sob): n^(1.4)\n\n");
    printf("\t      n\t\t\t\t  t(n)\t\t     t(n)/sub\t\t     t(n)/aj\t\t"
           "     t(n)/sob\n");
    for (n = 500; n <= 2048000; n = n * 2) {
        tiempo = tiempos(ord_shell, aleatorio, n, k);
        printf("\t% 8d\t\t% 15.4f\t\t% 14.12f\t\t% 14.12f\t\t% 14.12f\n", n,
               tiempo, tiempo / n, tiempo / (pow(n, 1.24)),
               tiempo / (pow(n, 1.4)));
    }
}

void medir_tiempos(){
    printf("\n\nVECTOR EN ORDEN ASCENDENTE\n");//listo
    printf("Ordenacion por Insercion con Inicialización ascendente\n");
    printf("\t    n\t\t   t(n)\t     t(n)/n^0.95\t"
            " (n)/n\t     t(n)/n^1.1\n");
    medirTiempos(ord_ins, ascendente, 0.95, 1, 1.1);

    printf("\nOrdenacion Rápida con Inicialización ascendente\n");
    printf("\t    n\t\t   t(n)\t      t(n)/n^1\t"
            "      t(n)/n^1.06    t(n)/n^1.3\n");
    medirTiempos(ord_rap, ascendente, 1, 1.06, 1.3);

    printf("\n\nVECTOR EN ORDEN DESCENDENTE\n");
    printf("Ordenacion por Insercion con Inicialización descendente\n");
    printf("\t    n\t\t   t(n)\t      t(n)/n^1.9     "
            "t(n)/n^2.01       t(n)/n^2.1\n");
    medirTiempos(ord_ins, descendente, 1.9, 2.01, 2.1);
    
    printf("\nOrdenacion Rápida con Inicialización descendente\n");
    printf("\t    n\t\t   t(n)\t      t(n)/n^1\t"
            "      t(n)/n^1.059    t(n)/n^1.2\n");
    medirTiempos(ord_rap, descendente, 1, 1.059, 1.2);


    printf("\n\nVECTOR DESORDENADO\n");
    printf("Ordenacion por Insercion con Inicialización desordenada \n");
    printf("\t    n\t\t   t(n)\t      t(n)/n^1.9\t"
            "t(n)/n^2       t(n)/n^2.1\n");
    medirTiempos(ord_ins, aleatorio, 1.9, 2, 2.1);

    printf("\nOrdenacion Rápida con inicializacion desordenada\n");
    printf("\t    n\t\t   t(n)\t      t(n)/n^1\t"
            "      t(n)/n^1.062    t(n)/n^1.2\n");
    medirTiempos(ord_rap, aleatorio, 1, 1.062, 1.2);
}

int main() {
    int n = 10; // Tamaño del vector
    inicializar_semilla();
    

    test_ord_inser(n); // Llamada a la función de test para ordenación por inserción
    test_ord_rap(n); // Llamada a la función de test para ordenación rápida
    test_ord_shell(n); // Llamada a la función de test para ordenación shell
    medir_tiempos();
    tiempo_shell();
    return 0;
}