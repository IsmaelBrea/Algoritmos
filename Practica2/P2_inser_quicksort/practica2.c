#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define UMBRAL 10
#define MAX 32000
#define MAX_PRUEBA 10


void testIns();
void testQuick();
void tablaUmbralDes();
void tablaUmbralAsc();
void tablaUmbralRan();
void umbralDes();
void umbralAsc();
void umbralRan();
void testDes();
void testAsc();
void testRan();

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

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorio entre -n y +n */
	int i, m=2*n+1;
	for (i=0; i < n; i++){
		v[i] = (rand() % m) - n;
	}	
}

void ascendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++){
		v[i] = i;
	}	
}

void descendente(int v [], int n) {
	int i;
	for (i=n-1; i >=0; i--){
		v[n-1-i] = i;
	}	
}

void ord_ins (int v[], int n){
	int x, j;
	for(int i=1;i<n;i++){
		x = v[i];
		j = i-1;
		while((j>=0)&&(v[j]>x)){
			v[j+1] = v[j];
			j = j-1;
		}
		v[j+1] = x;
	}
}

//////////////////////////////QUICKSORT//////////////////////////////////////////////

void intercambiar(int v[], int izd, int der){
	int aux;
	aux = v[izd];
	v[izd] = v[der];
	v[der] = aux;
}

void rapida_aux(int v[], int izd, int der){
    int pivote, x, i, j;
    if(izd+UMBRAL <= der)    {
        x = rand() % (der-izd+1) + izd;
        pivote = v[x];
        intercambiar (v, izd, x);
        i = izd+1;
        j = der;
        while (i <= j)        {
            while ((i <= der) && (v[i] < pivote)){
                i = i + 1;
            }
            while ((v[j] > pivote) && (j > izd)){
                j = j - 1;
            }
            if (i <= j){
                intercambiar(v, i, j);
                i = i + 1;
                j = j - 1;
            }
        }
        intercambiar(v, izd, j);
        rapida_aux(v, izd, j-1);
        rapida_aux(v, j+1, der);
    }
}
void ord_rapida(int v[], int n){
    rapida_aux(v, 0, n-1);
    if (UMBRAL > 1){
        ord_ins(v,n);
    }
}
//////////////////////////////QUICKSORT///////////////////////////////////////////////
int main(){
	testIns();
	testQuick();
	
	return 0;
}
void testIns()
{
	inicializar_semilla();
	int v[MAX_PRUEBA];
	int ordenado=1;
	printf("\nOrdenacion por insercion con inicializacion descendente\n");
	descendente(v,MAX_PRUEBA);
	for(int i=0;i<MAX_PRUEBA;i++){
		if(v[i]>v[i+1]){
			ordenado=0;
		}
		if(i==MAX_PRUEBA-1){
			printf("%d\n",v[i]);
		}else{
			printf("%d, ",v[i]);
		}
	}
	printf("ordenado? %d",ordenado);
	if(ordenado==0){
		printf("\nordenando...\n");
		ord_ins(v,MAX_PRUEBA);
		for(int i=0;i<MAX_PRUEBA;i++){
			if(i==MAX_PRUEBA-1)
			{
				printf("%d\n",v[i]);
			}else{
				printf("%d, ",v[i]);
			}
		}
		printf("esta ordenado\n");
	}
	printf("\nOrdenacion por insercion con inicializacion aleatoria\n");
	aleatorio(v,MAX_PRUEBA);
	for(int i=0;i<MAX_PRUEBA;i++){
		if(v[i]>v[i+1]){
			ordenado=0;
		}
		if(i==MAX_PRUEBA-1){
			printf("%d\n",v[i]);
		}else{
			printf("%d, ",v[i]);
		}
	}
	printf("ordenado? %d",ordenado);
	if(ordenado==0){
		printf("\nordenando...\n");
		ord_ins(v,MAX_PRUEBA);
		for(int i=0;i<MAX_PRUEBA;i++){
			if(i==MAX_PRUEBA-1)
			{
				printf("%d\n",v[i]);
			}else{
				printf("%d, ",v[i]);
			}
		}
		printf("esta ordenado\n");
	}
	testDes();
	testAsc();
	testRan();
}
// QUICKSORT //
void testQuick(){	
	inicializar_semilla();
	tablaUmbralDes();
	tablaUmbralAsc();
	tablaUmbralRan();
}

