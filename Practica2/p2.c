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
     srand(time(NULL));

    test_ord_inser(n); // Llamada a la función de test para ordenación por inserción
    test_ord_rap(n); // Llamada a la función de test para ordenación rápida
    medir_tiempos();
    return 0;
}