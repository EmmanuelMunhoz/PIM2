#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#define TAM 3
#define MAX_AGENTES 50
#define MAX_NOME 81
#define MAX_DESCRICAO 1001
#define MAX_CATEGORIA 51
#define MAX_INSTRUCOES 1001
#define TAM_DATA 20

int quantidadeAgentes = 0;
int proximoIdAgente = 1;
int idsAgentes[MAX_AGENTES];
char nomesAgentes[MAX_AGENTES][MAX_NOME];
char descricaoAgentes[MAX_AGENTES][MAX_DESCRICAO];
char categoriasAgentes[MAX_AGENTES][MAX_CATEGORIA];
char instrucoesAgentes[MAX_AGENTES][MAX_INSTRUCOES];
char datasCriacaoAgentes[MAX_AGENTES][TAM_DATA];
int statusAgentes[MAX_AGENTES];
double mediasAgentes[MAX_AGENTES];
int quantidadesAvaliacoesAgentes[MAX_AGENTES];

const char valor_digitado_errado[] = "\n\033[31m⚠️  Valor digitado Invalido!⚠️\033[0m\n"; //variavel global de erro;

int menu ()
{
    int escolha, leituraMenuOk;
    char entrada [TAM];
    do
    {
        printf("\n----------------------");
        printf("\nSeja Bem-Vindo\n");
        printf("----------------------\n\n");
        printf("Escolha uma das opções abaixo.\n\n");
        printf("[1] - Catálogo de Agentes.\n");
        printf("[2] - Painel Administrativo (acesso restrito).\n");
        printf("[0] - Sair\n\n");
        printf("Qual opção você deseja escolher: ");

        leituraMenuOk = lerEntrada(entrada,sizeof(entrada));

        if (leituraMenuOk == 1)
        {
            escolha = validarEntrada(entrada,2);

            switch (escolha)
            {
                case 1:
                {
                    printf("Você escolheu a opção: [%d]\n", escolha);
                    break;
                }
                case 2:
                {
                    int validarEntradaAdm = 0;
                    validarEntradaAdm = autenticarAdm ();

                    if (validarEntradaAdm == 0)
                    {
                        validarEntradaAdm = menuAdm();

                        if (validarEntradaAdm == -1)
                        {
                            return -1;
                        }
                    }
                    if (validarEntradaAdm == -1)
                    {
                        return -1;
                    }
                    break;
                }                        
                case 0:
                { 
                    printf("Você escolheu a opção: [%d]\n", escolha);
                    break;
                }
                default:
                {
                    printf("%s",valor_digitado_errado);
                    leituraMenuOk = 0;
                }                   
            }
        }
        if (leituraMenuOk == -1)
        {
            return -1;
        }
        if (leituraMenuOk == 0)
        {
            continue;
        } 
            
    }while(leituraMenuOk != 1 || escolha != 0);
    return escolha;
}

void limparBuffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int validarEntrada(char entrada[], int limiteMaximo)
{

    if(entrada[0] >= '0' && entrada[0] - '0' <= limiteMaximo)
    {
        if(entrada[1] == '\n' || entrada [1] == '\0')
        {
            return atoi(entrada);
        }

    }
    return -1;
}

int autenticarAdm(void)
{
    int leituraValidarEntradaOk;
    const char senhaAdm[] = "@Adminunip";
    char senhaDigitada[20];
    int tentativas = 3;

    do
    {
        printf("Qual a senha ADM: ");
        leituraValidarEntradaOk = lerEntrada(senhaDigitada,sizeof(senhaDigitada));

        if(leituraValidarEntradaOk == 1)
        {
            if(strcmp (senhaDigitada,senhaAdm) != 0)
            {
                printf("\033[31m\nSenha Incorreta, tentativas restantes [%d] tentativa(s)\033[0m\n", tentativas - 1);
                tentativas --;
            }
            if(strcmp (senhaDigitada,senhaAdm) == 0)
            {
                printf("\033[32mAcesso Permitido\033[0m\n\n");
                return 0;
            }
        }
        if (leituraValidarEntradaOk == -1)
        {
            return -1;
        }
        if (leituraValidarEntradaOk == 0)
        {
            tentativas --;
            continue;
        }
    }while (tentativas > 0);

    printf("\033[31mAcesso Negado\033[0m\n");
    printf("Voltando ao Menu.....\n");
    return 1;
}

