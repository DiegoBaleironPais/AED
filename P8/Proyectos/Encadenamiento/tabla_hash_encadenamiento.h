/* 
 * Tabla hash con encadenamiento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define Tam 53437 /*DEFINIR NUMERO de entradas en la tabla.*/

typedef struct{
    lista jugadores;
    int colisionesHueco;
    int pasosAdicionalesBusquedaHueco;
    int pasosAdicionalesInserccionHueco;
}TablaHash[Tam];

void InicializarTablaHash (TablaHash t);
void DestruirTablaHash (TablaHash t);
int Hash (char *cad);
int Busqueda(TablaHash t, char *clavebuscar, tipoelem *e);
int MiembroHash (TablaHash t, char *clavebuscar);
void InsertarHash (TablaHash *t, tipoelem elemento);
void BorrarHash (TablaHash *t, char *claveborrar);
//Lee todos los datos de un archivo y los mete en la tabla t
void leerArchivo (TablaHash *t);
//Devuelve el numero de colisiones totales que se produjeron en la tabla t
int getColisionesProducidas(TablaHash t);
//Devuelve el numero de pasos adicionales en insercciones que se produjeron en la tabla t
int getPasosAdicionalesInserccion(TablaHash t);
//Devuelve el numero de pasos adicionales en busquedas que se produjeron en la tabla t
int getPasosAdicionalesBusqueda(TablaHash t);
//Lee todos los datos de un archivo y los busca en la tabla t
void buscarArchivo (TablaHash t);

