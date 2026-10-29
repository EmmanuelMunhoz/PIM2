#include <stdio.h>    // Entrada e saida de dados, como printf().
#include <string.h>   // Manipulacao de strings, como strcmp().
#include <stdlib.h>   // Funcoes utilitarias do C (nao utilizada diretamente aqui).
#include "functions.h" // Declaracoes das funcoes compartilhadas entre arquivos.

int autenticarAdm(void)
{
    int leituraValidarEntradaOk;
    const char senhaAdm[] = "@Adminunip";
    char senhaDigitada[20];
    int tentativas = 3;

    do
    {
        printf("Qual a senha ADM: ");
        leituraValidarEntradaOk = lerEntrada(senhaDigitada,sizeof(senhaDigitada));

        if(leituraValidarEntradaOk == 1)
        {
            if(strcmp (senhaDigitada,senhaAdm) != 0)
            {
                printf("\033[31m\nSenha Incorreta, tentativas restantes [%d] tentativa(s)\033[0m\n", tentativas - 1);
                tentativas --;
            }

            if(strcmp (senhaDigitada,senhaAdm) == 0)
            {
                printf("\n\033[32mAcesso Permitido\033[0m");
                return 0;
            }
        }
        if (leituraValidarEntradaOk == -1)
        {
            return -1;
        }
        if (leituraValidarEntradaOk == 0) // Se a entrada ultrapassar o limite permitido, desconta uma tentativa e solicita a senha novamente.
        {
            tentativas --;
            continue;
        }
    }while (tentativas > 0);

    printf("\033[31mAcesso Negado\033[0m\n");
    printf("Voltando ao Menu.....\n");
    return 1;
}
