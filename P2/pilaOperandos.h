#ifndef PILAOPERANDOS_H
#define PILAOPERANDOS_H
#include "abin.h"
//Interfaz TAD pila
typedef void *pilaOperandos; /*tipo opaco*/

//CONTENIDO DE CADA ELEMENTO DE LA PILA
//MODIFICAR: PARA LA PILA DE OPERADORES: char
//MODIFICAR: PARA LA PILA DE OPERANDOS: abin
typedef abin tipoelemPilaOperandos;

//Funciones de creacion y destruccion
/**
 * Crea la pila vacia. 
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPilaAndos(pilaOperandos *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPilaAndos(pilaOperandos *P);

//Funciones de informacion
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPilaAndos(pilaOperandos P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 * 
*/
tipoelemPilaOperandos topeAndos(pilaOperandos P);

//Funciones de insercion/eliminacion
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * en el tope de la pila
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo. 
 */
void pushAndos(pilaOperandos *P, tipoelemPilaOperandos E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void popAndos(pilaOperandos *P);

#endif	// PILA_H

