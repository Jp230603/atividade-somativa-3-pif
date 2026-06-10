#include <stdio.h>
#include <stdlib.h>
#include "../include/clientes.h"

static void exibir_menu(void)
{
    printf("\n=== Sistema de Manutenção de Contas ===\n");
    printf("1. Cadastrar um novo cliente \n");
    printf("2. Consultar cliente por número de conta\n");
    printf("3. Atualizar saldo (R$)\n");
    printf("4. Encerrar conta\n");
    printf("5. Listar todos os clientes ativos\n");
    printf("6. Reler arquivo do inicio (rewind)\n");
    printf("7. Encerrar programa\n");

    printf("\n\t Digite sua opção: ");
}


int main(void)
{
    FILE *arquivo = fopen(ARQUIVO, "r+b");

    if (!arquivo)
    {
        arquivo = fopen(ARQUIVO, "w+b");

        if (!arquivo)
        {
            perror("Erro ao abrir arquivo.");
            return EXIT_FAILURE;
        }
    }

    int opcao;
    do 
    {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) 
        {
            case 1: cadastrar(arquivo);
            break;

            case 2: consultar(arquivo);
            break;

            case 3: atualizar_saldo(arquivo);
            break;

            case 4: encerrar_conta(arquivo);
            break;

            case 5: listar(arquivo);
            break;

            case 6: listar_do_inicio(arquivo);
            break;

            case 7: printf("Encerrando.\n");
            break;

            default: printf("Opção inválida.\n");
        }
    } 
    while
        (opcao != 7);

    fclose(arquivo);
    return EXIT_SUCCESS;
}