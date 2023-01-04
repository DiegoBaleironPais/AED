/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: diego
 *
 * Created on 9 de Decembro de 2020, 10:05
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 
 */

//#define tamanhoProblema 3
#define tamanhoProblema 6

//Funciones para el algoritmo de backtracking 
void backtracking(int n, int tareas[][n], int solucion[n], int mode);
void generarTarea(int *nivel, int n, int solucion[n], int tareas[][n], int *bact, int usada[], int mode, int *contador);
int criterio(int nivel, int solucion[], int usada[], int mode, int *contador);
int Solucion(int nivel, int solucion[], int n, int usada[], int mode, int *contador, int *contadorCriterio);
int masHermanos(int nivel, int n, int solucion[], int *contador);
void retroceder(int n, int *nivel, int solucion[], int tareas[][n], int *bact, int usada[], int mode, int *contador);

/*Este main resuelve el ejercicio para el primer ejemplo, en caso de que quieras resolverlo para el segundo
  hay que comentar este trozo de codigo junto con la variable global tamnhoProblema 3 y descomentar el otro main junto con 
  la variable tamanhoProblema 6*/
/*
int main(int argc, char** argv) {
    int tareas[tamanhoProblema][tamanhoProblema] = {4, 9, 1, 7, 2, 3, 6, 3, 5};
    int solucion[tamanhoProblema];
    char seleccion;

    do {
        printf("Pulsa 1 para ejecutar el algoritmo de backtracking estadar o 2 para"
                " ejecutar el algoritmo optimizado\n");
        scanf(" %c", &seleccion);
    } while (seleccion != '1' && seleccion != '2');
    if (seleccion == '1') {
        backtracking(tamanhoProblema, tareas, solucion, 0);
    } else {
        backtracking(tamanhoProblema, tareas, solucion, 1);
    }
    printf("La mejor solucion es:\n");
    for (int i = 0; i < tamanhoProblema; i++) {
        printf("%d\n", tareas[i][solucion[i]]);
    }

    return (EXIT_SUCCESS);
}
*/

/*Este main resuelve el ejercicio para el segundo ejemplo, en caso de que quieras resolverlo para el primero
  hay que comentar este trozo de codigo junto con la variable global tamnhoProblema 6 y descomentar el otro main junto con 
  la variable tamanhoProblema 3
 */
int main(int argc, char** argv) {
    int tareas[tamanhoProblema][tamanhoProblema] = {11,17,8,16,20,14,9,7,6,12,15,18,13,15,16,12,16,18,21,24,28,17,26,20,10,14,12,11,15,13,12,20,19,13,22,17};
    int solucion[tamanhoProblema];
    char seleccion;

    do {
        printf("Pulsa 1 para ejecutar el algoritmo de backtracking estadar o 2 para"
            " ejecutar el algoritmo optimizado\n");
        scanf(" %c",&seleccion);
    } while (seleccion != '1' && seleccion != '2');
    
    if (seleccion == '1') {
        backtracking(tamanhoProblema, tareas, solucion, 0);
    } else {
        backtracking(tamanhoProblema, tareas, solucion, 1);
    }
    
    printf("La mejor solucion es:\n");
    
    for (int i = 0; i < tamanhoProblema; i++) {
        printf("%d\n",tareas[i][solucion[i]]);
    }
    
    return (EXIT_SUCCESS);
}
 

void backtracking(int n, int tareas[][n], int solucion[n], int mode) {
    int nivel = 0;
    int voa = 0;
    int soa[n];
    int bact = 0;
    int usada[n];
    int nodosValidos = 0;
    int contadorGenerarTarea = 0;
    int contadorSolucion = 0;
    int contadorCriterio = 0;
    int contadorMasHermanos = 0;
    int contadorRetroceder = 0;

    for (int i = 0; i < n; i++) {
        solucion[i] = -1;
        if (mode == 1) {
            usada[i] = 0;
        }
    }

    do {
        generarTarea(&nivel, n, solucion, tareas, &bact, usada, mode, &contadorGenerarTarea);
        
        if (Solucion(nivel, solucion, n, usada, mode, &contadorSolucion, &contadorCriterio) && bact > voa) {
            nodosValidos++;
            voa = bact;
            for (int i = 0; i < n; i++) {
                soa[i] = solucion[i];
            }
        } else {
            if (Solucion(nivel, solucion, n, usada, mode, &contadorSolucion, &contadorCriterio)) {
                nodosValidos++;
            }
        }
        if (criterio(nivel, solucion, usada, mode, &contadorCriterio) && nivel < n - 1) {
            nodosValidos++;
            nivel++;
        }
        while (!masHermanos(nivel, n, solucion, &contadorMasHermanos) && nivel >= 0) {
            retroceder(n, &nivel, solucion, tareas, &bact, usada, mode, &contadorRetroceder);
        }
    } while (nivel != -1);

    for (int i = 0; i < n; i++) {
        solucion[i] = soa[i];
    }
    printf("Nodos válidos generados %d\n", nodosValidos);
    printf("La función generar() se ejecuto %d veces\n",contadorGenerarTarea);
    printf("La función solucion() se ejecuto %d veces\n",contadorSolucion);
    printf("La función criterio() se ejecuto %d veces\n",contadorCriterio);
    printf("La función masHermanos() se ejecuto %d veces\n",contadorMasHermanos);
    printf("La función retroceder() se ejecuto %d veces\n",contadorRetroceder);
    
}

void generarTarea(int *nivel, int n, int solucion[n], int tareas[][n], int *bact, int usada[], int mode, int *contador) {
    *contador = *contador + 1;
    if (mode == 1) {
        if (solucion[*nivel] != -1) {
            usada[solucion[*nivel]]--;
        }
    }
    solucion[*nivel] = solucion[*nivel] + 1;
    if (mode == 1) {
        usada[solucion[*nivel]]++;
    }
    if (solucion[*nivel] == 0) {
        *bact = *bact + tareas[*nivel][solucion[*nivel]];
    } else {
        *bact = *bact + tareas[*nivel][solucion[*nivel]] - tareas[*nivel][solucion[*nivel] - 1];
    }
}

int criterio(int nivel, int solucion[], int usada[], int mode, int *contador) {
    *contador = *contador + 1;
    if (mode == 0) {
        for (int i = 0; i < nivel; i++) {
            if (solucion[nivel] == solucion[i]) return 0;
        }
        return 1;
    }
    return usada[solucion[nivel]] == 1;
}

int Solucion(int nivel, int solucion[], int n, int usada[], int mode, int *contador, int *contadorCriterio) {
    *contador = *contador + 1;
    *contadorCriterio = *contadorCriterio + 1;
    /*El contador de criterio debería haber pasado a la función criterio y que 
     esta lo incremente, sin embargo me daba problemas por lo que obte por incre
     mentar aquí ambos contadores y pasarle a la función criterio un puntero a 
     mode ya que como esta función lo recibe por valor no importa lo que haga
     la función criterio con el*/
    return (nivel == n - 1 && criterio(nivel, solucion, usada, mode, &mode));
}

int masHermanos(int nivel, int n, int solucion[], int *contador) {
    *contador = *contador + 1;
    return solucion[nivel] < n - 1;
}

void retroceder(int n, int *nivel, int solucion[], int tareas[][n], int *bact, int usada[], int mode, int *contador) {
    *contador = *contador + 1;
    *bact = *bact - tareas[*nivel][solucion[*nivel]];
    if (mode == 1) {
        usada[solucion[*nivel]]--;
    }
    solucion[*nivel] = -1;
    *nivel = *nivel - 1;
}
