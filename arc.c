#include <stdio.h>
#include <stdlib.h>
#include "arq.h"

//funções gerais

void addAresta(struct Grafo* grafo, int origem, int destino){
  struct Nodo* novoNodo = criaNodo(destino);
  novoNodo->proximo = grafo->listAdj[origem];
  grafo->listAdj[origem] = novoNodo;

  if(origem != destino){
    novoNodo = criaNodo(origem);
    novoNodo->proximo = grafo->listAdj[destino];
    grafo->listAdj[destino] = novoNodo;
  }
}

void imprimeGrafo(struct Grafo* grafo){
  printf("\n");             
  for(int i = 0; i < grafo->nVertices; i++){
    printf("%d: ", i);
    struct Nodo* atual = grafo->listAdj[i];

    while(atual != NULL){
      printf("%d -> ", atual->vertice);
      atual = atual->proximo;
    }

    printf("NULL\n");
  }
}

//funçoes de sequência gráfica

int grauVertice(struct Grafo* grafo, int vertice){ //funcao que calcula o grau de um vertice
  int grau = 0;

  struct Nodo* temp = grafo->listAdj[vertice];

  while(temp != NULL){

    if(temp->vertice == vertice){ //se for laço conta 2x
      grau += 2;
    }else{
      grau++;
    }
      temp = temp->proximo;
  }

  return grau;
}

int comp(const void *a, const void *b){ //funcao de auxilio para fazer o qsort
  return (*(int*)b - *(int*)a);
}

int* sequenciaGrafica(struct Grafo* grafo){ //retorna sequencia grafica em ordem decrescente
  int* seqGraf = (int*) malloc(grafo->nVertices * sizeof(int));

  for(int i = 0;i < grafo->nVertices;i++){
    int grau = 0;
    grau = grauVertice(grafo, i);

    seqGraf[i] = grau;

  }

  qsort(seqGraf, grafo->nVertices, sizeof(int), comp);

  return seqGraf;
}

//determinação de tipo do grafo (simples/multigrafo)

int ehSimples(struct Grafo* grafo){ //verifica se grafo é simples
  if(quantLaco(grafo) == 0 && arestasParalelas(grafo) == 0){
    return 1;
  }else{
    return 0;
  }
}

int arestasParalelas(struct Grafo* grafo){
  int count = 0;

  for(int i = 0; i < grafo->nVertices; i++){
    struct Nodo* atual = grafo->listAdj[i];

    while(atual != NULL){

      struct Nodo* aux = atual->proximo;

      while(aux != NULL){
        if(atual->vertice == aux->vertice){
          count++;//adiciona aresta paralela ao contador
        }
        aux = aux->proximo;
      }

      atual = atual->proximo;
    }
  }

    return count;//retorna quantidade de arestas paralelas
}

int quantLaco(struct Grafo* grafo){
  int count = 0;
  for(int i = 0; i < grafo->nVertices; i++){
    struct Nodo* atual = grafo->listAdj[i];

    while(atual != NULL){
      if(atual->vertice == i){
        count++;
      }

      atual = atual->proximo;
    }
  }

  return count; //retorna quantidade de lacos
}

//componentes conexos

void dfs(struct Grafo* grafo, int vertice, int componente[], int vetMarca[], int* tamanho){
  vetMarca[vertice] = 1;
  componente[(*tamanho)++] = vertice;

  struct Nodo* atual = grafo->listAdj[vertice];

  while(atual != NULL){
    int v = atual->vertice;

    if(vetMarca[v]==0){
      dfs(grafo, v, componente, vetMarca, tamanho);
    }

    atual = atual->proximo;
  }
}

void componentesConexos(struct Grafo* grafo){
  int* vetMarca = (int*) calloc(grafo->nVertices, sizeof(int));
  int qtdComponentes = 0;

  for(int i = 0; i < grafo->nVertices; i++){
    if(vetMarca[i]==0){
      int* componente = (int*) malloc(grafo->nVertices * sizeof(int));
      int tamanho = 0;

      dfs(grafo, i, componente, vetMarca, &tamanho);
      qtdComponentes++;

      printf("Componente %d: { ", qtdComponentes);

      for(int j = 0; j < tamanho; j++){
        printf("%d ", componente[j]);
      }
      printf("} | Tamanho: %d\n", tamanho);
      free(componente);
    }
  } 

  free(vetMarca);
}

//funcao de analise

void info(struct Grafo* grafo) {
  imprimeGrafo(grafo);

  int* graus = sequenciaGrafica(grafo);
  int maxGrau = graus[0];
  int minGrau = graus[grafo->nVertices - 1];

  printf("\nGrau maximo: %d", maxGrau);
  printf("\nGrau minimo: %d\n", minGrau);

  free(graus);

  if (ehSimples(grafo)) {
      printf("\nO grafo é simples.\n");
  } else {
      printf("\nO grafo é um multigrafo.\n");
      printf("\nQuantidade de arestas paralelas: %d", arestasParalelas(grafo));
      printf("\nQuantidade de lacos: %d", quantLaco(grafo));
  }

  printf("\nComponentes conexos:\n");
  componentesConexos(grafo);
}

int main(){
  printf("\nExemplo 1\n");
  struct Grafo* grafo1 = criaGrafo(4);

  addAresta(grafo1, 0, 1);
  addAresta(grafo1, 0, 2);
  addAresta(grafo1, 0, 3);
  addAresta(grafo1, 2, 1);
  addAresta(grafo1, 2, 3);

  info(grafo1);

  printf("\nExemplo 2\n");
  struct Grafo* grafo2 = criaGrafo(5);

  addAresta(grafo2, 0, 1);
  addAresta(grafo2, 0, 4);
  addAresta(grafo2, 0, 4);
  addAresta(grafo2, 1, 1);
  addAresta(grafo2, 1, 2);
  addAresta(grafo2, 1, 2);
  addAresta(grafo2, 2, 3);
  addAresta(grafo2, 3 , 4);

  info(grafo2);

  printf("\nExemplo 3\n");
  struct Grafo* grafo3 = criaGrafo(8);

  addAresta(grafo3, 0, 1);
  addAresta(grafo3, 1, 2);
  addAresta(grafo3, 3, 4);
  addAresta(grafo3, 5, 6);
  addAresta(grafo3, 6, 7);

  info(grafo3);   

  return 0;
}
