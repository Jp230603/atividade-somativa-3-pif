#include <stdio.h>
#include <string.h>
#include "../include/clientes.h"

static long total_posicoes(FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    return ftell(arquivo) / sizeof(Cliente);
}

void cadastrar(FILE *arquivo)
{
    int posicao;
    Cliente c;
    long total = total_posicoes(arquivo);

    printf("Posição para cadastro (0 a %ld): ", total);
    scanf("%d", &posicao);
    getchar();

    fseek(arquivo, (long)posicao * sizeof(Cliente), SEEK_SET);
    Cliente existente;

    if (fread(&existente, sizeof(Cliente), 1, arquivo) == 1 && existente.ativo) 
    {
        printf("Posição já ocupada por conta %d.\n", existente.conta);
        return;
    }

    printf("Número da conta: ");
    scanf("%d", &c.conta);
    getchar();

    printf("Nome do titular: ");
    fgets(c.nome, NOME_MAX, stdin);

    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Saldo inicial (R$): ");
    scanf("%f", &c.saldo);

    c.ativo = 1;

    fseek(arquivo, (long)posicao * sizeof(Cliente), SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, arquivo);
    fflush(arquivo);
    printf("Cliente cadastrado na posição %d.\n", posicao);
}

void consultar(FILE *arquivo)
{
    int numero;
    printf("Número da conta: ");
    scanf("%d", &numero);

    long total = total_posicoes(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    Cliente c;

    for (long i = 0; i < total; i++) 
    {
        fread(&c, sizeof(Cliente), 1, arquivo);

        if (c.ativo && c.conta == numero) 
        {
            printf("\nPosição : %ld\n", i);
            printf("Conta   : %d\n", c.conta);
            printf("Nome    : %s\n", c.nome);
            printf("Saldo   : R$ %.2f\n", c.saldo);
            return;
        }
    }
    printf("Conta %d não encontrada.\n", numero);
}

void atualizar_saldo(FILE *arquivo)
{
    int numero;
    printf("Número da conta: ");
    scanf("%d", &numero);

    long total = total_posicoes(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    Cliente c;

    for (long i = 0; i < total; i++)
    {
        long pos = ftell(arquivo);
        fread(&c, sizeof(Cliente), 1, arquivo);

        if (c.ativo && c.conta == numero)
        {
            printf("Saldo atual: R$ %.2f\n", c.saldo);
            printf("Novo saldo : ");
            scanf("%f", &c.saldo);
            fseek(arquivo, pos, SEEK_SET);
            fwrite(&c, sizeof(Cliente), 1, arquivo);
            fflush(arquivo);
            printf("Saldo atualizado.\n");
            return;
        }
    }

    printf("Conta %d não encontrada.\n", numero);
}

void encerrar_conta(FILE *arquivo)
{
    int numero;
    printf("Número da conta a encerrar: ");
    scanf("%d", &numero);

    long total = total_posicoes(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    Cliente c;

    for (long i = 0; i < total; i++)
    {
        long pos = ftell(arquivo);
        fread(&c, sizeof(Cliente), 1, arquivo);

        if (c.ativo && c.conta == numero)
        {
            c.ativo = 0;
            fseek(arquivo, pos, SEEK_SET);
            fwrite(&c, sizeof(Cliente), 1, arquivo);
            fflush(arquivo);
            printf("Conta %d encerrada.\n", numero);
            return;
        }
    }

    printf("Conta %d não encontrada.\n", numero);
}

static void imprimir_lista(FILE *arquivo)
{
    long total = total_posicoes(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    Cliente c;
    int encontrou = 0;

    for (long i = 0; i < total; i++)
    {
        fread(&c, sizeof(Cliente), 1, arquivo);

        if (c.ativo)
        {
            printf("  [%ld] Conta: %d | Nome: %-30s | Saldo: R$ %.2f\n", 
                i, c.conta, c.nome, c.saldo);
            encontrou = 1;
        }
    }
    if (!encontrou)
    {
        printf(" \nNenhum cliente ativo.\n");
    }
}

void listar(FILE *arquivo)
{
    printf("\n--- Lista de Clientes ---\n");
    imprimir_lista(arquivo);
}

void listar_do_inicio(FILE *arquivo)
{
    printf("\n--- Releitura do inicio (rewind) ---\n");
    rewind(arquivo);
    imprimir_lista(arquivo);
}