#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include <unistd.h>

#define INF 1000000
#define MAXVERTICES 15

struct camino {
    int verticePredecesor;
    char mapa;
};


//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo
void _imprimir_camino (struct camino matrizPredecesores[MAXVERTICES][MAXVERTICES], 
        int origen, int destino, tipovertice *vertices);

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf("%s", v1.nombreHabitacion);
    
    if (existe_vertice(*G, v1))
        printf("Ese vertice ya esta en el grafo\n");
    else
        insertar_vertice(G, v1);
}

//Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf("%s", v1.nombreHabitacion);
    
    if (existe_vertice(*G, v1))
        borrar_vertice(G, v1);
    else
        printf("Ese vertice no existe en el grafo\n");
}

//Opción c del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G) {
    tipovertice v1, v2;
    int bandera;
    int valor;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Nueva relacion vertice1-->vertice2\n");
    printf("(Solo podrás crear un arco entre dos vertices si no existe ningun o "
            " si creas uno con un valor menor al arco existente, si quieres "
            "introducir un arco que no cumpla estas condiciones antes tendrás que "
            "borrar el ya existente)\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf("%s", v1.nombreHabitacion);
    
    if (!existe_vertice(*G, v1)) {
        printf("El vertice %s no existe en el grafo\n", v1.nombreHabitacion);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf("%s", v2.nombreHabitacion);
    
    if (!existe_vertice(*G, v2)) {
        printf("El vertice %s no existe en el grafo\n", v2.nombreHabitacion);
        return;
    }
    
    printf("Introduce el valor del arco: ");
    scanf("%d", &valor);
    
    if ( valor <= 0 ) {
        printf("valor %d no valido",valor);
        return;
    }
    
    do {
        printf("Quieres crear un arco para tripulantes o para impostores? Pulsa '1' o '2' respectivamente\n");
        scanf("%d", &bandera);
    } while (bandera < 1 || bandera > 2);
   
    if ( bandera == 1 ) {
        
        if (!son_adyacentes_T(*G, posicion(*G, v1), posicion(*G, v2)) ||
            son_adyacentes_T(*G, posicion(*G, v1), posicion(*G, v2)) > valor)
            crear_arco_T(G, posicion(*G, v1), posicion(*G, v2), valor);
    } else {
        
        if (!son_adyacentes_I(*G, posicion(*G, v1), posicion(*G, v2))
            || son_adyacentes_I(*G, posicion(*G, v1), posicion(*G, v2)) > valor)
            crear_arco_I(G, posicion(*G, v1), posicion(*G, v2), valor);
    }
    //Creación del arco
}

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G) {
    tipovertice v1, v2;
    int bandera;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Eliminar relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf("%s", v1.nombreHabitacion);
    
    if (!existe_vertice(*G, v1)) {
        printf("El vertice %s no existe en el grafo\n", v1.nombreHabitacion);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf("%s", v2.nombreHabitacion);
    
    if (!existe_vertice(*G, v2)) {
        printf("El vertice %s no existe en el grafo\n", v2.nombreHabitacion);
        return;
    }
    
    do {
        printf("Quieres borrar un arco de tripulantes o de impostores? Pulsa '1' o '2' respectivamente\n");
        scanf("%d", &bandera);
    } while (bandera < 1 || bandera > 2);
    
    //Eliminación del arco
    if (bandera == 1) {
        
        if (son_adyacentes_T(*G, posicion(*G, v1), posicion(*G, v2)))
            borrar_arco_T(G, posicion(*G, v1), posicion(*G, v2));
    } else {
        
        if (son_adyacentes_I(*G, posicion(*G, v1), posicion(*G, v2)))
            borrar_arco_I(G, posicion(*G, v1), posicion(*G, v2));
    }
    
}

//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer las matrices de adyacencia y de impostores
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    printf("El grafo actual es:\n");
    printf("\nMatriz de tripulantes:\n");
     //Recorrido de la matriz de tripulantes
    for (i = 0; i < N; i++) {
        //Imprimo el vértice
        printf("\nVertice(%s):\n", VECTOR[i].nombreHabitacion);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
            if (son_adyacentes_T(G, i, j))
                printf("\t%s--%d-%s\n", VECTOR[i].nombreHabitacion, son_adyacentes_T(G, i, j), VECTOR[j].nombreHabitacion);
    }
    
    printf("\nMatriz de impostores:\n");
    //Recorrido de la matriz de impostores
    for (i = 0; i < N; i++) {
        //Imprimo el vértice
        printf("\nVertice(%s):\n", VECTOR[i].nombreHabitacion);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
            if (son_adyacentes_I(G, i, j))
                printf("\t%s--%d-%s\n", VECTOR[i].nombreHabitacion, son_adyacentes_I(G, i, j), VECTOR[j].nombreHabitacion);
    }
}
//Opcion g del menu
//Guardado de datos del grafo en un archivo externo
void guardar_datos_grafo(grafo G) {
    FILE *fp;
    tipovertice *verticesGrafo = array_vertices(G);

    fp = fopen("datosGrafo.txt","w+");
    
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    //Impresion de vertices
    for (int i = 0; i < num_vertices(G); i++) {
        fprintf(fp,"%s\n",verticesGrafo[i].nombreHabitacion);
    }
    
    //Impresion de asterisco
    fprintf(fp,"*\n");
    
    //Impresion de arcos
    for (int i = 0; i < num_vertices(G); i++) {
        for (int j = 0; j <= i; j++) {
            
            if ( son_adyacentes_T(G,i,j)) {
                fprintf(fp,"%s",verticesGrafo[i].nombreHabitacion);
                fprintf(fp,"--");
                fprintf(fp,"%d",son_adyacentes_T(G,i,j));
                fprintf(fp,"-");
                fprintf(fp,"%s\n",verticesGrafo[j].nombreHabitacion);
            }
            
            if ( son_adyacentes_I(G,i,j) != son_adyacentes_T(G,i,j)) {
                fprintf(fp,"%s",verticesGrafo[i].nombreHabitacion);
                fprintf(fp,"..");
                fprintf(fp,"%d",son_adyacentes_I(G,i,j));
                fprintf(fp,"-");
                fprintf(fp,"%s\n",verticesGrafo[j].nombreHabitacion);
            }
        }
    }
   
    fclose(fp);
}

