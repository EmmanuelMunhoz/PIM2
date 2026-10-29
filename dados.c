#include "functions.h"

int quantidadeAgentes = 0;
int proximoIdAgente = 1;
int idsAgentes[MAX_AGENTES];
char nomesAgentes[MAX_AGENTES][MAX_NOME];
char descricaoAgentes[MAX_AGENTES][MAX_DESCRICAO];
char categoriasAgentes[MAX_AGENTES][MAX_CATEGORIA];
char instrucoesAgentes[MAX_AGENTES][MAX_INSTRUCOES];
int statusAgentes[MAX_AGENTES];
double mediasAgentes[MAX_AGENTES];
int quantidadesAvaliacoesAgentes[MAX_AGENTES];
int quantidadeAvaliacoes = 0;
int idsAgentesAvaliados[MAX_AVALIACOES];
int notasAvaliacoes[MAX_AVALIACOES];
int possuiMediaAgentes[MAX_AGENTES];

const char valor_digitado_errado[] = "\n\033[31m⚠️  Valor digitado Invalido!⚠️\033[0m\n"; //variavel global de erro;

