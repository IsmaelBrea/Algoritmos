//·Autores: José Comerón Lago, Ismael Brea Arias, Andrés Rey Luna.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define TAM_TABLA 11
#define TAM_TABLA_SINONIMOS 38197
#define PALABRAS 19062
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

// Estructura para los sinónimos
typedef struct {
    char clave[LONGITUD_CLAVE];
    char sinonimos[LONGITUD_SINONIMOS];
} item;

// Estructura para cada entrada en la tabla
typedef struct {
    int ocupada;
    char clave[LONGITUD_CLAVE];
    char sinonimos[LONGITUD_SINONIMOS];
} entrada;

typedef int pos;
typedef entrada *tabla_cerrada;

// Inicializa la tabla cerrada
void inicializar_cerrada(tabla_cerrada *diccionario, int tam) {
    int i;
    *diccionario = (tabla_cerrada)malloc(tam * sizeof(entrada));
    for ( i = 0; i < tam; i++) {
        (*diccionario)[i].ocupada = 0;  // Inicializa como no ocupada
        (*diccionario)[i].clave[0] = '\0'; // Inicializa la clave
        (*diccionario)[i].sinonimos[0] = '\0'; // Inicializa los sinónimos
    }
}

// Busca una clave en la tabla cerrada
pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
                   int *colisiones, unsigned int (*dispersion)(char *, int),
                   unsigned int (*resol_colisiones)(int, int)) {
    int pos_ini = dispersion(clave, tam);
    int i = 0,pos;
    *colisiones = 0;

    while (i < tam) {
        pos = resol_colisiones(pos_ini, i);
        if (!diccionario[pos].ocupada) return -1;  // No encontrado
        if (strcmp(diccionario[pos].clave, clave) == 0) return pos;
        (*colisiones)++;
        i++;
    }
    return -1;  // Tabla llena, no encontrado
}


// Inserta una clave en la tabla cerrada
int insertar_cerrada(char *clave, char *sinonimos, 
                    tabla_cerrada *diccionario, int tam,
                     unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(int, int)) {
    int pos_ini = dispersion(clave, tam);
    int i = 0;
    int colisiones = 0,pos;

    while (i < tam) {
        pos = resol_colisiones(pos_ini, i);
        if (!(*diccionario)[pos].ocupada) {
            // Aquí se realiza la inserción
            strcpy((*diccionario)[pos].clave, clave);
            strcpy((*diccionario)[pos].sinonimos, sinonimos);
            (*diccionario)[pos].ocupada = 1;
            return colisiones; // Retornar el número de colisiones
        }
        if (strcmp((*diccionario)[pos].clave, clave) == 0) {
            // Clave ya existe
            return colisiones; // No contar como colisión
        }
        colisiones++; // Contar la colisión
        i++;
    }
    return -1; // Tabla llena, no se puede insertar
}


// Muestra la tabla cerrada
void mostrar_cerrada(tabla_cerrada diccionario, int tam) {
    int i;
    printf("{\n");
    for (i = 0; i < tam; i++) {
        if (diccionario[i].ocupada) {
            printf("%d- (%s )\n", i, diccionario[i].clave);
        } else {
            printf("%d-\n", i);
        }
    }
    printf("}\n");
}

// PARTE 1: Implementación de tablas de dispersión cerradas

// Función de dispersión para el ejemplo de clase
unsigned int ndispersion(char *clave, int tamTabla) {
    if (strcmp(clave, "ANA")==0) return 7;
    if (strcmp(clave, "JOSE")==0) return 7;
    if (strcmp(clave, "OLGA")==0) return 7;
    return 6;
}

// Funciones de resolución de colisiones para la tabla de prueba
unsigned int resolucion_lineal_prueba(int pos_ini, int num_intento) {
    return (pos_ini + num_intento) % TAM_TABLA;
}

unsigned int resolucion_cuadratica_prueba(int pos_ini, int num_intento) {
    return (pos_ini + num_intento * num_intento) % TAM_TABLA;
}

unsigned int resolucion_doble_prueba(int pos_ini, int num_intento) {
    return (pos_ini + num_intento * (5 - (pos_ini % 5))) % TAM_TABLA;
}

