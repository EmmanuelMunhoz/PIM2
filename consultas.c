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
        printf("\n========== CATALOGO DE AGENTES ==========\n");
        for (int i = 0; i < quantidadeAgentes; i++)
        {
            printf("[%d] ID %d - %s - %s - ", i+1, idsAgentes[i], nomesAgentes[i], categoriasAgentes[i]);
            if (quantidadesAvaliacoesAgentes[i] == 0)
            {
                printf("Sem avaliacoes\n");
            }
            else
            {
                printf("Media: %.2f (%d avaliacoes)\n", mediasAgentes[i], quantidadesAvaliacoesAgentes[i]);
            }
        }

        if (quantidadeAgentes == 0)
        {
            printf("Nenhum agente cadastrado.\n");
        }

        printf("\n[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("[-2] Salvar\n");
        printf("\nEscolha uma opcao: ");

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
            printf("Opcao invalida.\n");
            continue;
        }

        int indice = escolha - 1;
        do
        {
            printf("\n========== FICHA PUBLICA ==========\n");
            printf("ID: %d\n", idsAgentes[indice]);
            printf("Nome: %s\n", nomesAgentes[indice]);
            printf("Categoria: %s\n", categoriasAgentes[indice]);
            printf("Descricao: %s\n", descricaoAgentes[indice]);
            printf("Instrucoes: %s\n", instrucoesAgentes[indice]);
            if (quantidadesAvaliacoesAgentes[indice] == 0)
            {
                printf("Nota media: Sem avaliacoes\n");
            }
            else
            {
                printf("Nota media: %.2f | Avaliacoes: %d\n", mediasAgentes[indice], quantidadesAvaliacoesAgentes[indice]);
            }
            printf("\n[1] Avaliar agente\n");
            printf("[0] Voltar\n");
            printf("[-1] Encerrar\n");
            printf("\nOpcao: ");
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
                printf("Opcao invalida.\n");
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
                printf("Nota invalida.\n");
                continue;
            }
            printf("\nNota: %d\n", nota);
            printf("[1] Confirmar\n");
            printf("[0] Cancelar\n");
            printf("[-1] Encerrar\n");
            printf("Opcao: ");
            leitura = lerEntrada(entrada, sizeof(entrada));
            if (leitura == -1)
            {
                return -1;
            }
            if (leitura != 1)
            {
                continue;
            }
            int confirmar = validarEntrada(entrada, 1);
            switch (confirmar)
            {
                case -1:
                    return -1;
                case 0:
                    printf("Avaliacao cancelada.\n");
                    break;
                case 1:
                {
                    int registrada = registrarAvaliacao(indice, nota);
                    if (registrada)
                    {
                        printf("Avaliacao registrada na RAM. Salve ao encerrar!\n");
                    }
                    else
                    {
                        printf("Falha ao registrar avaliacao.\n");
                    }
                    break;
                }
                default:
                    printf("Opcao invalida: avaliacao cancelada.\n");
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
                printf("Sem avaliacoes\n");
            }
            else
            {
                printf("Nota: %.2f (%d)\n", mediasAgentes[i], quantidadesAvaliacoesAgentes[i]);
            }
        }
        if (quantidadeAgentes == 0)
        {
            printf("Nenhum agente cadastrado.\n");
        }
        printf("\n[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("\nEscolha: ");
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
            printf("Opcao invalida.\n");
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
        printf("Descricao: %s\n", descricaoAgentes[indiceAgente]);
        printf("Instrucoes: %s\n", instrucoesAgentes[indiceAgente]);
        if (quantidadesAvaliacoesAgentes[indiceAgente] == 0)
        {
            printf("Nota media: Sem avaliacoes\n");
        }
        else
        {
            printf("Nota media: %.2f | Total: %d\n", mediasAgentes[indiceAgente], quantidadesAvaliacoesAgentes[indiceAgente]);
        }
        printf("\n[1] Editar\n");
        printf("[2] Excluir DEFINITIVAMENTE\n");
        printf("[0] Voltar\n");
        printf("[-1] Encerrar\n");
        printf("Opcao: ");
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
                printf("Confirma excluir ID %d e suas avaliacoes?\n", id);
                printf("[1] Sim\n");
                printf("[0] Nao\n");
                printf("[-1] Encerrar\n");
                printf("Opcao: ");
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
                    printf("Agente excluido da RAM. Salve ao encerrar!\n");
                    return 0;
                }
                printf("Exclusao cancelada.\n");
                continue;
            default:
                printf("Opcao invalida.\n");
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
        printf("ID invalido.\n");
        return 0;
    }
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (idsAgentes[i] == escolha)
        {
            return fichaAgenteAdm(i);
        }
    }
    printf("Agente nao encontrado.\n");
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
        printf("Nome invalido.\n");
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
    printf("\nEscolha: ");

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
        return fichaAgenteAdm(posicoes[escolha - 1]);
    }

    return 0;
}
