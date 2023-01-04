#ifndef PILAOPERADORES_H
#define PILAOPERADORES_H

//Interfaz TAD pila
typedef void *pilaOperadores; /*tipo opaco*/

//CONTENIDO DE CADA ELEMENTO DE LA PILA
//MODIFICAR: PARA LA PILA DE OPERADORES: char
//MODIFICAR: PARA LA PILA DE OPERANDOS: abin
typedef char tipoelemPilaOperadores;

//Funciones de creacion y destruccion
/**
 * Crea la pila vacia. 
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPilaDores(pilaOperadores *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPilaDores(pilaOperadores *P);

//Funciones de informacion
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPilaDores(pilaOperadores P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 * 
*/
tipoelemPilaOperadores topeDores(pilaOperadores P);

//Funciones de insercion/eliminacion
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * en el tope de la pila
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo. 
 */
void pushDores(pilaOperadores *P, tipoelemPilaOperadores E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void popDores(pilaOperadores *P);

#endif	// PILA_H

