#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int menu ()
{
    int escolha, leituraMenuOk;
    char entrada [TAM];
    do
    {
        printf("\n----------------------");
        printf("\nSeja Bem-Vindo\n");
        printf("----------------------\n\n");
        printf("Escolha uma das opções abaixo.\n\n");
        printf("[1] - Catálogo de Agentes.\n");
        printf("[2] - Painel Administrativo (acesso restrito).\n\n");
        printf("[0] - Sair\n");
        printf("[-1] Encerrar o sistema\n\n");
        printf("Qual opção você deseja escolher: ");

        leituraMenuOk = lerEntrada(entrada,sizeof(entrada));

        if (leituraMenuOk == 1)
        {
            escolha = validarEntrada(entrada,2);

            switch (escolha)
            {

                case -1:
                {
                    return -1;
                }
                case 1:
                {
                    int retornoCatalogo = catalogoAgentes();

                    if (retornoCatalogo == -1)
                    {
                        return -1;
                    }

                    break;
                }
                case 2:
                {
                    int validarEntradaAdm = autenticarAdm ();

                    if (validarEntradaAdm == 0)
                    {
                        validarEntradaAdm = menuAdm();

                        if (validarEntradaAdm == -1)
                        {
                            return -1;
                        }
                    }
                    if (validarEntradaAdm == -1)
                    {
                        return -1;
                    }
                    break;
                }
                case 0:
                {
                    printf("Você escolheu a opção: [%d]\n", escolha);
                    break;
                }
                default:
                {
                    printf("%s",valor_digitado_errado);
                    leituraMenuOk = 0;
                }
            }
        }
        if (leituraMenuOk == -1)
        {
            return -1;
        }
        if (leituraMenuOk == 0)
        {
            continue;
        }

    }while(leituraMenuOk != 1 || escolha != 0);
    return escolha;
}

int menuAdm()
{
    char entradaMenu[TAM];
    int retornoEntradaMenu = 0;
    int escolha;

    do
    {
        printf("\n\n========== PAINEL ADMINISTRATIVO ==========\n\n");

        printf("[1] Cadastrar agente\n");
        printf("[2] Listar agentes\n");
        printf("[3] Buscar agente por ID\n");
        printf("[4] Buscar agente por nome\n\n");
        printf("[0] Voltar ao menu principal\n");
        printf("[-1] Encerrar o sistema\n\n");

        printf("Escolha uma opção: ");

        retornoEntradaMenu = lerEntrada(entradaMenu,sizeof(entradaMenu));

        if (retornoEntradaMenu == 1)
            {
                escolha = validarEntrada(entradaMenu,4);

                switch (escolha)
                {

                    case -1:
                    {
                        return -1;
                    }
                    case 1:
                    {
                        cadastrarAgente();
                        break;
                    }
                    case 2:
                    {
                        int retornoListagem = listarAgentesAdm();

                        if (retornoListagem == -1)
                        {
                            return -1;
                        }

                        break;
                    }
                    case 3:
                    {
                        if (buscarAgentePorId() == -1)
                        {
                            return -1;
                        }

                        break;
                    }

                    case 4:
                    {
                        if (buscarAgentePorNome() == -1)
                        {
                            return -1;
                        }

                        break;
                    }
                    case 0:
                    {
                        return 0;
                    }
                    default:
                    {
                        printf("%s",valor_digitado_errado);
                        retornoEntradaMenu = 0;
                    }
                }
            }
            if (retornoEntradaMenu == -1)
            {
                return -1;
            }
            if (retornoEntradaMenu == 0)
            {
                continue;
            }
    }while(1);

    return 0;
}