// Prueba una estrategia de resolución de colisiones
void probar_estrategia(char *nombre_estrategia, unsigned int 
        (*resol_colisiones)(int, int), unsigned int (*dispersion)(char *, int)) {
    char *claves[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN"};
    int total_colisiones = 0,i,colisiones;
    int total_insertados = sizeof(claves) / sizeof(claves[0]);
    tabla_cerrada diccionario;
    inicializar_cerrada(&diccionario, TAM_TABLA);

    printf("***TABLA CERRADA %s\n", nombre_estrategia);

    for (i = 0; i < total_insertados; i++) {
        colisiones = insertar_cerrada(claves[i], "", &diccionario, 
            TAM_TABLA, ndispersion, resol_colisiones);
        if (colisiones != -1) {
            total_colisiones += colisiones; // Sumar solo si la inserción fue exitosa
        } else {
            printf("No se pudo insertar la clave: %s, tabla llena\n",
                 claves[i]);
        }
    }

    mostrar_cerrada(diccionario, TAM_TABLA);
    printf("Numero total de colisiones al insertar los elementos: %d\n", 
        total_colisiones);

    for (i = 0; i < total_insertados; i++) {
        colisiones=0;
        int pos = buscar_cerrada(claves[i], diccionario, TAM_TABLA,
             &colisiones, ndispersion, resol_colisiones);
        if (pos != -1) {
            printf("Al buscar: %s, encuentro: %s, colisiones: %d\n", 
                claves[i], diccionario[pos].clave, colisiones);
        } else {
            printf("Al buscar: %s, no se encontró, colisiones: %d\n",
                 claves[i], colisiones);
        }
    }

    colisiones=0;
    buscar_cerrada("CARLOS", diccionario, TAM_TABLA,
         &colisiones, ndispersion, resol_colisiones);
    printf("No encuentro: CARLOS, colisiones: %d\n", colisiones);

    free(diccionario);
    printf("\n");
}


// PARTE 2: Implementación del diccionario de sinónimos

// Funciones de dispersión para la tabla de sinónimos
unsigned int dispersionA(char *clave, int tamTabla) {
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++) 
        valor += clave[i];
    return valor % tamTabla;
}

unsigned int dispersionB(char *clave, int tamTabla) {
    int i, n = (strlen(clave) < 8) ? strlen(clave) : 8;
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++) 
        valor = (valor<<5) + clave[i]; 
    return valor % tamTabla;
}


unsigned int resolucion_lineal(int pos_ini, int num_intento) {
    return (pos_ini + num_intento) % TAM_TABLA_SINONIMOS;
}

unsigned int resolucion_cuadratica(int pos_ini, int num_intento) {
    return (pos_ini + num_intento * num_intento) % TAM_TABLA_SINONIMOS;
}

unsigned int resolucion_doble(int pos_ini, int num_intento) {
    return (pos_ini + num_intento * 
        (10007 - (pos_ini % 10007))) % TAM_TABLA_SINONIMOS;
}

// Lee los sinónimos desde un archivo
int leer_sinonimos(item datos[]) {
    char c;
    int i, j;
    FILE *archivo;

    if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
        printf("Error al abrir 'sinonimos.txt'\n");
        return(EXIT_FAILURE);
    }

    // Leer el archivo y llenar el array de datos
    for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
        if ((c = fgetc(archivo)) != '\t') {
            printf("Error al leer el tabulador\n");
            return(EXIT_FAILURE);
        }
        for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
            if (j < LONGITUD_SINONIMOS - 1)
                datos[i].sinonimos[j] = c;
        }
        datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS - 1)] = '\0';
    }

    if (fclose(archivo) != 0) {
        printf("Error al cerrar el fichero\n");
        return(EXIT_FAILURE);
    }
    return i; // Retorna el número de elementos leídos
}

void buscar_n_elementos(tabla_cerrada diccionario, int n, 
                        unsigned int (*dispersion)(char*, int),
                        unsigned int (*resol_colisiones)(int, int)) {
    int i,colisiones;
    char clave[LONGITUD_CLAVE];
    for (i = 0; i < n; i++) {
        sprintf(clave, "clave%d", rand() % TAM_TABLA_SINONIMOS);
        colisiones=0;
        buscar_cerrada(clave, diccionario, TAM_TABLA_SINONIMOS, 
            &colisiones, dispersion, resol_colisiones);
    }
}


int insertar_todos_elementos(unsigned int (*dispersion)(char*, int),
                             unsigned int (*resol_colisiones)(int, int)) {
    tabla_cerrada diccionario;
    item *datos = malloc(TAM_TABLA_SINONIMOS * sizeof(item));
    int num_sinonimos = leer_sinonimos(datos);
    int total_colisiones = 0,i,colisiones;
    inicializar_cerrada(&diccionario, TAM_TABLA_SINONIMOS);

    for(i = 0; i < num_sinonimos; i++) {
        colisiones = insertar_cerrada(datos[i].clave, datos[i].sinonimos, 
                                          &diccionario, TAM_TABLA_SINONIMOS, 
                                          dispersion, resol_colisiones);
        if (colisiones >= 0) {
            total_colisiones += colisiones;
        }
    }
    
    free(datos);
    free(diccionario);
    return total_colisiones;
}

//TIEMPOS DE EJECUCIÓN
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tabla(int n, double t, double sub, double cota,
         double sobre, bool promedio) {
    printf("%s\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n",
           promedio ? "(*)" : "   ",
           n, t, t / pow(n, sub), t / pow(n, cota), t / pow(n, sobre));
}

