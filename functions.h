#ifndef PIM2_FUNCTIONS_H
#define PIM2_FUNCTIONS_H

#define TAM 3
#define MAX_AGENTES 50
#define MAX_NOME 81
#define MAX_DESCRICAO 1001
#define MAX_CATEGORIA 51
#define MAX_INSTRUCOES 1001
#define MAX_AVALIACOES 1000

extern int quantidadeAgentes;
extern int proximoIdAgente;
extern int idsAgentes[MAX_AGENTES];
extern char nomesAgentes[MAX_AGENTES][MAX_NOME];
extern char descricaoAgentes[MAX_AGENTES][MAX_DESCRICAO];
extern char categoriasAgentes[MAX_AGENTES][MAX_CATEGORIA];
extern char instrucoesAgentes[MAX_AGENTES][MAX_INSTRUCOES];
extern int statusAgentes[MAX_AGENTES];
extern double mediasAgentes[MAX_AGENTES];
extern int quantidadesAvaliacoesAgentes[MAX_AGENTES];
extern int quantidadeAvaliacoes;
extern int idsAgentesAvaliados[MAX_AVALIACOES];
extern int notasAvaliacoes[MAX_AVALIACOES];
extern int possuiMediaAgentes[MAX_AGENTES];
extern const char valor_digitado_errado[];

int menu(void);
int menuAdm(void);
void limparBuffer(void);
int validarEntrada(char entrada[], int limiteMaximo);
int lerEntrada(char entrada[], int capacidade);
int autenticarAdm(void);
void cadastrarAgente(void);
int carregarControle(void);
int salvarControle(void);
int salvarAgentes(void);
int carregarAgentes(void);
int catalogoAgentes();
int carregarAvaliacoes(void);
int salvarAvaliacoes(void);
void calcularMediasAvaliacoes(void);
int registrarAvaliacao(int indiceAgente, int nota);
int listarAgentesAdm(void);
int fichaAgenteAdm(int indiceAgente);

#endif
