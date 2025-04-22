void inicializar_monticulo(monticulo *M){
    M->ultimo=0;
}

int monticulo_vacio(monticulo *M){
    return M->ultimo=0;
}

void insertar(int x, monticulo *M){
    if(M->ultimo==TAM){
        printf("\nerror monticulo lleno");
    }else{
        M->ultimo=M->ultimo+1;
        M->vector[M->ultimo]=x;
        flotar(M,M->ultimo);
    }
}

void flotar(monticulo *M, int i){
    int aux;
    while(i>0 && M->vector[i/2] < M->vector[i]){
        aux = M->vector[i/2];
        M->vector[i/2]=M->vector[i];
        M->vector[i]=aux;

        i=i/2;
    }
}
