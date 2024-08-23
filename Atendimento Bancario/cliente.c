#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

// Definindo o tempo das operacoes em segundos
#define TEMPO_SAQUE 50
#define TEMPO_DEPOSITO 70
#define TEMPO_PAGAMENTO 100
#define TEMPO_TRANSFERENCIA 60

// Funcao para criar um novo cliente
Cliente* criarCliente(int id, Prioridade prioridade) {
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente)); // Aloca memoria para um novo cliente
    novoCliente->id = id; // Define o ID do cliente
    novoCliente->prioridade = prioridade; // Define a prioridade do cliente
    novoCliente->tempoOperacoes = 0; // Inicializa o tempo total como 0
    novoCliente->tempoEspera = 0; // Inicializa o tempo de espera como 0
    novoCliente->anterior = NULL; // Define o ponteiro anterior como nulo
    novoCliente->proximo = NULL; // Define o proximo cliente como NULL
    return novoCliente; // Retorna o ponteiro para o novo cliente
}

// Funcao para converter numero de prioridade para enum
Prioridade converterPrioridade(int prioridadeNum) {
    switch (prioridadeNum) {
        case 1: return ALTA; // Se prioridadeNum e 1, retorna ALTA
        case 2: return MEDIA; // Se prioridadeNum e 2, retorna MEDIA
        case 3: return BAIXA; // Se prioridadeNum e 3, retorna BAIXA
        default: return BAIXA; // Se prioridadeNum e invalido, retorna BAIXA como padrao
    }
}

// Funcao para inserir o cliente na lista com base na prioridade
void inserirCliente(Cliente** cabeca, int id, Prioridade prioridade) {
    Cliente* novoCliente = criarCliente(id, prioridade); // Cria um novo cliente

    // Verifica se a lista esta vazia ou se o novo cliente tem prioridade maior (menor numero) que o primeiro da lista
    if (*cabeca == NULL || (*cabeca)->prioridade > prioridade) {
        novoCliente->proximo = *cabeca; // O proximo do novo cliente é o antigo primeiro da lista
        if (*cabeca != NULL) {
            (*cabeca)->anterior = novoCliente; // O anterior do antigo primeiro cliente agora aponta para o novo cliente
        }
        *cabeca = novoCliente; // O novo cliente se torna o primeiro da lista
    } else {
        Cliente* atual = *cabeca; // Comeca a partir do inicio da lista

        // Percorre a lista para encontrar a posicao correta para inserir o novo cliente
        while (atual->proximo != NULL && atual->proximo->prioridade <= prioridade) {
            atual = atual->proximo; // Move para o proximo cliente na lista
        }
        novoCliente->proximo = atual->proximo; // O proximo do novo cliente e o proximo cliente na lista
        if (atual->proximo != NULL) {
            atual->proximo->anterior = novoCliente; // O anterior do proximo cliente aponta para o novo cliente
        }
        atual->proximo = novoCliente; // O proximo do cliente atual e o novo cliente
        novoCliente->anterior = atual; // O anterior do novo cliente e o cliente atual
    }
}

// Funcao para liberar a memoria da lista
void liberarLista(Cliente* cabeca) {
    Cliente* atual;
    // Loop para liberar todos os clientes da lista
    while (cabeca != NULL) {
        atual = cabeca; // Armazena o cliente atual
        cabeca = cabeca->proximo; // Move para o proximo cliente
        free(atual); // Libera a memoria do cliente atual
    }
}

// Funcao para realizar operacoes e calcular tempo total
void realizarOperacoes(Cliente* cabeca) {
    Cliente* aux = cabeca; // Define uma variavel auxiliar para o tipo Cliente*
    while (aux != NULL) { // Percorre todos os clientes na lista
        int opcao;
        aux->tempoOperacoes = 0; // Reinicia o tempo total para cada cliente

        // Solicita ao usuario as operacoes a serem realizadas para o cliente atual
        printf("\nEscolha as operacoes a serem realizadas (0 para terminar):\n");
        printf("Cliente ID: %d\n", aux->id);
        printf("1 - Saque (50s)\n");
        printf("2 - Deposito (70s)\n");
        printf("3 - Pagamento (100s)\n");
        printf("4 - Transferencia (60s)\n");

        // Loop para capturar a opcao do usuario ate que ele escolha 0
        while (1) {
            printf("Digite a opcao (0 para terminar): ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: aux->tempoOperacoes += TEMPO_SAQUE; break; // Adiciona o tempo do saque
                case 2: aux->tempoOperacoes += TEMPO_DEPOSITO; break; // Adiciona o tempo do deposito
                case 3: aux->tempoOperacoes += TEMPO_PAGAMENTO; break; // Adiciona o tempo do pagamento
                case 4: aux->tempoOperacoes += TEMPO_TRANSFERENCIA; break; // Adiciona o tempo da transferencia
                case 0: break; // Encerra a captura de operacoes
                default: printf("Opcao invalida! Tente novamente.\n"); // Mensagem para opcoes invalidas
            }

            if (aux->anterior != NULL) {
                aux->tempoEspera = aux->anterior->tempoEspera + aux->anterior->tempoOperacoes;
            } else {
                aux->tempoEspera = 0;
            }

            if (opcao == 0) break; // Sai do loop quando a opcao e 0
        }
        aux = aux->proximo; // Move para o proximo cliente na lista
    }
}

// Funcao para imprimir o relatorio dos clientes com tempo total
void imprimirRelatorio(Cliente* cabeca) {
    Cliente* aux = cabeca;
    int contador = 0;  // Contador para o numero de clientes
    int tempo_total_atendimento = 0;
    // Imprime o relatorio dos clientes
    printf("\nRelatorio dos clientes em ordem de prioridade:\n");
    printf("+------------+------------+---------------------+--------------------------+-----------------+\n");
    printf("| Cliente ID | Prioridade | Tempo de Espera (s) | Tempo em Operacaoes (s) | Tempo Total (s)  |\n");
    printf("+------------+------------+---------------------+--------------------------+-----------------+\n");

    while (aux != NULL) { // Percorre todos os clientes na lista
        char* prioridadeStr;
        // Converte o valor da prioridade para uma string legivel
        switch (aux->prioridade) {
            case ALTA: prioridadeStr = "Alta"; break;
            case MEDIA: prioridadeStr = "Media"; break;
            case BAIXA: prioridadeStr = "Baixa"; break;
        }

        // Imprime o ID, prioridade e tempo total do cliente
        printf("| %-10d | %-10s | %-17d | %-24d | %-15d   |\n",
            aux->id, prioridadeStr, aux->tempoEspera, aux->tempoOperacoes, aux->tempoEspera + aux->tempoOperacoes);
        tempo_total_atendimento += aux->tempoEspera + aux->tempoOperacoes;
        aux = aux->proximo; // Move para o proximo cliente na lista
        contador++; // Incrementa o contador de clientes
    }

    printf("+------------+------------+---------------------+--------------------------+-----------------+\n");
    // Imprime o total de clientes atendidos
    printf("\nTotal de clientes atendidos: %d\n", contador);
    printf("\nTempo total destinado ao atendimento dos clientes: %ds\n", tempo_total_atendimento);
}
