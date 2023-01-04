#include "tabla_hash_recolocacion.h"

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

//Devuelve el numero de pasos adicionales en busquedas que se produjeron en la tabla 
int getPasosAdicionalesBusqueda(TablaHash t) {
    for (int i = 1; i < Tam; i++) {
        t[0].pasosAdicionalesBusquedaHueco += t[i].pasosAdicionalesBusquedaHueco;
    }
    return t[0].pasosAdicionalesBusquedaHueco;
}

/* TABLA HASH CON RECOLOCACION */
void InicializarTablaHash(TablaHash t) {
    int i;

    for (i = 0; i < Tam; i++) {
        t[i].jugador.clave[0]=VACIO;
        t[i].colisionesHueco = 0;
        t[i].pasosAdicionalesBusquedaHueco = 0;
        t[i].pasosAdicionalesInserccionHueco = 0;
    }
        

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
/*
int Hash (char *cad){
    int i,suma=0;
    for (i=strlen(cad)-1;i>=0;i--){
         suma=(suma*256+cad[i])%Tam;
     }
    return suma;
 }
 */
  
/* FUNCION HASH 3: Probad al menos dos valores para la constante K */

  int Hash (char *cad){
     int i,suma=0;
     int K=500;
     for (i=strlen(cad)-1;i>=0;i--){
         suma=(suma*K+cad[i])%Tam;
     }
     return suma;
 }

/* RECOLOCACION LINEAL: depende del valor de la constante a*/

/* Funci�n que localiza la posici�n del elemento cuando buscamos*/

int _PosicionBuscar(TablaHash t, char *cad) {
    /* Devuelve el sitio donde est� la clave cad, o donde deber�a estar. */
    /* No tiene en cuenta los borrados para avanzar.                     */

    int ini, i, aux, a;
    a = 1;
    /* Hay que dar valor a la variable de recolocaci�n a */

    ini = Hash(cad);
 
    for (i = 0; i < Tam; i++) {
        if (i > 0) {
            /* Cada iteración de este bucle es una busqueda en un hueco de la
             * tabla y solo se hacen nuevas iteraciones si no se encuentra el 
             * elemento en la tabla por lo que i iteraciones se traduce como i
             * pasos adicionales en la busqueda
             */
            t[i].pasosAdicionalesBusquedaHueco++; 
        }
        aux = (ini + a*i) % Tam;
        if (t[aux].jugador.clave[0] == VACIO)
            return aux;
        if (!strcmp(t[aux].jugador.clave, cad))
            return aux;
    }
    return ini;
}

/*Funci�n que localiza la posicion para insertar un elemento */

int _PosicionInsertar(TablaHash t, char *cad) {
    // Devuelve el sitio donde podriamos poner el elemento de clave cad

    int ini, aux, i, a;
    /* Hay que dar un valor a la variable de recolocaci�n a */

    a = 25;
    ini = Hash(cad);
  
    for (i = 0; i < Tam; i++) {
        if (i == 1) {
            /* Si i = 1 quiere decir que el valor asignado por la función hash
             * al valor cad ya esta siendo usando y por lo tanto se produce una 
             * colisión
             */ 
            
            t[ini].colisionesHueco++;
        }
        aux = (ini + a*i) % Tam;
        if (i > 0) {
            /* Cada iteración de este bucle cuenta como un paso más para la
             * insercción ya que no se encontró aún su posicion en la tabla
             */ 
            t[aux].pasosAdicionalesInserccionHueco++;
        }
        if (t[aux].jugador.clave[0] == VACIO || t[aux].jugador.clave[0] == BORRADO){
            return aux;
        }
        if (!strcmp(t[aux].jugador.clave, cad)){
            return aux;
        }
    }
    return ini;
}

/* RECOLOCACION CUADRATICA */

/*
int _PosicionBuscar(TablaHash t, char *cad) {
    // Devuelve el sitio donde esta cad  o donde deberia  estar. 
    // No tiene en cuenta los borrados.

    int ini, i, aux;
 
    ini = Hash(cad);
 
    for (i = 0; i < Tam; i++) {
        if (i > 0) {
            //Idem _PosicionBuscar lineal
            t[i].pasosAdicionalesBusquedaHueco++; 
        }
        aux = (ini + i*i) % Tam;
        if (t[aux].jugador.clave[0] == VACIO)
            return aux;
        if (!strcmp(t[aux].jugador.clave, cad))
            return aux;
    }
    return ini;
}
 */
/*
int _PosicionInsertar(TablaHash t, char *cad) {
   //Devuelve el sitio donde podriamos poner cad (recolocacion cuadratica)
    int ini, i, aux;

    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        if (i == 1) {
            t[ini].colisionesHueco++;
        }
        aux = (ini + i*i) % Tam;
        if (i > 0) {
            t[aux].pasosAdicionalesInserccionHueco++;
        }
        if (t[aux].jugador.clave[0] == VACIO || t[aux].jugador.clave[0] == BORRADO)
            return aux;
        if (!strcmp(t[aux].jugador.clave, cad))
            return aux;
    }
    return ini;
}
*/

/* Funcion que indica si un elemento est� o no en la tabla */
/* Devuelve 1 si el elemento de clave cad est� en la tabla, 0 si no est� */
int MiembroHash(TablaHash t, char *cad) {
    
    int nCol, colision;
    int pos = _PosicionBuscar(t,cad);

    if (t[pos].jugador.clave[0] == VACIO)
        return 0;
    else
        return (!strcmp(t[pos].jugador.clave, cad));
}

/* BUSCA UN ELEMENTO CON LA CLAVE INDICADA EN LA TABLA HASH, Y LO DEVUELVE, 
 * ADEMAS DE INDICAR CON 1 QUE EXISTE EL ELEMENTO, Y CON 0 QUE NO ESTA EN LA TABLA */
int Busqueda(TablaHash t, char *clavebuscar, tipo_jugador *e) {
    int pos = _PosicionBuscar(t,clavebuscar);

    if (t[pos].jugador.clave[0] == VACIO)
        return 0;
    else {
        if (strcmp(t[pos].jugador.clave, clavebuscar) == 0) {
            *e = t[pos].jugador;
            return 1;
        } else return 0;
    }
}

/* Funci�n que inserta un elemento en la tabla */
void InsertarHash(TablaHash t, tipo_jugador e) {
    int pos;
    
    pos = _PosicionInsertar(t,e.clave);
    
    if (t[pos].jugador.clave[0] == VACIO || t[pos].jugador.clave[0] == BORRADO) {
        t[pos].jugador = e;
    } 
    else if (strcmp(t[pos].jugador.clave,e.clave)){
        printf("No se encuentra posicion libre.\n");
    }
}
    

/* Funci�n que elimina un elemento de la tabla */
void BorrarHash(TablaHash t, char *cad) {

    int pos = _PosicionBuscar(t,cad);

    if (t[pos].jugador.clave[0] != VACIO && t[pos].jugador.clave[0] != BORRADO) {
        if (!strcmp(t[pos].jugador.clave, cad)) {
            t[pos].jugador.clave[0]= BORRADO;
            t[pos].jugador.clave[1]= VACIO;
        }
    }
}

//Lee todos los datos de un archivo y los mete en la tabla t
void leerArchivo (TablaHash t) {
    FILE *fp;
    
    fp = fopen("jugadores_amongETSE.txt","r");
    if (fp == NULL){
        printf("Archivo no encontrado.\n");
        exit(1);
    }
    int endPoint = 0;
    tipo_jugador newPlayer;
    
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
    tipo_jugador newPlayer;
    
    do {
        endPoint = fscanf(fp,"%s %s %s - %s - %s",newPlayer.nombre,newPlayer.apellido1,newPlayer.apellido2,newPlayer.clave,newPlayer.correo);
        Busqueda(t,newPlayer.clave,&newPlayer);
    }while(endPoint != EOF); 
}

