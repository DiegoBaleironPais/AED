#include <stdio.h>
#include <stdlib.h> //necesaria para rand()
#include <string.h> //para comparar cadenas
#include <math.h>
#include "abb.h"

#define NUMTAREAS 5

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

void asignarTareasHabitaciones(abb Arbol, abb Jugadores, int numTareas);

void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer, int numTareas);

void consultarJugador(abb Arbol);

void consultarPorHabitacion(abb Arbol);

void imprimirDatosHabitacion ( abb Arbol, char habitacion[] );

/*
 * Imprime todas las tareas y el lugar donde se desarrollan de una cola dada
 */
void _imprimirTareas(cola *C);

void guardarUsuarios ( abb Arbol );

/*
 * Escribe en un fichero de texto el nombre de los usuarios del arbol de usuarios
 */
void _escribirUsuarios ( abb Arbol, FILE * fp );

/*
 * Saca los elementos del arbol de Jugadores los copia en otra variable tipoelem
 * y los cambia por el su elemento correspondiente en el arbol de usuarios con
 * el objetivo de que al borrar el arbol de jugadores los elementos del arbol
 * de usuarios permanezcan intactos
 */
void _vaciarArbol (abb Arbol, abb Jugadores );

/*
 * Copia una cola origen en una cola destino
 */
void _copiarCola ( cola origen, cola *destino );

/*
 * Imprime el nombre de los jugadores la ultima tarea que hicieron y donde la hicieron
 */
void _ejecutarTarea ( abb Arbol, abb Jugadores );

/*
 * Permite a los impostores matar a un tripulante o hacer un sabotaje dependiendo
 * de si hay más jugadores en su sala o no
 */
void _traicion ( abb Arbol,abb JugadoresOriginal, abb JugadoresMovible, int *numTripulantes, int *numTareas );

/*
 * Busca si hay tripulantes en la sala donde el impostor está haciendo su tarea
 * y si los hay mata a uno aleatoriamente
 */
void _matarTripulante(abb Arbol,abb Jugadores, tipoelem newPlayer, int *i, int *numTripulantes);

/*
 * Vacia la cola del tipoelem que se le pasa como parametro
 */
void _vaciarCola (abb Arbol, abb Jugadores, tipoelem newPlayer2 );

/*
 * Permite expulsar a un jugador y matarlo
 */
void _expulsion ( abb Arbol, abb Jugadores, int *numTripulantes, int *numImpostores );

/*
 * Elimina la ultima tarea hecha por los jugadores
 */
void _siguienteTarea ( abb Arbol, abb Jugadores );


//Funciones privadas
unsigned int _aleatorio(int inf, int sup) {
    
    return (rand() % (sup - inf + 1)) +inf;
    
}


void _inicializarJugador(tipoelem *registro) { 

    crear_cola(&(registro->tareas));
    registro->rol = ' ';

}

void _imprimirJugador(tipoelem E) {
    
    printf("Nombre: %s\n",E.nombreJugador);
    printf("Ultima tarea realizada: %s\n",primero(E.tareas).descripcionTarea);
    printf("La tarea de hizo en: %s\n",primero(E.tareas).lugarTarea); 
    
}

void _imprimirJugadorCompleto(tipoelem E) {
   
    printf("Nombre: %s\n",E.nombreJugador);
    if (E.rol == ' ') {
        printf("Rol: no existe\n");
    } else {
        printf("Rol: %c\n",E.rol);
    }
    
    _imprimirTareas(&(E.tareas));
}

void _imprimirJugadorCompletoSinRol(tipoelem E) {
   
    printf("Nombre: %s\n",E.nombreJugador);
    _imprimirTareas(&(E.tareas));
    
}

void _imprimirTareas(cola *C) {
    
    cola aux;
    crear_cola(&aux);
    tipoelemCola auxElem;
    
    //Vacio la cola C imprimo su contenido y meto los elementos en la cola aux para no perderlos
    while ( !es_vacia_cola(*C) ) {
        
        auxElem = primero(*C);
        printf("Tarea: %s en %s\n",auxElem.descripcionTarea,auxElem.lugarTarea);
        suprimir_cola(C);
        insertar_cola(&aux,auxElem);
    }
    
    //No me funcionaba igual la cola *C a la cola aux por lo que copio uno a uno los elementos de la cola aux en la cola C
    while ( !es_vacia_cola(aux) ) {
        
        auxElem = primero(aux);
        suprimir_cola(&aux);
        insertar_cola(C,auxElem);
        
    }
}

