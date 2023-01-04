
#ifndef FUNCIONESAMONGETSE_H
#define FUNCIONESAMONGETSE_H

#include "abb.h"

int redondeo (double valor);

void leerArchivo(abb *A);

void menu(abb *Arbol);

void altaJugador(abb *Arbol);

void bajaJugador(abb *Arbol); 

void listadoJugadores(abb Arbol);

void listadoJugadoresNombre(abb Arbol);

void generarPartida(abb *Arbol, abb *Jugadores);

void seleccionManual (abb Arbol, int numJugadores, abb *Jugadores);

void asignarImpostores(abb Arbol, abb Jugadores, int numJugadores);

void postOrdenImpostores(abb Arbol, abb Jugadores, int numImpostores, int *impostoresReales);

void asignarTripulantes(abb Arbol, abb Jugadores);

void asignarTareasHabitaciones(abb Arbol, abb Jugadores);

void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer);

void consultarJugador(abb Arbol);

void consultarPorHabitacion(abb Arbol);

void imprimirDatosHabitacion ( abb Arbol, char habitacion[] );

#endif	// FUNCIONESAMONGETSE_H

