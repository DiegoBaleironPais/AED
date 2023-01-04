/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: diego
 *
 * Created on 7 de Outubro de 2020, 10:20
 */

#include <stdio.h>
#include <stdlib.h>
#include "abin.h"
#include "FuncionesExpresion.h"
#include "recorridos.h"



/*
 * 
 */

int main(int argc, char** argv) {

    char expresion[25];
    abin arbol;
    crear(&arbol);
    
    printf("Introduce la expresión: "); scanf("%s",expresion); printf("\n");
    arbol = arbolExpresion(expresion);
    printf("Expresión en inorden: "); inorden(arbol); printf("\n");
    printf("Expresión en preorden: "); preorden(arbol); printf("\n");
    printf("Expresión en postorden: "); postorden(arbol); printf("\n");

}


