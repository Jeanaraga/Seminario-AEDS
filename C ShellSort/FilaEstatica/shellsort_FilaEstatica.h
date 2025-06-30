#ifndef SHELLSORT_FILAESTATICA_H
#define SHELLSORT_FILAESTATICA_H


#define MAX_FILA 1000000

#include "../config.h"


typedef struct {
    int id;
    int movieID;
    float nota;
    int timestamp;
} Usuarios;

typedef struct {
    Usuarios dados[MAX_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializarFila(Fila* f);
int filaVazia(Fila* f);
int filaCheia(Fila* f);
int enfileirar(Fila* f, Usuarios u);
int desenfileirar(Fila* f, Usuarios* u);
void shellsort(Usuarios usuarios[], int n);
int estaOrdenado(Usuarios usuarios[], int n);
int lerCSV(const char* nomeArquivo, Fila* f);

#endif
