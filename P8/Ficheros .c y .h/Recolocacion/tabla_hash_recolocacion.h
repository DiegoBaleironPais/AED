/* 
 * File:   tablas_hash_recolocacion.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Tam 15111
/*DEFINIR NUMERO de entradas en la tabla.*/
#define VACIO '\0'
#define BORRADO ' '

typedef struct{
    char nombre[15];
    char apellido1[15];
    char apellido2[15];
    char clave[20];
    char correo[60];
}tipo_jugador;

typedef struct{
    tipo_jugador jugador;
    int colisionesHueco;
    int pasosAdicionalesBusquedaHueco;
    int pasosAdicionalesInserccionHueco;
}TablaHash[Tam];

void InicializarTablaHash(TablaHash t);
int Hash(char *cad);
int PosicionBuscar(TablaHash t, char *cad);
int PosicionInsertar(TablaHash t, char *cad);
int MiembroHash(TablaHash t, char *cad) ;
int Busqueda(TablaHash t, char *cad, tipo_jugador *e);
void InsertarHash(TablaHash t, tipo_jugador e);
void BorrarHash(TablaHash t, char *cad);
//Lee todos los datos de un archivo y los mete en la tabla t
void leerArchivo (TablaHash t);
//Lee todos los datos de un archivo y los busca en la tabla t
void buscarArchivo (TablaHash t);
//Devuelve el numero de colisiones totales que se produjeron en la tabla t
int getColisionesProducidas();
//Devuelve el numero de pasos adicionales en insercciones que se produjeron en la tabla t
int getPasosAdicionalesInserccion();
//Devuelve el numero de pasos adicionales en busquedas que se produjeron en la tabla 
int getPasosAdicionalesBusqueda();