int lerEntrada(char entrada[], int capacidade)
{

    if(capacidade <2)
    {
        return -1;
    }

    int leituraOK;
    leituraOK = (fgets(entrada, capacidade, stdin) != NULL);

    if(leituraOK == 1)
    {
        if(strchr(entrada,'\n') != NULL)
        {
            entrada[strcspn(entrada,"\n")] = '\0';
            return 1;
        }
        else
        {
            int procurarN = getchar();
            if (procurarN == '\n')
            {
                return 1;
            }
            if (procurarN == EOF)
            {
                if(ferror(stdin))
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            limparBuffer();
            printf("\033[31m ⚠️  Entrada excedeu o tamanho máximo permitido ⚠️ \033[0m\n\n");
            return 0;
        }
    }
    else
    {
        if (feof(stdin))
        {
            printf("Entrada encerrada (EOF).\n");
        }
        else if (ferror(stdin))
        {
            printf("Erro ao ler a entrada.\n");
        }
        else
        {
            printf("Falha de leitura desconhecida.\n");
        }
        return -1;
    }
}

int menuAdm()
{
    char entradaMenu[TAM];
    int retornoEntradaMenu = 0;
    int escolha;

    do
    {
        printf("\n\n========== PAINEL ADMINISTRATIVO ==========\n\n");

        printf("[1] Cadastrar agente\n");
        printf("[2] Listar agentes\n");
        printf("[3] Buscar agente por ID\n");
        printf("[4] Buscar agente por nome\n");
        printf("[5] Fechar o programar\n");
        printf("[0] Voltar ao menu principal\n\n");

        printf("Escolha uma opção: ");

        retornoEntradaMenu = lerEntrada(entradaMenu,sizeof(entradaMenu));

        if (retornoEntradaMenu == 1)
            {
                escolha = validarEntrada(entradaMenu,5);

                switch (escolha)
                {
                    case 1:
                    {
                        cadastrarAgente();
                        break;
                    }
                    case 2:
                    {
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    }
                    case 3:
                    {
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    }
                    case 4:
                    {
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    } 
                    case 5:
                    {
                        printf("Você escolheu a opção: [%d]\n", escolha);
                        break;
                    }                       
                    case 0:
                    { 
                        return 0;
                    }
                    default:
                    {
                        printf("%s",valor_digitado_errado);
                        retornoEntradaMenu = 0;
                    }                   
                }
            }
            if (retornoEntradaMenu == -1)
            {
                return -1;
            }
            if (retornoEntradaMenu == 0)
            {
                continue;
            }
    }while(retornoEntradaMenu != 0);
     
    return 0;
}

void cadastrarAgente(void)
{
    int indiceAgente = quantidadeAgentes;
    int retornoLeitura;

    if(quantidadeAgentes >= MAX_AGENTES)
    {
        printf("Não pode ser cadastrado mais AGENTES\n");
        return;
    }

    printf("\nNome do Agente: ");
    retornoLeitura = lerEntrada(nomesAgentes[indiceAgente],sizeof(nomesAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {
        return;
    }

    if (nomesAgentes[indiceAgente][0] == '\0')
    {
        printf("Nome obrigatorio!\n");
        return;
    }

    printf("\nQual a descrição do AGENTE: ");
    retornoLeitura = lerEntrada(descricaoAgentes[indiceAgente],sizeof(descricaoAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {   
       
        return;
    }
     
    if (descricaoAgentes[indiceAgente][0] == '\0')
    {
        printf("Descrição obrigatoria!\n");
        return;
    }

    printf("\nQual a categoria do Agente: ");
    retornoLeitura = lerEntrada(categoriasAgentes[indiceAgente],sizeof(categoriasAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {
        
        return;
    }
    
    if (categoriasAgentes[indiceAgente][0] == '\0')
    {
        printf("Categoria obrigatoria!\n");
        return;
    }

    printf("\nQual a instrução do AGENTE: ");
    retornoLeitura = lerEntrada(instrucoesAgentes[indiceAgente],sizeof(instrucoesAgentes[indiceAgente]));

    if(retornoLeitura != 1)
    {
        
        return;
    }

    if (instrucoesAgentes[indiceAgente][0] == '\0')
    {
        printf("Intruções obrigatorias!\n");
        return;
    }

    idsAgentes[indiceAgente] = proximoIdAgente;
    statusAgentes[indiceAgente] = 1;
    mediasAgentes[indiceAgente] = 0.0;
    quantidadesAvaliacoesAgentes[indiceAgente] = 0;
    datasCriacaoAgentes[indiceAgente][0] = '\0';

    quantidadeAgentes++;
    proximoIdAgente++;
}

int salvarControle()
{
    FILE *arquivoControle;
    arquivoControle = fopen("dados/controle.json", "w");

    if(arquivoControle == NULL)
    {
        printf("Não foi possivel salvar os dados");
        return 0;
    }

    int resultadoEscrita = fprintf(arquivoControle,
    "{\n"
    "    \"quantidadeAgentes\": %d,\n"
    "    \"proximoIdAgente\": %d\n"
    "}\n",
    quantidadeAgentes,
    proximoIdAgente);

    if (resultadoEscrita < 0)
    {
        printf("Erro ao escrever no JSON, fechando arquivo.");
        
        fclose(arquivoControle);
        return 0;
    }

    if (fclose(arquivoControle) == EOF)
    {
        printf("Erro ao fechar controle.json!\n");
        return 0;
    }

    return 1;   
}

int salvarAgentes()
{
    FILE *arquivoAgentes;
    arquivoAgentes = fopen("dados/agentes.json", "w");

    if(arquivoAgentes == NULL)
    {
        printf("Não foi possivel salvar os dados");
        return 0;
    }

    int resultadoEscrita = fprintf(arquivoAgentes, "[\n");

    if (resultadoEscrita < 0)
    {
        printf("Erro ao iniciar agentes.json!\n");
        fclose(arquivoAgentes);
        return 0;
    }
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        fprintf(arquivoAgentes, "    \"id\": %d,\n", idsAgentes[i]);
        fprintf(arquivoAgentes, "    \"nome\": \"%s\",\n", nomesAgentes[i]);
        fprintf(arquivoAgentes, "    \"descricao\": \"%s\",\n", descricaoAgentes[i]);
        fprintf(arquivoAgentes, "    \"categoria\": \"%s\",\n", categoriasAgentes[i]);
        fprintf(arquivoAgentes, "    \"instrucoes\": \"%s\",\n", instrucoesAgentes[i]);
        fprintf(arquivoAgentes, "    \"dataCriacao\": \"%s\",\n", datasCriacaoAgentes[i]);
        fprintf(arquivoAgentes, "    \"status\": %d,\n", statusAgentes[i]);

        if (quantidadesAvaliacoesAgentes[i] == 0)
        {
            fprintf(arquivoAgentes, "    \"notaMedia\": null\n");
        }
        else
        {
            fprintf(arquivoAgentes, "    \"notaMedia\": %.1f\n", mediasAgentes[i]);
        }

        if (i < quantidadeAgentes - 1)
        {
            fprintf(arquivoAgentes, "  },\n");
        }
        else
        {
            fprintf(arquivoAgentes, "  }\n");
        }
    }
    fprintf(arquivoAgentes, "]\n");

    if (ferror(arquivoAgentes))
    {
        printf("Erro ao escrever em agentes.json!\n");
        fclose(arquivoAgentes);
        return 0;
    }

    if (fclose(arquivoAgentes) == EOF)
    {
        printf("Erro ao fechar agentes.json!\n");
        return 0;
    }

    return 1;
}