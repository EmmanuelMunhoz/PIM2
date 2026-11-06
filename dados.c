#include "dados.h"

// Cada indice representa o MESMO agente em todos os vetores paralelos.
int quantidadeAgentes = 0;
int idsAgentes[MAX_AGENTES];
char nomesAgentes[MAX_AGENTES][MAX_NOME];
char descricaoAgentes[MAX_AGENTES][MAX_DESCRICAO];
char categoriasAgentes[MAX_AGENTES][MAX_CATEGORIA];
char instrucoesAgentes[MAX_AGENTES][MAX_INSTRUCOES];
double mediasAgentes[MAX_AGENTES];
int quantidadesAvaliacoesAgentes[MAX_AGENTES];
int alteracoesPendentes = 0;