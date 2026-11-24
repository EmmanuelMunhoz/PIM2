#include <stdio.h>
#include <string.h>
#include "consultas.h"
#include "entrada.h"
#include "dados.h"
#include "cadastro.h"
#include "persistencia.h"
#include "menus.h"

// Exibe catalogo publico e permite abrir fichas de agentes existentes.
int catalogoAgentes(void)
{
    char entrada[TAM];
    int escolha;
    int leitura;
    do
    {
        printf("\n========== CATÁLOGO DE AGENTES ==========\n");
        for (int i = 0; i < quantidadeAgentes; i++)
        {
            printf("[%d] ID %d - %s - %s - ", i+1, idsAgentes[i], nomesAgentes[i], categoriasAgentes[i]);
            if (quantidadesAvaliacoesAgentes[i] == 0)
            {
                printf("Sem avaliações\n");
            }
            else
            {
                printf("Nota média: %.1f | Avaliações: %d\n", mediasAgentes[i], quantidadesAvaliacoesAgentes[i]);
            }
        }

        if (quantidadeAgentes == 0)
        {
            printf("Nenhum agente cadastrado.\n");
        }

        printf("\n[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("[-2] Salvar\n");
        printf("\nOpção: ");

        leitura = lerEntrada(entrada, sizeof(entrada));

        if (leitura == -1)
        {
            return -1;
        }

        if (leitura != 1)
        {
            continue;
        }

        if (strcmp(entrada, "-2") == 0)
        {
            salvarAlteracoes();
            continue;
        }

        escolha = validarEntrada(entrada, quantidadeAgentes);

        if (escolha == -1)
        {
            return -1;
        }

        if (escolha == 0)
        {
            return 0;
        }

        if (escolha < 1)
        {
            printf("Opção inválida.\n");
            continue;
        }

        int indice = escolha - 1;
        do
        {
            printf("\n========== FICHA PÚBLICA ==========\n");
            printf("ID: %d\n", idsAgentes[indice]);
            printf("Nome: %s\n", nomesAgentes[indice]);
            printf("Categoria: %s\n", categoriasAgentes[indice]);
            printf("Descrição: %s\n", descricaoAgentes[indice]);
            printf("Instruções: %s\n", instrucoesAgentes[indice]);
            if (quantidadesAvaliacoesAgentes[indice] == 0)
            {
                printf("Sem avaliações\n");
            }
            else
            {
                printf("Nota média: %.1f | Avaliações: %d\n", mediasAgentes[indice], quantidadesAvaliacoesAgentes[indice]);
            }
            printf("\n[1] Avaliar agente\n");
            printf("[0] Voltar\n");
            printf("[-1] Encerrar\n");
            printf("\nOpção: ");
            leitura = lerEntrada(entrada, sizeof(entrada));
            if (leitura == -1)
            {
                return -1;
            }
            if (leitura != 1)
            {
                continue;
            }
            escolha = validarEntrada(entrada, 1);
            if (escolha == -1)
            {
                return -1;
            }
            if (escolha == 0)
            {
                break;
            }
            if (escolha != 1)
            {
                printf("Opção inválida.\n");
                continue;
            }
            printf("Nota de 0 a 5 (ou -1 para encerrar): ");
            leitura = lerEntrada(entrada, sizeof(entrada));
            if (leitura == -1)
            {
                return -1;
            }
            if (leitura != 1)
            {
                continue;
            }
            int nota = validarEntrada(entrada, 5);
            if (nota == -1)
            {
                return -1;
            }
            if (nota < 0)
            {
                printf("Nota inválida.\n");
                continue;
            }
            printf("\nNota: %d\n", nota);
            printf("[1] Confirmar\n");
            printf("[0] Cancelar\n");
            printf("[-1] Encerrar\n");
            printf("Opção: ");
            leitura = lerEntrada(entrada, sizeof(entrada));
            if (leitura == -1)
            {
                return -1;
            }
            if (leitura != 1)
            {
                continue;
            }
            int opcaoConfirmacao = validarEntrada(entrada, 1);
            switch (opcaoConfirmacao)
            {
                case -1:
                    return -1;
                case 0:
                    printf("Avaliação cancelada.\n");
                    break;
                case 1:
                {
                    int registrada = registrarAvaliacao(indice, nota);
                    if (registrada)
                    {
                        printf("Avaliação registrada na memória RAM. Salve ao encerrar!\n");
                    }
                    else
                    {
                        printf("Falha ao registrar a avaliação.\n");
                    }
                    break;
                }
                default:
                    printf("Opção inválida. Avaliação cancelada.\n");
                    break;
            }
        } while (1);
    } while (1);
}

// Lista os agentes no painel administrativo; a escolha abre uma ficha.
int listarAgentesAdm(void)
{
    char entrada[TAM];
    int leitura;
    int escolha;
    int retorno;
    do
    {
        printf("\n========== LISTAGEM ADMINISTRATIVA ==========\n");
        for (int i = 0; i < quantidadeAgentes; i++)
        {
            printf("[%d] ID %d - %s - %s - ", i+1, idsAgentes[i], nomesAgentes[i], categoriasAgentes[i]);
            if (quantidadesAvaliacoesAgentes[i] == 0)
            {
                printf("Sem avaliações\n");
            }
            else
            {
                printf("Nota média: %.1f | Avaliações: %d\n", mediasAgentes[i], quantidadesAvaliacoesAgentes[i]);
            }
        }
        if (quantidadeAgentes == 0)
        {
            printf("Nenhum agente cadastrado.\n");
        }
        printf("\n[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("\nOpção: ");
        leitura = lerEntrada(entrada, sizeof(entrada));
        if (leitura == -1)
        {
            return -1;
        }
        if (leitura != 1)
        {
            continue;
        }
        escolha = validarEntrada(entrada, quantidadeAgentes);
        if (escolha == -1)
        {
            return -1;
        }
        if (escolha == 0)
        {
            return 0;
        }
        if (escolha < 1)
        {
            printf("Opção inválida.\n");
            continue;
        }
        retorno = fichaAgenteAdm(escolha - 1);
        if (retorno == -1)
        {
            return -1;
        }
    } while (1);
}

// Exibe ficha administrativa e abre edicao ou exclusao real do registro.
int fichaAgenteAdm(int indiceAgente)
{
    char entrada[TAM];
    int escolha;
    int leitura;
    int id;
    int retorno;
    if (indiceAgente < 0 || indiceAgente >= quantidadeAgentes)
    {
        return 0;
    }
    id = idsAgentes[indiceAgente];
    do
    {
        printf("\n========== FICHA ADMINISTRATIVA ==========\n");
        printf("ID: %d\n", id);
        printf("Nome: %s\n", nomesAgentes[indiceAgente]);
        printf("Categoria: %s\n", categoriasAgentes[indiceAgente]);
        printf("Descrição: %s\n", descricaoAgentes[indiceAgente]);
        printf("Instruções: %s\n", instrucoesAgentes[indiceAgente]);
        if (quantidadesAvaliacoesAgentes[indiceAgente] == 0)
        {
            printf("Sem avaliações\n");
        }
        else
        {
            printf("Nota média: %.1f | Avaliações: %d\n", mediasAgentes[indiceAgente], quantidadesAvaliacoesAgentes[indiceAgente]);
        }
        printf("\n[1] Editar\n");
        printf("[2] Excluir DEFINITIVAMENTE\n");
        printf("[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("Opção: ");
        leitura = lerEntrada(entrada, sizeof(entrada));
        if (leitura == -1)
        {
            return -1;
        }
        if (leitura != 1)
        {
            continue;
        }
        escolha = validarEntrada(entrada, 2);
        switch (escolha)
        {
            case -1:
                return -1;
            case 0:
                return 0;
            case 1:
                retorno = editarAgente(indiceAgente);
                if (retorno == -1)
                {
                    return -1;
                }
                continue;
            case 2:
                printf("Confirma a exclusão do agente com ID %d e de suas avaliações?\n", id);
                printf("[1] Sim\n");
                printf("[0] Não\n");
                printf("[-1] Encerrar\n");
                printf("Opção: ");
                leitura = lerEntrada(entrada, sizeof(entrada));
                if (leitura == -1)
                {
                    return -1;
                }
                if (leitura != 1)
                {
                    continue;
                }
                escolha = validarEntrada(entrada, 1);
                if (escolha == -1)
                {
                    return -1;
                }
                if (escolha == 1)
                {
                    excluirAgente(indiceAgente);
                    printf("Agente excluído da memória RAM. Salve ao encerrar!\n");
                    return 0;
                }
                printf("Exclusão cancelada.\n");
                continue;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (1);
}

// Procura um ID real, nao a posicao de exibicao.
int buscarAgentePorId(void)
{
    char entrada[20];
    int escolha;
    int leitura;
    printf("\n========== BUSCAR AGENTE POR ID ==========\n");
    printf("\n[0] Voltar\n");
    printf("[-1] Encerrar\n");
    printf("\nDigite o ID: ");
    leitura = lerEntrada(entrada, sizeof(entrada));
    if (leitura == -1)
    {
        return -1;
    }
    if (leitura != 1)
    {
        return 0;
    }
    escolha = validarEntrada(entrada, 999999);
    if (escolha == -1)
    {
        return -1;
    }
    if (escolha == 0)
    {
        return 0;
    }
    if (escolha == -2)
    {
        printf("ID inválido.\n");
        return 0;
    }
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (idsAgentes[i] == escolha)
        {
            return fichaAgenteAdm(i);
        }
    }
    printf("Agente não encontrado.\n");
    return 0;
}

// Encontra nomes contendo o trecho digitado e abre a ficha da posicao escolhida.
int buscarAgentePorNome(void)
{
    char trecho[MAX_NOME];
    char entrada[TAM];
    int posicoes[MAX_AGENTES];
    int encontrados = 0;
    int leitura;
    int escolha;

    printf("\n========== BUSCAR AGENTE POR NOME ==========\n");
    printf("\n[0] Voltar\n");
    printf("[-1] Encerrar\n");
    printf("\nNome ou parte do nome: ");

    leitura = lerEntrada(trecho, sizeof(trecho));

    if (leitura == -1)
    {
        return -1;
    }

    if (leitura != 1 || trecho[0] == '\0')
    {
        printf("Nome inválido.\n");
        return 0;
    }

    if (strcmp(trecho, "0") == 0)
    {
        return 0;
    }

    if (strcmp(trecho, "-1") == 0)
    {
        return -1;
    }


    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (strstr(nomesAgentes[i], trecho) != NULL)
        {
            posicoes[encontrados] = i;
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf("Nenhum agente encontrado.\n");
        return 0;
    }

    printf("\n========== RESULTADO DA BUSCA ==========\n");
    for (int i = 0; i < encontrados; i++)
    {
        int indice = posicoes[i];
        printf("[%d] ID %d - %s\n", i + 1, idsAgentes[indice], nomesAgentes[indice]);
    }

    printf("\n[0] Voltar\n");
    printf("[-1] Encerrar\n");
    printf("\nOpção: ");

    leitura = lerEntrada(entrada, sizeof(entrada));

    if (leitura == -1)
    {
        return -1;
    }
    if (leitura != 1)
    {
        return 0;
    }

    escolha = validarEntrada(entrada, encontrados);

    if (escolha == -1)
    {
        return -1;
    }
    if (escolha >= 1 && escolha <= encontrados)
    {
        int indiceAgente = posicoes[escolha - 1];

        return fichaAgenteAdm(indiceAgente);
    }

    return 0;
}
