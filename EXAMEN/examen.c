//Ismael Brea Arias

//montículo de mínimos
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include<stdbool.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;

void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
int kesimoMayor(int v[], int n, int k);

void inicializar_semilla() {
    srand(time(NULL));
    /*se establece la semilla de una nueva serie de enteros pseudo-aleatorio*/
}

//  ARRAYS --------------------------------------------

void aleatorio(int v [], int n) {
    int i, m;
    m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* se generan números pseudoaleatorio entre -n y +n */
}

void ascendente(int vector[],int n){
    int i = 0;
    while ( i < n){
        vector[i] = i + 1;
        i++;
    }
}

void descendente(int vector[],int n){
    int i = 0;
    while ( i < n){
        vector[i] = n - i;
        i++;
    }
}

void listar_vector(int v[], int n){
    int i;
    for(i=0;i<n;i++){
        if (v[i]<0)
            printf("%d",v[i]);
        else
            printf(" %d",v[i]);
    }
}
// MONTICULOS ----------------------------------------

void flotar(pmonticulo m, int i) {
    int padre = (i - 1) / 2;
    while (i > 0 && m->vector[i] < m->vector[padre]) {
        int temp = m->vector[i];
        m->vector[i] = m->vector[padre];
        m->vector[padre] = temp;
        i = padre;
        padre = (i - 1) / 2;
    }
}

void hundir(pmonticulo M,int i) {
    int HijoIzq,HijoDer,j,temp;
    while (1) {
        HijoIzq = 2 * i + 1;
        HijoDer = 2 * i + 2;
        j = i;
        if(HijoDer <= M->ultimo && M->vector[HijoDer] < M->vector[i]){
            i = HijoDer;
        }
        if(HijoIzq <= M->ultimo && M->vector[HijoIzq] < M->vector[i]){
            i = HijoIzq;
        }
        temp = M->vector[i];
        M->vector[i] = M->vector[j];
        M->vector[j] = temp;
        if(i == j){
            break;
        }
    }
}

void iniMonticulo(pmonticulo m) {
    m->ultimo = -1;
}

void insertarMonticulo(pmonticulo m, int x) {
    if (m->ultimo == TAM - 1) {
        printf("Error: el montículo está lleno.\n");
        return;
    }
    m->ultimo++;
    m->vector[m->ultimo] = x;
    flotar(m, m->ultimo);
}

void quitarMenor(pmonticulo m) {
    if (m->ultimo < 0) {
        printf("Error: el montículo está vacío.\n");
        return;
    }
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;
    hundir(m, 0);
}

int consultarMenor(const pmonticulo m) {
    if (m->ultimo < 0) {
        printf("Error: el montículo está vacío.\n");
        return -1; 
    }
    return m->vector[0];
}

void crearMonticulo(pmonticulo m, int v[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        m->vector[i] = v[i];
    }
    m->ultimo = n -1;
    for (i = (m->ultimo -1)/2; i >= 0; i--) {
        hundir(m, i);
    }
}

int kesimoMayor(int v[], int n, int k){
    int i;
    pmonticulo M = (pmonticulo)malloc(sizeof(struct monticulo));
    if (M == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo\n");
        return -1;
    }
    crearMonticulo(M, v, k);
    for (i = k; i < n; i++) {
        if (v[i] > consultarMenor(M)) {
            quitarMenor(M);
            insertarMonticulo(M, v[i]);
        }
    }
    int x = consultarMenor(M);
    free(M);
    return x;
}

void ordenarPorMonticulos(int v[], int n) {
    int i;
    pmonticulo m;
    m = (pmonticulo)malloc(sizeof(struct monticulo));
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo\n");
        return;
    }
    iniMonticulo(m);
    crearMonticulo(m, v, n); 
    for (i = 0; i < n; i++) {
        v[i] = consultarMenor(m); 
        quitarMenor(m);           
    }
    free(m);
}


int es_monticulo_minimos(int arr[], int n) {
    int izquierdo , derecho,i;
    izquierdo=0;
    derecho=0;
    for ( i = 0; i < n; i++) {
         izquierdo = 2 * i + 1;
         derecho = 2 * i + 2;
        if ((izquierdo < n && arr[i] > arr[izquierdo])
            || (derecho < n && arr[i] > arr[derecho])) {
            return 0; // No es un montículo de mínimos
        }
    }
    return 1; // Es un montículo de mínimos
}

 

