#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

// Definindo o tempo das operações em segundos
#define TEMPO_SAQUE 50
#define TEMPO_DEPOSITO 70
#define TEMPO_PAGAMENTO 100
#define TEMPO_TRANSFERENCIA 60

// Função para criar um novo cliente
Cliente* criarCliente(int id, Prioridade prioridade) {
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente)); // Aloca memória para um novo cliente
    novoCliente->id = id; // Define o ID do cliente
    novoCliente->prioridade = prioridade; // Define a prioridade do cliente
    novoCliente->tempoTotal = 0; // Inicializa o tempo total como 0
    novoCliente->proximo = NULL; // Define o próximo cliente como NULL
    return novoCliente; // Retorna o ponteiro para o novo cliente
}

// Função para converter número de prioridade para enum
Prioridade converterPrioridade(int prioridadeNum) {
    switch (prioridadeNum) {
        case 1: return ALTA; // Se prioridadeNum é 1, retorna ALTA
        case 2: return MEDIA; // Se prioridadeNum é 2, retorna MEDIA
        case 3: return BAIXA; // Se prioridadeNum é 3, retorna BAIXA
        default: return BAIXA; // Se prioridadeNum é inválido, retorna BAIXA como padrão
    }
}

// Função para inserir o cliente na lista com base na prioridade
void inserirCliente(Cliente** cabeca, int id, Prioridade prioridade) {
    Cliente* novoCliente = criarCliente(id, prioridade); // Cria um novo cliente
    // Verifica se a lista está vazia ou se o novo cliente tem prioridade maior (menor número) que o primeiro da lista
    if (*cabeca == NULL || (*cabeca)->prioridade > prioridade) {
        novoCliente->proximo = *cabeca; // O próximo do novo cliente é o antigo primeiro da lista
        *cabeca = novoCliente; // O novo cliente se torna o primeiro da lista
    } else {
        Cliente* atual = *cabeca; // Começa a partir do início da lista
        // Percorre a lista para encontrar a posição correta para inserir o novo cliente
        while (atual->proximo != NULL && atual->proximo->prioridade <= prioridade) {
            atual = atual->proximo; // Move para o próximo cliente na lista
        }
        novoCliente->proximo = atual->proximo; // O próximo do novo cliente é o próximo cliente na lista
        atual->proximo = novoCliente; // O próximo do cliente atual é o novo cliente
    }
}

// Função para liberar a memória da lista
void liberarLista(Cliente* cabeca) {
    Cliente* atual;
    // Loop para liberar todos os clientes da lista
    while (cabeca != NULL) {
        atual = cabeca; // Armazena o cliente atual
        cabeca = cabeca->proximo; // Move para o próximo cliente
        free(atual); // Libera a memória do cliente atual
    }
}

// Função para realizar operações e calcular tempo total
void realizarOperacoes(Cliente* cabeca) {
    Cliente* atual = cabeca;
    while (atual != NULL) { // Percorre todos os clientes na lista
        int opcao;
        atual->tempoTotal = 0; // Reinicia o tempo total para cada cliente

        // Solicita ao usuário as operações a serem realizadas para o cliente atual
        printf("\nEscolha as operações a serem realizadas (0 para terminar):\n");
        printf("Cliente ID: %d\n", atual->id);
        printf("1 - Saque (50s)\n");
        printf("2 - Depósito (70s)\n");
        printf("3 - Pagamento (100s)\n");
        printf("4 - Transferência (60s)\n");

        // Loop para capturar a opção do usuário até que ele escolha 0
        while (1) {
            printf("Digite a opção (0 para terminar): ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: atual->tempoTotal += TEMPO_SAQUE; break; // Adiciona o tempo do saque
                case 2: atual->tempoTotal += TEMPO_DEPOSITO; break; // Adiciona o tempo do depósito
                case 3: atual->tempoTotal += TEMPO_PAGAMENTO; break; // Adiciona o tempo do pagamento
                case 4: atual->tempoTotal += TEMPO_TRANSFERENCIA; break; // Adiciona o tempo da transferência
                case 0: // Caso o usuário digite 0, encerra a captura de operações
                    break;
                default: printf("Opção inválida! Tente novamente.\n"); // Mensagem para opções inválidas
            }
            if (opcao == 0) break; // Sai do loop quando a opção é 0
        }

        atual = atual->proximo; // Move para o próximo cliente na lista
    }
}

// Função para imprimir o relatório dos clientes com tempo total
void imprimirRelatorio(Cliente* cabeca) {
    Cliente* atual = cabeca;
    int contador = 0; // Contador para o número de clientes

    // Imprime o relatório dos clientes
    printf("\nRelatório dos clientes em ordem de prioridade:\n");
    while (atual != NULL) { // Percorre todos os clientes na lista
        char* prioridadeStr;
        // Converte o valor da prioridade para uma string legível
        switch (atual->prioridade) {
            case ALTA: prioridadeStr = "Alta"; break;
            case MEDIA: prioridadeStr = "Média"; break;
            case BAIXA: prioridadeStr = "Baixa"; break;
        }
        // Imprime o ID, prioridade e tempo total do cliente
        printf("Cliente ID: %d, Prioridade: %s, Tempo Total: %d segundos\n",
               atual->id, prioridadeStr, atual->tempoTotal);
        atual = atual->proximo; // Move para o próximo cliente na lista
        contador++; // Incrementa o contador de clientes
    }
    // Imprime o total de clientes atendidos
    printf("\nTotal de clientes atendidos: %d\n", contador);
}
