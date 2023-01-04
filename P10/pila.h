#ifndef PILA_H
#define PILA_H

//Numero de trabajadores y de tareas a resolver
#define tamanhoProblema 6

//Interfaz TAD pila
typedef void *pila; /*tipo opaco*/

//Struct que representa un nodo del arbol

typedef struct tipoelemPila {
    int solucion[tamanhoProblema];
    int nivel;
    int valorActual;
    float CI;
    float BE;
    float CS;
} tipoelemPila;


//Creacion de un nodo con estimaciones triviales
tipoelemPila crearTipoelemPilaTrivial(int tareas[][tamanhoProblema], int solucion[], int maximoValor);

//Creacion de un nodo con estimaciones precisas
tipoelemPila crearTipoelemPilaNoTrivial(int tareas[][tamanhoProblema], int solucion[], int cotaSuperior, int cotaInferior);

/**
 * Crea la pila vacia. 
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPila(pila *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPila(pila *P);

//Funciones de informacion
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPila(pila P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 * 
 */
tipoelemPila tope(pila P);

//Funciones de insercion/eliminacion
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * segun la prioridad de E
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo. 
 */
void push(pila *P, tipoelemPila E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void pop(pila *P);

#endif // PILA_H

