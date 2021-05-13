#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647/2
#define INFINITO INT_MAX;

int **criaGrafo(int *numeroVertices);
void insereVertices(int **grafo, int linha, int coluna, int peso);
void insereManual(int **grafo, int numeroVertices);
void listarGrafo(int **grafo, int numeroVertices);
void dijkstra(int **grafo, int pInicial, int pFinal, int numeroVertices);
void menu(int **grafo, int numeroVertices);
void clear(int **grafo, int numeroVertices);

int main() {
    int **grafo = NULL, numeroVertices, pInicial, pFinal, opcao;
    
    /* Cria o grafo e inicializa com valores */
    grafo = criaGrafo(&numeroVertices);

    /* Define se quer alterar os pesos do grafo ou utilizar pesos já definidos */
    menu(grafo, numeroVertices);

    do {
        printf("Informe o ponto Inicial: ");
        scanf("%d", &pInicial);

        printf("Informe o ponto Final: ");
        scanf("%d", &pFinal);


        /* Aplica o algoritmo de dijkstra */
        dijkstra(grafo, pInicial, pFinal, numeroVertices);

        printf("Calcular outro caminho(0.Nao 1.Sim): ");
        scanf("%d", &opcao);

    } while (opcao != 0);

    clear(grafo, numeroVertices);
    
    return 0;
}

int **criaGrafo(int *numeroVertices) {
    int **novoGrafo = NULL, i, j;
    do {
        printf("Informe o numero de vertices: ");
        scanf("%d", numeroVertices);

    } while (*numeroVertices < 1 || *numeroVertices > 20);

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

void insereVertices(int **grafo, int linha, int coluna, int peso) {
    grafo[linha][coluna] = peso;
}

void dijkstra(int **grafo, int pInicial, int pFinal, int numeroVertices) {
    int distancia[numeroVertices], predecessor[numeroVertices], visitado[numeroVertices], contVertices = 0, menorDistancia, indexMenor = pFinal, i;
    
    /* Inicializa os vetores auxiliares */
    for (i = 0; i < numeroVertices; i++) {
        distancia[i] = grafo[pInicial][i];
        predecessor[i] = pInicial;
        visitado[i] = 0;
    }
    /* Estabelece a distância do vértice para ele mesmo é zero e marca como visitado */
    distancia[pInicial] = 0;
    visitado[pInicial] = 1;
    contVertices++;

   while (contVertices < numeroVertices) {
        menorDistancia = INFINITO;

        /* Vértices que possuem conexão e ainda não foram visitados */
        for (i = 0; i < numeroVertices; i++) {
            if (distancia[i] < menorDistancia && !visitado[i]) {
                menorDistancia = distancia[i];
                indexMenor = i;
            }
        }

        /* Marca o vértice que está sendo visitado */
        visitado[indexMenor] = 1;

        /* Verifica os vértices que não foram visitados para procurar se existe caminho melhor */
        for (i = 0; i < numeroVertices; i++) {
            if (!visitado[i])
                /* Se não foi visitado e o caminho é menor, atualiza os vetores auxiliares */
                if (menorDistancia + grafo[indexMenor][i] < distancia[i]) {
                    distancia[i] = menorDistancia + grafo[indexMenor][i];
                    predecessor[i] = indexMenor;
                }
        }

        contVertices++;
    }

    printf("Distancia = %d\n", distancia[pFinal]);
    printf("Caminho = %d ", pFinal);

    do {
        pFinal = predecessor[pFinal];
        printf("%d ", pFinal);
    } while (pFinal != pInicial);

    printf("\n");
}

void listarGrafo(int **grafo, int numeroVertices) {
    int i, j;

    for (i = 0; i < numeroVertices; i++) {
        for (j = 0; j < numeroVertices; j++) 
            printf("%d ", grafo[i][j]);
        printf("\n");
    }
}

void insereManual(int **grafo, int numeroVertices) {
    int linha, coluna;

    for (linha = 0; linha < numeroVertices; linha++) {
        for (coluna = 0; coluna < numeroVertices; coluna++) {
            printf("[%d, %d]: ", linha, coluna);
            scanf("%d", &grafo[linha][coluna]);
        }
    }
}

void menu(int **grafo, int numeroVertices) {
    int opcao;

    do {
        printf("1.Gerar Grafo Automatico\n2.Gerar Grafo Manualmente\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: insereVertices(grafo, 0, 1, 10);
                    insereVertices(grafo, 0, 3, 5);
                    insereVertices(grafo, 1, 2, 1);
                    insereVertices(grafo, 2, 4, 4);
                    insereVertices(grafo, 2, 5, 4);
                    insereVertices(grafo, 3, 1, 3);
                    insereVertices(grafo, 3, 2, 8);
                    insereVertices(grafo, 3, 4, 2);
                    insereVertices(grafo, 4, 5, 6);
                    break;

            case 2: insereManual(grafo, numeroVertices);
                    break;
            
            default: printf("Informe uma opcao valida\n");
                     break;
        }
    } while (opcao != 1 && opcao != 2);
}

void clear(int **grafo, int numeroVertices) {
    int linha;

    for (linha = 0; linha < numeroVertices; linha++) 
        free(grafo[linha]);
    

    free(grafo);
}