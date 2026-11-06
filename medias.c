#include "medias.h"

// Media incremental sem somaNotas no JSON. Arredondar so ao EXIBIR.
double calcularNovaMedia(double mediaAtual, int quantidadeAnterior, int novaNota)
{
    if (quantidadeAnterior == 0) return (double)novaNota;
    return (mediaAtual * quantidadeAnterior + novaNota) / (quantidadeAnterior + 1);
}
