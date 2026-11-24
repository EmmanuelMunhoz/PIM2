#ifndef PIM2_ENTRADA_H
#define PIM2_ENTRADA_H
void limparBuffer(void);
// Retorna um número de 0 a limiteMaximo (incluindo 0 e 1 quando válidos),
// -1 para o literal "-1" ou -2 para entrada inválida.
int validarEntrada(char entrada[], int limiteMaximo);

// A capacidade inclui o '\0'. Retorna 1 para leitura aceita, 0 para linha
// longa ou capacidade menor que 2, e -1 para fim da entrada sem linha ou erro.
int lerEntrada(char entrada[], int capacidade);
#endif