//Opcion l del menú, lee los datos de un archivo de texto introducido por teclado y los guarda en el grafo
void leer_datos_archivo(grafo *G) {
    FILE *fp;
    char linea[100];
    int bandera = 1;
    char codigos;
    int valor = 0;
    tipovertice nuevoVertice1, nuevoVertice2;
    
    fp = fopen("grafocompleto.txt","r");
    
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    //Guarda todas las cadenas como vertices hasta que se encuentra con el caracter '*'
    do {
        fscanf(fp," %s",linea);
        bandera = strcmp(linea,"*");
        
        if (bandera != 0) {
            strcpy(nuevoVertice1.nombreHabitacion,linea);
            insertar_vertice(G,nuevoVertice1);
        }

    } while (bandera != 0);
    
    //Guarda todos los arcos del archivo hasta que la funcion fscanf retorna el valor EOF que significa sin del archivo
    do {
        bandera = fscanf(fp," %s",linea);
        sscanf(linea,"%[^-.]%[-.]%d-%s",nuevoVertice1.nombreHabitacion,(char *) &codigos, &valor, nuevoVertice2.nombreHabitacion);
        
        if ( codigos == '.') {
            crear_arco_I(G,posicion(*G,nuevoVertice1),posicion(*G,nuevoVertice2),valor);
        } else {
            crear_arco_T(G,posicion(*G,nuevoVertice1),posicion(*G,nuevoVertice2),valor);
        }

    } while (bandera != EOF);
    
    fclose(fp);
}

//Se aplica el algoritmo de floyd_wharsall para dos vertices y imprime por pantalla la ruta optima
void floyd_wharsall (grafo G) {
    int len = num_vertices(G); //Numero vertices en el grafo
    int D[len][len]; //Matriz de caminos 
    struct camino P[len][len]; //Matriz de predecesores
    tipovertice origen; //Vertice origen
    tipovertice destino; //Vertice destino
    char rol; //Rol que indica la matriz de adyacencia que usará el algoritmo
    
    //Entrada de datos por teclado más chequeo
    printf("Que vertice quieres tener como origen?.\n");
    scanf(" %s",origen.nombreHabitacion);   
    
    if (!existe_vertice(G,origen)) {
        printf("El vertice no existe.\n");
        exit(1);
    }
    
    printf("Que vertice quieres tener como destino?.\n");
    scanf(" %s",destino.nombreHabitacion);
    
    if (!existe_vertice(G,destino)) {
        printf("El vertice no existe.\n");
        exit(1);
    }
  
    do{
    printf("Rol?(T-I)\n");
    scanf(" %c",&rol);
    } while (rol != 'T' && rol != 'I');
    
    //Inicializacion matrices para Tripulantes
    if (rol == 'T') {
        for (int i = 0; i < len; i++) {
        for ( int j = 0; j < len; j++) {   
            if (i != j && son_adyacentes_T(G,i,j) != 0) {
                D[i][j] = son_adyacentes_T(G,i,j);    
            } else {
                if (i == j) {
                    D[i][j] = 0;
                } else {
                    D[i][j] = INF;
                }
            }
            if (son_adyacentes_T(G,i,j) != 0 && i != j) {
                P[i][j].verticePredecesor = i;
                P[i][j].mapa = '-';
            } else {
                P[i][j].verticePredecesor = 0;
            }
        }
    }
    //Inicializacion matrices para Impostores
    } else {
        for (int i = 0; i < len; i++) {
        for ( int j = 0; j < len; j++) {   
            if (i != j && son_adyacentes_I(G,i,j) != 0) {
                D[i][j] = son_adyacentes_I(G,i,j);    
            } else {
                if (i == j) {
                    D[i][j] = 0;
                } else {
                    D[i][j] = INF;
                }
            }
            if (son_adyacentes_I(G,i,j) != 0 && son_adyacentes_T(G,i,j) != 0 && i != j) {
                P[i][j].verticePredecesor = i;
                if (son_adyacentes_T(G,i,j) != son_adyacentes_I(G,i,j)) {
                    P[i][j].mapa = '.';
                } else {
                    P[i][j].mapa = '-';
                }
            } else {
                P[i][j].verticePredecesor = 0;
            }
        }
    }
    }
    
    //Algoritmo de Floyd-Wharsall
    for (int k = 0; k < len; k++) {
        for ( int i = 0; i < len; i++) {
            for ( int j = 0; j < len; j++) {
                if (D[i][j] > 
                        D[i][k] + D[k][j]) {
                    D[i][j] =
                            D[i][k] + D[k][j];
                    P[i][j].verticePredecesor = P[k][j].verticePredecesor;  
                    P[i][j].mapa = P[k][j].mapa;
                }
            }
        }
    }
    
    tipovertice *vertices = array_vertices(G);
    //Impresion del camino con una función privada
    _imprimir_camino(P, posicion(G,origen), posicion(G,destino), vertices);
}


