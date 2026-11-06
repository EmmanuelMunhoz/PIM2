#include <stdio.h>
#include "persistencia.h"
#include "menus.h"

// Inicializa vetores pelo unico JSON, executa menus e encerra corretamente.
int main(void)
{
    int retorno;
    if (!carregarAgentes())
    {
        printf("Falha ao carregar os agentes. Programa encerrado.\n");
        return 1;
    }
    retorno = menu();
    if (retorno == -1)
    {
        printf("Encerramento por erro ou fim da entrada.\n");
        return 1;
    }
    return 0;
}
