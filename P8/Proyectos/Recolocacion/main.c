/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: diego
 *
 * Created on 25 de Novembro de 2020, 10:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tabla_hash_recolocacion.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    clock_t inicio, fin;
    double tiempoconsumido;
    TablaHash t;
    InicializarTablaHash(t);
    leerArchivo(t);
    inicio = clock();
    buscarArchivo (t);
    fin = clock();
    tiempoconsumido = ((double)(fin-inicio))/CLOCKS_PER_SEC;
    printf("contador colisiones: \n");
    printf("%d colisiones\n",getColisionesProducidas(t));
    printf("%d operaciones adicionales de insercción\n",getPasosAdicionalesInserccion(t));
    printf("%d operaciones adicionales de busqueda en %lf ms\n",getPasosAdicionalesBusqueda(t),tiempoconsumido);
    return (EXIT_SUCCESS);
}

