#include <stdio.h>
#include <string.h>
#include "functions.h"

int catalogoAgentes(void)
{
    int i;
    int numeroExibicao;
    int escolha, leituraMenuOk;
    char entrada[TAM];

    do
    {
        numeroExibicao = 0;
        int posicoesAgentes[50];

        printf("\n========== CATALOGO DE AGENTES ==========\n\n");

        for (i = 0; i < quantidadeAgentes; i++)
        {
            if (statusAgentes[i] == 1)
            {
                posicoesAgentes[numeroExibicao] = i;
                numeroExibicao++;

                printf("[%d] %s - %s - ",numeroExibicao,nomesAgentes[i],categoriasAgentes[i]);

                if (possuiMediaAgentes[i] == 1)
                {
                    printf("Nota: %.1f\n",mediasAgentes[i]);
                }
                else
                {
                    printf("Sem avaliacoes\n");
                }
            }
        }

        if (numeroExibicao == 0)
        {
            printf("Nenhum agente ativo disponivel.\n");
        }

        printf("\n[0] Voltar ao menu principal");
        printf("\n[-1] Sair do sistema");
        printf("\n\nQual opcao voce deseja escolher: ");

        leituraMenuOk = lerEntrada(entrada,sizeof(entrada));

        if (leituraMenuOk == -1)
        {
            return -1;
        }

        if (leituraMenuOk == 0)
        {
            printf("\nEntrada invalida!\n");
            continue;
        }

        escolha = validarEntrada(entrada,50);

        if (escolha == 0)
        {
            return 0;
        }

        if (escolha == -1)
        {
            return -1;
        }

        if (escolha >= 1 && escolha <= numeroExibicao)
        {
            int indiceAgente = posicoesAgentes[escolha - 1];
            int escolhaFicha, leituraFichaOk;
            char entradaFicha[TAM];

            do
            {
                printf("\n========== FICHA DO AGENTE ==========\n\n");
                printf("Nome: %s\n",nomesAgentes[indiceAgente]);
                printf("Categoria: %s\n",categoriasAgentes[indiceAgente]);
                printf("Descricao: %s\n",descricaoAgentes[indiceAgente]);
                printf("Instrucoes: %s\n",instrucoesAgentes[indiceAgente]);

                if (possuiMediaAgentes[indiceAgente] == 1)
                {
                    printf("Nota media: %.1f\n",mediasAgentes[indiceAgente]);
                }
                else
                {
                    printf("Nota media: Sem avaliacoes\n");
                }

                printf("\n[1] Avaliar agente");
                printf("\n[2] Voltar ao catalogo");
                printf("\n[-1] Encerrar o sistema");
                printf("\n\nEscolha uma opcao: ");

                leituraFichaOk = lerEntrada(entradaFicha,sizeof(entradaFicha));

                if (leituraFichaOk == -1)
                {
                    return -1;
                }

                if (leituraFichaOk == 0)
                {
                    printf("\nEntrada invalida!\n");
                    continue;
                }

                escolhaFicha = validarEntrada(entradaFicha,2);

                if (escolhaFicha == -1)
                {
                    return -1;
                }

                if (escolhaFicha == 2)
                {
                    break;
                }

                if (escolhaFicha == 1)
                {
                    int nota, escolhaConfirmacao, leituraNotaOk, leituraConfirmacaoOk;
                    char entradaNota[TAM], entradaConfirmacao[TAM];

                    do
                    {
                        printf("\n========== AVALIAR AGENTE ==========\n");
                        printf("\nAgente: %s\n",nomesAgentes[indiceAgente]);
                        printf("Digite uma nota de 0 a 5: ");

                        leituraNotaOk = lerEntrada(entradaNota,sizeof(entradaNota));

                        if (leituraNotaOk == -1)
                        {
                            return -1;
                        }

                        if (leituraNotaOk == 0)
                        {
                            printf("\nEntrada invalida!\n");
                            continue;
                        }

                        nota = validarEntrada(entradaNota,5);

                        if (nota == -1)
                        {
                            return -1;
                        }

                        if (nota == -2)
                        {
                            printf("\nNota invalida! Digite um numero de 0 a 5.\n");
                            continue;
                        }

                        do
                        {
                            printf("\nNota escolhida: %d\n",nota);
                            printf("\n[1] Confirmar avaliacao");
                            printf("\n[2] Alterar nota");
                            printf("\n[0] Cancelar avaliacao");
                            printf("\n[-1] Encerrar o sistema");
                            printf("\n\nEscolha uma opcao: ");

                            leituraConfirmacaoOk = lerEntrada(entradaConfirmacao,sizeof(entradaConfirmacao));

                            if (leituraConfirmacaoOk == -1)
                            {
                                return -1;
                            }

                            if (leituraConfirmacaoOk == 0)
                            {
                                printf("\nEntrada invalida!\n");
                                continue;
                            }

                            escolhaConfirmacao = validarEntrada(entradaConfirmacao,2);

                            if (escolhaConfirmacao == -1)
                            {
                                return -1;
                            }

                            if (escolhaConfirmacao == 1)
                            {
                                if (registrarAvaliacao(indiceAgente,nota) == 1)
                                {
                                    printf("\nAvaliacao salva com sucesso!\n");
                                }
                                else
                                {
                                    printf("\nNao foi possivel salvar a avaliacao.\n");
                                }
                                break;
                            }

                            if (escolhaConfirmacao == 2)
                            {
                                break;
                            }

                            if (escolhaConfirmacao == 0)
                            {
                                printf("\nAvaliacao cancelada.\n");
                                break;
                            }

                            printf("\nOpcao invalida!\n");

                        } while (1);

                        if (escolhaConfirmacao == 2)
                        {
                            continue;
                        }

                        break;

                    } while (1);

                    continue;
                }


                printf("\nOpcao invalida!\n");

            } while (1);

            continue;
        }
        printf("\nOpcao ainda nao implementada ou invalida.\n");
    } while (1);
}


