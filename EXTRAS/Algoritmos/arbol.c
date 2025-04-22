#include <stdio.h>
#include <stdlib.h>

struct nodo
{
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};

typedef struct nodo *posicion;
typedef struct nodo *arbol;

static struct nodo *crearnodo(int e)
{
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL)
    {
        printf("memoria agotada\n");
        exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

arbol insertar(int e, arbol a)
{
    if (a == NULL)
        return crearnodo(e);
    else if (e < a->elem)
        a->izq = insertar(e, a->izq);
    else if (e > a->elem)
        a->der = insertar(e, a->der);
    else
        a->num_repeticiones++;
    return a;
}

arbol creararbol()
{
    return NULL;
}

int esarbolvacio(arbol a)
{
    if (a == NULL)
        return 1;
    else
        return 0;
}

posicion hijoizquierdo(arbol a)
{
    if (a->izq != NULL)
        return a->izq;
    else
        return NULL;
}

posicion hijoderecho(arbol a)
{
    if (a->der != NULL)
        return a->der;
    else
        return NULL;
}

int elemento(posicion p)
{
    return p->elem;
}

int numerorepeticiones(posicion p)
{
    return p->num_repeticiones;
}

posicion buscar(int i, arbol a)
{
    if (a == NULL)
        return NULL;
    else if (i == elemento(a))
        return a;
    else if (i < elemento(a))
        return buscar(i, hijoizquierdo(a));
    else if (i > elemento(a))
        return buscar(i, hijoderecho(a));
    else
        return NULL;
}

arbol eliminararbol(arbol a)
{
    if (a != NULL)
    {
        a->izq = eliminararbol(hijoizquierdo(a));
        a->der = eliminararbol(hijoderecho(a));
        free(a);
    }
    return NULL;
}

int altura(arbol a)
{
    int alt = 0, altizq = 0, altder = 0;

    if (esarbolvacio(a))
        return -1;
    else if (esarbolvacio(hijoizquierdo(a)) && esarbolvacio(hijoderecho(a)))
        return 0;
    else
    {
        if (!esarbolvacio(hijoizquierdo(a)))
            altizq += altura(hijoizquierdo(a));
        if (!esarbolvacio(hijoderecho(a)))
            altder += altura(hijoderecho(a));
        if (altizq >= altder)
            alt = altizq;
        else
            alt = altder;
        return ++alt;
    }
}

void visualizar(arbol a)
{
    if (esarbolvacio(a))
        printf("()");
    else
    {
        if (!esarbolvacio(hijoizquierdo(a)))
        {
            printf("(");
            visualizar(hijoizquierdo(a));
            printf(")");
        }
        printf(" %d ", elemento(a));
        if (!esarbolvacio(hijoderecho(a)))
        {
            printf("(");
            visualizar(hijoderecho(a));
            printf(")");
        }
    }
}

void test()
{
    int i;
    posicion p;
    arbol a = creararbol();

    printf("arbol vacio: ");
    visualizar(a);
    printf(".\n");
    printf("altura del arbol: %i\n", altura(a));
    printf("inserto un 3\n");
    a = insertar(3, a);
    printf("inserto un 1\n");
    a = insertar(1, a);
    printf("inserto un 2\n");
    a = insertar(2, a);
    printf("inserto un 5\n");
    a = insertar(5, a);
    printf("inserto un 4\n");
    a = insertar(4, a);
    printf("inserto un 5\n");
    a = insertar(5, a);
    printf("arbol: ");
    visualizar(a);
    printf(".\n");
    printf("altura del arbol: %i\n", altura(a));
    for (i = 1; i <= 6; i++)
    {
        p = buscar(i, a);
        if (p != NULL)
            printf("busco %d y encuentro %d repetido: %d veces\n", i,
                   elemento(p), numerorepeticiones(p));
        else
            printf("busco %d y no encuentro nada\n", i);
    }
    printf("borro todos los nodos liberando la memoria:\n");
    a = eliminararbol(a);
    printf("arbol vacio: ");
    visualizar(a);
    printf(".\n");
    printf("altura del arbol: %i\n", altura(a));
}

int main()
{
    test();
    return 0;
}