void _limpiarDatos( abb Arbol ) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(Arbol) ) {
        
        _limpiarDatos(izq(Arbol));
     
        leer(Arbol,&newPlayer);
        
        newPlayer.rol = ' ';
        
        while( !es_vacia_cola(newPlayer.tareas) ) {
        
        suprimir_cola(&(newPlayer.tareas));
        
        }
        
        modificar(Arbol,newPlayer);
        
        _limpiarDatos(der(Arbol));
        
    }

}

void _vaciarArbol (abb Arbol, abb Jugadores ) {
    
    tipoelem newPlayer;
    tipoelem newPlayer2;
    
    if ( !es_vacio(Jugadores) ) {
        
        _vaciarArbol(Arbol,izq(Jugadores));
        
        /*Creo una variable newPlayer2 dos con todos los valores iguales que 
        * los de newPlayer y luego meto newPlayer2 en el abb Arbol para que Arbol
        * y Jugadores tengan nodos distintos y estos se puedan eliminar sin 
        * problemas
        */
        leer(Jugadores,&newPlayer);
        strcpy(newPlayer2.nombreJugador,newPlayer.nombreJugador);
        newPlayer2.rol = newPlayer.rol;
        crear_cola(&(newPlayer2.tareas));
        _copiarCola(newPlayer.tareas,&(newPlayer2.tareas));
        modificar(Arbol,newPlayer2);
        
        _vaciarArbol(Arbol,der(Jugadores));;
        
    }
    
}

void _copiarCola ( cola origen, cola *destino ) {
    
    tipoelemCola newPlayer;
    
    while ( !es_vacia_cola(origen) ) {
        
        newPlayer = primero(origen);
        insertar_cola(destino,newPlayer);
        suprimir_cola(&origen);
        
    }
    
}

int redondeo (double valor) {
    
    int parteEntera = (int) valor;
    valor = valor - parteEntera;
    
    if ( valor >= 0.5 ) 
        
        return parteEntera + 1;
   
    return parteEntera;
  
}

//Lectura de archivo
void leerArchivo(abb *A) {
    
    tipoelem registro;
    FILE *fp;
    
    fp = fopen("ETSErsG3.txt", "rt");
    
    if (fp) {
        
        fscanf(fp, " %s", registro.nombreJugador);
        while (!feof(fp)) {
            
            _inicializarJugador(&registro);
            insertar(A, registro);
            fscanf(fp, " %s", registro.nombreJugador);
        
        }
        
        fclose(fp);
    
    }
}

//Menu y todas sus funciones por orden
void menu(abb *Arbol) {
    
    char opcion;
    abb Jugadores;
    crear(&Jugadores);
    
    printf("Bienvenid@ a AmongETSE\n");
    
    do {
        
        printf("a. Alta de jugador@\n");
        printf("b. Baja de jugador@\n");
        printf("l. Listado de jugador@s por orden alfabético\n");
        printf("u. Consulta por jugador@ de la última tarea asignada\n");
        printf("j. Jugar Partida\n");
        printf("h. Consulta jugador@s por habitación\n");
        printf("f. Guarda todos los usuarios en un archivo de disco\n");
        printf("s. Salir de la aplicación\n");
        
           
        scanf(" %c",&opcion);
        
        switch ( opcion ) {
            
            case 'a':
                altaJugador(Arbol);
                break;
            
            case 'b':
                bajaJugador(Arbol);
                break;
                
            case 'l':
                printf("Listado de posibles jugadores:\n");
                listadoJugadores(*Arbol);
                break;
                
            case 'j':
                generarPartida(Arbol,&Jugadores);
                break;
                
            case 'u':
                consultarJugador(*Arbol);
                break;
                
            case 'h':
                consultarPorHabitacion(*Arbol);
                break;  
                
            case 'f':
                guardarUsuarios(*Arbol);
                break;
            
            case 's':
                printf ("\nSalimos del programa.\n");
                break;
                
            default:
                printf("Caracter incorrecto.\n");
                break;
             
        }
        
        printf("\n\n");
            
    } while (opcion != 's');
    
     if ( !es_vacio(Jugadores) ) {
        
        _vaciarArbol(*Arbol,Jugadores);
        destruir(&Jugadores);
    }
      
}

