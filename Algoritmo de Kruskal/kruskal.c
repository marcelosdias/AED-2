#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647/2
#define INFINITO INT_MAX;

typedef struct {
    int origem, destino, peso;
} Arestas;

int **criaGrafo(int *numeroVertices);
void insereArestas(Arestas *vetorArestas, int pInicial, int pFinal, int peso, int *index);
void listarVetor(Arestas *vetorArestas, int numeroArestas);
void kruskal(Arestas *vetorArestas, Arestas *vetorFinal, int numeroArestas, int numeroVertices);
void insertionSort(Arestas *p, int n);
int procura(int *vetorPai, int vertice);
void uniao(int *vetorPai, int *vetorPeso, int vOrigem, int vDestino);
void copiaDados(int **grafo, Arestas *vetorFinal, int numeroArestas);
void listarGrafo(int **grafo, int numeroVertices);
Arestas *insereGrafo(int numeroVertices, int *numeroArestas, int *ehAutomatico);
void clear(int **grafo, Arestas *vetorArestas, Arestas *vetorFinal, int numeroVertices);

int main() {
    Arestas *vetorArestas = NULL, *vetorFinal = NULL;
    int **grafo = NULL, numeroArestas = 14, numeroVertices = 9, index = 0;

    grafo = criaGrafo(&numeroVertices);

    vetorArestas = (Arestas*)malloc(numeroArestas * sizeof(Arestas)); 
    vetorFinal = (Arestas*)malloc((numeroVertices-1) * sizeof(Arestas));

    /* Mesmo grafo utilizado nos Slides */
    insereArestas(vetorArestas, 0, 1, 4, &index);
    insereArestas(vetorArestas, 0, 7, 8, &index);
    insereArestas(vetorArestas, 1, 7, 11, &index);
    insereArestas(vetorArestas, 1, 2, 8, &index);
    insereArestas(vetorArestas, 2, 3, 7, &index);
    insereArestas(vetorArestas, 2, 5, 4, &index);
    insereArestas(vetorArestas, 2, 8, 2, &index);
    insereArestas(vetorArestas, 3, 4, 9, &index);
    insereArestas(vetorArestas, 3, 5, 14, &index);
    insereArestas(vetorArestas, 4, 5, 10, &index);
    insereArestas(vetorArestas, 5, 6, 2, &index);
    insereArestas(vetorArestas, 6, 8, 6, &index);
    insereArestas(vetorArestas, 6, 7, 1, &index);
    insereArestas(vetorArestas, 7, 8, 7, &index);

    printf("Arestas Originais\n");
    listarVetor(vetorArestas, numeroArestas);

    kruskal(vetorArestas, vetorFinal, numeroArestas, numeroVertices);

    printf("Arestas Resultantes\n");
    listarVetor(vetorFinal, numeroVertices-1);

    copiaDados(grafo, vetorFinal, numeroVertices-1);

    listarGrafo(grafo, numeroVertices);

    clear(grafo, vetorArestas, vetorFinal, numeroVertices);

    return 0;
}

void copiaDados(int **grafo, Arestas *vetorFinal, int numeroArestas) {
    int i;

    for (i = 0; i < numeroArestas; i++) {
        grafo[vetorFinal[i].origem][vetorFinal[i].destino] = vetorFinal[i].peso;
        grafo[vetorFinal[i].destino][vetorFinal[i].origem] = vetorFinal[i].peso;
    }
}

int **criaGrafo(int *numeroVertices) {
    int **novoGrafo = NULL, i, j;

    novoGrafo = (int**)malloc((*numeroVertices) * sizeof(int*));

    if (!novoGrafo) {
        printf("Erro ao Alocar memoria\n");
        exit(1);
    }

    for (i = 0; i < *numeroVertices; i++) {
        novoGrafo[i] = (int*)malloc(*numeroVertices * sizeof(int));

        if (!novoGrafo[i]) {
            printf("Erro ao Alocar memoria\n");
            exit(1);
        }
    }

    for (i = 0; i < *numeroVertices; i++) 
        for (j = 0; j < *numeroVertices; j++) 
            novoGrafo[i][j] = INFINITO;
        
    return novoGrafo;
}

void kruskal(Arestas *vetorArestas, Arestas *vetorFinal, int numeroArestas, int numeroVertices) {
    int i, vetorPai[numeroVertices], vetorPeso[numeroVertices], index = 0;

    for (i = 0; i < numeroVertices; i++) {
        vetorPai[i] = i;
        vetorPeso[i] = -1;
    }

    insertionSort(vetorArestas, numeroArestas);


    for (i = 0; i < numeroArestas; i++) {
        if (procura(vetorPai, vetorArestas[i].origem) != procura(vetorPai, vetorArestas[i].destino)) {
            uniao(vetorPai, vetorPeso, vetorArestas[i].origem, vetorArestas[i].destino);
            vetorFinal[index++] = vetorArestas[i];
        }
    }
}

void uniao(int *vetorPai, int *vetorPeso, int vOrigem, int vDestino) {
    vOrigem = procura(vetorPai, vOrigem);
    vDestino = procura(vetorPai, vDestino);

    if(vetorPeso[vOrigem] < vetorPeso[vDestino])
        vetorPai[vOrigem] = vDestino;
    else 
        if(vetorPeso[vDestino] < vetorPeso[vOrigem])
            vetorPai[vDestino] = vOrigem;
        else{
            vetorPai[vOrigem] = vDestino;
            vetorPeso[vOrigem]++;
    }
}

void insereArestas(Arestas *vetorArestas, int pInicial, int pFinal, int peso, int *index) {
    vetorArestas[*index].origem = pInicial;
    vetorArestas[*index].destino = pFinal;
    vetorArestas[*index].peso = peso;
    (*index)++;
}

void insertionSort(Arestas *vetorArestas, int numeroArestas) {
    int i, j;
    Arestas aux;

    for (j = 1; j < numeroArestas; j++) {
        i = j - 1;
        aux = vetorArestas[j];

        while ((i >= 0) && (aux.peso < vetorArestas[i].peso)) {
            vetorArestas[i+1] = vetorArestas[i];
            i--;
        }
        vetorArestas[i+1] = aux;
    }
}

int procura(int *vetorPai, int vertice) {
    if (vetorPai[vertice] == vertice) 
        return vertice;

    return vetorPai[vertice] = procura(vetorPai, vetorPai[vertice]);
}

void listarVetor(Arestas *vetorArestas, int numeroArestas) {
    int i;

    for (i = 0; i < numeroArestas; i++) {
        printf("(%d, %d): %d\n", vetorArestas[i].origem, vetorArestas[i].destino, vetorArestas[i].peso);
    }

    printf("\n");
}

void listarGrafo(int **grafo, int numeroVertices) {
    int i, j;

    printf("Grafo Resultante\n");

    for (i = 0; i < numeroVertices; i++) {
        for (j = 0; j < numeroVertices; j++) 
            printf("%d ", grafo[i][j]);
        printf("\n");
    }
}

void clear(int **grafo, Arestas *vetorArestas, Arestas *vetorFinal, int numeroVertices) {
    int linha;

    for (linha = 0; linha < numeroVertices; linha++) 
        free(grafo[linha]);

    
    free(vetorArestas);
    free(vetorFinal);
    free(grafo);
}