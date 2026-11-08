#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "persistencia.h"
#include "dados.h"
#include "medias.h"

// Carrega UMA VEZ o agentes.json para os vetores paralelos na RAM.
// O leitor espera o formato simples que salvarAgentes produz, uma chave por linha.
// Devolve 1 em sucesso e 0 se encontrar arquivo incompleto ou dados invalidos.


int carregarAgentes(void)
{
    FILE *arquivo;
    char marcador = 0;
    char fechamento;
    char nota[40];
    int leitura;
    int camposLidos;
    int indiceAgente = 0;

    arquivo = fopen("dados/agentes.json", "r");
    if (arquivo == NULL)
    {
        return 0;
    }

    leitura = fscanf(arquivo, " %c", &marcador);

    if (leitura != 1 || marcador != '[')
    {
        fclose(arquivo);
        return 0;
    }

    while (1)
    {
        leitura = fscanf(arquivo, " %c", &marcador);

        if (leitura != 1 || marcador == ']')
        {
            break;
        }

        if (marcador == ',')
        {
            continue;
        }

        if (marcador != '{' || indiceAgente >= MAX_AGENTES)
        {
            break;
        }

        camposLidos = fscanf(arquivo,
            " \"id\": %d,"
            " \"nome\": \"%80[^\"]\","
            " \"descricao\": \"%300[^\"]\","
            " \"categoria\": \"%50[^\"]\","
            " \"instrucoes\": \"%1000[^\"]\","
            " \"notaMedia\": %39[^,],"
            " \"quantidadeAvaliacoes\": %d %c",
            &idsAgentes[indiceAgente],
            nomesAgentes[indiceAgente],
            descricaoAgentes[indiceAgente],
            categoriasAgentes[indiceAgente],
            instrucoesAgentes[indiceAgente],
            nota,&quantidadesAvaliacoesAgentes[indiceAgente],&fechamento);

        if (camposLidos != 8 || fechamento != '}')
        {
            break;
        }

        mediasAgentes[indiceAgente] = 0.0;
        sscanf(nota, "%lf", &mediasAgentes[indiceAgente]);

        indiceAgente++;
    }

    fclose(arquivo);

    if (marcador != ']')
    {
        return 0;
    }

    quantidadeAgentes = indiceAgente;
    alteracoesPendentes = 0;
    return 1;
}

// Salva TODO o estado dos vetores no unico JSON, apenas quando o usuario solicitar.
// Serializa double com %.17g para nao arredondar a media a cada reinicializacao.
int salvarAgentes(void)
{
    FILE *arquivo = fopen("dados/agentes.json", "w");
    int erro = 0;
    if (arquivo == NULL)
    {
        printf("Falha ao abrir agentes.json para salvar.\n");
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
        if (quantidadesAvaliacoesAgentes[i] == 0)
        {
            fprintf(arquivo, "    \"notaMedia\": null,\n");
        }
        else
        {
            fprintf(arquivo, "    \"notaMedia\": %.17g,\n", mediasAgentes[i]);
        }
        fprintf(arquivo, "    \"quantidadeAvaliacoes\": %d\n", quantidadesAvaliacoesAgentes[i]);
        fprintf(arquivo, "  }%s\n", i + 1 < quantidadeAgentes ? "," : "");
    }

    fprintf(arquivo, "]\n");

    if (ferror(arquivo))
    {
        erro = 1;
    }
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }
    if (erro)
    {
        printf("Erro ao gravar agentes.json. Confira o arquivo.\n");
        return 0;
    }
    alteracoesPendentes = 0;
    return 1;
}

// Atualiza media e quantidade APENAS na RAM, sem gravar arquivos nesta etapa.
// O proprio agente guarda suas avaliacoes agregadas; nao ha notas individuais.
int registrarAvaliacao(int indiceAgente, int nota)
{
    int n;
    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes || nota < 0 || nota > 5)
    {
        return 0;
    }
    n = quantidadesAvaliacoesAgentes[indiceAgente];
    if (n == INT_MAX)
    {
        return 0;
    }
    mediasAgentes[indiceAgente] = calcularNovaMedia(mediasAgentes[indiceAgente], n, nota);
    quantidadesAvaliacoesAgentes[indiceAgente] = n + 1;
    alteracoesPendentes = 1;
    return 1;
}
