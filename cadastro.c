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



int editarAgente(int indiceAgente)
{
    int escolha, leituraOk, capacidade;
    int statusAnterior, novoStatus;
    char entrada[TAM];
    char novoTexto[MAX_DESCRICAO];
    char textoAnterior[MAX_DESCRICAO];
    char *campo = NULL;

    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes)
    {
        printf("\nAgente invalido!\n");
        return 0;
    }

    do
    {
        printf("\n========== EDITAR AGENTE ==========\n\n");
        printf("ID: %d\n",idsAgentes[indiceAgente]);
        printf("Nome: %s\n",nomesAgentes[indiceAgente]);
        printf("Descricao: %s\n",descricaoAgentes[indiceAgente]);
        printf("Categoria: %s\n",categoriasAgentes[indiceAgente]);
        printf("Instrucoes: %s\n",instrucoesAgentes[indiceAgente]);
        printf("Status: %s\n",statusAgentes[indiceAgente] == 1 ? "ATIVO" : "INATIVO");

        printf("\n[1] Alterar nome");
        printf("\n[2] Alterar descricao");
        printf("\n[3] Alterar categoria");
        printf("\n[4] Alterar instrucoes");
        printf("\n[5] Alterar status");
        printf("\n[0] Voltar a ficha");
        printf("\n[-1] Encerrar o sistema");
        printf("\n\nEscolha uma opcao: ");

        leituraOk = lerEntrada(entrada,sizeof(entrada));

        if (leituraOk == -1)
        {
            return -1;
        }

        if (leituraOk != 1)
        {
            printf("\nEntrada invalida!\n");
            continue;
        }

        escolha = validarEntrada(entrada,5);

        if (escolha == -1)
        {
            return -1;
        }

        if (escolha == 0)
        {
            return 0;
        }

        if (escolha < 1 || escolha > 5)
        {
            printf("\nOpcao invalida!\n");
            continue;
        }

        if (escolha == 5)
        {
            printf("\n[1] Ativar agente");
            printf("\n[0] Inativar agente");
            printf("\n[-1] Encerrar o sistema");
            printf("\n\nNovo status: ");

            leituraOk = lerEntrada(entrada,sizeof(entrada));

            if (leituraOk == -1)
            {
                return -1;
            }

            if (leituraOk != 1)
            {
                printf("\nEntrada invalida!\n");
                continue;
            }

            novoStatus = validarEntrada(entrada,1);

            if (novoStatus == -1)
            {
                return -1;
            }

            if (novoStatus != 0 && novoStatus != 1)
            {
                printf("\nStatus invalido!\n");
                continue;
            }

            statusAnterior = statusAgentes[indiceAgente];
            statusAgentes[indiceAgente] = novoStatus;

            if (salvarAgentes() == 1)
            {
                printf("\nStatus atualizado com sucesso!\n");
            }
            else
            {
                statusAgentes[indiceAgente] = statusAnterior;
                printf("\nFalha ao salvar. Estado anterior restaurado na memoria.\n");
                printf("Verifique agentes.json antes de continuar.\n");
                return 0;
            }

            continue;
        }

        campo = NULL;
        capacidade = 0;

        switch (escolha)
        {
            case 1:
                campo = nomesAgentes[indiceAgente];
                capacidade = MAX_NOME;
                printf("\nNovo nome: ");
                break;

            case 2:
                campo = descricaoAgentes[indiceAgente];
                capacidade = MAX_DESCRICAO;
                printf("\nNova descricao: ");
                break;

            case 3:
                campo = categoriasAgentes[indiceAgente];
                capacidade = MAX_CATEGORIA;
                printf("\nNova categoria: ");
                break;

            case 4:
                campo = instrucoesAgentes[indiceAgente];
                capacidade = MAX_INSTRUCOES;
                printf("\nNovas instrucoes: ");
                break;
        }

        if (campo == NULL)
        {
            continue;
        }

        leituraOk = lerEntrada(novoTexto,capacidade);

        if (leituraOk == -1)
        {
            return -1;
        }

        if (leituraOk != 1)
        {
            printf("\nAlteracao cancelada: entrada invalida.\n");
            continue;
        }

        if (strcmp(novoTexto,"-1") == 0)
        {
            return -1;
        }

        if (novoTexto[0] == '\0')
        {
            printf("\nO campo nao pode ficar vazio!\n");
            continue;
        }

        int caractereInvalido = 0;

        for (int i = 0; novoTexto[i] != '\0'; i++)
        {
            if (novoTexto[i] == '"' || novoTexto[i] == '\\' ||
                (unsigned char)novoTexto[i] < 32)
            {
                caractereInvalido = 1;
                break;
            }
        }

        if (caractereInvalido == 1)
        {
            printf("\nTexto contem caracteres nao permitidos no JSON.\n");
            continue;
        }

        strcpy(textoAnterior,campo);
        strcpy(campo,novoTexto);

        if (salvarAgentes() == 1)
        {
            printf("\nInformacao atualizada com sucesso!\n");
        }
        else
        {
            strcpy(campo,textoAnterior);
            printf("\nFalha ao salvar. Valor anterior restaurado na memoria.\n");
            printf("Verifique agentes.json antes de continuar.\n");
            return 0;
        }

    } while (1);
}
