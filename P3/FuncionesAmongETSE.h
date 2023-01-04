
#ifndef FUNCIONESAMONGETSE_H
#define FUNCIONESAMONGETSE_H

#include "abb.h"

/**
 * lee un archivo de jugadores de un fichero
 * @param A
 */
void leerArchivo(abb *A);

/**
 * lee un archivo de jugadores de un fichero
 * @param A
 */
void altaJugador(abb *A); 
/*Permite dar de alta a un jugador en el arbol de usuarios
 para luego poder meterlo en el arbol de jugadores
 */

void bajaJugador(abb *A);

/*Permite dar de baja un usuario del arbol de usuarios
 */
void menu(abb *Arbol);
/*
 Función que ejecuta un menú de varias opciones en bucle hasta que el usuario 
 pida salir por teclado*/

void listadoJugadores(abb A);
/*
 Imprime el nombre de todos los nodos del arbol haciendo un recorrido inorden
 */

/**
 * Genera una nueva partida, asignando valores a cada jugador
 * @param A
 */
void generarPartida(abb *A,abb *Jugadores);

/**
 * Genera una nueva partida, asignando valores a cada jugador
 * @param A
 */
void consultarJugador(abb A);
/*
 Funcion que pide el nombre de un usuario y si este está en el abb A y 
 tiene alguna tarea asignada se impimiran todos sus datos excepto su rol
 */

void asignarImpostores(abb Arbol, abb Jugadores, int numJugadores);
/*
 * Calcula el numero de impostores que tienen que haber en la partida a partir
 * del numero de jugadores y llama a la funcioon postOrdenImpostores(..) hasta
 * que esta asigne el numero de jugadores como impostores
 */

void asignarTripulantes(abb Arbol, abb Jugadores);
/*Sirve para asignar el rol tripulante a todos los jugadores que no tengan rol 
 * luego de haber pasado por  la funcion asignarImpostores
*/
void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer); 
/*Coge el primer nodo del arbol Jugadores que se le manda y le asigna
 * una tarea y una habitacion aleatoriamente luego cambia ese nodo por el que 
 * estaba en el arbol Jugadores y Arbol
 */


void asignarTareasHabitaciones(abb Arbol, abb Jugadores);
/*Recorre todo el arbol de jugadores y manda cada nodo a la funcion 
 * asignarTareaUsuario(....) para asignarle a cada usuario una tarea y un lugar 
 donde desarrollarla aleatoriamente*/

void postOrdenImpostores(abb A, abb Jugadores, int numImpostores, int *impostoresReales);
/*
 A partir del numero de jugadores asigna uno o dos impostores aleatoriamente
 */

void seleccionManual (abb Arbol, int numJugadores, abb *Jugadores);
/*Te permite introducir en partida uno o varios usuarios registrados anteriormente
 los usuarios que no introduzcas manualmente los introducira la funcion*/


void consultarPorHabitacion(abb A);
/*Permite seleccionar una de las habitaciones del juego y luego la funcion se la
 * pasa a la funcion imprimirDatosHabitacion(..) */

void imprimirDatosHabitacion (abb Arbol, char habitacion[]);
/*Imprime todos los datos de los jugadores que tengan una tarea asignada en esa 
 habitacion excepto el rol*/

int redondeo (double valor);
/*Funcion que redondea un double al entero mas cercano*/



#endif	// FUNCIONESAMONGETSE_H

