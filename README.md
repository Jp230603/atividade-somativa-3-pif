<h1 align="center">Sistema de Manutencao de Contas </h1>

Sistema em C para gerenciar contas bancarias em arquivo 🏦binario de registros de tamanho fixo.

## Estrutura da atividade:

```
.
├── include/
│   └── clientes.h    # struct Cliente e assinaturas das funcoes
├── src/
│   └── clientes.c    # operacoes sobre o arquivo binario
├── main/
│   ├── main.c        # menu interativo e loop principal
├── Makefile
└── README.md
```

## Como compilar e executar

```bash
make
./contas
```

O `make` executa internamente:

```bash
gcc -Wall -Wextra -I include -o contas src/main.c src/clientes.c
```

| Flag | Significado |
|------|-------------|
| `-Wall` | Ativa todos os avisos comuns do compilador (variaveis nao usadas, comparacoes suspeitas, etc.) |
| `-Wextra` | Ativa avisos adicionais alem dos cobertos por `-Wall` (parametros sem uso, comparacoes entre signed/unsigned, etc.) |
| `-I include` | Adiciona o diretorio `include/` ao caminho de busca de headers, permitindo `#include "clientes.h"` sem indicar o caminho completo |
| `-o contas` | Define o nome do executavel de saida como `contas` |

Para limpar os arquivos gerados:

```bash
make clean
```

Remove o executavel `contas` e o arquivo de dados `contas.bin`.

## Struct do registro 🏗️:

```c
typedef struct 
{
    int   conta;        // numero da conta
    char  nome[70];     // nome do titular
    float saldo;        // saldo atual
    int   ativo;        // 1 = ativo, 0 = encerrado
} Cliente;
```

Cada registro ocupa exatamente `sizeof(Cliente)` bytes no arquivo `contas.bin`, garantindo acesso direto por posicao via `fseek()`.

## Funcionalidades:

1. **Cadastrar** — escolhe a posicao (indice) no arquivo, verifica se esta livre e grava o registro com `fwrite()` apos posicionamento por `fseek()`.
2. **Consultar** — percorre os registros com `fread()` ate encontrar o numero de conta informado.
3. **Atualizar saldo** — localiza o registro, salva a posicao com `ftell()`, atualiza o campo `saldo` e regrava no mesmo lugar com `fseek()` + `fwrite()`.
4. **Encerrar conta** — mesma logica da atualizacao, porem marca o campo `ativo = 0` (exclusao logica), preservando o espaco no arquivo para reuso.
5. **Listar** — le todos os registros do inicio ao fim e exibe apenas os ativos.
6. **Rewind** — usa `rewind()` para mover o ponteiro ao inicio do arquivo e repete a listagem.
7. **Encerrar** — fecha o arquivo e termina o programa.

## Decisões de implementação:

- **Exclusao logica**: contas encerradas nao sao removidas fisicamente; o campo `ativo` as oculta, preservando indices e permitindo reuso do espaco.
- **fflush apos escrita**: garante que os dados sejam persistidos antes da proxima leitura no mesmo `FILE *`.
- **fseek apos total_posicoes**: a funcao auxiliar move o ponteiro ao fim para calcular o tamanho; por isso, toda funcao que a chama reposiciona o ponteiro antes de iniciar a leitura.
