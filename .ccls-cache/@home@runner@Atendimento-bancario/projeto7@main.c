#include <stdio.h>
#include <locale.h>
#include "cliente.h"




// Fun�o principal do programa
int main() {
    // Configura a localidade para o padr�o portugu�s
    setlocale(LC_ALL,"portuguese");

    // Inicializa a fila de clientes como nula
    Cliente* fila = NULL;

    // Vari�vel para armazenar o n�mero de clientes
    int numClientes;

    // Vari�vel para armazenar o valor num�rico da prioridade
    int prioridadeNum;

    // Vari�vel para armazenar a prioridade convertida
    Prioridade prioridade;

    // Contador de ID para atribuir IDs �nicos aos clientes
    int idCounter = 1; // Contador de ID baseado na ordem de chegada

    // Solicita ao usu�rio o n�mero de clientes
    printf("Digite o n�mero de clientes: ");
    scanf("%d", &numClientes);

    // Loop para adicionar os clientes � fila
    for (int i = 0; i < numClientes; i++) {
        // Solicita ao usu�rio a prioridade do cliente
        printf("Digite a prioridade do cliente %d (1 - Alta, 2 - M�dia, 3 - Baixa): ", i + 1);
        scanf("%d", &prioridadeNum);

        // Converte a prioridade num�rica para o tipo Prioridade
        prioridade = converterPrioridade(prioridadeNum);

        // Insere o cliente na fila com um ID autom�tico baseado na ordem de chegada
        inserirCliente(&fila, idCounter++, prioridade);
    }

    // Realiza as opera�es para cada cliente na fila e calcula o tempo total
    realizarOperacoes(fila);

    // Imprime o relat�rio com o tempo total das opera�es de cada cliente
    imprimirRelatorio(fila);

    // Libera a mem�ria alocada para a lista de clientes
    liberarLista(fila);

    return 0;
}
