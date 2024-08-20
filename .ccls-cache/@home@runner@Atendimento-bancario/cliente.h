#ifndef CLIENTE_H // Verifica se CLIENTE_H não está definido
#define CLIENTE_H // Define CLIENTE_H para evitar múltiplas inclusões

// Definindo a enumeração para prioridades
typedef enum {
    BAIXA = 3, // Prioridade baixa com valor 3
    MEDIA = 2, // Prioridade média com valor 2
    ALTA = 1   // Prioridade alta com valor 1
} Prioridade; // Nome do tipo enum: Prioridade

// Estrutura do Cliente
typedef struct Cliente {
    int id;                    // ID do cliente
    Prioridade prioridade;     // Prioridade do cliente (ALTA, MEDIA, BAIXA)
    int tempoTotal;            // Adicionado para armazenar o tempo total das operações do cliente
    struct Cliente* proximo;   // Ponteiro para o próximo cliente na lista
} Cliente; // Nome do tipo struct: Cliente

// Declaração das funções que serão implementadas em cliente.c
Cliente* criarCliente(int id, Prioridade prioridade); // Função para criar um novo cliente
Prioridade converterPrioridade(int prioridadeNum);   // Função para converter número de prioridade para enum
void inserirCliente(Cliente** cabeca, int id, Prioridade prioridade); // Função para inserir o cliente na lista com base na prioridade
void imprimirRelatorio(Cliente* cabeca); // Função para imprimir o relatório dos clientes com tempo total
void liberarLista(Cliente* cabeca); // Função para liberar a memória da lista

// Função para realizar operações e calcular tempo total
void realizarOperacoes(Cliente* cabeca); // Função para realizar operações dos clientes e calcular o tempo total

#endif // CLIENTE_H // Fim da verificação de múltiplas inclusões
