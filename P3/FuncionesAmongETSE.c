#include <stdio.h>
#include <stdlib.h> //necesaria para rand()
#include <string.h> //para comparar cadenas
#include <math.h>
#include "abb.h"

void listadoJugadores(abb Arbol);

void seleccionManual (abb Arbol, int numJugadores, abb *Jugadores);

int redondeo (double valor);

void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer);

void asignarTareasHabitaciones(abb Arbol, abb Jugadores);

void imprimirDatosHabitacion ( abb Arbol, char habitacion[] );

void asignarImpostores(abb Arbol, abb Jugadores, int numJugadores);

void asignarTripulantes(abb Arbol, abb Jugadores);


unsigned int _aleatorio(int inf, int sup) {
    
    return (rand() % (sup - inf + 1)) +inf;
    
}

void _inicializarJugador(tipoelem *registro) { 

    strncpy(registro->lugarTarea,"",2);
    registro->rol = ' ';
    strncpy(registro->lugarTarea,"",2);

}

void _imprimirJugador(tipoelem E) {
    
    printf("Nombre: %s\n",E.nombreJugador);
    printf("Ultima tarea realizada: %s\n",E.descripcionTarea);  
    
}

void _imprimirJugadorCompleto(tipoelem E) {
    
    printf("Nombre: %s\nTarea: %s\nLugar donde se realizo la tarea: %s \nRol: %c\n\n",E.nombreJugador,E.descripcionTarea,E.lugarTarea,E.rol);
    
}

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

void listadoJugadores(abb A) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(A) ) {
        
        listadoJugadores(izq(A));
     
        leer(A,&newPlayer);
        printf("Nombre: %s\n",newPlayer.nombreJugador);
        
        listadoJugadores(der(A));
        
    }
    
}

void generarPartida(abb *Arbol, abb *Jugadores) {
    
    int numJugadores;
    
    do {
        
        printf("Introduce el número de jugadores: (entre 4 y 10)\n");
        scanf("%d",&numJugadores);
        
    } while ( numJugadores < 4 || numJugadores > 10 );
    
    
    seleccionManual(*Arbol, numJugadores, Jugadores);
    
    asignarImpostores(*Arbol,*Jugadores, numJugadores);
    
    asignarTripulantes(*Arbol,*Jugadores);
    
    asignarTareasHabitaciones(*Arbol, *Jugadores );
    
    
}

void asignarTripulantes(abb Arbol, abb Jugadores) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(Jugadores) ) {
        
        asignarTripulantes(Arbol,izq(Jugadores));
        leer(Jugadores,&newPlayer);
        
        if ( newPlayer.rol != 'I') {
            
            newPlayer.rol = 'T';
            modificar(Arbol,newPlayer);
            modificar(Jugadores,newPlayer);
            
        }
        
        asignarTareasHabitaciones(Arbol,der(Jugadores));
        
        
    } 
    
}

void asignarTareasHabitaciones(abb Arbol, abb Jugadores) {
    
    tipoelem newPlayer;
    
    if ( !es_vacio(Jugadores) ) {
        
        asignarTareasHabitaciones(Arbol,izq(Jugadores));
        leer(Jugadores,&newPlayer);
        asignarTareaUsuario(Arbol,Jugadores,newPlayer);
        asignarTareasHabitaciones(Arbol,der(Jugadores));
        
        
    } 
    
}

