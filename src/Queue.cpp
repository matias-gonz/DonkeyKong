#include "Queue.h"
#include <cstdlib>

/*Definicion de struct Nodo y su primitiva*/
typedef struct Nodo{
    void* dato;
    struct Nodo* prox;
}nodo_t;

nodo_t* nodo_crear(void* valor){
    nodo_t* nodo = static_cast<nodo_t *>(malloc(sizeof(nodo_t)));
    if(!nodo) return NULL;
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}
//-------------------------------------------------------------

/*Definicion del struct cola y sus primitivas*/
typedef struct cola{
    nodo_t* prim;
    nodo_t* ultimo;
}cola_t;

cola_t* cola_crear(void){
    cola_t* cola = static_cast<cola_t *>(malloc(sizeof(cola_t)));
    if(!cola) return NULL;
    cola->prim = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t* cola,void destruir_dato(void*)){
    while(!cola_esta_vacia(cola)){
        void* valor = cola_desencolar(cola);
        if (destruir_dato) destruir_dato(valor);
    }
    free(cola);
}


bool cola_esta_vacia(const cola_t* cola){
    return !cola->prim;
}

bool cola_encolar(cola_t* cola, void* valor){
    nodo_t* elemento = nodo_crear(valor);
    if(!elemento) return false;

    if (cola_esta_vacia(cola)){
        cola->prim = elemento;
        cola->ultimo = cola->prim;
    }
    else{
        cola->ultimo->prox = elemento;
        cola->ultimo = cola->ultimo->prox;
    }
    return true;
}

void* cola_ver_primero(const cola_t* cola){
    if(cola_esta_vacia(cola)) return NULL;
    return cola->prim->dato;
}

void* cola_desencolar(cola_t* cola){
    if (cola_esta_vacia(cola)) return NULL;
    nodo_t* elemento = cola->prim;
    void* dato = elemento->dato;
    cola->prim = cola->prim->prox;
    free(elemento);
    return dato;
}