//Alta de jugador
void altaJugador(abb *Arbol) {
    
    tipoelem newPlayer;
    
    printf("Como se llama el nuevo jugador?\n");
    scanf(" %s",newPlayer.nombreJugador);
    
    if ( newPlayer.nombreJugador[0] != '@' ) {
        
        printf ("El jugador no puedo registrarse ya que su nick no empieza por"
        " @.\n");
        return;
        
    } else {
        
        if ( es_miembro(*Arbol,newPlayer) ) {
            
            printf("Ese nickname ya se está usando no se pudo registrar el "
                    "usuario.\n");
            return;
            
        }
        
        _inicializarJugador(&newPlayer);
        insertar(Arbol,newPlayer);
    }
    
}

//Baja de jugador
void bajaJugador(abb *Arbol) {
    
    tipoelem newPlayer;
    
    printf("Como se llama el jugador que quieres eliminar?\n");
    scanf("%s",newPlayer.nombreJugador);
    
    if ( newPlayer.nombreJugador[0] != '@' ) {
        
        printf ("El jugador no empieza por '@' lo has escrito mal.\n");
        return;
        
    } else {
        
        if ( !es_miembro(*Arbol,newPlayer) ) {
            
            printf("No hay ningun jugador con ese nombre.\n");
            return;
            
        }
        
        suprimir(Arbol, newPlayer);
        printf("El jugador se ha eliminado correctamente.\n");
        
    }
    
    
}

//Listado de Jugadores
void listadoJugadores(abb A) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(A) ) {
        
        listadoJugadores(izq(A));
     
        leer(A,&newPlayer);
        _imprimirJugadorCompleto(newPlayer);
        
        listadoJugadores(der(A));
        
    }
    
}

//Conjunto de funciones que intervienen en generarPartida
void generarPartida(abb *Arbol, abb *Jugadores) {
    
    char s;
    
    if ( !es_vacio(*Jugadores) ) {
        
        _vaciarArbol(*Arbol,*Jugadores);
        destruir(Jugadores);
        crear(Jugadores);
        
    }
        
    _limpiarDatos(*Arbol);

    int numJugadores;
    
    do {
        
        printf("Introduce el número de jugadores: (entre 4 y 10)\n");
        scanf(" %d",&numJugadores);
        
    } while ( numJugadores < 4 || numJugadores > 10 );
    
    int numImpostores = redondeo(numJugadores/5.0);
    int numTripulantes = numJugadores - numImpostores;
    int numTareas = 5;
    
    seleccionManual(*Arbol, numJugadores, Jugadores);
    
    asignarImpostores(*Arbol,*Jugadores, numJugadores);
    
    asignarTripulantes(*Arbol,*Jugadores);
    
    asignarTareasHabitaciones(*Arbol, *Jugadores, 5 );
    
    while ( numImpostores > 0 && numTripulantes > numImpostores  && numTareas > 0) {
        
        printf("\n");
        //Se imprimen los datos de los jugadores
        _ejecutarTarea(*Arbol, *Jugadores);
        printf("\n");
        
        abb JugadoresMovible = *Jugadores;
        //Los impostores sabotean tareas o matan a otros jugadores
        _traicion(*Arbol, *Jugadores, JugadoresMovible, &numTripulantes, &numTareas);
        printf("\n");
        
        //Condición de salida del bucle
        if ( numTripulantes <= numImpostores ) {
            
            break;
        }
        
        do {
            
            printf("\nPulsa s si quieres eliminar a algun jugador.\n");
            scanf ( " %c",&s);
            
            if ( s == 's') {
                //Funcion para expulsar manualmente a algun jugador
                _expulsion(*Arbol, *Jugadores, &numTripulantes, &numImpostores);
            }
            
            printf("\nNum tripulantes: %d\n",numTripulantes);
            printf("Num impostores: %d\n",numImpostores);
            
        
        } while ( s == 's' && numImpostores != 0 && numTripulantes != 0 && numImpostores < numTripulantes );
       
        //Condicion de salida del bucle
        if ( numTripulantes <= numImpostores || numImpostores == 0 ) {
            
            break;
        }

        _siguienteTarea(*Arbol,*Jugadores);
        numTareas = numTareas - 1;
        printf("Num tareas restantes: %d\n",numTareas);
    }
    
    if ( numImpostores >= numTripulantes ) {
        
        printf("\nHan ganado los impostores.\n");
        
    } else {
          
        printf("\nHan ganado los tripulantes.\n");
        
    }
       
    
    
}

