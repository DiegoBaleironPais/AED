#ifndef ABB_H
#define ABB_H

#include "cola.h"

/**
 * Tipo de dato abstracto para arbol binario con clave de
 * ordenacion y elemento de celda.
 */


///////////////////////////////////////INICIO PARTE MODIFICABLE
typedef char * tipoclave;

typedef struct tipoelem{
    char nombreJugador[30];
    char rol;
    cola tareas;
    
}tipoelem;

//////////////////////////////////////////FIN PARTE MODIFICABLE
		
typedef struct celda * abb;//tipo opaco

/////////////////////////////// FUNCIONES

//FUNCIONES DE CREACIÓN Y DESTRUCCIÓN DEL ÁRBOL

void crear(abb *A);

void destruir(abb *A);

unsigned es_vacio(abb A);

abb izq(abb A);

abb der(abb A);

unsigned es_miembro(abb A, tipoelem E);

void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo);

void insertar(abb *A, tipoelem E);

void suprimir(abb *A,tipoelem E);

void modificar(abb A, tipoelem nodo);

void leer(abb A, tipoelem *E);

#endif	// ABB_H

