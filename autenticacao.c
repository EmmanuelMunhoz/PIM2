#include <stdio.h>
#include <string.h>
#include "autenticacao.h"
#include "entrada.h"

// Verifica a senha do painel administrativo com ate tres tentativas.
// 1 = autenticado, 0 = acesso negado, -1 = erro/EOF.
int autenticarAdm(void)
{
    const char senhaAdm[] = "@Adminunip";
    char senhaDigitada[20];
    int tentativas = 3;
    int retorno;

    while (tentativas > 0)
    {
        printf("\nQual a senha ADM: ");
        retorno = lerEntrada(senhaDigitada, sizeof(senhaDigitada));

        if (retorno == -1)
        {
            return -1;
        }

        if (retorno == 1 && strcmp(senhaDigitada, senhaAdm) == 0)
        {
            printf("\n\033[1;32mAcesso permitido!\033[0m\n");
            return 1;
        }

        tentativas--;

        printf("\033[1;31mSenha invalida. Tentativas restantes: %d\033[0m\n", tentativas);
    }
    printf("\033[1;31mAcesso negado. Retornando ao menu.\033[0m\n");
    return 0;
}