// TIEMPOS -------------------------------------------------------------
double microsegundos(){ /*obtiene la hora del sistema en microsegundos*/
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void medirTiempos(void (*inicializar)(int[], int),
    void (*algoritmo)(int[], int),double subf,double ajusf,double sobref) {
    int v[TAM];
    int temp = 2000;
    int k = 1000,i=0,j=0,l=0;
    double ta, tb, t1, t2, t;
    for ( i = 0; i < 8; ++i) {
        inicializar(v, temp);
        ta = microsegundos();
        algoritmo(v, temp);
        tb = microsegundos();
        t1 = tb - ta;

        if (t1 < 500) {
            printf("*");
            ta = microsegundos();
            for ( j = 0; j < k; ++j) {
                inicializar(v, temp);
                algoritmo(v, temp);
            }
            tb = microsegundos();
            t1 = tb - ta;
            ta = microsegundos();
            for ( l = 0; l < k; ++l) {
                inicializar(v, temp);
            }
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1 - t2) / k;
        } else {
            printf(" ");
            t = t1;
        }
        printf("    %10d     %15.8f     %15.8f     %15.8f     %15.8f\n",
            temp, t, t / pow(temp,subf),
            t / (pow(temp,ajusf)), t /pow(temp,sobref));
        temp = temp * 2;
    }
}

void medirTiemposDeCrearMonticulo(void (*inicializar)(int[], int),void 
    (*algoritmo)(pmonticulo, int[], int), double sub, double ajusf, 
    double sobre) {
    int v[TAM],temp = 2000,k = 1000, i = 0, j = 0, l = 0;
    double ta, tb, t1, t2, t;
    pmonticulo M = (pmonticulo)malloc(sizeof(struct monticulo));
    if (M == NULL) return;
    iniMonticulo(M);
    for (i = 0; i < 8; ++i) {
        inicializar(v, temp);
        ta = microsegundos();
        algoritmo(M, v, temp);
        tb = microsegundos();
        t1 = tb - ta;

        if (t1 < 500) {
            printf("*");
            ta = microsegundos();
            for (j = 0; j < k; ++j) {
                inicializar(v, temp);
                algoritmo(M, v, temp);
            }
            tb = microsegundos();
            t1 = tb - ta;
            ta = microsegundos();
            for (l = 0; l < k; ++l) inicializar(v, temp);
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1 - t2) / k;
        } else {
            printf(" ");
            t = t1;
        }
        printf("    %10d     %15.8f     %15.8f     %15.8f     %15.8f\n",temp,
        t, t / pow(temp, sub), t / pow(temp, ajusf), t / pow(temp, sobre));
        temp = temp * 2;
    }
    free(M); // Liberar memoria
}

void medirTiemposInsertarMonticulo(double sub,double ajusf,double sup) {
    int n = 2000, maxN = 128000, *v,i,rep;
    double ta, tb, t, tAux, ajustado;
    pmonticulo m;
    while (n <= maxN) {
        if (!(v = (int *)malloc(n * sizeof(int))) || !(m = 
        (pmonticulo)malloc(sizeof(struct monticulo)))) {
            printf("Error: No se pudo asignar memoria.\n");
            free(v), free(m); return;
        }
        for (i = 0; i < n; i++) v[i] = rand() % 1000000;
        iniMonticulo(m);
        ta = microsegundos();
        for (i = 0; i < n; i++) insertarMonticulo(m, v[i]);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            printf("*");
            ta = microsegundos();
            for (rep = 0; rep < 1000; rep++) {
                iniMonticulo(m);
                for (i = 0; i < n; i++) insertarMonticulo(m, v[i]);
            }
            tb = microsegundos();
            t = (tb - ta) / 1000;
        }
        else printf(" ");
        tAux = t;  
        ajustado = tAux / pow(n, ajusf);
        printf("%10d     %15.3f     %15.6f     %15.6f     %15.6f\n", n, tAux,
        tAux /pow(n,sub),ajustado,tAux /pow(n,sup));
        free(v), free(m);
        n *= 2;
    }
}

