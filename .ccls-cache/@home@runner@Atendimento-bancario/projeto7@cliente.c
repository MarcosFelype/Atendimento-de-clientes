#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

// Definindo o tempo das opera�es em segundos
#define TEMPO_SAQUE 50
#define TEMPO_DEPOSITO 70
#define TEMPO_PAGAMENTO 100
#define TEMPO_TRANSFERENCIA 60

// Fun�o para criar um novo cliente
Cliente* criarCliente(int id, Prioridade prioridade) {
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente)); // Aloca mem�ria para um novo cliente
    novoCliente->id = id; // Define o ID do cliente
    novoCliente->prioridade = prioridade; // Define a prioridade do cliente
    novoCliente->tempoOperacoes = 0; // Inicializa o tempo total como 0
    novoCliente->proximo = NULL; // Define o pr�ximo cliente como NULL
    return novoCliente; // Retorna o ponteiro para o novo cliente
}

// Fun�o para converter n�mero de prioridade para enum
Prioridade converterPrioridade(int prioridadeNum) {
    switch (prioridadeNum) {
        case 1: return ALTA; // Se prioridadeNum � 1, retorna ALTA
        case 2: return MEDIA; // Se prioridadeNum � 2, retorna MEDIA
        case 3: return BAIXA; // Se prioridadeNum � 3, retorna BAIXA
        default: return BAIXA; // Se prioridadeNum � inv�lido, retorna BAIXA como padr�o
    }
}

// Fun�o para inserir o cliente na lista com base na prioridade
void inserirCliente(Cliente** cabeca, int id, Prioridade prioridade) {
    Cliente* novoCliente = criarCliente(id, prioridade); // Cria um novo cliente
    // Verifica se a lista est� vazia ou se o novo cliente tem prioridade maior (menor n�mero) que o primeiro da lista
    if (*cabeca == NULL || (*cabeca)->prioridade > prioridade) {
        novoCliente->proximo = *cabeca; // O pr�ximo do novo cliente � o antigo primeiro da lista
        *cabeca = novoCliente; // O novo cliente se torna o primeiro da lista
    } else {
        Cliente* atual = *cabeca; // Come�a a partir do in�cio da lista
        // Percorre a lista para encontrar a posi�o correta para inserir o novo cliente
        while (atual->proximo != NULL && atual->proximo->prioridade <= prioridade) {
            atual = atual->proximo; // Move para o pr�ximo cliente na lista
        }
        novoCliente->proximo = atual->proximo; // O pr�ximo do novo cliente � o pr�ximo cliente na lista
        atual->proximo = novoCliente; // O pr�ximo do cliente atual � o novo cliente
    }
}

// Fun�o para liberar a mem�ria da lista
void liberarLista(Cliente* cabeca) {
    Cliente* atual;
    // Loop para liberar todos os clientes da lista
    while (cabeca != NULL) {
        atual = cabeca; // Armazena o cliente atual
        cabeca = cabeca->proximo; // Move para o pr�ximo cliente
        free(atual); // Libera a mem�ria do cliente atual
    }
}

// Fun�o para realizar opera�es e calcular tempo total
void realizarOperacoes(Cliente* cabeca) {
    int tempoAcumulado = 0;
    Cliente* atual = cabeca; // Define uma varável auxiliar para o tipo Cliente*
    while (atual != NULL) { // Percorre todos os clientes na lista
        int opcao;
        atual->tempoOperacoes = 0; // Reinicia o tempo total para cada cliente
        //atual->tempoEspera = 0;
        // Solicita ao usu�rio as opera�es a serem realizadas para o cliente atual
        printf("\nEscolha as opera�es a serem realizadas (0 para terminar):\n");
        printf("Cliente ID: %d\n", atual->id);
        printf("1 - Saque (50s)\n");
        printf("2 - Dep�sito (70s)\n");
        printf("3 - Pagamento (100s)\n");
        printf("4 - Transfer�ncia (60s)\n");

        // Loop para capturar a op�o do usu�rio at� que ele escolha 0
        while (1) {
            printf("Digite a op�o (0 para terminar): ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1: atual->tempoOperacoes += TEMPO_SAQUE; break; // Adiciona o tempo do saque
                case 2: atual->tempoOperacoes += TEMPO_DEPOSITO; break; // Adiciona o tempo do dep�sito
                case 3: atual->tempoOperacoes += TEMPO_PAGAMENTO; break; // Adiciona o tempo do pagamento
                case 4: atual->tempoOperacoes += TEMPO_TRANSFERENCIA; break; // Adiciona o tempo da transfer�ncia
                case 0: // Caso o usu�rio digite 0, encerra a captura de opera�es
                    break;
                default: printf("Op�o inv�lida! Tente novamente.\n"); // Mensagem para op�es inv�lidas
            }
            if (opcao == 0) break; // Sai do loop quando a op�o � 0
        } 
        tempoAcumulado += atual->tempoOperacoes;
        //adicionar um ponteiro para identificar o primeiro cliente da fila?
        atual = atual->proximo; // Move para o pr�ximo cliente na lista
    }
}

// Fun�o para imprimir o relat�rio dos clientes com tempo total
void imprimirRelatorio(Cliente* cabeca) {
    Cliente* atual = cabeca;
    int contador = 0; // Contador para o n�mero de clientes

    // Imprime o relat�rio dos clientes
    printf("\nRelat�rio dos clientes em ordem de prioridade:\n");
    while (atual != NULL) { // Percorre todos os clientes na lista
        char* prioridadeStr;
        // Converte o valor da prioridade para uma string leg�vel
        switch (atual->prioridade) {
            case ALTA: prioridadeStr = "Alta"; break;
            case MEDIA: prioridadeStr = "M�dia"; break;
            case BAIXA: prioridadeStr = "Baixa"; break;
        }
        // Imprime o ID, prioridade e tempo total do cliente
        printf("Cliente ID: %d, Prioridade: %s, Tempo Total: %d segundos\n",
               atual->id, prioridadeStr, atual->tempoOperacoes);
        atual = atual->proximo; // Move para o pr�ximo cliente na lista
        contador++; // Incrementa o contador de clientes
    }
    // Imprime o total de clientes atendidos
    printf("\nTotal de clientes atendidos: %d\n", contador);
}
