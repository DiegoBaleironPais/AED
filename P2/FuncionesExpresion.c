#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilaOperadores.h"
#include "pilaOperandos.h"
#include "abin.h"
#include "FuncionesExpresion.h"
#include "recorridos.h"

void introducirPilaOperandos(char aux, pilaOperandos *piladOperandos );

void segundoIf ( char aux, pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

void tercerIf ( pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

abin vaciarPilaOperadores ( pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

void desapilarOperandos(char *caux, abin *arbol, pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos);

//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 0; //nunca va a entrar en la pila, provoca vaciado
            break;
    }
    return prior;
}

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op) {
    int prior;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 4; //para que SIEMPRE entre en la pila
            break;
    }
    return prior;
}

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c) {
    unsigned ope;
    switch (c) {
        case '^': case '*': case '/': case '+': case '-': case '(':
            ope = 1;
            break;
        default:
            ope = 0;
    }
    return ope;
}

//Devuelve 1 si c es un operando: mayúsculas y minúsculas
//completar para caracteres 0 a 9
unsigned esOperando(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48  && c <= 57))
        return 1;
    else
        return 0;
}

//Recibe una cadena de caracteres y devuelve el arbol de expresion
//DEBES ESCRIBIR ESTA FUNCIÓN
abin arbolExpresion(char expr_infija[]) {

    pilaOperandos piladOperandos;
    pilaOperadores piladOperadores;
    char aux;
    
    crearPilaAndos(&piladOperandos);
    crearPilaDores(&piladOperadores);

    
    for ( int i = 0; i < strlen(expr_infija); i++ ) {
        
        aux = expr_infija[i];
        
        if ( esOperando(aux) ) {
            
            introducirPilaOperandos(aux,&piladOperandos);
        
        } else {
            if ( esOperador(aux) ) {
                
                segundoIf(aux, &piladOperadores, &piladOperandos);
                
            } else {
                
                if ( aux == ')' ){
                    
                    tercerIf(&piladOperadores, &piladOperandos);
                    
                }
            }
        }
        
    }
    
    return vaciarPilaOperadores(&piladOperadores, &piladOperandos);
    
}

void introducirPilaOperandos(char aux, pilaOperandos *piladOperandos ) {
    
    abin nuevo;
    
    crear(&nuevo);
    insder(&nuevo,aux);
    pushAndos(piladOperandos,nuevo);
    nuevo = NULL;
    
}

void segundoIf ( char aux, pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos) {
    
    char caux;
    abin arbol;
    
    while (!esVacio(*piladOperadores) 
            && (prioridadFuera(aux) 
            <= prioridadDentro(topeDores(*piladOperadores)))) {
        
        desapilarOperandos(&caux, &arbol, piladOperadores, piladOperandos);
        
        
    }
    
    pushDores(piladOperadores,aux);
 
}

void tercerIf ( pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos) {
    
    char caux;
    abin arbol;
    
    while ( topeDores(*piladOperadores) != '(' ) {
        
        desapilarOperandos(&caux, &arbol, piladOperadores, piladOperandos);
        
    }
    
    popDores(piladOperadores);
    
 
}

abin vaciarPilaOperadores ( pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos) {
    
    char caux;
    abin arbol;
    
    while ( !esVaciaPilaDores(*piladOperadores) ) {
        
       desapilarOperandos(&caux, &arbol, piladOperadores, piladOperandos);
        
    }
    
    destruirPilaDores(piladOperadores);
    arbol = topeAndos(*piladOperandos);
    destruirPilaAndos(piladOperandos);
    
    return arbol;
}

void desapilarOperandos(char *caux, abin *arbol, pilaOperadores *piladOperadores, 
        pilaOperandos *piladOperandos) {
    
        *caux = topeDores(*piladOperadores);
        popDores(piladOperadores);
        crear(arbol);
        insder(arbol,*caux);
        insArbolder(arbol,topeAndos(*piladOperandos));
        popAndos(piladOperandos);
        insArbolizq(arbol,topeAndos(*piladOperandos));
        popAndos(piladOperandos);
        pushAndos(piladOperandos,*arbol);
        
}
