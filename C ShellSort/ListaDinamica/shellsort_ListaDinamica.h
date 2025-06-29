#ifndef SHELLSORT_LISTADINAMICA_H
#define SHELLSORT_LISTADINAMICA_H

#define LINHA_MAX 100
#define MAX 100

typedef struct {
    int id;
    int movieID;
    float nota;
    int timestamp;
} Usuarios;

void shellsort(Usuarios usuarios[], int n);
int estaOrdenado(Usuarios usuarios[], int n);
int lerCSV(const char* nomeArquivo, Usuarios** lista);

#endif
