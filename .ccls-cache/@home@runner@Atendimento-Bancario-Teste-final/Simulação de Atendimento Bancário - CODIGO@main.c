#include <stdio.h>
#include "cliente.h"

// Funcao principal do programa
int main() {
    // Inicializa a fila de clientes como nula
    Cliente* fila = NULL;

    // Variavel para armazenar o numero de clientes
    int numClientes;

    // Variavel para armazenar o valor numerico da prioridade
    int prioridadeNum;

    // Variavel para armazenar a prioridade convertida
    Prioridade prioridade;

    // Contador de ID para atribuir IDs unicos aos clientes
    int idCounter = 1; // Contador de ID baseado na ordem de chegada

    // Solicita ao usuario o numero de clientes
    printf("Digite o numero de clientes: ");
    scanf("%d", &numClientes);

    // Loop para adicionar os clientes a fila
    for (int i = 0; i < numClientes; i++) {
        // Solicita ao usuario a prioridade do cliente
        printf("Digite a prioridade do cliente %d (1 - Alta, 2 - Media, 3 - Baixa): ", i + 1);
        scanf("%d", &prioridadeNum);

        // Converte a prioridade numerica para o tipo Prioridade
        prioridade = converterPrioridade(prioridadeNum);

        // Insere o cliente na fila com um ID automatico baseado na ordem de chegada
        inserirCliente(&fila, idCounter++, prioridade);
    }

    // Realiza as operacoes para cada cliente na fila e calcula o tempo total
    realizarOperacoes(fila);

    // Imprime o relatorio com o tempo total das operacoes de cada cliente
    imprimirRelatorio(fila);

    // Libera a memoria alocada para a lista de clientes
    liberarLista(fila);

    return 0;
}