void tablaUmbralDes(){
	int v[MAX];
	int k=1000;
	int promedio=0;
	double t1,t2,t;
	
	if(UMBRAL==1){
		printf("\n%20s---(UMBRAL 1) Vector descendente (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%7st(n)/n^0.9%4st(n)/n^1.08%5st(n)/n^1.3\n","","","","","");
	}
	else if(UMBRAL==10){
		printf("\n%20s---(UMBRAL 10) Vector descendente (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%7st(n)/n^0.9%5st(n)/n^1.1%5st(n)/n^1.3\n","","","","","");
	}
	else if(UMBRAL==100){
		printf("\n%20s---(UMBRAL 100) Vector descendente (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%7st(n)/n^0.9%4st(n)/n^1.118%5st(n)/n^1.3\n","","","","","");
	}
	
	for(int n=500;n<=MAX;n=n*2){
		descendente(v,n);
		t1 = microsegundos();
		ord_rapida(v,n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = 1;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				descendente(v,n);
				ord_rapida(v,n);
			}
			t2=microsegundos();
			t=(t2-t1)/k;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				descendente(v,n);
			}
			t2=microsegundos();
			t = t - ((t2-t1)/k);
		}else{
			promedio = 0;
		}
		umbralDes(n,t,promedio);
	}
}

void tablaUmbralAsc(){
	int v[MAX];
	int k=1000;
	int promedio=0;
	double t1,t2,t;
	
	if(UMBRAL==1){
	printf("\n%20s---(UMBRAL 1) Vector ascendente (QUICKSORT)---\n","");
	printf("\n%13sn%11st(n)%7st(n)/n^0.9%4st(n)/n^1.08%5st(n)/n^1.3\n","","","","","");
	}
	else if(UMBRAL==10){
		printf("\n%20s---(UMBRAL 10) Vector ascendente (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%7st(n)/n^0.9%4st(n)/n^1.11%5st(n)/n^1.3\n","","","","","");
	}
	else if(UMBRAL==100){
		printf("\n%20s---(UMBRAL 100) Vector ascendente (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%7st(n)/n^0.9%4st(n)/n^1.12%5st(n)/n^1.3\n","","","","","");
	}
	
	for(int n=500;n<=MAX;n=n*2){
		ascendente(v,n);
		t1 = microsegundos();
		ord_rapida(v,n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = 1;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				ascendente(v,n);
				ord_rapida(v,n);
			}
			t2=microsegundos();
			t=(t2-t1)/k;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				ascendente(v,n);
			}
			t2=microsegundos();
			t = t - ((t2-t1)/k);
		}else{
			promedio = 0;
		}
		umbralAsc(n,t,promedio);
	}
}

void tablaUmbralRan(){
	int v[MAX];
	int k=1000;
	int promedio=0;
	double t1,t2,t;
	
	if(UMBRAL==1){
	printf("\n%20s---(UMBRAL 1) Vector aleatorio (QUICKSORT)---\n","");
	printf("\n%13sn%11st(n)%9st(n)/n%7st(n)/n^1.1%5st(n)/n^1.3\n","","","","","");
	}
	else if(UMBRAL==10){
		printf("\n%20s---(UMBRAL 10) Vector aleatorio (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%9st(n)/n%6st(n)/n^1.112%4st(n)/n^1.3\n","","","","","");
	}
	else if(UMBRAL==100){
		printf("\n%20s---(UMBRAL 100) Vector aleatorio (QUICKSORT)---\n","");
		printf("\n%13sn%11st(n)%9st(n)/n%7st(n)/n^1.1%5st(n)/n^1.3\n","","","","","");
	}
	
	for(int n=500;n<=MAX;n=n*2){
		aleatorio(v,n);
		t1 = microsegundos();
		ord_rapida(v,n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = 1;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				aleatorio(v,n);
				ord_rapida(v,n);
			}
			t2=microsegundos();
			t=(t2-t1)/k;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				aleatorio(v,n);
			}
			t2=microsegundos();
			t = t - ((t2-t1)/k);
		}else{
			promedio = 0;
		}
		umbralRan(n,t,promedio);
	}
}

