#ifndef CLIENTES_H
#define CLIENTES_H

#define ARQUIVO "contas.bin"
#define NOME_MAX 70

typedef struct 
{
    int conta;
    char nome[NOME_MAX];
    float saldo;
    int ativo; 
} Cliente;

void cadastrar(FILE *arquivo);
void consultar(FILE *arquivo);
void atualizar_saldo(FILE *arquivo);
void encerrar_conta(FILE *arquivo);
void listar(FILE *arquivo);
void listar_do_inicio(FILE *arquivo);

#endif
