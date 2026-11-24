#ifndef PIM2_DADOS_H
#define PIM2_DADOS_H

// Capacidade dos buffers de opção em bytes, incluindo '\0'.
#define TAM 16
// Quantidade máxima de agentes nos vetores paralelos.
#define MAX_AGENTES 50

// Capacidades dos campos de texto em bytes, incluindo '\0'.
#define MAX_NOME 81
#define MAX_DESCRICAO 301
#define MAX_CATEGORIA 51
#define MAX_INSTRUCOES 1001

extern int quantidadeAgentes;
extern int idsAgentes[MAX_AGENTES];
extern char nomesAgentes[MAX_AGENTES][MAX_NOME];
extern char descricaoAgentes[MAX_AGENTES][MAX_DESCRICAO];
extern char categoriasAgentes[MAX_AGENTES][MAX_CATEGORIA];
extern char instrucoesAgentes[MAX_AGENTES][MAX_INSTRUCOES];
extern double mediasAgentes[MAX_AGENTES];
extern int quantidadesAvaliacoesAgentes[MAX_AGENTES];
extern int alteracoesPendentes;

#endif