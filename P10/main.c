
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

//Algoritmo de ramificacion y poda
int ramificacionPoda(int tareas[][tamanhoProblema], int solucion[], int mode);
//Comprueba si se rellenaron todos los niveles
int esSolucion(tipoelemPila nodo);
/*Calcula la solucion de un nodo mediante un algoritmo voraz ignorando el resto
 * de sus hijos
 */
int solVoraz(int tareas[][tamanhoProblema], int solucion[], int *nivel);
//Comprueba si se cumplen las restricciones de asignacion de tareas
int valoresCorrectos(tipoelemPila nodo);
/*Calculo de la cota superior de un nodo. (Hay que sumarle el valorActual del 
 * nodo padre para obtener el resultado)
 */
int cotaSuperior(int tareas[][tamanhoProblema], int solucion[], int nivel);
/*Calculo de la cota inferior de un nodo. (Hay que sumarle el valorActual del 
 * nodo padre para obtener el resultado)
 */
int cotaInferior(int tareas[][tamanhoProblema], int solucion[], int nivel);
/*
 Sumatorio de la eficiencia de las tareas asignadas a los trabajadores hasta el
 nivel n (n=nivel)
 */
int sumatorioActual(int tareas[][tamanhoProblema], int solucion[], int nivel);

int main(int argc, char** argv) {
    int tareas[tamanhoProblema][tamanhoProblema] = {11, 17, 8, 16, 20, 14, 9, 7, 6, 12, 15, 18, 13, 15, 16, 12, 16, 18, 21, 24, 28, 17, 26, 20, 10, 14, 12, 11, 15, 13, 12, 20, 19, 13, 22, 17};
    /*IMPORTANTE:   
     Para cambiar entre los dos vectores de tareas es necesario cambiar los
     dos defines tamanho que estan ubicados en el archivo pila.h y pila.c,
     si solo se cambia uno el programa crashea*/
    //int tareas[tamanhoProblema][tamanhoProblema] = {4, 9, 1, 7, 2, 3, 6, 3, 5};
    int solucion[tamanhoProblema];
    int resultado = 0;
    int opcion;

    do {
        printf("Pulsa 0 para realizar el algoritmo con estimaciones triviales en"
                " sus cotas o 1 para trabajar con estimaciones precisas\n");
        scanf(" %d", &opcion);

    } while (opcion != 1 && opcion != 0);
    
    printf("Nodos metidos en la pila: %d\n",ramificacionPoda(tareas, solucion, opcion));
    for (int i = 0; i < tamanhoProblema; i++) {
        resultado += tareas[i][solucion[i]];
    }

    printf("RESULTADO: %d\n", resultado);
}

//Algoritmo de ramificacion y poda