void seleccionManual (abb Arbol, int numJugadores, abb *Jugadores) {
    
    char opcion;
    tipoelem newPlayer;
    abb aux = Arbol;
    
    //Se añaden jugadores al arbol de Jugadores de forma manual
    do {
        
        printf("Si quieres seleccionar a algún jugador manualmente pulsa 's': "
                "(en caso contrario pulsa cualquier tecla y los %d huecos restantes "
                "serán cubiertos con jugadores seleccionados aleatoriamente)\n",numJugadores);
        
        scanf(" %c",&opcion);
        
        if ( opcion == 's') {
            
        printf("Como se llama la persona que quieres añadir a la partida?\n");
        scanf(" %s",newPlayer.nombreJugador);
        
        if ( es_miembro(Arbol,newPlayer) && !es_miembro(*Jugadores,newPlayer) ) {
            
            _inicializarJugador(&newPlayer);
            insertar(Jugadores,newPlayer);
            numJugadores--;

        } else {
            
            printf("El nombre no coincide con el de ninguna persona registrada");
            printf(" o ya está añadido.\n");
            
        }
            
        }
            
    } while (opcion == 's' && numJugadores > 0);
    
    //Los huecos no rellenados de forma manual se añaden de forma automática
    while ( numJugadores > 0 ) {
        
        tipoelem A;
        leer(aux,(&A));
        
        if ( !es_miembro(*Jugadores,A) ) {
            
            insertar( Jugadores, A );
            numJugadores--;
        }
       
        aux = izq(aux);
             
    }
    
    printf("\nLos usuarios que van a jugar son:\n");
    listadoJugadoresNombre(*Jugadores);
    
}

void listadoJugadoresNombre(abb Jugadores) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(Jugadores) ) {
        
        listadoJugadoresNombre(izq(Jugadores));
     
        leer(Jugadores,&newPlayer);
        printf("Nombre: %s\n",newPlayer.nombreJugador);
        
        listadoJugadoresNombre(der(Jugadores));
        
    }
}

void asignarImpostores(abb Arbol, abb Jugadores, int numJugadores ) {
    
    int numImpostores = redondeo(numJugadores/5.0);
    int impostoresReales = 0;
    
    do {
        
        impostoresReales = 0;
        postOrdenImpostores(Arbol, Jugadores, numImpostores, &impostoresReales);
        
        
    } while ( impostoresReales != numImpostores );
             
}

void postOrdenImpostores(abb Arbol, abb Jugadores, int numImpostores, int *impostoresReales) {
    
    tipoelem newPlayer;
    int i;
    //Asigna el rol de impostor de manera aleatoria a los jugadores
    if ( !es_vacio(Jugadores) ) {
        
        leer(Jugadores,&newPlayer);
       
        if (*impostoresReales < numImpostores ) {
            
            i = _aleatorio(1,2);
            
            if ( i == 2 ) {
                
                newPlayer.rol = 'I';
                modificar(Jugadores,newPlayer);
                modificar(Arbol,newPlayer);
                *impostoresReales+= 1;
        
           } 
                
           if ( !es_vacio(izq(Jugadores)) && !es_vacio(der(Jugadores)) ) {

                i = _aleatorio(1,2);

                if ( i == 1 ) {

                    postOrdenImpostores( Arbol,  izq(Jugadores),  numImpostores, impostoresReales);

                } else {

                    postOrdenImpostores( Arbol, der (Jugadores), numImpostores,impostoresReales);

                }
           } else {

                if ( !es_vacio(izq(Jugadores)) ) {

                    postOrdenImpostores( Arbol,  izq(Jugadores),  numImpostores, impostoresReales);

                } else {

                    postOrdenImpostores( Arbol, der (Jugadores), numImpostores,impostoresReales);

                }
           }                    
}   
}
}

void asignarTripulantes(abb Arbol, abb Jugadores) {
    
    tipoelem newPlayer;
    //Se asigna el rol de tripulante a los jugadores que no sean impostores
    if ( !es_vacio(Jugadores) ) {
        
        asignarTripulantes(Arbol,izq(Jugadores));
        leer(Jugadores,&newPlayer);
        
        if ( newPlayer.rol != 'I') {
            
            newPlayer.rol = 'T';
            modificar(Arbol,newPlayer);
            modificar(Jugadores,newPlayer);
            
        }
        
        asignarTripulantes(Arbol,der(Jugadores));
        
    } 
    
}

