#include <stdio.h>
#include<string.h>
#include "functions.h"

char valor_digitado_errado[] = "\033[31m⚠️  Valor digitado Invalido!⚠️\033[0m\n\n"; //variavel global de erro
void validarEntrada(char entrada[]);


int menu ()
{
    int escolha, validarEntrada;
    char entrada [20];
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


        if (fgets(entrada, sizeof entrada, stdin) != NULL)
        {
            //executar outra função agora
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
                    validarEntrada = 0;
            }
        }
        else
        {
            printf("\033[31mA leitura falho\033[0m");
            validarEntrada = 0;
        }


    }while(validarEntrada != 1);
    return escolha;
}

void limparBuffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void validarEntrada(char entrada[])
{

}