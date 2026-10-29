#include <stdio.h>    // Entrada e saida de dados, como printf().
#include <string.h>   // Manipulacao de strings, como strcmp().
#include <stdlib.h>   // Funcoes utilitarias do C (nao utilizada diretamente aqui).
#include "functions.h" // Declaracoes das funcoes compartilhadas entre arquivos.

void cadastrarAgente(void)
{
    int indiceAgente = quantidadeAgentes;
    int retornoLeitura;

    if(quantidadeAgentes >= MAX_AGENTES)
    {
        printf("Não pode ser cadastrado mais AGENTES\n");
        return;
    }
    if (proximoIdAgente <= 0)
    {
        printf("Nao ha IDs disponiveis para novos agentes.\n");
        return;
    }

    printf("\nNome do Agente: ");retornoLeitura = lerEntrada(nomesAgentes[indiceAgente],sizeof(nomesAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {
        return;
    }

    if (nomesAgentes[indiceAgente][0] == '\0')
    {
        printf("Nome obrigatorio!\n");
        return;
    }

    printf("\nQual a descrição do AGENTE: ");retornoLeitura = lerEntrada(descricaoAgentes[indiceAgente],sizeof(descricaoAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {

        return;
    }

    if (descricaoAgentes[indiceAgente][0] == '\0')
    {
        printf("Descrição obrigatoria!\n");
        return;
    }

    printf("\nQual a categoria do Agente: ");retornoLeitura = lerEntrada(categoriasAgentes[indiceAgente],sizeof(categoriasAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {

        return;
    }

    if (categoriasAgentes[indiceAgente][0] == '\0')
    {
        printf("Categoria obrigatoria!\n");
        return;
    }

    printf("\nQual a instrução do AGENTE: ");retornoLeitura = lerEntrada(instrucoesAgentes[indiceAgente],sizeof(instrucoesAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {

        return;
    }

    if (instrucoesAgentes[indiceAgente][0] == '\0')
    {
        printf("Intruções obrigatorias!\n");
        return;
    }

    // As aspas e barras invertidas exigiriam tratamento especial no JSON.
    // Nesta versao simples, esses caracteres nao sao aceitos no cadastro.
    if (strchr(nomesAgentes[indiceAgente], '"') != NULL ||
        strchr(nomesAgentes[indiceAgente], '\\') != NULL ||
        strchr(descricaoAgentes[indiceAgente], '"') != NULL ||
        strchr(descricaoAgentes[indiceAgente], '\\') != NULL ||
        strchr(categoriasAgentes[indiceAgente], '"') != NULL ||
        strchr(categoriasAgentes[indiceAgente], '\\') != NULL ||
        strchr(instrucoesAgentes[indiceAgente], '"') != NULL ||
        strchr(instrucoesAgentes[indiceAgente], '\\') != NULL)
    {
        printf("Nao use aspas ou barra invertida nos campos do agente.\n");
        return;
    }

    idsAgentes[indiceAgente] = proximoIdAgente;
    statusAgentes[indiceAgente] = 1;
    mediasAgentes[indiceAgente] = 0.0;
    quantidadesAvaliacoesAgentes[indiceAgente] = 0;
    possuiMediaAgentes[indiceAgente] = 0;
    quantidadeAgentes++;
    proximoIdAgente++;

    if (salvarAgentes() == 1)
    {
        if (salvarControle() == 1)
        {
            printf("\033[32m\nAgente salvo com sucesso!\033[0m");
            printf("\033[32m\nControle atualizado!\033[0m");
        }
        else
        {
            quantidadeAgentes--;
            proximoIdAgente--;
            if (salvarAgentes() == 1)
            {
                printf("Cadastro desfeito porque controle.json nao foi salvo.\n");
            }
            else
            {
                quantidadeAgentes++;
                proximoIdAgente++;
                printf("Falha ao salvar controle e ao desfazer agentes.json. Verifique os arquivos.\n");
            }
        }
    }
    else
    {
        quantidadeAgentes--;
        proximoIdAgente--;
        printf("Erro ao salvar agente!\n");
    }
}
