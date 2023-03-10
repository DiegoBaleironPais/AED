#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Estructura privada
struct tipografo {
    int N; //número de vértices del grafo
    tipovertice VERTICES[MAXVERTICES]; //vector de vértices
    int AT[MAXVERTICES][MAXVERTICES]; //matriz de adyacencia de tripulantes
    int AI[MAXVERTICES][MAXVERTICES]; //matriz de adyacencia de impostores
};

//////////////////////////////////////////////////////////////// FUNCIONES

//HAY QUE MODIFICAR ESTA FUNCIÓN SI SE CAMBIA EL TIPO DE DATO tipovertice
/* 
 * Esta función devuelve 0 si los dos nodos son iguales
 * -1 si V1 es "menor" que V2 o 1 si es "mayor".
 */
int _comparar_vertices(tipovertice V1, tipovertice V2){
    int flag;
    
    flag = strcmp(V1.nombreHabitacion,V2.nombreHabitacion); 
    
    if (flag == 0) {
        return 0;
    } else {
        if (flag > 0) {
            return 1;
        } else {
            return -1;
        }
    }
}

//Creación del grafo con 0 nodos
void crear_grafo(grafo *G) {
    *G = (struct tipografo*) malloc(sizeof (struct tipografo));
    (*G)->N = 0;
}

//Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
//Si devuelve -1 es porque no encontró el vértice
int posicion(grafo G, tipovertice V) {
    int contador = 0;
    //comparo V con todos los vertices almacenados en VERTICES 
    while (contador < G->N) {
        //if (G->VERTICES[contador]==V)  //encontré la posicion de V
		if (_comparar_vertices(G->VERTICES[contador], V) == 0){
            return contador; 
        }
        contador++;
    }
    return -1;
}

//Devuelve 1 si el grafo G existe y 0 en caso contrario
int existe(grafo G) {
    return (G != NULL);
}

//Devuelve 1 si el vértice Vert existe en el grafo G
int existe_vertice(grafo G, tipovertice V) {
    return (posicion(G, V) >= 0);
}

//Inserta un vértice en el grafo, devuelve -1 si no ha podido insertarlo por estar el grafo lleno
//Sino devuelve la posicion del nuevo vertice
int insertar_vertice(grafo *G, tipovertice Vert) {
    int i;
    if ((*G)->N == MAXVERTICES) {
    	// Se ha llegado al maximo numero de vertices
    	return -1;
    }
   
    (*G)->N++;
    (*G)->VERTICES[((*G)->N) - 1] = Vert;
    for (i = 0; i < (*G)->N; i++) {
        (*G)->AT[i][((*G)->N) - 1] = 0;
        (*G)->AT[((*G)->N) - 1][i] = 0;
        (*G)->AI[i][((*G)->N) - 1] = 0;
        (*G)->AI[((*G)->N) - 1][i] = 0;
    }
	return (*G)->N-1;
}

//Borra un vertice del grafo
void borrar_vertice(grafo *G, tipovertice Vert) {
    int F, C, P, N = (*G)->N;
    P = posicion(*G, Vert);
    if(P == -1){
    	return;
    }
    //if (P >= 0 && P < (*G)->N) {
    for (F = P; F < N - 1; F++){
        (*G)->VERTICES[F] = (*G)->VERTICES[F + 1];
	}
    for (C = P; C < N - 1; C++){
        for (F = 0; F < N; F++){
            (*G)->AT[F][C] = (*G)->AT[F][C + 1];
            (*G)->AI[F][C] = (*G)->AI[F][C + 1];
        }
	}
    for (F = P; F < N - 1; F++){
        for (C = 0; C < N; C++){
            (*G)->AT[F][C] = (*G)->AT[F + 1][C];
            (*G)->AI[F][C] = (*G)->AI[F + 1][C];
        }
	}
    (*G)->N--;    
}

//Crea un arco de tripulantes entre VERTICES(pos1) y VERTICES(pos2) con el valor "valor"
//Si no hay ningun arco de impostores creado entre estos vertices el arco tambien se creará en la matriz de impostores
void crear_arco_T(grafo *G, int pos1, int pos2, int valor) {
    if (son_adyacentes_I(*G,pos1,pos2) == 0 || son_adyacentes_I(*G,pos1,pos2) == son_adyacentes_T(*G,pos1,pos2)) {
        (*G)->AI[pos1][pos2] = valor;
        (*G)->AI[pos2][pos1] = valor;
    }
    
    (*G)->AT[pos1][pos2] = valor;
    (*G)->AT[pos2][pos1] = valor;
       
}

//Crea un arco de impostores entre VERTICES(pos1) y VERTICES(pos2) con el valor "valor"
void crear_arco_I(grafo *G, int pos1, int pos2, int valor) {
    (*G)->AI[pos1][pos2] = valor;
    (*G)->AI[pos2][pos1] = valor;
}

//Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
//En caso de que el valor del arco de impostores y el arco de tripulantes sean iguales se borraran ambos
void borrar_arco_T(grafo *G, int pos1, int pos2) {
    if (son_adyacentes_I(*G,pos1,pos2) == son_adyacentes_T(*G,pos1,pos2)) {
        (*G)->AI[pos1][pos2] = 0;
        (*G)->AI[pos2][pos1] = 0;
    }
    (*G)->AT[pos1][pos2] = 0;
    (*G)->AT[pos2][pos1] = 0;
}
//Borra el arco de impostores entre VERTICES(pos1) y VERTICES(pos2)
//En caso de que el valor del arco de impostores y el arco de tripulantes sean iguales se borraran ambos
void borrar_arco_I(grafo *G, int pos1, int pos2) {
    if (son_adyacentes_I(*G,pos1,pos2) == son_adyacentes_T(*G,pos1,pos2)) {
        (*G)->AT[pos1][pos2] = 0;
        (*G)->AT[pos2][pos1] = 0;
    }
    (*G)->AI[pos1][pos2] = 0;
    (*G)->AI[pos2][pos1] = 0;
}

//Devuelve el valor del arco de tripulante si VERTICES(pos1) y VERTICES(pos2) son vértices adyacentes
int son_adyacentes_T(grafo G, int pos1, int pos2) {
    return (G->AT[pos1][pos2]);
}

//Devuelve el valor del arco de impostores si VERTICES(pos1) y VERTICES(pos2) son vértices adyacentes
int son_adyacentes_I(grafo G, int pos1, int pos2) {
    return (G->AI[pos1][pos2]);
}

//Destruye el grafo
void borrar_grafo(grafo *G) {
    free(*G);
    *G = NULL;
}

//Devuelve el número de vértices del grafo G
int num_vertices(grafo G) {
    return G->N;
}

//Devuelve el vector de vértices VERTICES del grafo G
tipovertice* array_vertices(grafo G) {
    return G->VERTICES;
}