void asignarTareasHabitaciones(abb Arbol, abb Jugadores, int numTareas) {
    
    tipoelem newPlayer;
    /*Se llama a la funcion asignarTareasUsuarios para todos los jugadores que no
     *esten muertos para asignarles n tareas. (n = numTareas)
     */
    if ( !es_vacio(Jugadores) ) {
        
        asignarTareasHabitaciones(Arbol,izq(Jugadores), numTareas);
        leer(Jugadores,&newPlayer);
        
        if ( newPlayer.rol != 'K') {
            asignarTareaUsuario(Arbol,Jugadores,newPlayer, numTareas);
        }
       
        asignarTareasHabitaciones(Arbol,der(Jugadores), numTareas);
        
        
    } 
    
}

void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer, int numTareas) {
    
    int numHabitacion;
    tipoelemCola aux;
    //Se asignan n tareas al jugador newPlayer y se introduce de nuevo en los dos arboles
    for ( int i = 0; i < numTareas; i++ ) {
        
        int numTarea = _aleatorio(1,8);
         
        switch(numTarea) {
        
            case 1:

                strcpy(aux.descripcionTarea,"Alinear la salida del motor");
                strcpy(aux.lugarTarea, "Motores");
                break;

            case 2:

                strcpy(aux.descripcionTarea,"Calibrar distribuidor");
                strcpy(aux.lugarTarea, "Electricidad");
                break;

            case 3:

                strcpy(aux.descripcionTarea,"Descargar datos/subir datos");

                numHabitacion = _aleatorio(1,5);

                switch (numHabitacion) {

                    case 1:

                        strcpy(aux.lugarTarea, "Cafeteria");
                        break;

                    case 2:

                        strcpy(aux.lugarTarea, "Comunicaciones");
                        break;

                    case 3:

                        strcpy(aux.lugarTarea, "Armeria");
                        break;

                    case 4:

                        strcpy(aux.lugarTarea, "Electricidad");
                        break;

                    case 5:

                        strcpy(aux.lugarTarea, "Navegacion");
                        break;

                }

                break;

            case 4:

                strcpy(aux.descripcionTarea,"Desviar energía");

                numHabitacion = _aleatorio(1,7);

                switch (numHabitacion) {

                    case 1:

                        strcpy(aux.lugarTarea, "Navegacion");
                        break;

                    case 2:

                        strcpy(aux.lugarTarea, "O2");
                        break;

                    case 3:

                        strcpy(aux.lugarTarea, "Seguridad");
                        break;

                    case 4:

                        strcpy(aux.lugarTarea, "Armeria");
                        break;

                    case 5:

                        strcpy(aux.lugarTarea, "Comunicaciones");
                        break;

                    case 6:

                        strcpy(aux.lugarTarea, "Escudos");
                        break;

                    case 7:

                        strcpy(aux.lugarTarea, "Motores");
                        break;

                }

                break;

            case 5:

                strcpy(aux.descripcionTarea,"Encender Escudos");
                strcpy(aux.lugarTarea, "Escudos");
                break;

            case 6:

                strcpy(aux.descripcionTarea,"Estabilizar dirección");
                strcpy(aux.lugarTarea, "Navegacion");
                break;

            case 7:

                strcpy(aux.descripcionTarea,"Limpiar el filtro O2");
                strcpy(aux.lugarTarea, "O2");
                break;

            case 8:

                strcpy(aux.descripcionTarea,"Mapa de navegación");
                strcpy(aux.lugarTarea, "Navegacion");
                break;
 
        }
        
        insertar_cola(&(newPlayer.tareas),aux);
    }
    
    modificar(Jugadores,newPlayer);
    modificar(Arbol,newPlayer);
    
}

void _ejecutarTarea ( abb Arbol, abb Jugadores ) {
    
    tipoelem newPlayer;
    //Se imprime de forma recursiva el nombre de los jugadores sus ultimas tareas realizada y el lugar donde la realizaron
    if ( !es_vacio(Jugadores) ) {
        
        _ejecutarTarea(Arbol,izq(Jugadores));
        
        leer(Jugadores,&newPlayer);
        if (newPlayer.rol != 'K' && !es_vacia_cola(newPlayer.tareas)) {
        
            printf("%s ha completado su tarea %s en %s.\n",newPlayer.nombreJugador,primero(newPlayer.tareas).descripcionTarea,primero(newPlayer.tareas).lugarTarea);
        }
        
        _ejecutarTarea(Arbol,der(Jugadores));
        
    }
}

