/* Practica 1: Prueba de manejo de Arboles Binarios  */
#include <stdlib.h>
#include <stdio.h>

#include "abin.h"
#include "recorridos.h"
#include "funcionesArboles.h"

int main(int argc, char** argv) {
    
    abin arbol, aux;//Variables necesarias para realizar el programa
    tipoelem p;
    crear(&arbol); //Creación del arbol
    
    //Asignacion de nodos para construir el arbol que pide el ejercicio
    insizq(&arbol,'R');
    insizq(&arbol,'P');
    insder(&arbol,'T');
    aux = izq(arbol);
    insizq(&aux,'M');
    insder(&aux,'Q');
    aux = izq(aux);
    insizq(&aux,'A');
    insder(&aux,'O');
    aux = der(arbol);
    insizq(&aux,'S');
    insder(&aux,'V');
    aux = der(aux);
    insizq(&aux,'U');
    
    printf("Altura del arbol: %d\n",AlturaArbol(arbol)); //Altura
    printf("Recorrido del arbol por anchura: "); anchura(arbol);//Recorrido en anchura
    printf("\n");
    
    /* Busqueda del nodo P manual
    aux = izq(arbol);
    */
    
    buscar(arbol,'P',&aux); //Busqued con la función
    printf("Selecciona el nodo al que le quieres eliminar el subarbol izquierdo: ");
    scanf("%c",&p);
    supizq(&aux);
   
    
   
    printf("\nRecorrido del arbol resultante en preorden: "); preorden(arbol);
    printf("\nAltura del arbol resultante: %d\n",AlturaArbol(arbol)); //Altura
    printf("Numero de nodos del arbol resultante: %d\n",NumeroNodos(arbol));
    


    return (EXIT_SUCCESS);
}