void medirTiemposKesimoMayor(int k, double sub, double ajusf, double sobre) {
    int v[TAM], temp = 2000, i = 0, j = 0, l = 0;
    double ta, tb, t1, t2, t;
    for (i = 0; i < 8; ++i) {
        aleatorio(v, temp);
        ta = microsegundos();
        kesimoMayor(v, temp, k);
        tb = microsegundos();
        t1 = tb - ta;

        if (t1 < 500) {
            printf("*");
            ta = microsegundos();
            for (j = 0; j < 1000; ++j) {
                aleatorio(v, temp);
                kesimoMayor(v, temp, k);
            }
            tb = microsegundos();
            t1 = tb - ta;
            ta = microsegundos();
            for (l = 0; l < 1000; ++l) aleatorio(v, temp);
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1 - t2) / 1000;
        } else {
            printf(" ");
            t = t1;
        }
        printf("    %10d     %15.8f     %15.8f     %15.8f     %15.8f\n", temp,
        t, t / pow(temp, sub), t / pow(temp, ajusf), t / pow(temp, sobre));
        temp = temp * 2;
    }
}
void medirTiemposKesimoMayorMitad(double sub, double ajusf, double sobre) {
    int v[TAM], temp = 2000, i = 0, j = 0, l = 0;
    double ta, tb, t1, t2, t;
    for (i = 0; i < 8; ++i) {
        aleatorio(v, temp);
        ta = microsegundos();
        kesimoMayor(v, temp, temp / 2);
        tb = microsegundos();
        t1 = tb - ta;

        if (t1 < 500) {
            printf("*");
            ta = microsegundos();
            for (j = 0; j < 1000; ++j) {
                aleatorio(v, temp);
                kesimoMayor(v, temp, temp / 2);
            }
            tb = microsegundos();
            t1 = tb - ta;
            ta = microsegundos();
            for (l = 0; l < 1000; ++l) aleatorio(v, temp);
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1 - t2) / 1000;
        } else {
            printf(" ");
            t = t1;
        }
        printf("    %10d     %15.8f     %15.8f     %15.8f     %15.8f\n", temp,
        t, t / pow(temp, sub), t / pow(temp, ajusf), t / pow(temp, sobre));
        temp = temp * 2;
    }
}

// TESTS --------------------------------------------------------------

void test1(){
    int arr1[8],arr2[8],arr3[8],n=8;
    aleatorio(arr1,n);
    ascendente(arr2,n);
    descendente(arr3,n);
    printf("Test1: correctas inicializaciones de vectores:\n\n");
    printf("Vector aleatorio:   ");
    listar_vector(arr1,n);
    printf("\nVector ascendente:  ");
    listar_vector(arr2,n);
    printf("\nVector descendente: ");
    listar_vector(arr3,n);
}
void test2() {
    int arr[8];
    int n = 8;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo)); 
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo.\n");
        return;
    }
    iniMonticulo(m);
    aleatorio(arr, n);
    printf("Test2: correcta ordenación por montículo de minimos\n\n");
    printf("Vector aleatorio:                                    ");
    listar_vector(arr, n);
    if(es_monticulo_minimos(arr,n)){
        printf("\n Es monticulo de minimos: si");
    } else{
        printf("\n Es monticulo de minimos: no");
    }
    printf("\nLo ordenamos como monticulo min:                     ");
    crearMonticulo(m,arr, n);
    listar_vector(m->vector, n);
      if(es_monticulo_minimos(m->vector, n)){
        printf("\n Es monticulo de minimos: si");
    } else{
        printf("\n Es monticulo de minimos: no");
    }
    printf("\nVector ordenado por la ordenacion por monticulos:    ");
    ordenarPorMonticulos(arr, n);
    listar_vector(arr, n);
    free(m); // Liberar memoria
}

void test3(){
    printf("Test3: prueba empirica de la complejidad de crearMonticulo");
    printf("\n\n");
    printf("%13sn%13st(microS)%10st(n)/n^0.8%10st(n)/n   %10st(n)/n^1.2\n",
    "","","","","");
    medirTiemposDeCrearMonticulo(aleatorio,crearMonticulo,0.8,1,1.2);
}

void test4(){
    printf("Test4: prueba empirica de la complejidad de insertarMonticulo");
    printf("\n\n");
    printf("%13sn%13st(microS)%10st(n)/n^0.8%10st(n)/nlogn   %10st(n)/n^1.2\n",
     "", "", "", "", "");
    medirTiemposInsertarMonticulo(0.8,1.06,1.2);
}

void test5(){
    printf("Test5: prueba empirica de la complejidad de kesimoMayor para k=9");
    printf("\n\n");
    printf("%13sn%13st(microS)%10st(n)/n^0.8%10st(n)/nlogn   %10st(n)/n^1.2\n",
     "", "", "", "", "");
    medirTiemposKesimoMayor(5,0.8,1.06,1.2);
}

void test6(){
    printf("Test6: prueba empirica de la complejidad de kesimoMayor k=n/2");
    printf("\n\n");
    printf("%13sn%13st(microS)%10st(n)/n^0.8%10st(n)/nlogn   %10st(n)/n^1.2\n",
     "", "", "", "", "");
    medirTiemposKesimoMayorMitad(0.8,1.06,1.2);
}

