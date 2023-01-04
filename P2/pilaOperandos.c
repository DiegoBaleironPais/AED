#include <stdlib.h>
#include "abin.h"
//Implementacion TAD pila

//CONTENIDO DE CADA ELEMENTO DE LA PILA
//MODIFICAR: PARA LA PILA DE OPERADORES: char
//MODIFICAR: PARA LA PILA DE OPERANDOS: abin
typedef abin tipoelemPilaOperandos;
///////////////////////////////////////////////////////

//Definicion del tipo de datos pila
struct tipo_celda {
    tipoelemPilaOperandos elemento;
    struct tipo_celda * sig;
};

typedef struct tipo_celda * pilaOperandos;
/////////////////////////////////////////////////////////

void crearPilaAndos(pilaOperandos *P) {
    *P = NULL;
}

void destruirPilaAndos(pilaOperandos *P) {
    pilaOperandos aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

unsigned esVaciaPilaAndos(pilaOperandos P) {
    return P == NULL;
}

tipoelemPilaOperandos topeAndos(pilaOperandos P) {
    if (!esVaciaPilaAndos(P)) /*si pila no vacia*/
        return P->elemento;
}

void pushAndos(pilaOperandos *P, tipoelemPilaOperandos E) {
    pilaOperandos aux;
    aux = (pilaOperandos) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    aux->sig = *P;
    *P = aux;
}

void popAndos(pilaOperandos *P) {
    pilaOperandos aux;
    if (!esVaciaPilaAndos(*P)) /*si pila no vacia*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
