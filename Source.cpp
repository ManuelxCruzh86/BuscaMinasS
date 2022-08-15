

#include <windows.h>
#include <assert.h>  
#include <ctype.h>   
#include <stdio.h>   
#include <stdlib.h>  


#define ERROR_MINA_ENCONTRADA 1
#define ERROR_ESPACIO_YA_DESCUBIERTO 2
#define ERROR_NINGUNO 3

#define COLUMNAS 6
#define FILAS 6
#define ESPACIO_SIN_DESCUBRIR '.'
#define ESPACIO_DESCUBIERTO ' '
#define MINA '*'
#define CANTIDAD_MINAS \
  6  
#define DEBUG 0  


int main() {
    printf("BUSCAMINAS\n");
    char tablero[FILAS][COLUMNAS];
    int deberiaMostrarMinas = 0;


    iniciarTablero(tablero);
    colocarMinasAleatoriamente(tablero);
    while (1) {
        imprimirTablero(tablero, deberiaMostrarMinas);
        if (deberiaMostrarMinas) {
            break;
        }
        int columna;
        char fila;
        printf("Ingresa la fila: ");
        scanf(" %c", &fila);
        printf("Ingresa la columna: ");
        scanf("%d", &columna);
        int status = abrirCasilla(fila, columna, tablero);
        if (noHayCasillasSinAbrir(tablero)) {
            printf("Has ganado\n");
            deberiaMostrarMinas = 1;
        }
        else if (status == ERROR_ESPACIO_YA_DESCUBIERTO) {
            printf("Ya has abierto esta casilla\n");
        }
        else if (status == ERROR_MINA_ENCONTRADA) {
            printf("Has perdido\n");
            deberiaMostrarMinas = 1;
        }
    }
    return 0;
}

int abrirCasilla(char filaLetra, int columna, char tablero[FILAS][COLUMNAS]) {

    filaLetra = toupper(filaLetra);
    columna--;
    int fila = filaLetra - 'A';
    assert(columna < COLUMNAS&& columna >= 0);
    assert(fila < FILAS&& fila >= 0);
    if (tablero[fila][columna] == MINA) {
        return ERROR_MINA_ENCONTRADA;
    }
    if (tablero[fila][columna] == ESPACIO_DESCUBIERTO) {
        return ERROR_ESPACIO_YA_DESCUBIERTO;
    }
    tablero[fila][columna] = ESPACIO_DESCUBIERTO;
    return ERROR_NINGUNO;
}

int noHayCasillasSinAbrir(char tablero[FILAS][COLUMNAS]) {
    int i;
    for (i = 0; i < FILAS; i++) {
        int m;
        for (m = 0; m < COLUMNAS; m++) {
            char actual = tablero[i][m];
            if (actual == ESPACIO_SIN_DESCUBRIR) {
                return 0;
            }
        }
    }
    return 1;
}


int obtenerMinasCercanas(int fila, int columna, char tablero[FILAS][COLUMNAS]) {
    int conteo = 0, filaInicio, filaFin, columnaInicio, columnaFin;
    if (fila <= 0) {
        filaInicio = 0;
    }
    else {
        filaInicio = fila - 1;
    }

    if (fila + 1 >= FILAS) {
        filaFin = FILAS - 1;
    }
    else {
        filaFin = fila + 1;
    }

    if (columna <= 0) {
        columnaInicio = 0;
    }
    else {
        columnaInicio = columna - 1;
    }
    if (columna + 1 >= COLUMNAS) {
        columnaFin = COLUMNAS - 1;
    }
    else {
        columnaFin = columna + 1;
    }
    int m;
    for (m = filaInicio; m <= filaFin; m++) {
        int l;
        for (l = columnaInicio; l <= columnaFin; l++) {
            if (tablero[m][l] == MINA) {
                conteo++;
            }
        }
    }
    return conteo;
}


void iniciarTablero(char tablero[FILAS][COLUMNAS]) {
    int i;
    for (i = 0; i < FILAS; i++) {
        int m;
        for (m = 0; m < COLUMNAS; m++) {
            tablero[i][m] = ESPACIO_SIN_DESCUBRIR;
        }
    }
}

void colocarMinasAleatoriamente(char tablero[FILAS][COLUMNAS]) {
    int i;
    

    for (i = 0; i < CANTIDAD_MINAS; i++) {
        int fila = aleatorioEnRango(0, FILAS - 1);
        int columna = aleatorioEnRango(0, COLUMNAS - 1);
        colocarMina(fila, columna, tablero);
    }
}