void postOrdenImpostores(abb Arbol, abb Jugadores, int numImpostores, int *impostoresReales) {
    
    tipoelem newPlayer;
    int i;
    
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

void asignarImpostores(abb Arbol, abb Jugadores, int numJugadores ) {
    
    int numImpostores = redondeo(numJugadores/5.0);
    int impostoresReales = 0;
    
    do {
        
        impostoresReales = 0;
        postOrdenImpostores(Arbol, Jugadores, numImpostores, &impostoresReales);
        
        
    } while ( impostoresReales != numImpostores );
        
        
        
}

void asignarTareaUsuario(abb Arbol, abb Jugadores, tipoelem newPlayer) {
    
    int numTarea = _aleatorio(1,8);
    int numHabitacion;
   
    
    switch(numTarea) {
        
        case 1:
            
            strcpy(newPlayer.descripcionTarea,"Alinear la salida del motor");
            strcpy(newPlayer.lugarTarea, "Motores");
            break;
            
        case 2:
            
            strcpy(newPlayer.descripcionTarea,"Calibrar distribuidor");
            strcpy(newPlayer.lugarTarea, "Electricidad");
            break;
        
        case 3:
            
            strcpy(newPlayer.descripcionTarea,"Descargar datos/subir datos");
            
            numHabitacion = _aleatorio(1,5);
            
            switch (numHabitacion) {
                
                case 1:
                    
                    strcpy(newPlayer.lugarTarea, "Cafetería");
                    break;
                    
                case 2:
                    
                    strcpy(newPlayer.lugarTarea, "Comunicaciones");
                    break;
                    
                case 3:
                    
                    strcpy(newPlayer.lugarTarea, "Armería");
                    break;
                    
                case 4:
                    
                    strcpy(newPlayer.lugarTarea, "Electricidad");
                    break;
                    
                case 5:
                    
                    strcpy(newPlayer.lugarTarea, "Navegación");
                    break;
                    
            }
            
            break;
            
        case 4:
        
            strcpy(newPlayer.descripcionTarea,"Desviar energía");
            
            numHabitacion = _aleatorio(1,7);
            
            switch (numHabitacion) {
                
                case 1:
                    
                    strcpy(newPlayer.lugarTarea, "Navegación");
                    break;
                    
                case 2:
                    
                    strcpy(newPlayer.lugarTarea, "O2");
                    break;
                    
                case 3:
                    
                    strcpy(newPlayer.lugarTarea, "Seguridad");
                    break;
                    
                case 4:
                    
                    strcpy(newPlayer.lugarTarea, "Armería");
                    break;
                    
                case 5:
                    
                    strcpy(newPlayer.lugarTarea, "Comunicaciones");
                    break;
                    
                case 6:
                    
                    strcpy(newPlayer.lugarTarea, "Escudos");
                    break;
                    
                case 7:
                    
                    strcpy(newPlayer.lugarTarea, "Motores");
                    break;
                    
            }
            
            break;
            
        case 5:
            
            strcpy(newPlayer.descripcionTarea,"Encender Escudos");
            strcpy(newPlayer.lugarTarea, "Escudos");
            break;
            
        case 6:
            
            strcpy(newPlayer.descripcionTarea,"Estabilizar dirección");
            strcpy(newPlayer.lugarTarea, "Navegación");
            break;
            
        case 7:
            
            strcpy(newPlayer.descripcionTarea,"Limpiar el filtro O2");
            strcpy(newPlayer.lugarTarea, "O2");
            break;
            
        case 8:
            
            strcpy(newPlayer.descripcionTarea,"Mapa de navegación");
            strcpy(newPlayer.lugarTarea, "Navegación");
            break;
 
    }
    
    modificar(Jugadores,newPlayer);
    modificar(Arbol,newPlayer);
    
}

void seleccionManual (abb Arbol, int numJugadores, abb *Jugadores) {
    
    char opcion;
    tipoelem newPlayer;
    abb aux = Arbol;
    
    
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
    
    while ( numJugadores > 0 ) {
        
        tipoelem A;
        leer(aux,(&A));
        
        if ( !es_miembro(*Jugadores,A) ) {
            
            insertar( Jugadores, A );
            numJugadores--;
        }
       
        aux = izq(aux);
             
    }
    
    printf("\nLos que van a jugar son:\n");
    listadoJugadores(*Jugadores);
    
}

void consultarJugador(abb Arbol) {
    
    char name[30];
    tipoelem newPlayer;
    
    printf("Como se llama el jugador que quieres consultar?\n");
    scanf( " %s",name);
    
    strcpy(newPlayer.nombreJugador,name);
    
    if ( es_miembro(Arbol,newPlayer)) {
        
        buscar_nodo(Arbol,newPlayer.nombreJugador,&newPlayer);
        
        if (strcmp(newPlayer.descripcionTarea,"") != 0) {

            _imprimirJugador(newPlayer);

        } else {
            
            printf("El jugador no tiene ninguna tarea asignada.\n");
            
        }
       
    } else {
        
        printf("El nombre introducido no coincide con el de ningún usuario\n");
        
    }
}

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
        
        if ( strcmp(newPlayer.lugarTarea,habitacion) == 0 ) {
            
            _imprimirJugadorCompleto(newPlayer);
            
        }
        imprimirDatosHabitacion(der(Arbol),habitacion);
    }
    
}

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
        printf("g. Generar datos partida\n");
        printf("h. Consulta jugador@s por habitación\n");
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
                
            case 'g':
                generarPartida(Arbol,&Jugadores);
                break;
                
            case 'u':
                consultarJugador(*Arbol);
                break;
                
            case 'h':
                consultarPorHabitacion(*Arbol);
                break;  
             
        }
        
        printf("\n\n");
            
    } while (opcion != 's');
    
    destruir(&Jugadores);
   
    
}

int redondeo (double valor) {
    
    int parteEntera = (int) valor;
    valor = valor - parteEntera;
    
    if ( valor >= 0.5 ) 
        
        return parteEntera + 1;
   
    return parteEntera;
    
    
}



