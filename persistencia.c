#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int carregarControle(void)
{
    FILE *arquivo = fopen("dados/controle.json", "r");
    if (arquivo == NULL)
    {
        // Primeira execucao: so e valido sem agentes cadastrados.
        if (quantidadeAgentes == 0)
        {
            proximoIdAgente = 1;
            return 1;
        }
        printf("Erro ao abrir controle.json!\n");
        return 0;
    }

    int quantidadeLida, proximoIdLido;
    int resultado = fscanf(arquivo," { \"quantidadeAgentes\" : %d , \"proximoIdAgente\" : %d }",&quantidadeLida, &proximoIdLido);
    int erro = (resultado != 2);
    if (ferror(arquivo))
    {
        erro = 1;
    }
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }

    if (erro || quantidadeLida != quantidadeAgentes ||proximoIdLido <= 0 || quantidadeLida > MAX_AGENTES)
    {
        printf("Dados inconsistentes em controle.json!\n");
        return 0;
    }
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (proximoIdLido <= idsAgentes[i])
        {
            printf("Proximo ID invalido em controle.json!\n");
            return 0;
        }
    }

    proximoIdAgente = proximoIdLido;
    return 1;
}

int salvarControle(void)
{
    FILE *arquivo = fopen("dados/controle.json", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir controle.json para gravacao!\n");
        return 0;
    }

    fprintf(arquivo,
        "{\n"
        "    \"quantidadeAgentes\": %d,\n"
        "    \"proximoIdAgente\": %d\n"
        "}\n", quantidadeAgentes, proximoIdAgente);

    int erro = ferror(arquivo);
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }
    if (erro)
    {
        printf("Erro ao gravar controle.json!\n");
        return 0;
    }
    return 1;
}



int salvarAgentes(void)
{
    FILE *arquivo = fopen("dados/agentes.json", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir agentes.json para gravacao!\n");
        return 0;
    }

    fprintf(arquivo, "[\n");
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        fprintf(arquivo, "  {\n");
        fprintf(arquivo, "    \"id\": %d,\n", idsAgentes[i]);
        fprintf(arquivo, "    \"nome\": \"%s\",\n", nomesAgentes[i]);
        fprintf(arquivo, "    \"descricao\": \"%s\",\n", descricaoAgentes[i]);
        fprintf(arquivo, "    \"categoria\": \"%s\",\n", categoriasAgentes[i]);
        fprintf(arquivo, "    \"instrucoes\": \"%s\",\n", instrucoesAgentes[i]);
        fprintf(arquivo, "    \"status\": %d,\n", statusAgentes[i]);

        if (possuiMediaAgentes[i] == 1)
        {
            fprintf(arquivo, "    \"notaMedia\": %.1f\n", mediasAgentes[i]);
        }
        else
        {
            fprintf(arquivo, "    \"notaMedia\": null\n");
        }

        fprintf(arquivo, "  }%s\n", i < quantidadeAgentes - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");

    int erro = ferror(arquivo);

    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }

    if (erro)
    {
        printf("Erro ao gravar agentes.json!\n");
        return 0;
    }

    return 1;
}


int carregarAgentes(void)
{
    FILE *arquivo = fopen("dados/agentes.json", "r");
    if (arquivo == NULL)
    {
        quantidadeAgentes = 0;
        return 1;
    }

    char linha[1200];
    int indice = 0;
    int erro = 0;
    int fim = 0;

    if (fgets(linha, sizeof(linha), arquivo) == NULL ||strchr(linha, '[') == NULL)
    {
        erro = 1;
    }

    while (erro == 0 && fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strchr(linha, ']') != NULL)
        {
            fim = 1;
            break;
        }
        if (strchr(linha, '{') == NULL || indice >= MAX_AGENTES)
        {
            erro = 1;
            break;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||sscanf(linha, " \"id\": %d", &idsAgentes[indice]) != 1 ||
            idsAgentes[indice] <= 0)
        {
            erro = 1;
            break;
        }
        for (int i = 0; i < indice; i++)
        {
            if (idsAgentes[i] == idsAgentes[indice])
            {
                erro = 1;
            }
        }
        if (erro) break;

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"nome\": \"%80[^\"]\"", nomesAgentes[indice]) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"descricao\": \"%1000[^\"]\"", descricaoAgentes[indice]) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"categoria\": \"%50[^\"]\"", categoriasAgentes[indice]) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"instrucoes\": \"%1000[^\"]\"", instrucoesAgentes[indice]) != 1)
        {
            erro = 1;
            break;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL)
        {
            erro = 1;
            break;
        }
        if (strstr(linha, "\"dataCriacao\"") != NULL)
        {
            if (fgets(linha, sizeof(linha), arquivo) == NULL)
            {
                erro = 1;
                break;
            }
        }
        if (sscanf(linha, " \"status\": %d", &statusAgentes[indice]) != 1 ||
            (statusAgentes[indice] != 0 && statusAgentes[indice] != 1))
        {
            erro = 1;
            break;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL)
        {
            erro = 1;
            break;
        }
        if (strstr(linha, "\"notaMedia\": null") != NULL)
        {
            mediasAgentes[indice] = 0.0;
            possuiMediaAgentes[indice] = 0;
        }
        else if (sscanf(linha, " \"notaMedia\": %lf", &mediasAgentes[indice]) == 1 &&
                 mediasAgentes[indice] >= 0.0 && mediasAgentes[indice] <= 5.0)
        {
            possuiMediaAgentes[indice] = 1;
        }
        else
        {
            erro = 1;
            break;
        }
        quantidadesAvaliacoesAgentes[indice] = 0;

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||
            strchr(linha, '}') == NULL)
        {
            erro = 1;
            break;
        }
        indice++;
    }

    if (!fim || ferror(arquivo))
    {
        erro = 1;
    }
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }
    if (erro)
    {
        quantidadeAgentes = 0;
        printf("Erro ao carregar agentes.json!\n");
        return 0;
    }

    quantidadeAgentes = indice;
    return 1;
}

