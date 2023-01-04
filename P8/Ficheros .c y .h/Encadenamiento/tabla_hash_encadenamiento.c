#include "tabla_hash_encadenamiento.h"

/* TABLA HASH CON ENCADENAMIENTO */
//Devuelve el numero de colisiones totales que se produjeron en la tabla t
int getColisionesProducidas(TablaHash t) {
    for (int i = 1; i < Tam; i++) {
        t[0].colisionesHueco += t[i].colisionesHueco;
    }
    return t[0].colisionesHueco;
}
//Devuelve el numero de pasos adicionales en insercciones que se produjeron en la tabla t
int getPasosAdicionalesInserccion(TablaHash t) {
    for (int i = 1; i < Tam; i++) {
        t[0].pasosAdicionalesInserccionHueco += t[i].pasosAdicionalesInserccionHueco;
    }
    return t[0].pasosAdicionalesInserccionHueco;
}

//Devuelve el numero de pasos adicionales en busquedas que se produjeron en la tabla t
int getPasosAdicionalesBusqueda(TablaHash t) {
    for (int i = 1; i < Tam; i++) {
        t[0].pasosAdicionalesInserccionHueco += t[i].pasosAdicionalesInserccionHueco;
    }
    return t[0].pasosAdicionalesInserccionHueco;
}
/* CREAR TABLA VACIA */
void InicializarTablaHash (TablaHash t) {
   int i;
   for (i=0;i<Tam;i++){
      crea(&t[i].jugadores);
      t[i].colisionesHueco = 0;
      t[i].pasosAdicionalesBusquedaHueco = 0;
      t[i].pasosAdicionalesInserccionHueco = 0;
   }
      
}

/* DESTRUIR TABLA */
void DestruirTablaHash (TablaHash t){
   int i;
   for (i=0;i<Tam;i++)
      destruye(&t[i].jugadores);
}

/******* FUNCIONES HASH *******/

/* FUNCION HASH 1 */

/*
int Hash(char *cad) {
    int valor;
    unsigned char *c;

    for (c = cad, valor = 0; *c; c++)
        valor += (int) *c;

    return (valor % Tam);
}
*/


/* FUNCION HASH 2 */

  int Hash (char *cad){
     int i,suma=0;
     for (i=strlen(cad)-1;i>=0;i--){
         suma=(suma*256+cad[i])%Tam;
     }
     return suma;
 }
 
/* FUNCION HASH 3: Probad al menos dos valores para la constante K */
/*
  int Hash (char *cad){
     int i,suma=0;
     int K=500;
     for (i=strlen(cad)-1;i>=0;i--){
         suma=(suma*K+cad[i])%Tam;
     }
     return suma;
  }
*/
 

/* BUSCA UN ELEMENTO CON LA CLAVE INDICADA EN LA TABLA HASH, Y LO DEVUELVE, 
 * ADEMAS DE INDICAR CON 1 QUE EXISTE EL ELEMENTO, Y CON 0 QUE NO ESTA EN LA TABLA */
int Busqueda(TablaHash t, char *clavebuscar, tipoelem *e)
{
   posicion p;
   int enc;
   tipoelem ele;
   int pos=Hash(clavebuscar);
   
   p=primero(t[pos].jugadores);
   enc=0;
  
   while (p!=fin(t[pos].jugadores) && !enc) {
       recupera(t[pos].jugadores,p,&ele);
      if (strcmp(ele.clave,clavebuscar)==0){
         enc=1;
         *e=ele;
      }
      else
         p=siguiente(t[pos].jugadores,p);
   }

   return enc;
}

/* DEVUELVE 1 SI EL ELEMENTO e ESTA EN LA TABLA Y 0 SI NO LO ESTA */
int MiembroHash (TablaHash t, char *clavebuscar){
   posicion p;
   int enc;
   tipoelem elemento;
   int pos=Hash(clavebuscar);
   p=primero(t[pos].jugadores);
   enc=0;
   while (p!=fin(t[pos].jugadores) && !enc) {
      recupera(t[pos].jugadores,p,&elemento);
      if (strcmp(clavebuscar,elemento.clave)==0)
         enc=1;
      else
         p=siguiente(t[pos].jugadores,p);
   }

   return enc;
}

/* INSERTA UN ELEMENTO EN LA TABLA HASH: AL PRINCIPIO DE LA LISTA EN LA 
 * POSICION INDICADA POR LA FUNCION HASH */
void InsertarHash (TablaHash *t, tipoelem elemento){
   int pos;
  
   pos=Hash(elemento.clave);
   int longi = longitud((*t)[pos].jugadores);
   if (longi != 0) {
       (*t)[pos].colisionesHueco++;
   }
   (*t)[pos].pasosAdicionalesInserccionHueco += longi;
   
   
   inserta(&(*t)[pos].jugadores,primero((*t)[pos].jugadores),elemento);
}

/* Elimina de la tabla el elemento con la clave indicada */
void BorrarHash (TablaHash *t, char *claveborrar){
   posicion p;
   tipoelem elemento;
   int pos=Hash(claveborrar);

   p=primero((*t)[pos].jugadores);
   recupera((*t)[pos].jugadores,p,&elemento);
   while (p!=fin((*t)[pos].jugadores) && strcmp(claveborrar,elemento.clave))
   {
      p=siguiente((*t)[pos].jugadores,p);
      recupera((*t)[pos].jugadores,p,&elemento);
   }
   if (p!=fin((*t)[pos].jugadores))
      suprime(&(*t)[pos].jugadores,p);
}

//Lee todos los datos de un archivo y los mete en la tabla t
void leerArchivo (TablaHash *t) {
    FILE *fp;
    
    fp = fopen("jugadores_amongETSE.txt","r");
    if (fp == NULL){
        printf("Archivo no encontrado.\n");
        exit(1);
    }
    int endPoint = 0;
    tipoelem newPlayer;
    
    do {
        endPoint = fscanf(fp,"%s %s %s - %s - %s",newPlayer.nombre,newPlayer.apellido1,newPlayer.apellido2,newPlayer.clave,newPlayer.correo);
        InsertarHash(t,newPlayer);
    }while(endPoint != EOF); 
}

//Lee todos los datos de un archivo y los busca en la tabla t
void buscarArchivo (TablaHash t) {
    FILE *fp;
    
    fp = fopen("jugadores_amongETSE.txt","r");
    if (fp == NULL){
        printf("Archivo no encontrado.\n");
        exit(1);
    }
    int endPoint = 0;
    tipoelem newPlayer;
    
    do {
        endPoint = fscanf(fp,"%s %s %s - %s - %s",newPlayer.nombre,newPlayer.apellido1,newPlayer.apellido2,newPlayer.clave,newPlayer.correo);
        Busqueda(t,newPlayer.clave,&newPlayer);
    }while(endPoint != EOF); 
}
