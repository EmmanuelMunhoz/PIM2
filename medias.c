#include "medias.h"

// Mantem a media com precisao de double; o catalogo exibira com %.1f.
double calcularNovaMedia(double mediaAtual, int quantidadeAnterior, int novaNota)
{
    if (quantidadeAnterior == 0)
    {
        return (double)novaNota;
    }

    return (mediaAtual * quantidadeAnterior + novaNota) / (quantidadeAnterior + 1);
}