int listarAgentesAdm(void)
{
    int i, escolha, leituraOk;
    char entrada[TAM];

    do
    {
        printf("\n========== LISTAGEM ADMINISTRATIVA ==========\n\n");

        for (i = 0; i < quantidadeAgentes; i++)
        {
            printf("[%d] %s - %s - ",i + 1,nomesAgentes[i],categoriasAgentes[i]);

            if (possuiMediaAgentes[i] == 1)
            {
                printf("Nota: %.1f - ",mediasAgentes[i]);
            }
            else
            {
                printf("Sem avaliacoes - ");
            }

            if (statusAgentes[i] == 1)
            {
                printf("ATIVO\n");
            }
            else
            {
                printf("INATIVO\n");
            }
        }

        if (quantidadeAgentes == 0)
        {
            printf("Nenhum agente cadastrado.\n");
        }

        printf("\n[0] Voltar ao painel administrativo");
        printf("\n[-1] Encerrar o sistema");
        printf("\n\nEscolha uma opcao: ");

        leituraOk = lerEntrada(entrada,sizeof(entrada));

        if (leituraOk == -1)
        {
            return -1;
        }

        if (leituraOk == 0)
        {
            printf("\nEntrada invalida!\n");
            continue;
        }

        escolha = validarEntrada(entrada,MAX_AGENTES);

        if (escolha == -1)
        {
            return -1;
        }

        if (escolha == 0)
        {
            return 0;
        }

        if (escolha >= 1 && escolha <= quantidadeAgentes)
        {
            int indiceAgente = escolha - 1;

            if (fichaAgenteAdm(indiceAgente) == -1)
            {
                return -1;
            }

            continue;
        }

        printf("\nOpcao invalida!\n");

    } while (1);
}


