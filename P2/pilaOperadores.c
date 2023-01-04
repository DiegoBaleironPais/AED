#include <stdlib.h>

//Implementacion TAD pila

//CONTENIDO DE CADA ELEMENTO DE LA PILA
//MODIFICAR: PARA LA PILA DE OPERADORES: char
//MODIFICAR: PARA LA PILA DE OPERANDOS: abin
typedef char tipoelemPilaOperadores;
///////////////////////////////////////////////////////

//Definicion del tipo de datos pila
struct tipo_celda {
    tipoelemPilaOperadores elemento;
    struct tipo_celda * sig;
};

typedef struct tipo_celda * pilaOperadores;
/////////////////////////////////////////////////////////

void crearPilaDores(pilaOperadores *P) {
    *P = NULL;
}

void destruirPilaDores(pilaOperadores *P) {
    pilaOperadores aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

unsigned esVaciaPilaDores(pilaOperadores P) {
    return P == NULL;
}

tipoelemPilaOperadores topeDores(pilaOperadores P) {
    if (!esVaciaPilaDores(P)) /*si pila no vacia*/
        return P->elemento;
}

void pushDores(pilaOperadores *P, tipoelemPilaOperadores E) {
    pilaOperadores aux;
    aux = (pilaOperadores) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    aux->sig = *P;
    *P = aux;
}

void popDores(pilaOperadores *P) {
    pilaOperadores aux;
    if (!esVaciaPilaDores(*P)) /*si pila no vacia*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
