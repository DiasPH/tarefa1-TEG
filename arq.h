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

void addAresta(struct Grafo grafo, int origem, int destino){
    struct Nodo* novoNodo = criaNodo(destino);
    novoNodo->proximo = grafo->listAdj[origem];
    grafo->listAdj[origem] = novoNodo;

    novoNodo = criaNodo(origem);
    novoNodo->proximo = grafo->listAdj[destino];
    grafo->listAdj[destino] = novoNodo;
}