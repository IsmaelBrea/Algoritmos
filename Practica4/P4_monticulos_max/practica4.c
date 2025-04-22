// PRACTICA HECHA POR LUCAS PIÑEIRO AÑON Y ANTONIO PARADA MIRANDA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define TAM 512000

typedef struct {
    int vector[TAM];
    int ultimo;
} monticulo;

// GENERADOR DE Nº ALEATORIOS Y VECTORES EN DISTINTOS ORDENES
double microsegundos();
void inicializar_semilla();
void aleatorio(int v[],int n);
void ascendente();
void descendente();

//             MONTICULOS
// GENERADORAS
void crear_monticulo(int [], int, monticulo *);

// MODIFICADORAS
void hundir(monticulo *M, int);
void ord_monticulo(int [],int n);

// DESTRUCTORAS
int eliminar_mayor(monticulo *);

// TEST
void test();

// TABLAS
void tablaTest();
void tablaAsc();
void tablaDes();
void tablaRan();

// FUNCIONES AUXILIARES
double medirTiempo();


// GENERADOR DE Nº ALEATORIOS Y VECTORES EN DISTINTOS ORDENES

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
}

void descendente(int v [], int n) {
    int i;
    for (i=n-1; i >=0; i--){
        v[n-1-i] = i;
    }
}

void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++){
        v[i] = i;
    }
}

//             MONTICULOS

// GENERADORAS

void crear_monticulo(int v[],int n, monticulo *M){
    int i;
    for(i=0;i<=n;i++){
        M->vector[i]=v[i];
    }
    M->ultimo=n;
    for(i=(M->ultimo)/2;i>=0;i--){
        hundir(M,i);
    }
}

// MODIFICADORAS

void hundir(monticulo *M, int i){
    int hijoIzd,hijoDer,j,aux;
    do{
        hijoIzd=2*i+1;
        hijoDer=2*i+2;
        j=i;
        if(hijoDer<=M->ultimo && M->vector[hijoDer]>M->vector[i]){
            i = hijoDer;
        }
        if(hijoIzd<=M->ultimo && M->vector[hijoIzd]>M->vector[i]){
            i = hijoIzd;
        }
        aux=M->vector[j];
        M->vector[j]=M->vector[i];
        M->vector[i]=aux;
    } while(j!=i);
}

void ord_monticulo(int v[],int n){
    int i;
    monticulo M;
    crear_monticulo(v,n,&M);
    for(i=n;i>=1;i--){
        v[i]=eliminar_mayor(&M);
    }
}

// DESTRUCTORAS

int eliminar_mayor(monticulo *M){
    int x;
    x=M->vector[0];
    M->vector[0]=M->vector[M->ultimo];
    M->ultimo=M->ultimo-1;
    if(M->ultimo > 0){
        hundir(M,0);
    }
    return x;
}


// TEST

void test(){
    int v[TAM],i,aux[] = {1,5,3,7,9,2};
    monticulo M;
    inicializar_semilla();
    aleatorio(v,TAM);
    printf("\nVector a insertar en monticulo:\n");
    for(i=0;i<6;i++){
        printf("%d ",aux[i]);
    }
    crear_monticulo(aux,5,&M);
    printf("\n\nVector ya insertado:\n");
    for(i=0;i<=M.ultimo;i++){
        printf("%d ",M.vector[i]);
    }    
    printf("\n");
    ord_monticulo(aux,5);
    printf("\nVector ordenado por monticulos:\n");
    for(i=0;i<=5;i++){
        printf("%d ",aux[i]);
    }
    printf("\n\nMonticulo del vector:");
    for(i=0;i<=M.ultimo;i++){
        printf("\nRaiz: %d\n",M.vector[i]);
        if(M.vector[i*2+1]!=0 && (i*2+1)<=M.ultimo){
            printf("Hijo Izquierdo: %d\n",M.vector[i*2+1]);
        }
        if(M.vector[i*2+2]!=0 && (i*2+2)<=M.ultimo){
            printf("Hijo Derecho: %d\n",M.vector[i*2+2]);
        }
    }
    eliminar_mayor(&M);
    printf("\n\nEliminamos el mayor:");
    printf("\n\nVector resultante:\n");
    for(i=0;i<=M.ultimo;i++){
        printf("%d ",M.vector[i]);
    }
    printf("\n");
    for(i=0;i<=M.ultimo;i++){
        printf("\nRaiz: %d\n",M.vector[i]);
        if(M.vector[i*2+1]!=0 && (i*2+1)<=M.ultimo){
            printf("Hijo Izquierdo: %d\n",M.vector[i*2+1]);
        }
        if(M.vector[i*2+2]!=0 && (i*2+2)<=M.ultimo){
            printf("Hijo Derecho: %d\n",M.vector[i*2+2]);
        }
    }
}

