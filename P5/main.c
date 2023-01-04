#include <stdio.h>
#include <stdlib.h>
#include <time.h> //para utilizar la semilla aleatoria time(NULL)
#include "FuncionesAmongETSE.h"


int main(int argc, char** argv) {
    
    srand((unsigned int) time(NULL)); //semilla para aleatorios, se llamar sólo una vez al principio de main
    
    //Crear el árbol de jugadores
    abb Arbol;
    crear(&Arbol);

  
   //Leer el archivo de disco
    leerArchivo(&Arbol);
    
    //Menú
    menu(&Arbol);
    
    //Destruir el árbol al finalizar
    destruir(&Arbol);

    return (EXIT_SUCCESS);
}