//Función privada que imprime el camino
void _imprimir_camino (struct camino P[][MAXVERTICES], int origen, int destino, 
        tipovertice *vertices){
    
    if (origen != destino) {
        _imprimir_camino(P, origen, P[origen][destino].verticePredecesor, vertices);
    }
    
    if (P[origen][destino].mapa == '.') {
        printf("..%s ",vertices[destino].nombreHabitacion);
    } else {
        printf("--%s ",vertices[destino].nombreHabitacion);
    }    
}

//Se aplica el algoritmo de prim y se obtiene el arbol de coste minimo
void prim(grafo G) {
    int numVertices = num_vertices(G); //Numero de vertices
    int selected[numVertices]; //Array para saber que vertices están ya seleccionados
    int numArcos = 0; //Arcos totales
    int distanciaTotal = 0;//Distancia del arbol
    tipovertice *vertices = array_vertices(G); //Array de vertices
    char tipoArco; //Tipo del arco (I/T)
    char rol; //Rol para indicar que tipo de arbol de costes minimos se quiere calcular, el de impostores o el de tripulantes
    
    //Inicializacion del array selected que indica que ningún vertice a sido seleccionado aun
    for (int i = 0; i < numVertices; i++) {
        selected[i] = 0;
    }
    
    //Seleccion del primer vertice
    selected[0] = 1;
    
    //Seleccion rol
    do{
        printf("Para que Rol quieres calcular el árbol de coste mínimo? (T/I) ");
        scanf(" %c",&rol);
    }while (rol != 'T' && rol != 'I');
    
    //Algoritmo para tripulantes
    if (rol == 'T') {
        while (numArcos < numVertices - 1){
        int minimo = INF;
        int vx = 0; 
        int vy = 0;
        
        for (int i = 0; i < numVertices; i++) {
            if (selected[i] == 1) {
                for (int j = 0; j < numVertices; j++) {
                    if (selected[j] == 0 && son_adyacentes_T(G,i,j) > 0) {
                        if (minimo > son_adyacentes_T(G,i,j)) {
                            minimo = son_adyacentes_T(G,i,j);
                            vx = i;
                            vy = j;
                        }
                    }
                }
            }
        }
        selected[vy] = 1;
        numArcos++;
        printf("\t%s - %s: %d\n",vertices[vx].nombreHabitacion,
                vertices[vy].nombreHabitacion,minimo);
        distanciaTotal += minimo;
    }
    //Algoritmo para impostores
    } else {
        while (numArcos < numVertices - 1){
        int minimo = INF;
        int vx = 0; 
        int vy = 0;
        
        for (int i = 0; i < numVertices; i++) {
            if (selected[i] == 1) {
                for (int j = 0; j < numVertices; j++) {
                    if (selected[j] == 0 && son_adyacentes_I(G,i,j) > 0) {
                        if (minimo > son_adyacentes_I(G,i,j)) {
                            minimo = son_adyacentes_I(G,i,j);
                            if (son_adyacentes_I(G,i,j) != son_adyacentes_T(G,i,j)) {
                                tipoArco = '.';
                            } else {
                                tipoArco = '-';
                            }
                            vx = i;
                            vy = j;
                        }
                    }
                }
            }
        }
        selected[vy] = 1;
        numArcos++;
        printf("\t%s %c %s: %d\n",vertices[vx].nombreHabitacion, tipoArco,
                vertices[vy].nombreHabitacion,minimo);
        distanciaTotal += minimo;
    }
    }
    
    printf("Distancia Total del árbol de expansión de coste mínimo = %d\n",distanciaTotal);
}