int ramificacionPoda(int tareas[][tamanhoProblema], int solucion[], int mode) {
    int nodosGenerados = 1;
    int nodosMetidosPila = 1;
    int maximoValor = 0; //Variable para calcular la CS en las estimaciones triviales
    pila aux; //Pila auxiliar donde guardar los nodos generados
    tipoelemPila nodo; //Variable aux tipoelemPila
    tipoelemPila nodoHijo; //Variable aux tipoelemPila
    float C; //Valor C que servirá para filtrar los nodos a examinar
    int valorMejorOpcion = 0; //Mejor valor obtenido

    crearPila(&aux);

    /*Iniciliazacion del array solucion + busqueda de la combinacion trabajador/
     * tarea mas eficiente
     */
    for (int i = 0; i < tamanhoProblema; i++) {
        solucion[i] = -1;
        for (int j = 0; j < tamanhoProblema; j++) {
            if (maximoValor < tareas[i][j])
                maximoValor = tareas[i][j];
        }
    }

    //Creación del nodo raíz
    if (mode == 0) {
        nodo = crearTipoelemPilaTrivial(tareas, solucion, maximoValor);
    } else {
        nodo = crearTipoelemPilaNoTrivial(tareas, solucion, cotaSuperior(tareas,
                solucion, -1), cotaInferior(tareas, solucion, -1));
    }
    C = nodo.CI;
    //Insercción del nodo en la pila
    push(&aux, nodo);

    //Se examinan todos los nodos hasta que la pila este vacia
    while (!esVaciaPila(aux)) {
        nodo = tope(aux);
        pop(&aux);
        //Filtrado de los nodos
        if (nodo.CS > C) {
            //Generacion de los hijos del último nodo sacado de la pila
            for (int i = 0; i < tamanhoProblema; i++) {
                nodo.solucion[nodo.nivel + 1] = i;
                //Creacion del nodo hijo
                if (mode == 0) {
                    nodoHijo = crearTipoelemPilaTrivial(tareas, nodo.solucion,
                            maximoValor);
                } else {
                    nodoHijo = crearTipoelemPilaNoTrivial(tareas, nodo.solucion,
                            sumatorioActual(tareas,nodo.solucion,nodo.nivel+1)
                            + cotaSuperior(tareas, nodo.solucion,
                            nodo.nivel+1),
                            sumatorioActual(tareas,nodo.solucion,nodo.nivel+1)
                            + cotaInferior(tareas, nodo.solucion, nodo.nivel+1));
                }
                /*Comprobación de que las asignaciones de tareas cumplen las 
                 * restricciones, en caso contrario no se sigue trabajando con ese
                 * nodo
                 */
                if (valoresCorrectos(nodoHijo)) {
                    /*En caso de que CS == CI se sabe que el mejor hijo del nodo
                     * se puede obtener mediante un algoritmo voraz por lo que 
                     * no tiene sentido meter este nodo en la pila y generar
                     * sus hijos, por lo que se genera solamente un hijo a partir
                     * de un algoritmo voraz 
                     */
                    nodosGenerados++;
                    if (mode == 1 && nodoHijo.CS == nodoHijo.CI) {
                        nodoHijo.valorActual = solVoraz(tareas,nodoHijo.solucion,
                                &(nodoHijo.nivel));
                        nodosGenerados++;
                    }   
                    /*Comprobacion de si el nodo actual es solucion y si es
                     * mas eficiente que la solucion actual, en caso de que lo
                     * se guarda la nueva solucion
                     */
                    if (esSolucion(nodoHijo) && nodoHijo.valorActual >
                            valorMejorOpcion) {
                        valorMejorOpcion = nodoHijo.valorActual;
                        for (int i = 0; i < tamanhoProblema; i++) {
                            solucion[i] = nodoHijo.solucion[i];
                        }
                        //Optimizacion de C
                        if (nodoHijo.valorActual > C) {
                            C = nodoHijo.valorActual;
                        }
                    } else {
                        //Guardado de los nodos que no son solucion en la pila
                        if (!esSolucion(nodoHijo) && nodoHijo.CS > C) {
                            push(&aux, nodoHijo);
                            nodosMetidosPila++;
                            //Optimizacion de C
                            if (nodoHijo.CI > C) {
                                C = nodoHijo.CI;
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("Nodos generados: %d\n",nodosGenerados);
    return nodosMetidosPila;
}

//Comprueba si se rellenaron todos los niveles

int esSolucion(tipoelemPila nodo) {
    return nodo.nivel == tamanhoProblema - 1;
}

//Comprueba si se cumplen las restricciones de asignacion de tareas

int valoresCorrectos(tipoelemPila nodo) {
    int toReturn = 1;

    for (int i = 0; i < nodo.nivel; i++) {
        if (nodo.solucion[i] == nodo.solucion[nodo.nivel]) {
            toReturn = 0;
        }
    }

    return toReturn;
}

/*Calculo de la cota superior de un nodo. (Hay que sumarle el valorActual del 
 * nodo padre para obtener el resultado)
 */
int cotaSuperior(int tareas[][tamanhoProblema], int solucion[], int nivel) {
    int toReturn = 0;
    int columnaOcupada = 0;
    int maximoValorFila = 0;

    for (int i = nivel + 1; i < tamanhoProblema; i++) {
        for (int j = 0; j < tamanhoProblema; j++) {
            columnaOcupada = 0;
            for (int k = 0; k <= nivel; k++) {
                if (j == solucion[k])
                    columnaOcupada = 1;
            }
            if (columnaOcupada == 0 && maximoValorFila < tareas[i][j])
                maximoValorFila = tareas[i][j];
        }
        toReturn += maximoValorFila;
        maximoValorFila = 0;
    }
    return toReturn;
}

/*Calculo de la cota inferior de un nodo. (Hay que sumarle el valorActual del 
 * nodo padre para obtener el resultado)
 */
int cotaInferior(int tareas[][tamanhoProblema], int solucion[], int nivel) {
    int toReturn = 0;
    int columnaOcupada = 0;
    int maximoValorFila = 0;
    int columnasUsadas[tamanhoProblema];

    for (int i = 0; i < tamanhoProblema; i++) {
        columnasUsadas[i] = solucion[i];
    }

    for (int i = nivel + 1; i < tamanhoProblema; i++) {
        for (int j = 0; j < tamanhoProblema; j++) {
            columnaOcupada = 0;
            for (int k = 0; k <= i; k++) {
                if (j == columnasUsadas[k]) {
                    columnaOcupada = 1;
                }
            }
            if (columnaOcupada == 0 && maximoValorFila < tareas[i][j]) {
                maximoValorFila = tareas[i][j];
                columnasUsadas[i] = j;
            }
        }
        toReturn += maximoValorFila;
        maximoValorFila = 0;
    }

    return toReturn;
}

/*Calcula la solucion de un nodo mediante un algoritmo voraz ignorando el resto
 * de sus hijos
 */
int solVoraz(int tareas[][tamanhoProblema], int solucion[], int *nivel) {
    int columnaOcupada = 0;
    int maximoValorFila = 0;

    for (int i = *nivel + 1; i < tamanhoProblema; i++) {
        for (int j = 0; j < tamanhoProblema; j++) {
            columnaOcupada = 0;
            for (int k = 0; k <= i; k++) {
                if (j == solucion[k]) {
                    columnaOcupada = 1;
                }
            }
            if (columnaOcupada == 0 && maximoValorFila < tareas[i][j]) {
                maximoValorFila = tareas[i][j];
                solucion[i] = j;
            }
        }
        maximoValorFila = 0;
    }

    *nivel = tamanhoProblema - 1;
    return sumatorioActual(tareas,solucion,*nivel);
}

/*
 Sumatorio de la eficiencia de las tareas asignadas a los trabajadores hasta el
 nivel n (n=nivel)
 */
int sumatorioActual(int tareas[][tamanhoProblema], int solucion[], int nivel) {
    int toReturn = 0;
    
    for (int i = 0; i <= nivel; i++) {
        toReturn += tareas[i][solucion[i]];
    }
    
    return toReturn;
}
