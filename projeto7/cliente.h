#ifndef CLIENTE_H // Verifica se CLIENTE_H n�o est� definido
#define CLIENTE_H // Define CLIENTE_H para evitar m�ltiplas inclus�es

// Definindo a enumera�o para prioridades
typedef enum {
    BAIXA = 3, // Prioridade baixa com valor 3
    MEDIA = 2, // Prioridade m�dia com valor 2
    ALTA = 1   // Prioridade alta com valor 1
} Prioridade; // Nome do tipo enum: Prioridade

// Estrutura do Cliente
typedef struct Cliente {
    int id;                    // ID do cliente
    Prioridade prioridade;     // Prioridade do cliente (ALTA, MEDIA, BAIXA)
    int tempoOperacoes;            // Adicionado para armazenar o tempo total das opera�es do cliente
    int tempoEspera;            // Tempo pelo qual o cliente esperou na fila
    struct Cliente* anterior; // Ponteiro para o cliente anterior na fila
    struct Cliente* proximo;   // Ponteiro para o pr�ximo cliente na lista
} Cliente; // Nome do tipo struct: Cliente

// Declara�o das fun�es que ser�o implementadas em cliente.c
Cliente* criarCliente(int id, Prioridade prioridade); // Fun�o para criar um novo cliente
Prioridade converterPrioridade(int prioridadeNum);   // Fun�o para converter n�mero de prioridade para enum
void inserirCliente(Cliente** cabeca, int id, Prioridade prioridade); // Fun�o para inserir o cliente na lista com base na prioridade
void imprimirRelatorio(Cliente* cabeca); // Fun�o para imprimir o relat�rio dos clientes com tempo total
void liberarLista(Cliente* cabeca); // Fun�o para liberar a mem�ria da lista

// Fun�o para realizar opera�es e calcular tempo total
void realizarOperacoes(Cliente* cabeca); // Fun�o para realizar opera�es dos clientes e calcular o tempo total

#endif // CLIENTE_H // Fim da verifica�o de m�ltiplas inclus�es
