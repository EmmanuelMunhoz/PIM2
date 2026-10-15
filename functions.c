#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

char valor_digitado_errado[] = "\033[31m⚠️  Valor digitado Invalido!⚠️\033[0m\n\n"; //variavel global de erro
int validarEntrada(char entrada[]);


int menu ()
{
    int escolha, leituraOk;
    char entrada [3];
    do
    {
        printf("----------------------");
        printf("\nSeja Bem-Vindo\n");
        printf("----------------------\n\n");
        printf("Escolha uma das opções abaixo.\n\n");
        printf("[1] - Catálogo de Agentes.\n");
        printf("[2] - Painel Administrativo (acesso restrito).\n");
        printf("[0] - Sair\n\n");
        printf("Qual opção você deseja escolher: ");

        leituraOk = (fgets(entrada, sizeof entrada, stdin) != NULL);

        if (leituraOk == 1)
        {
            if (strchr(entrada, '\n') != NULL)
            {
                escolha = validarEntrada(entrada);

                switch (escolha)
                {
                    case 1:
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    case 2:
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    case 0:
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    default:
                        printf("%s",valor_digitado_errado);
                        leituraOk = 0;
                }
            }
            else
            {
                limparBuffer();
                printf("%s",valor_digitado_errado);
                leituraOk = 0;
            }

        }
        else
        {
            if (feof(stdin))
            {
                printf("Entrada encerrada (EOF).\n");
            }
            else if (ferror(stdin))
            {
                printf("Erro ao ler a entrada.\n");
            }
            else
            {
                printf("Falha de leitura desconhecida.\n");
            }

            return -1;
        }
    }while(leituraOk != 1);
    return escolha;
}

int validarEntrada(char entrada[])
{

    if(entrada[0] >= '0' && entrada[0] <= '2')
    {
        if(entrada[1] == '\n' || entrada [1] == '\0')
        {
            return atoi(entrada);
        }

    }
    return -1;
}

void limparBuffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}