// TABLAS

void tablaTest(){
    monticulo M;
    int v[TAM],n,i,k=1000;
    double t,t1,t2,x;
    bool promedio=false;
    printf("\n%20s---Test crear monticulo---\n","");
    printf("\n%13sn%11st(n)%9st(n)/n\n","","",""); 
    for(n=1000; n<TAM; n=n*2){
        aleatorio(v,n);
        t1 = microsegundos();
        crear_monticulo(v,n,&M);
        t2 = microsegundos();
        t = t2 - t1;
        if(t<500){
            promedio = true;
            t1=microsegundos();
            for(int i=0;i<k;i++){
                aleatorio(v,n);
                crear_monticulo(v,n,&M);
            }
            t2=microsegundos();
            t=(t2-t1)/k;
            t1=microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
            }
            t2=microsegundos();
            t = t - ((t2-t1)/k);
        }else{
            promedio = false;
        }
        x = t/n;
        if(promedio){
            printf("(*)");
            printf("%12d%15.3f%15.6f\n", n, t, x);
        }
        else{
            printf("   %12d%15.3f%15.6f\n", n, t, x);
        }
    }
}

void tablaAsc(){
    monticulo M;
    int v[TAM],n,i,k=1000; //si k = 10000 salen mejores tiempos pero tarda mucho mas
    double t,t1,t2,x,y,z;
    bool promedio=false;
    printf("\n%20s---Vector ascendente---\n","");
    printf("\n%13sn%11st(n)%7st(n)/n^0.9%3st(n)/n*log(n)%4st(n)/n^1.3\n","","","","","");
    for(n=1000; n<TAM; n=n*2){
        ascendente(v,n);
        t = medirTiempo(v,n);
        if(t<500){
            promedio = true;
            t1=microsegundos();
            for(i=0;i<k;i++){
                ord_monticulo(v,n);
            }
            t2=microsegundos();
            t=(t2-t1)/k;
        }else{
            promedio = false;
        }
        x = t/pow(n,0.9);
        y = t/(n*log(n)); 
        z = t/pow(n,1.3);
        if(promedio){
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
        else{
            printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
    }
}

void tablaDes(){
    monticulo M;
    int v[TAM],n,i,k=1000;
    double t,t1,t2,x,y,z;
    bool promedio=false;
    printf("\n%20s---Vector descendente---\n","");
    printf("\n%13sn%11st(n)%7st(n)/n^0.9%3st(n)/n*log(n)%4st(n)/n^1.3\n","","","","","");
    for(n=1000; n<TAM; n=n*2){
        descendente(v,n);
        t = medirTiempo(v,n,k);
        if(t<500){
            promedio = true;
            t1=microsegundos();
            for(i=0;i<k;i++){
                descendente(v,n);
                ord_monticulo(v,n);
            }
            t2=microsegundos();
            t=(t2-t1)/k;
            t1=microsegundos();
            for(i=0;i<k;i++){
                descendente(v,n);                
            }
            t2=microsegundos();
            t = t - ((t2-t1)/k);
        }else{
            promedio = false;
        }
        x = t/pow(n,0.9);
        y = t/(n*log(n)); 
        z = t/pow(n,1.3);
        if(promedio){
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
        else{
            printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
    }
}

void tablaRan(){
    monticulo M;
    int v[TAM],n,i,k=1000;
    double t,t1,t2,x,y,z;
    bool promedio=false;
    printf("\n%20s---Vector aleatorio---\n","");
    printf("\n%13sn%11st(n)%7st(n)/n^0.9%3st(n)/n*log(n)%4st(n)/n^1.3\n","","","","","");
    for(n=1000; n<TAM; n=n*2){
        aleatorio(v,n);
        t = medirTiempo(v,n);
        if(t<500){
            promedio = true;
            t1=microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
                ord_monticulo(v,n);
            }
            t2=microsegundos();
            t=(t2-t1)/k;
            t1=microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
            }
            t2=microsegundos();
            t = t - ((t2-t1)/k);
        }else{
            promedio = false;
        }
        x = t/pow(n,0.9);
        y = t/(n*log(n)); 
        z = t/pow(n,1.3);
        if(promedio){
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
        else{
            printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }
    }
}

// FUNCIONES AUXILIARES

double medirTiempo(int v[], int n){
    monticulo M;
    double t,t1,t2;
    t1 = microsegundos();
    ord_monticulo(v,n);
    t2 = microsegundos();
    t = t2 - t1;
    return t;
}

// MAIN

int main(){
    test();
    tablaTest();
    tablaAsc();       
    tablaDes();
    tablaRan();
}








