#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 ){
		return 0.0;
	}
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

int fib1(int n){
	if(n<2) return n;
	else return (fib1(n-1) + fib1(n-2));
}

int fib2(int n){
	int i=1, j=0;
	for(int k=1;k<=n;k++){
		j=i+j;
		i=j-i;
	}
	return j;
}

int fib3(int n){
	int i=1, j=0, k=0, h=1, t=0;
	while(n>0){
		if (n%2!=0){
			t=j*h;
			j=i*h+j*k+t;
			i=i*k+t;
		}
		t=h*h;
		h=2*k*h+t;
		k=k*k+t;
		n=n/2;
	}
	return j;
}

void test1(){
	int n, i;
	int k=100000;
	bool promedio = false;
	double t1, t2, t, x, y, z, prima;
	printf("\t      n\t\t     t\t   t(n)/1.1^n\t t(n)/1.61^n\t   t(n)/2^n\n\n");
	for(n=2;n<=32;n=n*2){
		t1 = microsegundos();	
		fib1(n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = true;
			t1=microsegundos();
			for(i=0;i<k;i++){
				fib1(n);
			}
			t2=microsegundos();
			prima=t2-t1;
			t=prima/k;	
		} else{
		promedio = false;
		}
		x=t/pow(1.1,n);
		y=t/pow(((1+sqrt(5))/2),n);
		z=t/pow(2,n);
		if(promedio){
			printf("(*)");
			printf("%12d%15.5f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		} else{
		printf("   %12d%15.5f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
	printf("\n");
}

void test2() {
	int n, i;
	int k=10000;
	bool promedio = false;
	double t1, t2, t, x, y, z, prima;
	printf("\t      n\t\t     t\t   t(n)/n^0.8\t t(n)/n\t   t(n)/n*log(n)\n\n");
	for(n=1000;n<=10000000;n=n*10){
		t1 = microsegundos();
		fib2(n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = true;
			t1=microsegundos();
			for(i=0;i<k;i++){
				fib2(n);
			}
			t2=microsegundos();
			prima=t2-t1;
			t=prima/k;
		} else{
		promedio = false;
		}
		x=t/pow(n,0.8);
		y=t/n;
		z=t/(n*log(n));
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		} else{
		printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
	printf("\n");
}

void test3() {
	int n, i;
	int k=1000000;
	bool promedio = false;
	double t1, t2, t, x, y, z, prima;
	printf("\t      n\t\t     t\t   t(n)/sqrt(log(n))\t t(n)/log(n)\t   t(n)/n^0.5\n\n");
	for(n=1000;n<=10000000;n=n*10){
		t1 = microsegundos();
		fib3(n);
		t2 = microsegundos();
		t = t2-t1;
		if(t<500){
			promedio = true;
			t1=microsegundos();
			for(i=0;i<k;i++){
				fib3(n);
			}
			t2=microsegundos();
			prima=t2-t1;
			t=prima/k;
		} else{
		promedio = false;
		}
		x = t / sqrt(log(n));
		y = t / log(n);
		z = t / pow(n, 0.5);
		if(promedio){
			printf("(*)");
			printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		} else{
		printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		}
	}
	printf("\n");
}

int main(){
	test1();
	//test1();
	//test1();
	printf("-----------------------------------------------------------------------------\n");
	test2();
	//test2();
	//test2();
	printf("-----------------------------------------------------------------------------\n");
	test3();
	//test3();
	//test3();
	return 0;
}