void umbralDes(int n, double t, int promedio){
	double x,y,z;
	if(UMBRAL==1){
		x = t/pow(n,0.9);
		y = t/pow(n,1.08);
		z = t/pow(n,1.3);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		} 
		else{
			printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
	else if(UMBRAL==10){
		x = t/pow(n,0.9);
		y = t/pow(n,1.1);
		z = t/pow(n,1.3);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
		else{
			printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
		else if(UMBRAL==100){
			x = t/pow(n,0.9);
			y = t/pow(n,1.118);
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

void umbralAsc(int n, double t, int promedio){

	double x,y,z;
	if(UMBRAL==1){
		x = t/pow(n,0.9);
		y = t/pow(n,1.08);
		z = t/pow(n,1.3);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		} 
		else{
			printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
	else if(UMBRAL==10){
		x = t/pow(n,0.9);
		y = t/pow(n,1.11);
		z = t/pow(n,1.3);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
		else{
			printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
		else if(UMBRAL==100){
			x = t/pow(n,0.9);
			y = t/pow(n,1.12);
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

void umbralRan(int n, double t, int promedio){

	double x,y,z;
	if(UMBRAL==1){
		x = t/pow(n,0.9);
		y = t/pow(n,1.1);
		z = t/pow(n,1.3);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		} 
		else{
			printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
	else if(UMBRAL==10){
		x = t/pow(n,0.9);
		y = t/pow(n,1.112);
		z = t/pow(n,1.3);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
		else{
			printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
		else if(UMBRAL==100){
			x = t/pow(n,0.9);
			y = t/pow(n,1.1);
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

void testDes(){
	int v[MAX];
	int k=10000;
	double t1,t2,t,x,y,z;
	bool promedio = false;	
	
	printf("%27s---Vector descendente---\n","");
	printf("\n%13sn%11st(n)%6st(n)/n^1.8%6st(n)/n^2%6st(n)/n^2.2\n","","","","","");
	
	for(int n=500;n<=MAX;n=n*2){
		descendente(v,n);
		t1 = microsegundos();
		ord_ins(v,n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = true;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				descendente(v,n);
				ord_ins(v,n);
			}
			t2=microsegundos();
			t=(t2-t1)/k;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				descendente(v,n);
			}
			t2=microsegundos();
			t = t - ((t2-t1)/k);
		}else{
			promedio = false;
		}
		x = t/pow(n,1.8);
		y = t/(n*n);
		z = t/pow(n,2.2);
		
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
		} else{
		printf("   %12d%15.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
		}
	}
}

void testAsc(){
	int v[MAX];
	int k=10000;
	double t1,t2,t,x,y,z;
	bool promedio = false;
	
	printf("\n%28s---Vector ascendente---\n","");
	printf("\n%13sn%11st(n)%6st(n)/n^0.9%7st(n)/n%7st(n)/n^1.1\n","","","","","");
	
	for(int n=500;n<=32000;n=n*2){
		ascendente(v,n);
		t1 = microsegundos();
		ord_ins(v,n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = true;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				ord_ins(v,n);
			}
			t2=microsegundos();
			t=(t2-t1)/k;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				ascendente(v,n);
			}
			t2=microsegundos();
			t = t - ((t2-t1)/k);
		}else{
			promedio = false;
		}
		x = t/pow(n,0.9);
		y = t/n;
		z = t/pow(n,1.1);
		
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
		} else{
		printf("   %12d%15.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
		}
	}
}

void testRan(){
	int v[MAX];
	int k=10000;
	double t1,t2,t,x,y,z;
	bool promedio = false;
	
	printf("\n%29s---Vector aleatorio---\n","");
	printf("\n%13sn%11st(n)%6st(n)/n^1.8%6st(n)/n^2%6st(n)/n^2.2\n","","","","","");
	
	for(int n=500;n<=32000;n=n*2){
		aleatorio(v,n);
		t1 = microsegundos();
		ord_ins(v,n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = true;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				aleatorio(v,n);
				ord_ins(v,n);
			}
			t2=microsegundos();
			t=(t2-t1)/k;
			t1=microsegundos();
			for(int i=0;i<k;i++){
				aleatorio(v,n);
			}
			t2=microsegundos();
			t = t - ((t2-t1)/k);
		}else{
			promedio = false;
		}
		x = t/pow(n,1.8);
		y = t/(n*n);
		z = t/pow(n,2.2);
		
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
		} else{
		printf("   %12d%15.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
		}
	}
}









