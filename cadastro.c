#include <stdio.h>
#include <string.h>
#include "cadastro.h"
#include "dados.h"
#include "entrada.h"

// Confere se o texto pode ser escrito pelo gravador JSON simplificado.
// Como nao ha biblioteca externa, aspas, barras e controles sao rejeitados.
int textoValido(const char texto[])
{
    if (texto[0] == '\0') return 0;
    for (int i = 0; texto[i] != '\0'; i++)
        if (texto[i] == '"' || texto[i] == '\\' || (unsigned char)texto[i] < 32) return 0;
    return 1;
}

// Pede um campo obrigatorio; retorna 1=texto valido, 0=cancelado, -1=EOF.
int pedirCampo(char destino[], int capacidade, const char rotulo[])
{
    int retorno;
    printf("%s", rotulo);
    retorno = lerEntrada(destino, capacidade);
    if (retorno == -1) return -1;
    if (retorno != 1 || !textoValido(destino))
    { printf("Campo vazio ou com caracteres invalidos (aspas/barra invertida).\n"); return 0; }
    return 1;
}

// Cadastra agente na proxima posicao disponivel, sem salvar em disco.
// O ID e maiorID+1; nao se utiliza quantidade+1 nem controle.json.
void cadastrarAgente(void)
{
    int indice = quantidadeAgentes, maior = 0;
    if (quantidadeAgentes >= MAX_AGENTES)
    { printf("Capacidade de %d agentes atingida.\n", MAX_AGENTES); return; }
    for (int i = 0; i < quantidadeAgentes; i++)
        if (idsAgentes[i] > maior) maior = idsAgentes[i];
    if (maior >= 999999) { printf("Limite de identificadores atingido.\n"); return; }
    if (pedirCampo(nomesAgentes[indice], MAX_NOME, "Nome: ") != 1 ||
        pedirCampo(descricaoAgentes[indice], MAX_DESCRICAO, "Descricao: ") != 1 ||
        pedirCampo(categoriasAgentes[indice], MAX_CATEGORIA, "Categoria: ") != 1 ||
        pedirCampo(instrucoesAgentes[indice], MAX_INSTRUCOES, "Instrucoes: ") != 1)
    { printf("Cadastro cancelado.\n"); return; }
    idsAgentes[indice] = maior + 1;
    mediasAgentes[indice] = 0.0;
    quantidadesAvaliacoesAgentes[indice] = 0;
    quantidadeAgentes++;
    alteracoesPendentes = 1;
    printf("Agente ID %d cadastrado na memoria. Salve ao sair!\n", idsAgentes[indice]);
}

// Edita nome, descricao, categoria ou instrucoes do agente na RAM.
// -1 solicita saida; 1 volta a ficha; 0 indica indice invalido.
int editarAgente(int indiceAgente)
{
    char entrada[TAM], novoTexto[MAX_DESCRICAO];
    int opcao, retorno, capacidade;
    char *destino;
    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes) return 0;
    for (;;)
    {
        printf("\n=== EDITAR: %s (ID %d) ===\n", nomesAgentes[indiceAgente], idsAgentes[indiceAgente]);
        printf("[1] Nome\n");
        printf("[2] Descricao\n");
        printf("[3] Categoria\n");
        printf("[4] Instrucoes\n");
        printf("[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("Opcao: ");
        retorno = lerEntrada(entrada, sizeof(entrada));
        if (retorno == -1) return -1;
        if (retorno != 1) continue;
        opcao = validarEntrada(entrada, 4);
        if (opcao == -1) return -1;
        if (opcao == 0) return 1;
        destino = NULL;
        capacidade = 0;
        switch (opcao)
        {
            case 1:
                destino = nomesAgentes[indiceAgente];
                capacidade = MAX_NOME;
                break;
            case 2:
                destino = descricaoAgentes[indiceAgente];
                capacidade = MAX_DESCRICAO;
                break;
            case 3:
                destino = categoriasAgentes[indiceAgente];
                capacidade = MAX_CATEGORIA;
                break;
            case 4:
                destino = instrucoesAgentes[indiceAgente];
                capacidade = MAX_INSTRUCOES;
                break;
            default:
                break;
        }
        if (destino == NULL) { printf("Opcao invalida.\n"); continue; }
        printf("Novo texto: ");
        retorno = lerEntrada(novoTexto, capacidade);
        if (retorno == -1) return -1;
        if (retorno != 1 || !textoValido(novoTexto)) { printf("Texto invalido.\n"); continue; }
        if (strcmp(novoTexto, "-1") == 0) return -1;
        if (strcmp(destino, novoTexto) != 0)
        {
            strcpy(destino, novoTexto);
            alteracoesPendentes = 1;
            printf("Alteracao registrada na RAM.\n");
        }
    }
}

// Remove FISICAMENTE o agente e seus totais, deslocando TODOS os vetores.
// IDs dos agentes restantes nao sao modificados; a quantidade diminui.
int excluirAgente(int indiceAgente)
{
    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes) return 0;
    for (int i = indiceAgente; i < quantidadeAgentes - 1; i++)
    {
        idsAgentes[i] = idsAgentes[i+1];
        strcpy(nomesAgentes[i], nomesAgentes[i+1]);
        strcpy(descricaoAgentes[i], descricaoAgentes[i+1]);
        strcpy(categoriasAgentes[i], categoriasAgentes[i+1]);
        strcpy(instrucoesAgentes[i], instrucoesAgentes[i+1]);
        mediasAgentes[i] = mediasAgentes[i+1];
        quantidadesAvaliacoesAgentes[i] = quantidadesAvaliacoesAgentes[i+1];
    }
    quantidadeAgentes--;
    alteracoesPendentes = 1;
    return 1;
}