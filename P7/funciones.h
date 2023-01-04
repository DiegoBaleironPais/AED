#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "grafo.h"

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS
//Opción a del menú, introducir un vertice en el grafo
void introducir_vertice(grafo *G);

//Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G);

//Opción c del menú, crear una relación entre dos vértices
void nuevo_arco(grafo *G);

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G);

//Opción i del menú, imprimir el grafo
void imprimir_grafo(grafo G);

//Se guardan los datos del grafo en un archivo externo
void guardar_datos_grafo(grafo G);

//Se leen los datos de un archivo externo
void leer_datos_archivo(grafo *G);

//Se aplica el algoritmo de floyd_wharsall para dos vertices y imprime por pantalla la ruta optima
void floyd_wharsall (grafo G);

//Se aplica el algoritmo de prim y se obtiene el arbol de coste minimo
void prim(grafo G);
#endif	/* FUNCIONES_H */