void _traicion ( abb Arbol, abb JugadoresOriginal, abb JugadoresMovible, int *numTripulantes, int *numTareas ) {
    
    tipoelem newPlayer;
    /*
     *Se recorre el arbol de forma recursiva y cuando se encuentre un Impostor 
     * se llama a la función matarTripulante para que mate a alguien de su misma
     * sala, en caso de que no lo haya hará un sabotaje y llamará a la funcion 
     * asignarTareasHabitaciones para asignarle una tarea nueva a cada jugadir  */
    if ( !es_vacio(JugadoresMovible) ) {
        
        _traicion (Arbol, JugadoresOriginal, izq(JugadoresMovible), numTripulantes, numTareas);
        
        leer(JugadoresMovible,&newPlayer);
        
        if ( newPlayer.rol == 'I' ) {
            
            int i = 0;
            _matarTripulante(Arbol, JugadoresOriginal, newPlayer, &i, numTripulantes);
            
            if ( i == 0 ) {
                
                *numTareas = *numTareas + 1;
                printf("Acaba de producirse un sabotaje.\n");
                asignarTareasHabitaciones(Arbol, JugadoresOriginal, 1);
            
            }
        }
        
        _traicion (Arbol, JugadoresOriginal, der(JugadoresMovible), numTripulantes, numTareas );
        
    }

}

void _matarTripulante(abb Arbol, abb Jugadores, tipoelem newPlayer, int *i, int *numTripulantes) {
    
    tipoelem newPlayer2;
    /*
     *Se recorre el arbol de forma recursiva y si se encuentra a algún tripulante
     *en la misma habitación que el impostor que se pasa como parámetro lo mata
     *y el tripulante pasa a tener el rol 'K' y se vacia su cola, una vez 
     que el impostor mata a un tripulante se sale de la recursiva actualizando el 
     puntero *i
     */
    
    if ( !es_vacio(Jugadores) ) {
        
        leer(Jugadores,&newPlayer2);
        
        if ( newPlayer2.rol == 'T' && 
                strcmp(newPlayer.nombreJugador,newPlayer2.nombreJugador) != 0 
                && strcmp(primero(newPlayer.tareas).lugarTarea,primero(newPlayer2.tareas).lugarTarea) == 0) {
            
            printf("El jugador %s ha sido asesinado en %s.\n",newPlayer2.nombreJugador,primero(newPlayer2.tareas).lugarTarea);
            
            newPlayer2.rol = 'K';
            *i = 1;
            *numTripulantes = *numTripulantes - 1;
            _vaciarCola(Arbol, Jugadores, newPlayer2);
           
        }
        
        if ( *i != 1 ) {
        
            _matarTripulante(Arbol,izq(Jugadores), newPlayer, i, numTripulantes);
        
        }
        
         if ( *i != 1 ) {
        
            _matarTripulante(Arbol,der(Jugadores), newPlayer, i, numTripulantes);
        
        }
        
    }
    
}

void _vaciarCola (abb Arbol, abb Jugadores, tipoelem newPlayer2 ) {
    
    while ( !es_vacia_cola(newPlayer2.tareas) ) {
        
        suprimir_cola(&(newPlayer2.tareas));
        
    }
    
    modificar(Arbol,newPlayer2);
    modificar(Jugadores,newPlayer2);
}

void _expulsion (abb Arbol, abb Jugadores, int *numTripulantes, int *numImpostores ) {
    
    char s;
    tipoelem newPlayer;
    char nombreExpulsado[30];

    printf("Escribe el nombre del jugador que quieres expulsar.\n");
    scanf(" %s",nombreExpulsado);
    strcpy(newPlayer.nombreJugador,nombreExpulsado);

    if ( es_miembro(Jugadores, newPlayer) ) {

        buscar_nodo(Jugadores,nombreExpulsado,&newPlayer);

        if ( newPlayer.rol != 'K' ) {

             if ( newPlayer.rol == 'T' ) {
                

                *numTripulantes = *numTripulantes - 1;

            } else {
                 
                *numImpostores = *numImpostores - 1;
            }

            newPlayer.rol = 'K';
            _vaciarCola(Arbol, Jugadores, newPlayer);


        } else {

            printf("El jugador seleccionado está muerto.\n");
        }

    } else {

        printf("El nombre introducido no coincide con el de ningún jugador.\n");
    }
        
}

