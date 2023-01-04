#ifndef FUNCIONESEXPRESION_H
#define FUNCIONESEXPRESION_H
#include <stdio.h>
#include <stdlib.h>
#include "pilaOperadores.h"
#include "pilaOperandos.h"
#include "abin.h"

//Funciones para construccion del arbol de expresion

//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op);

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op);

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c);

//Devuelve 1 si c es un operando: 
//numeros de 1 cifra y letras mayusculas y minusculas
unsigned esOperando(char c); //COMPLETARLA

//Recibe una cadena de caracteres y devuelve el arbol de expresion
abin arbolExpresion(char expr_infija[]); //ESCRIBIR ESTA FUNCION

void introducirPilaOperandos(char aux, pilaOperandos *piladOperandos );

void segundoIf ( char aux, pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

void tercerIf ( pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

abin vaciarPilaOperadores ( pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

void desapilarOperandos(char *caux, abin *arbol, pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

#endif	// FUNCIONESEXPRESION_H