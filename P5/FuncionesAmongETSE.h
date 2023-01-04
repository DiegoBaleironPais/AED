
#ifndef FUNCIONESAMONGETSE_H
#define FUNCIONESAMONGETSE_H

#include "abb.h"

/*Toma como parametro un double y devuelve el entero más cercano a ese double
 * (tuve que hacer esta función ya que tenía problemas con la librería math)
 */
int redondeo (double valor);

/*Toma como parametro el arbol de usuarios vacio y inicializa en el todos los
 *  elementos de un archivo*/
void leerArchivo(abb *A);

/*
 Toma como parámetro el arbol de usuarios y permite elegir entre varias funciones
 distintas para realizar acciones concretas*/
void menu(abb *Arbol);

/*Permite dar de alta en el arbol de usuarios un nuevo jugador*/
void altaJugador(abb *Arbol);

/*Permite dar de baja en el arbol de usuarios un usuario*/
void bajaJugador(abb *Arbol); 

/*
 Lista todos los usuarios del arbol de usuarios junto con su rol
 */
void listadoJugadores(abb Arbol);

/*
 * Realiza un recorrido inorden del arbol de jugadores y imprime el nombre de 
 * todos los jugadores
 */
void listadoJugadoresNombre(abb Arbol);

/*
 * Borra los datos del arbol de Jugadores, limpia los datos del arbol de usuarios
 * y lleva a cabo las acciones necesarias para jugar una partida.
 */
void generarPartida(abb *Arbol, abb *Jugadores);

/*
 * Permite elegir entre introducir manualmente los usuarios al arbol de jugadores
 * o hacerlo de forma automatica
 */
void seleccionManual (abb Arbol, int numJugadores, abb *Jugadores);

/*
 * Dependiendo del numero de jugadores calcula el numero de impostores que tiene
 * que haber en la partida y llama a otra funcion para que esta le asigne el rol 
 * a los jugadores
 */
void asignarImpostores(abb Arbol, abb Jugadores, int numJugadores);

/*
 *Asigna el rol de impostor a los usuarios de forma aleatoria
 */

void postOrdenImpostores(abb Arbol, abb Jugadores, int numImpostores, int *impostoresReales);

/*
 * Asigna el rol de tripulante a todo el que no sea impostor
 */
void asignarTripulantes(abb Arbol, abb Jugadores);

/*
 * Recorre el arbol de usuarios y llama a la funcion asignarTareaUsuario para que le
 * asigne las tareas a todos los jugadores
 */
void asignarTareasHabitaciones(abb Arbol, abb Jugadores, int numTareas);

/*
 * Asigna de forma aleatoria al usuario que se le pasa como parametro n
 * tareas con n = numTareas
 */

void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer, int numTareas);

/*
 * A partir del nombre de usuario imprime los datos de un usuario
 */
void consultarJugador(abb Arbol);

/*
 * Permite seleccionar una de las habitaciones del juego y se la pasa a 
 * imprimirDatosHabitacion()
 */
void consultarPorHabitacion(abb Arbol);

/*
 * A partir de una habitación dada imprime datos de los usuarios que están en ella
 */
void imprimirDatosHabitacion ( abb Arbol, char habitacion[] );

/*
 * Permite guardar los nombres de los usuarios en un fichero auxiliar
 */
void guardarUsuarios ( abb Arbol );
//LAS FUNCIONES PRIVADAS ESTAN COMENTADAS EN EL FICHERO .C
#endif	// FUNCIONESAMONGETSE_H