void _siguienteTarea ( abb Arbol, abb Jugadores ) {
    /*
     *Borra la ultima tarea que se hizo en todos los nodos del arbol Jugadores
     */
    tipoelem newPlayer;
    
    if ( !es_vacio(Jugadores) ) {
        
        _siguienteTarea (Arbol, izq(Jugadores));
        
        leer(Jugadores,&newPlayer);
        
        if ( newPlayer.rol != 'K' ) {
            
            suprimir_cola(&newPlayer.tareas);
        }
        
        modificar(Arbol, newPlayer);
        modificar(Jugadores, newPlayer);
        
        _siguienteTarea (Arbol, der(Jugadores) );
        
    }  
    
}

//Consultar Jugador
void consultarJugador(abb Arbol) {
    
    char name[30];
    tipoelem newPlayer;
    
    printf("Como se llama el jugador que quieres consultar?\n");
    scanf( " %s",name);
    
    strcpy(newPlayer.nombreJugador,name);
    
    if ( es_miembro(Arbol,newPlayer)) {
        
        buscar_nodo(Arbol,newPlayer.nombreJugador,&newPlayer);
        
        if ( !es_vacia_cola(newPlayer.tareas)) {

            _imprimirJugador(newPlayer);

        } else {
            
            printf("El jugador ya ha realizado todas sus tareas.\n");
            
        }
       
    } else {
        
        printf("El nombre introducido no coincide con el de ningun jugador\n");
        
    }
}

//Consultar por Habitacion
void consultarPorHabitacion(abb Arbol) {
    
    int numHabitacion;
    
    printf("Introduce el num asociado a la habitación que quieres consultar:\n");
    printf("Numeros asocidos a las habitaciones:\n\tMotores (1)\n\tElectricidad (2)\n\tCafeteria (3)\n\tComunicaciones (4)\n\tArmeria (5)\n\tNavegacion (6)\n");
    printf("\tSeguridad (7)\n\tO2 (8)\n\tEscudos (9)\n");
    
    scanf( " %d", &numHabitacion );
    
    char habitacion[25];
    
    switch (numHabitacion) {
        
        case 1:
            
            strcpy(habitacion,"Motores");
            break;
            
        case 2:
            
            strcpy(habitacion,"Electricidad");
            break;
            
        case 3:
            
            strcpy(habitacion,"Cafeteria");
            break;
            
        case 4:
            
            strcpy(habitacion,"Comunicaciones");
            break;
            
        case 5:
            
            strcpy(habitacion,"Armeria");
            break;
            
        case 6:
            
            strcpy(habitacion,"Navegacion");
            break;
            
        case 7:
            
            strcpy(habitacion,"Seguridad");
            break;
            
        case 8:
            
            strcpy(habitacion,"Cafeteria");
            break;
            
        case 9:
            strcpy(habitacion,"Escudos");
            break;
            
    }
    
    imprimirDatosHabitacion(Arbol,habitacion);
    
  
}

void imprimirDatosHabitacion ( abb Arbol, char habitacion[] ) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(Arbol) ) {
        
        imprimirDatosHabitacion(izq(Arbol),habitacion);
        leer(Arbol,&newPlayer);
        
        if ( !es_vacia_cola(newPlayer.tareas) && strcmp(primero(newPlayer.tareas).lugarTarea,habitacion) == 0 ) {
            
            _imprimirJugadorCompletoSinRol(newPlayer);
            
        }
        imprimirDatosHabitacion(der(Arbol),habitacion);
    }
    
}

//Guardar Usuarios
void guardarUsuarios ( abb Arbol ) {
    
    FILE *fp;
    fp = fopen ("jugadores.txt", "w+");
    
    _escribirUsuarios(Arbol,fp);
    
    fclose(fp);
    
}

void _escribirUsuarios ( abb Arbol, FILE * fp ) {
    
    tipoelem newPlayer;
       
    if ( !es_vacio(Arbol) ) {
        
        leer(Arbol,&newPlayer);
        fprintf(fp,"Nombre: %s \n",newPlayer.nombreJugador);
        
        _escribirUsuarios(izq(Arbol),fp);
        _escribirUsuarios(der(Arbol),fp);
        
        
    } 
}
