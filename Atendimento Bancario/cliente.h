#ifndef CLIENTE_H // Verifica se CLIENTE_H nao esta definido
#define CLIENTE_H // Define CLIENTE_H para evitar multiplas inclusoes

// Definindo a enumeracao para prioridades
typedef enum {
    BAIXA = 3, // Prioridade baixa com valor 3
    MEDIA = 2, // Prioridade media com valor 2
    ALTA = 1   // Prioridade alta com valor 1
} Prioridade; // Nome do tipo enum: Prioridade

// Estrutura do Cliente
typedef struct Cliente {
    int id;                    // ID do cliente
    Prioridade prioridade;     // Prioridade do cliente (ALTA, MEDIA, BAIXA)
    int tempoOperacoes;        // Tempo total das operacoes do cliente
    int tempoEspera;           // Tempo pelo qual o cliente esperou na fila
    struct Cliente* anterior;  // Ponteiro para o cliente anterior na fila
    struct Cliente* proximo;   // Ponteiro para o proximo cliente na lista
} Cliente; // Nome do tipo struct: Cliente

// Declaracao das funcoes que serao implementadas em cliente.c
Cliente* criarCliente(int id, Prioridade prioridade); // Funcao para criar um novo cliente
Prioridade converterPrioridade(int prioridadeNum);   // Funcao para converter numero de prioridade para enum
void inserirCliente(Cliente** cabeca, int id, Prioridade prioridade); // Funcao para inserir o cliente na lista com base na prioridade
void imprimirRelatorio(Cliente* cabeca); // Funcao para imprimir o relatorio dos clientes com tempo total
void liberarLista(Cliente* cabeca); // Funcao para liberar a memoria da lista

// Funcao para realizar operacoes e calcular tempo total
void realizarOperacoes(Cliente* cabeca); // Funcao para realizar operacoes dos clientes e calcular o tempo total

#endif // CLIENTE_H // Fim da verificacao de multiplas inclusoes