int carregarAvaliacoes(void)
{
    FILE *arquivo = fopen("dados/avaliacoes.json", "r");
    char linha[1200];
    int id, nota;
    int agenteEncontrado;

    quantidadeAvaliacoes = 0;

    if (arquivo == NULL)
    {
        printf("Erro ao abrir avaliacoes.json!\n");
        return 0;
    }

    if (fgets(linha,sizeof(linha),arquivo) == NULL || strchr(linha,'[') == NULL)
    {
        fclose(arquivo);
        return 0;
    }

    while (fgets(linha,sizeof(linha),arquivo) != NULL)
    {
        if (strchr(linha,']') != NULL)
        {
            fclose(arquivo);
            return 1;
        }

        if (quantidadeAvaliacoes >= MAX_AVALIACOES)
        {
            fclose(arquivo);
            return 0;
        }

        if (sscanf(linha," { \"idAgente\": %d, \"nota\": %d",&id,&nota) != 2)
        {
            fclose(arquivo);
            return 0;
        }

        if (nota < 0 || nota > 5)
        {
            fclose(arquivo);
            return 0;
        }

        agenteEncontrado = 0;

        for (int i = 0; i < quantidadeAgentes; i++)
        {
            if (idsAgentes[i] == id)
            {
                agenteEncontrado = 1;
                quantidadesAvaliacoesAgentes[i]++;
                break;
            }
        }

        if (agenteEncontrado == 0)
        {
            fclose(arquivo);
            return 0;
        }

        idsAgentesAvaliados[quantidadeAvaliacoes] = id;
        notasAvaliacoes[quantidadeAvaliacoes] = nota;
        quantidadeAvaliacoes++;
    }

    fclose(arquivo);
    return 0;
}

int salvarAvaliacoes(void)
{
    FILE *arquivo = fopen("dados/avaliacoes.json", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir avaliacoes.json para gravacao!\n");
        return 0;
    }

    fprintf(arquivo,"[\n");

    for (int i = 0; i < quantidadeAvaliacoes; i++)
    {
        fprintf(arquivo,"  {\"idAgente\": %d, \"nota\": %d}%s\n",idsAgentesAvaliados[i],notasAvaliacoes[i],i < quantidadeAvaliacoes - 1 ? "," : "");
    }

    fprintf(arquivo,"]\n");

    int erro = ferror(arquivo);

    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }

    if (erro)
    {
        printf("Erro ao gravar avaliacoes.json!\n");
        return 0;
    }

    return 1;
}


void calcularMediasAvaliacoes(void)
{
    int i, j;
    int soma, quantidade;

    for (i = 0; i < quantidadeAgentes; i++)
    {
        soma = 0;
        quantidade = 0;

        for (j = 0; j < quantidadeAvaliacoes; j++)
        {
            if (idsAgentesAvaliados[j] == idsAgentes[i])
            {
                soma += notasAvaliacoes[j];
                quantidade++;
            }
        }

        quantidadesAvaliacoesAgentes[i] = quantidade;

        if (quantidade > 0)
        {
            mediasAgentes[i] = (double)soma / quantidade;
            possuiMediaAgentes[i] = 1;
        }
        else
        {
            mediasAgentes[i] = 0.0;
            possuiMediaAgentes[i] = 0;
        }
    }
}

int registrarAvaliacao(int indiceAgente, int nota)
{
    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes)
    {
        return 0;
    }

    if (nota < 0 || nota > 5 || quantidadeAvaliacoes >= MAX_AVALIACOES)
    {
        return 0;
    }

    idsAgentesAvaliados[quantidadeAvaliacoes] = idsAgentes[indiceAgente];
    notasAvaliacoes[quantidadeAvaliacoes] = nota;
    quantidadeAvaliacoes++;

    calcularMediasAvaliacoes();

    if (salvarAvaliacoes() == 0)
    {
        quantidadeAvaliacoes--;
        calcularMediasAvaliacoes();
        printf("Erro ao salvar a avaliacao!\n");
        return 0;
    }

    if (salvarAgentes() == 0)
    {
        quantidadeAvaliacoes--;
        calcularMediasAvaliacoes();

        int restaurouAvaliacoes = salvarAvaliacoes();
        int restaurouAgentes = salvarAgentes();

        if (restaurouAvaliacoes == 0 || restaurouAgentes == 0)
        {
            printf("ATENCAO: nao foi possivel restaurar os arquivos JSON!\n");
        }

        printf("Erro ao atualizar a media do agente!\n");
        return 0;
    }

    return 1;
}
