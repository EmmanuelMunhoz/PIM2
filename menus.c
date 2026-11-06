#include <stdio.h>
#include "menus.h"
#include "entrada.h"
#include "dados.h"
#include "autenticacao.h"
#include "cadastro.h"
#include "consultas.h"
#include "persistencia.h"

// Confirma saida com alteracoes pendentes. 1=sair, 0=cancelar, -1=erro/EOF.
// Quando o salvamento falha, continua no programa e permite outra tentativa.
int confirmarSaida(void)
{
    char entrada[TAM];
    int escolha, leitura;
    if (!alteracoesPendentes) return 1;
    for (;;)
    {
        printf("\nVoce possui alteracoes nao salvas.\n");
        printf("[1] Salvar e sair\n");
        printf("[2] Sair sem salvar\n");
        printf("[0] Cancelar e voltar\n");
        printf("Escolha: ");
        leitura = lerEntrada(entrada, TAM);
        if (leitura == -1) return -1;
        if (leitura != 1) continue;
        escolha = validarEntrada(entrada, 2);
        switch (escolha)
        {
            case 0:
                return 0;
            case 1:
                if (salvarAgentes())
                {
                    printf("Alteracoes salvas em dados/agentes.json.\n");
                    return 1;
                }
                printf("Falha ao salvar. Programa continua aberto.\n");
                break;
            case 2:
                return 1;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

// Exibe o menu principal; centraliza a confirmacao de saida por 0 ou -1.

int menu(void)
{
    char entrada[TAM];
    int escolha, leitura, retorno, sair;

    do
    {
        printf("\n========== AI AGENT REGISTRY ==========\n");
        printf("[1] Catalogo de agentes\n");
        printf("[2] Painel administrativo\n");
        printf("[0] Sair\n");
        printf("[-1] Encerrar\n");
        printf("Opcao: ");

        leitura = lerEntrada(entrada, TAM);

        if (leitura == -1) return -1;
        if (leitura != 1) continue;

        escolha = validarEntrada(entrada, 2);

        switch (escolha)
        {
            case -1:
            case 0:
                sair = confirmarSaida();
                if (sair == 1) return 0;
                if (sair == -1) return -1;
                break;

            case 1:
                retorno = catalogoAgentes();
                if (retorno == -1)
                {
                    sair = confirmarSaida();
                    if (sair == 1) return 0;
                    if (sair == -1) return -1;
                }
                break;

            case 2:
                retorno = autenticarAdm();
                if (retorno == 1) retorno = menuAdm();
                if (retorno == -1)
                {
                    sair = confirmarSaida();
                    if (sair == 1) return 0;
                    if (sair == -1) return -1;
                }
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (1);
}

// Encaminha a escolha administrativa para cadastro, listagem e buscas.
int menuAdm(void)
{
    char entrada[TAM];
    int escolha, leitura, retorno;
    for (;;)
    {
        printf("\n========== PAINEL ADMINISTRATIVO ==========\n");
        printf("[1] Cadastrar agente\n");
        printf("[2] Listar agentes\n");
        printf("[3] Buscar por ID\n");
        printf("[4] Buscar por nome\n");
        printf("[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("Opcao: ");

        leitura = lerEntrada(entrada, TAM);

        if (leitura == -1) return -1;
        if (leitura != 1) continue;

        escolha = validarEntrada(entrada, 4);
        retorno = 0;

        switch (escolha)
        {
            case -1:
                return -1;
            case 0:
                return 0;
            case 1:
                cadastrarAgente();
                break;
            case 2:
                retorno = listarAgentesAdm();
                break;
            case 3:
                retorno = buscarAgentePorId();
                break;
            case 4:
                retorno = buscarAgentePorNome();
                break;
            default:
                printf("\033[1;31mOpcao invalida.\033[0m\n");
                break;
        }
        if (retorno == -1) return -1;
    }
}