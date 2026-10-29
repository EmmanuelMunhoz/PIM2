#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

void limparBuffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int validarEntrada(char entrada[], int limiteMaximo)
{
    int i = 0;
    int numero;

    if (entrada[0] == '-' && entrada[1] == '1' && (entrada[2] == '\0' || entrada[2] == '\n'))
    {
        return -1;
    }

    if (entrada[0] == '\0' || entrada[0] == '\n')
    {
        return -2;
    }

    while (entrada[i] != '\0' && entrada[i] != '\n')
    {
        if (entrada[i] < '0' || entrada[i] > '9')
        {
            return -2;
        }

        i++;
    }

    numero = atoi(entrada);

    if (numero >= 0 && numero <= limiteMaximo)
    {
        return numero;
    }

    return -2;
}


int lerEntrada(char entrada[], int capacidade)
{

    if(capacidade <2)
    {
        return -1;
    }

    int leituraOK;
    leituraOK = (fgets(entrada, capacidade, stdin) != NULL);

    if(leituraOK == 1)
    {
        if(strchr(entrada,'\n') != NULL)
        {
            entrada[strcspn(entrada,"\n")] = '\0';
            return 1;
        }
        else
        {
            int procurarN = getchar();
            if (procurarN == '\n')
            {
                return 1;
            }
            if (procurarN == EOF)
            {
                if(ferror(stdin))
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            limparBuffer();
            printf("\033[31m ⚠️  Entrada excedeu o tamanho máximo permitido ⚠️ \033[0m\n\n");
            return 0;
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
}