void tiemposEjecuion(tabla_cerrada *diccionario, item *datos,
             unsigned int (*dispersion)(char *, int),
             unsigned int (*resol_colisiones)(int, int),
             double cota1, double cota2, double cota3) {
    int i, n=125, j, colisiones, totalColisiones, random, t1;
    double ta, tb, t;
    i = 0;
    colisiones = 0;
    totalColisiones = 0;
    t1 = 0;
    inicializar_cerrada(diccionario, TAM_TABLA_SINONIMOS);

    // Insertamos las palabras y contamos las colisiones
    for (; i < PALABRAS; i++) {
        colisiones = insertar_cerrada(datos[i].clave, datos[i].sinonimos,
                                      diccionario, TAM_TABLA_SINONIMOS,
                                       dispersion,resol_colisiones);
        totalColisiones += colisiones;
    }
    // Imprimimos los resultados de la inserción
    printf("\nInsertando %d elementos...\n",PALABRAS);
    printf("total de colisiones: %d\n", totalColisiones);
    printf("Buscando n elementos...\n\n");
    printf("\t    n\t\t   t(n)\t  t(n)/subestimada  "
            "(n)/ajustada    (n)/n^sobreestimada\n");
    // Realizamos las pruebas de tiempo de búsqueda para diferentes tamaños de n
    while (n <= 16000) {
        ta = microsegundos(); // Tiempo antes de comenzar la búsqueda
        // Realizamos la búsqueda de n elementos aleatorios
        for (j = 0; j < n; j++) {
            random = rand() % PALABRAS;
            buscar_cerrada(datos[random].clave,*diccionario,
                            TAM_TABLA_SINONIMOS,
                           &colisiones, dispersion, resol_colisiones);
        }
        t = microsegundos() - ta; // Tiempo total de búsqueda
        ta = microsegundos(); // Tiempo para el ciclo de referencia (sin operaciones de búsqueda)
        for (j = 0; j < n; j++) {
            random = rand() % PALABRAS;
        }
        t1 = microsegundos() - ta; // Tiempo de referencia
        t = t - t1; // Ajustamos el tiempo real de búsqueda

        if (t <= 500) {
            tb = microsegundos(); // Medición adicional si el tiempo es bajo
            for (i = 0; i < 1000; i++) {
                for (j = 0; j < n; j++) {
                    random = rand() % PALABRAS;
                    buscar_cerrada(datos[random].clave, *diccionario,
                                   TAM_TABLA_SINONIMOS, &colisiones,dispersion,
                                   resol_colisiones);
                }
            }
            ta = microsegundos() - tb;
            t = (ta - t1) / 1000; // Promediamos los tiempos si es necesario
            printf("(*)");
        }else printf("  ");
        
        // Imprimimos los resultados en formato de tabla
        printf("\t%6d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\n", 
               n,t, t / pow(n, cota1), t / pow(n, cota2), t / pow(n, cota3));
        n=n*2;
    }
}

void probar_tiempos_busqueda() {
    item datos[PALABRAS];
    leer_sinonimos(datos);
    tabla_cerrada diccionario = malloc(TAM_TABLA_SINONIMOS * sizeof(entrada));

    printf("\n***Dispersion cerrada lineal con dispersion A: ");
    tiemposEjecuion(&diccionario, datos, dispersionA, 
    resolucion_lineal, 0.8, 1, 1.2);
    printf("\n***Dispersion cerrada cuadratica con dispersion A: ");
    tiemposEjecuion(&diccionario, datos, dispersionA, 
    resolucion_cuadratica, 0.9, 1.02, 1.2);
    printf("\n***Dispersion cerrada doble con dispersion A: ");
    tiemposEjecuion(&diccionario, datos, dispersionA,
     resolucion_doble, 0.9, 1.05, 1.2);
    printf("\n***Dispersion cerrada lineal con dispersion B: ");
    tiemposEjecuion(&diccionario, datos, dispersionB, 
    resolucion_lineal, 0.9, 0.95, 1.2);
    printf("\n***Dispersion cerrada cuadratica con dispersion B: ");
    tiemposEjecuion(&diccionario, datos, dispersionB, 
    resolucion_cuadratica, 0.9, 1.07, 1.2);
    printf("\n***Dispersion cerrada doble con dispersion B: ");
    tiemposEjecuion(&diccionario, datos, dispersionB, 
    resolucion_doble, 0.8, 1., 1.2);

    free(diccionario);
}

int main() {
    srand(time(NULL));
    probar_estrategia("LINEAL", resolucion_lineal_prueba, ndispersion);
    probar_estrategia("CUADRATICA", resolucion_cuadratica_prueba, ndispersion);
    probar_estrategia("DOBLE", resolucion_doble_prueba, ndispersion);

    probar_tiempos_busqueda();
    return 0;
}