void testIniMonticulo() {
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo.\n");
        return;
    }
    iniMonticulo(m);
    printf("Test iniMonticulo:\n");
    printf("   Último índice esperado: -1, obtenido: %d\n", m->ultimo);
    free(m);
}

void testInsertarMonticulo() {
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo.\n");
        return;
    }
    iniMonticulo(m);
    insertarMonticulo(m, 10);
    insertarMonticulo(m, 5);
    insertarMonticulo(m, 20);
    printf("Test insertarMonticulo:\n");
    printf("   Valores esperados: 5, 10, 20. Obtenidos: ");
    listar_vector(m->vector, m->ultimo + 1);
    printf("\n");
    free(m);
}

void testQuitarMenor() {
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo.\n");
        return;
    }
    iniMonticulo(m);
    insertarMonticulo(m, 10);
    insertarMonticulo(m, 5);
    insertarMonticulo(m, 20);
    printf("Test quitarMenor:\n");
    printf("   Quitando menor: %d\n", consultarMenor(m)); // Debe ser 5
    quitarMenor(m); // Elimina el menor
    printf("   Quitando siguiente menor: %d\n", consultarMenor(m)); // Es 10
    quitarMenor(m); // Elimina el menor
    free(m);
}


void testConsultarMenor() {
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo.\n");
        return;
    }
    iniMonticulo(m);
    insertarMonticulo(m, 15);
    insertarMonticulo(m, 10);
    insertarMonticulo(m, 30);
    printf("Test consultarMenor:\n");
    if (m->ultimo >= 0) {
        printf("   Menor valor esperado: 10, obtenido: %d\n", m->vector[0]);
    } else {
        printf("   El montículo está vacío.\n");
    }
    free(m);
}

void testCrearMonticulo() {
    int v[] = {30, 20, 10, 5, 15};
    int n = 5;
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo.\n");
        return;
    }
    crearMonticulo(m, v, n);
    printf("Test crearMonticulo:\n");
    printf("   Montículo creado: ");
    listar_vector(m->vector, n);
    printf("\n   Es montículo de mínimos: %d\n",
        es_monticulo_minimos(m->vector, n));
    free(m);
}

void testKesimoMayor(){
    int mayor, i;
    int v[10];    //vector de 10 elementos
    int n = 10;   //tamaño del vector
    int k = 10;   // k primeros máximos elementos del vector
    pmonticulo m = (pmonticulo)malloc(sizeof(struct monticulo));   
    if (m == NULL) {
        printf("Error: No se pudo asignar memoria para el montículo\n");
        return;
    }
    printf("Test Kesimo Mayor\n");
    aleatorio(v, n);
    printf("Vector original (aleatorio):   ");
    listar_vector(v,n);
    printf("\nLos %d elementos extraidos son: ", k);
    for (i = 1; i <= k; i++) {
        mayor = kesimoMayor(v, n, i);
        printf("%d ", mayor);
    }
    printf("\n");
    free(m);
}

// MAIN -------------------------------------------------------
int main() {
    inicializar_semilla();
    testIniMonticulo();
    testInsertarMonticulo();
    testQuitarMenor();
    testConsultarMenor();
    testCrearMonticulo();
    testKesimoMayor();
    printf("\n------------------------------------------");
    printf("------------------------------------------\n");
    test1();
    printf("\n------------------------------------------");
    printf("------------------------------------------\n");
    test2();
    printf("\n------------------------------------------");
    printf("------------------------------------------\n");
    test3();
    printf("\n------------------------------------------");
    printf("------------------------------------------\n");
    test4();
    printf("\n------------------------------------------");
    printf("------------------------------------------\n");
    test5();
    printf("\n------------------------------------------");
    printf("------------------------------------------\n");
    test6();
    printf("------------------------------------------\nAleatorio\n");
    printf("%13sn%12st(microS)%9st(n)/n^1      %7st(n)/nlogn"
           "%9st(n)/n^1.3\n","","","","","");
    medirTiempos(aleatorio,ordenarPorMonticulos,1,1.1,1.3);
    printf("\n------------------------------------------");
    printf("------------------------------------------\nAscendente\n");
    printf("%13sn%12st(microS)%9st(n)/n^1     %7st(n)/nlogn"
           "%9st(n)/n^1.3\n","","","","","");
    medirTiempos(ascendente,ordenarPorMonticulos,1,1.06,1.3);
    printf("\n------------------------------------------");
    printf("------------------------------------------\nDescendente\n");
    printf("%13sn%12st(microS)%9st(n)/n^1     %7st(n)/nlogn"
           "%9st(n)/n^1.3\n","","","","","");
    medirTiempos(descendente,ordenarPorMonticulos,1,1.061,1.3);

    return 0;
}
