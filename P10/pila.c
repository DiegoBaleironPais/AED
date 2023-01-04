#include <stdlib.h>
#include <stdio.h>

//Numero de trabajadores y de tareas a resolver
#define tamanhoProblema 6

//Struct que representa un nodo del arbol
typedef struct tipoelemPila {
    int solucion[tamanhoProblema];
    int nivel;
    int valorActual;
    float CI;
    float BE;
    float CS;
}tipoelemPila;
///////////////////////////////////////////////////////

//Definicion del tipo de datos pila
struct tipo_celda {
    tipoelemPila elemento;
    struct tipo_celda * sig;
};

typedef struct tipo_celda * pila;
/////////////////////////////////////////////////////////

//Creacion de un nodo con estimaciones triviales
tipoelemPila crearTipoelemPilaTrivial (int tareas[][tamanhoProblema], int solucion[], int maximoValor) {
    tipoelemPila nuevo;
    int CI = 0;
    int CS = 0;
    int nivel = -1;
    
    for (int i = 0; i < tamanhoProblema; i++) {
        nuevo.solucion[i] = solucion[i];
        if (solucion[i] != -1) {
            nivel++;
            CS += tareas[i][solucion[i]];
            CI += tareas[i][solucion[i]];
        }
    }
    
    CS += maximoValor * (tamanhoProblema - (nivel+1));
    nuevo.CI = CI;
    nuevo.valorActual = CI;
    nuevo.CS = CS;
    nuevo.nivel = nivel;
    nuevo.BE = (nuevo.CS + nuevo.CI) / 2;
    return nuevo;
}

//Creacion de un nodo con estimaciones precisas
tipoelemPila crearTipoelemPilaNoTrivial (int tareas[][tamanhoProblema], int solucion[], int cotaSuperior, int cotaInferior) {
    tipoelemPila nuevo;
    int nivel = -1;
    int valorActual = 0;
    
    for (int i = 0; i < tamanhoProblema; i++) {
        nuevo.solucion[i] = solucion[i];
        if (solucion[i] != -1) {
            nivel++;
            valorActual += tareas[i][solucion[i]];
        }
    }
    
    nuevo.CI = cotaInferior;
    nuevo.valorActual = valorActual;
    nuevo.CS = cotaSuperior;
    nuevo.nivel = nivel;
    nuevo.BE = (nuevo.CS + nuevo.CI) / 2;
    return nuevo;
}

/**
 * Crea la pila vacia. 
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPila(pila *P) {
    *P = NULL;
}

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPila(pila *P) {
    pila aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPila(pila P) {
    return P == NULL;
}

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 * 
*/
tipoelemPila tope(pila P) {
    if (!esVaciaPila(P)) /*si pila no vacia*/
        return P->elemento;
}

//Funciones de insercion/eliminacion
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * segun la prioridad de E
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo. 
 */
void push(pila *P, tipoelemPila E) {
    pila aux;
    pila new = *P;
    pila new2;
    aux = (pila) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    
    if (*P == NULL || (*P)->elemento.BE <= aux->elemento.BE) {
        aux->sig = *P;
        *P = aux;
    } else {
        while ( new != NULL && new->elemento.BE > aux->elemento.BE) {
            new2 = new;
            new = new->sig;
        }
        new2->sig = aux;
        aux->sig = new;
    }
}

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void pop(pila *P) {
    pila aux;
    if (!esVaciaPila(*P)) /*si pila no vacia*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