int fichaAgenteAdm(int indiceAgente)
{
    int escolha, leituraOk;
    char entrada[TAM];

    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes)
    {
        printf("\nAgente invalido!\n");
        return 0;
    }

    do
    {
        printf("\n========== FICHA ADMINISTRATIVA ==========\n\n");
        printf("ID: %d\n",idsAgentes[indiceAgente]);
        printf("Nome: %s\n",nomesAgentes[indiceAgente]);
        printf("Categoria: %s\n",categoriasAgentes[indiceAgente]);
        printf("Descricao: %s\n",descricaoAgentes[indiceAgente]);
        printf("Instrucoes: %s\n",instrucoesAgentes[indiceAgente]);
        printf("Status: %s\n",statusAgentes[indiceAgente] == 1 ? "ATIVO" : "INATIVO");

        if (possuiMediaAgentes[indiceAgente] == 1)
        {
            printf("Nota media: %.1f\n",mediasAgentes[indiceAgente]);
        }
        else
        {
            printf("Nota media: Sem avaliacoes\n");
        }

        printf("\n[1] Editar informacoes");
        printf("\n[0] Voltar a consulta");
        printf("\n[-1] Encerrar o sistema");
        printf("\n\nEscolha uma opcao: ");

        leituraOk = lerEntrada(entrada,sizeof(entrada));

        if (leituraOk == -1)
        {
            return -1;
        }

        if (leituraOk != 1)
        {
            printf("\nEntrada invalida!\n");
            continue;
        }

        escolha = validarEntrada(entrada,1);

        if (escolha == -1)
        {
            return -1;
        }

        if (escolha == 0)
        {
            return 0;
        }

        if (escolha == 1)
        {
            if (editarAgente(indiceAgente) == -1)
            {
                return -1;
            }

            continue;
        }

        printf("\nOpcao invalida!\n");

    } while (1);
}


int buscarAgentePorId(void)
{
    char entrada[20];
    int idBuscado, leituraOk;

    printf("\n========== BUSCAR AGENTE POR ID ==========\n");
    printf("\nDigite o ID do agente:");
    printf("\n[0] Voltar");
    printf("\n[-1] Encerrar o sistema");
    printf("\n\nID: ");

    leituraOk = lerEntrada(entrada,sizeof(entrada));

    if (leituraOk == -1)
    {
        return -1;
    }

    if (leituraOk != 1)
    {
        printf("\nEntrada invalida!\n");
        return 0;
    }

    idBuscado = validarEntrada(entrada,999999);

    if (idBuscado == -1)
    {
        return -1;
    }

    if (idBuscado == 0)
    {
        return 0;
    }

    if (idBuscado == -2)
    {
        printf("\nID invalido!\n");
        return 0;
    }

    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (idsAgentes[i] == idBuscado)
        {
            return fichaAgenteAdm(i);
        }
    }

    printf("\nAgente nao encontrado!\n");
    return 0;
}


int buscarAgentePorNome(void)
{
    char nomeBusca[MAX_NOME];
    char entrada[TAM];
    int posicoes[MAX_AGENTES];
    int encontrados = 0;
    int leituraOk, escolha;

    printf("\n========== BUSCAR AGENTE POR NOME ==========\n");
    printf("\nDigite o nome ou parte do nome:");
    printf("\n[-1] Encerrar o sistema");
    printf("\n\nNome: ");

    leituraOk = lerEntrada(nomeBusca,sizeof(nomeBusca));

    if (leituraOk == -1)
    {
        return -1;
    }

    if (leituraOk != 1 || nomeBusca[0] == '\0')
    {
        printf("\nNome invalido!\n");
        return 0;
    }

    if (strcmp(nomeBusca,"-1") == 0)
    {
        return -1;
    }

    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (strstr(nomesAgentes[i],nomeBusca) != NULL)
        {
            posicoes[encontrados] = i;
            encontrados++;

            printf("\n[%d] ID: %d - %s - %s",
                   encontrados,idsAgentes[i],nomesAgentes[i],
                   statusAgentes[i] == 1 ? "ATIVO" : "INATIVO");
        }
    }

    if (encontrados == 0)
    {
        printf("\nNenhum agente encontrado!\n");
        return 0;
    }

    printf("\n\n[0] Voltar ao painel administrativo");
    printf("\n[-1] Encerrar o sistema");
    printf("\n\nEscolha um agente: ");

    leituraOk = lerEntrada(entrada,sizeof(entrada));

    if (leituraOk == -1)
    {
        return -1;
    }

    if (leituraOk != 1)
    {
        printf("\nEntrada invalida!\n");
        return 0;
    }

    escolha = validarEntrada(entrada,encontrados);

    if (escolha == -1)
    {
        return -1;
    }

    if (escolha == 0)
    {
        return 0;
    }

    if (escolha < 1 || escolha > encontrados)
    {
        printf("\nOpcao invalida!\n");
        return 0;
    }

    return fichaAgenteAdm(posicoes[escolha - 1]);
}
