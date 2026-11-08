
#include <stdio.h>
#include "menus.h"
#include "entrada.h"
#include "dados.h"
#include "autenticacao.h"
#include "cadastro.h"
#include "consultas.h"
#include "persistencia.h"

// Salva apenas quando houver alteracoes e devolve o controle ao menu atual.
void salvarAlteracoes(void)
{
    int salvo;

    if (!alteracoesPendentes)
    {
        printf("Nao ha alteracoes para salvar.\n");
        return;
    }

    salvo = salvarAgentes();
    if (salvo)
    {
        printf("Alteracoes salvas em dados/agentes.json.\n");
    }
    else
    {
        printf("Falha ao salvar. Programa continua aberto.\n");
    }
}

// Confirma saida com alteracoes pendentes.
// 1 = sair, 0 = cancelar, -1 = erro/EOF.
int confirmarSaida(void)
{
    char entrada[TAM];
    int escolha;
    int leitura;
    int salvo;

    if (!alteracoesPendentes)
    {
        return 1;
    }

    do
    {
        printf("\nVoce possui alteracoes nao salvas.\n");
        printf("[1] Salvar e sair\n");
        printf("[2] Sair sem salvar\n");
        printf("[0] Cancelar e voltar\n");
        printf("Escolha: ");

        leitura = lerEntrada(entrada, TAM);

        if (leitura == -1)
        {
            return -1;
        }

        if (leitura != 1)
        {
            continue;
        }

        escolha = validarEntrada(entrada, 2);

        switch (escolha)
        {
            case 0:
                return 0;

            case 1:
                salvo = salvarAgentes();
                if (salvo)
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

    } while (1);
}

// Exibe o menu principal e controla o encerramento.
int menu(void)
{
    char entrada[TAM];
    int escolha;
    int leitura;
    int retorno;
    int sair;

    do
    {
        printf("\n========== NEXT HOST ==========\n");
        printf("[1] Catalogo de agentes\n");
        printf("[2] Painel administrativo\n");
        printf("[0] Sair\n");
        printf("\nOpcao: ");

        leitura = lerEntrada(entrada, TAM);

        if (leitura == -1)
        {
            return -1;
        }

        if (leitura == 0)
        {
            continue;
        }

        escolha = validarEntrada(entrada, 2);

        switch (escolha)
        {
            case -1:
            case 0:
                sair = confirmarSaida();

                if (sair == 1)
                {
                    return 0;
                }

                if (sair == -1)
                {
                    return -1;
                }

                break;

            case 1:
                retorno = catalogoAgentes();

                if (retorno == -1)
                {
                    sair = confirmarSaida();

                    if (sair == 1)
                    {
                        return 0;
                    }

                    if (sair == -1)
                    {
                        return -1;
                    }
                }

                break;

            case 2:
                retorno = autenticarAdm();

                if (retorno == 1)
                {
                    retorno = menuAdm();
                }

                if (retorno == -1)
                {
                    sair = confirmarSaida();

                    if (sair == 1)
                    {
                        return 0;
                    }

                    if (sair == -1)
                    {
                        return -1;
                    }
                }
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (1);
}

// Encaminha as opcoes do painel administrativo.
int menuAdm(void)
{
    char entrada[TAM];
    int escolha;
    int leitura;
    int retorno;

    do
    {
        printf("\n========== PAINEL ADMINISTRATIVO ==========\n");
        printf("[1] Cadastrar agente\n");
        printf("[2] Listar agentes\n");
        printf("[3] Buscar por ID\n");
        printf("[4] Buscar por nome\n");
        printf("[5] Salvar\n");
        printf("[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("Opcao: ");

        leitura = lerEntrada(entrada, TAM);

        if (leitura == -1)
        {
            return -1;
        }

        if (leitura != 1)
        {
            continue;
        }

        escolha = validarEntrada(entrada, 5);
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

            case 5:
                salvarAlteracoes();
                break;

            default:
                printf("\033[1;31mOpcao invalida.\033[0m\n");
                break;
        }

        if (retorno == -1)
        {
            return -1;
        }

    } while (1);
}
