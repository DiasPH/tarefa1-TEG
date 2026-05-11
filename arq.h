#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Nodo{
    int vertice;
    struct Nodo* proximo;
};

struct Grafo{
    int nVertices;
    struct Nodo** listAdj;
};

struct Nodo* criaNodo(int v){
    struct Nodo* novoNodo = malloc(sizeof(struct Nodo));
    novoNodo->vertice = v;
    novoNodo->proximo = NULL;
    return novoNodo;
}

struct Grafo* criaGrafo(int vertices){
    struct Grafo* grafo = malloc(sizeof(struct Grafo));
    grafo->nVertices = vertices;

    grafo->listAdj = malloc(vertices * sizeof(struct Node*));

    for(int i = 0; i < vertices; i++){
        grafo->listAdj[i] = NULL;
    }

    return grafo;
}

void addAresta(struct Grafo* grafo, int origem, int destino);
int grauVertice(struct Grafo* grafo, int vertice);
int* sequenciaGrafica(struct Grafo* grafo);
int comp(const void *a, const void *b);
int arestasParalelas(struct Grafo* grafo);
int quantLaco(struct Grafo* grafo);
void imprimeGrafo(struct Grafo* grafo);
int ehSimples(struct Grafo* grafo);
void dfs(struct Grafo* grafo, int vertice, int componente[], int vetMarca[], int* index);
void componentesConexos(struct Grafo* grafo);   
void info(struct Grafo* grafo);