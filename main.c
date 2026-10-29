#include <stdio.h>
#include "functions.h"

int main ()
{
    if (carregarAgentes() == 0 || carregarControle() == 0)
    {
        printf("Falha ao carregar os dados persistentes. Programa encerrado.\n");
        return 1;
    }

    if (carregarAvaliacoes() == 0)
    {
        printf("Erro ao carregar avaliacoes!\n");
        return 1;
    }

    int retorno = menu ();

    if (retorno == -1)
    {
        return 1;
    }
    return 0;
}