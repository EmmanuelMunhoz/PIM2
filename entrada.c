#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

// Descarta o restante de uma entrada que ultrapassou a capacidade.
void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Aceita inteiros entre zero e o limite, ou -1 (pedido de encerramento).
// Devolve -2 para texto vazio, letras, numeros fora do limite e negativos invalidos.
int validarEntrada(char entrada[], int limiteMaximo)
{
    int i = 0;
    int numero;
    if (strcmp(entrada, "-1") == 0) return -1;
    if (entrada[0] == '\0') return -2;
    while (entrada[i] != '\0')
    {
        if (entrada[i] < '0' || entrada[i] > '9') return -2;
        i++;
    }
    // Limita o tamanho antes de converter para evitar estouro no atoi.
    if (i > 6) return -2;
    numero = atoi(entrada);
    if (numero >= 0 && numero <= limiteMaximo) return numero;
    return -2;
}

// Le uma linha da entrada padrao: 1=sucesso, 0=texto longo, -1=EOF/erro.
int lerEntrada(char entrada[], int capacidade)
{
    int c;
    int posicao;
    char *resultadoLeitura;

    if (capacidade < 2)
    {
        return 0;
    }

    resultadoLeitura = fgets(entrada, capacidade, stdin);
    if (resultadoLeitura == NULL)
    {
        return -1;
    }

    posicao = strcspn(entrada, "\n");
    if (entrada[posicao] == '\n')
    {
        entrada[posicao] = '\0';
        return 1;
    }

    // Verifica se o texto terminou no limite permitido ou se ultrapassou esse limite.
    c = getchar();
    if (c == '\n' || c == EOF)
    {
        if (ferror(stdin))
        {
            return -1;
        }
        return 1;
    }

    limparBuffer();
    
    printf("Entrada excedeu o tamanho maximo permitido.\n");
    return 0;
}
