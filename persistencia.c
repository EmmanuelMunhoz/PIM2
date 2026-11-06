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
    FILE *arquivo = fopen("dados/agentes.json", "r");
    char linha[1400];
    int indice = 0, id, quantidade, fim = 0, valido = 1, semMedia = 0;
    double media = 0.0;
    char nome[MAX_NOME], descricao[MAX_DESCRICAO];
    char categoria[MAX_CATEGORIA], instrucoes[MAX_INSTRUCOES];
    if (arquivo == NULL)
    {
        printf("Erro: dados/agentes.json nao encontrado.\n");
        return 0;
    }
    if (fgets(linha, sizeof(linha), arquivo) == NULL || strchr(linha, '[') == NULL)
        valido = 0;

    while (valido && fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strchr(linha, ']') != NULL) { fim = 1; break; }
        if (indice >= MAX_AGENTES || strchr(linha, '{') == NULL) { valido = 0; break; }

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"id\": %d", &id) != 1 || id < 1 || id > 999999)
        { valido = 0; break; }
        for (int j = 0; j < indice; j++)
            if (idsAgentes[j] == id) valido = 0;
        if (!valido) break;

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"nome\": \"%80[^\"]\"", nome) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"descricao\": \"%1000[^\"]\"", descricao) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"categoria\": \"%50[^\"]\"", categoria) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"instrucoes\": \"%1000[^\"]\"", instrucoes) != 1)
        { valido = 0; break; }

        if (fgets(linha, sizeof(linha), arquivo) == NULL) { valido = 0; break; }
        semMedia = (strstr(linha, "\"notaMedia\": null") != NULL);
        if (semMedia) { media = 0.0; quantidade = 0; }
        else if (sscanf(linha, " \"notaMedia\": %lf", &media) != 1 ||
                 !(media >= 0.0 && media <= 5.0))
        { valido = 0; break; }
        else quantidade = -1; // Sera lida na linha seguinte.

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||
            sscanf(linha, " \"quantidadeAvaliacoes\": %d", &quantidade) != 1 || quantidade < 0)
        { valido = 0; break; }
        if ((quantidade == 0 && !semMedia) || (quantidade > 0 && semMedia))
        { valido = 0; break; }
        if (fgets(linha, sizeof(linha), arquivo) == NULL || strchr(linha, '}') == NULL)
        { valido = 0; break; }

        idsAgentes[indice] = id;
        strcpy(nomesAgentes[indice], nome);
        strcpy(descricaoAgentes[indice], descricao);
        strcpy(categoriasAgentes[indice], categoria);
        strcpy(instrucoesAgentes[indice], instrucoes);
        mediasAgentes[indice] = media;
        quantidadesAvaliacoesAgentes[indice] = quantidade;
        indice++;
    }
    if (ferror(arquivo) || !fim) valido = 0;
    if (fclose(arquivo) == EOF) valido = 0;
    if (!valido)
    {
        quantidadeAgentes = 0;
        printf("Erro: formato invalido em dados/agentes.json.\n");
        return 0;
    }
    quantidadeAgentes = indice;
    alteracoesPendentes = 0;
    return 1;
}

// Salva TODO o estado dos vetores no unico JSON, apenas quando o usuario solicitar.
// Serializa double com %.17g para nao arredondar a media a cada reinicializacao.
int salvarAgentes(void)
{
    FILE *arquivo = fopen("dados/agentes.json", "w");
    int erro = 0;
    if (arquivo == NULL) { printf("Falha ao abrir agentes.json para salvar.\n"); return 0; }
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
            fprintf(arquivo, "    \"notaMedia\": null,\n");
        else
            fprintf(arquivo, "    \"notaMedia\": %.17g,\n", mediasAgentes[i]);
        fprintf(arquivo, "    \"quantidadeAvaliacoes\": %d\n", quantidadesAvaliacoesAgentes[i]);
        fprintf(arquivo, "  }%s\n", i + 1 < quantidadeAgentes ? "," : "");
    }
    fprintf(arquivo, "]\n");
    if (ferror(arquivo)) erro = 1;
    if (fclose(arquivo) == EOF) erro = 1;
    if (erro) { printf("Erro ao gravar agentes.json. Confira o arquivo.\n"); return 0; }
    alteracoesPendentes = 0;
    return 1;
}

// Atualiza media e quantidade APENAS na RAM, sem gravar arquivos nesta etapa.
// O proprio agente guarda suas avaliacoes agregadas; nao ha notas individuais.
int registrarAvaliacao(int indiceAgente, int nota)
{
    int n;
    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes || nota < 0 || nota > 5)
        return 0;
    n = quantidadesAvaliacoesAgentes[indiceAgente];
    if (n == INT_MAX) return 0;
    mediasAgentes[indiceAgente] = calcularNovaMedia(mediasAgentes[indiceAgente], n, nota);
    quantidadesAvaliacoesAgentes[indiceAgente] = n + 1;
    alteracoesPendentes = 1;
    return 1;
}
