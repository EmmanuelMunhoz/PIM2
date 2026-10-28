#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#define TAM 3
#define MAX_AGENTES 50
#define MAX_NOME 81
#define MAX_DESCRICAO 1001
#define MAX_CATEGORIA 51
#define MAX_INSTRUCOES 1001

int quantidadeAgentes = 0;
int proximoIdAgente = 1;
int idsAgentes[MAX_AGENTES];
char nomesAgentes[MAX_AGENTES][MAX_NOME];
char descricaoAgentes[MAX_AGENTES][MAX_DESCRICAO];
char categoriasAgentes[MAX_AGENTES][MAX_CATEGORIA];
char instrucoesAgentes[MAX_AGENTES][MAX_INSTRUCOES];
int statusAgentes[MAX_AGENTES];
double mediasAgentes[MAX_AGENTES];
int quantidadesAvaliacoesAgentes[MAX_AGENTES];
int possuiMediaAgentes[MAX_AGENTES];

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
                printf("\n\033[32mAcesso Permitido\033[0m");
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
        printf("[0] Voltar ao menu principal\n\n");

        printf("Escolha uma opção: ");

        retornoEntradaMenu = lerEntrada(entradaMenu,sizeof(entradaMenu));

        if (retornoEntradaMenu == 1)
            {
                escolha = validarEntrada(entradaMenu,4);

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
    if (proximoIdAgente <= 0)
    {
        printf("Nao ha IDs disponiveis para novos agentes.\n");
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

    // As aspas e barras invertidas exigiriam tratamento especial no JSON.
    // Nesta versao simples, esses caracteres nao sao aceitos no cadastro.
    if (strchr(nomesAgentes[indiceAgente], '"') != NULL ||
        strchr(nomesAgentes[indiceAgente], '\\') != NULL ||
        strchr(descricaoAgentes[indiceAgente], '"') != NULL ||
        strchr(descricaoAgentes[indiceAgente], '\\') != NULL ||
        strchr(categoriasAgentes[indiceAgente], '"') != NULL ||
        strchr(categoriasAgentes[indiceAgente], '\\') != NULL ||
        strchr(instrucoesAgentes[indiceAgente], '"') != NULL ||
        strchr(instrucoesAgentes[indiceAgente], '\\') != NULL)
    {
        printf("Nao use aspas ou barra invertida nos campos do agente.\n");
        return;
    }

    idsAgentes[indiceAgente] = proximoIdAgente;
    statusAgentes[indiceAgente] = 1;
    mediasAgentes[indiceAgente] = 0.0;
    quantidadesAvaliacoesAgentes[indiceAgente] = 0;
    possuiMediaAgentes[indiceAgente] = 0;
    quantidadeAgentes++;
    proximoIdAgente++;

    if (salvarAgentes() == 1)
    {
        if (salvarControle() == 1)
        {
            printf("\033[32m\nAgente salvo com sucesso!\033[0m");
            printf("\033[32m\nControle atualizado!\033[0m");
        }
        else
        {
            quantidadeAgentes--;
            proximoIdAgente--;
            if (salvarAgentes() == 1)
            {
                printf("Cadastro desfeito porque controle.json nao foi salvo.\n");
            }
            else
            {
                quantidadeAgentes++;
                proximoIdAgente++;
                printf("Falha ao salvar controle e ao desfazer agentes.json. Verifique os arquivos.\n");
            }
        }
    }
    else
    {
        quantidadeAgentes--;
        proximoIdAgente--;
        printf("Erro ao salvar agente!\n");
    }
}

int carregarControle(void)
{
    FILE *arquivo = fopen("dados/controle.json", "r");
    if (arquivo == NULL)
    {
        if (quantidadeAgentes == 0)
        {
            proximoIdAgente = 1;
            return 1;
        }
        printf("Erro ao abrir controle.json!\n");
        return 0;
    }

    int quantidadeLida, proximoIdLido;
    int resultado = fscanf(arquivo," { \"quantidadeAgentes\" : %d , \"proximoIdAgente\" : %d }",&quantidadeLida, &proximoIdLido);
    int erro = (resultado != 2);
    if (ferror(arquivo))
    {
        erro = 1;
    }
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }

    if (erro || quantidadeLida != quantidadeAgentes ||proximoIdLido <= 0 || quantidadeLida > MAX_AGENTES)
    {
        printf("Dados inconsistentes em controle.json!\n");
        return 0;
    }
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        if (proximoIdLido <= idsAgentes[i])
        {
            printf("Proximo ID invalido em controle.json!\n");
            return 0;
        }
    }

    proximoIdAgente = proximoIdLido;
    return 1;
}

int salvarControle(void)
{
    FILE *arquivo = fopen("dados/controle.json", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir controle.json para gravacao!\n");
        return 0;
    }

    fprintf(arquivo,"{\n""    \"quantidadeAgentes\": %d,\n""    \"proximoIdAgente\": %d\n""}\n", quantidadeAgentes, proximoIdAgente);

    int erro = ferror(arquivo);
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }
    if (erro)
    {
        printf("Erro ao gravar controle.json!\n");
        return 0;
    }
    return 1;
}

int salvarAgentes(void)
{
    FILE *arquivo = fopen("dados/agentes.json", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir agentes.json para gravacao!\n");
        return 0;
    }

    fprintf(arquivo, "[\n");
    for (int i = 0; i < quantidadeAgentes; i++)
    {
        fprintf(arquivo, "  {\n");
        fprintf(arquivo, "    \"id\": %d,\n", idsAgentes[i]);
        fprintf(arquivo, "    \"nome\": \"%s\",\n", nomesAgentes[i]);
        fprintf(arquivo, "    \"descricao\": \"%s\",\n", descricaoAgentes[i]);
        fprintf(arquivo, "    \"categoria\": \"%s\",\n", categoriasAgentes[i]);
        fprintf(arquivo, "    \"instrucoes\": \"%s\",\n", instrucoesAgentes[i]);
        fprintf(arquivo, "    \"status\": %d,\n", statusAgentes[i]);
        if (possuiMediaAgentes[i] == 1)
        {
            fprintf(arquivo, "    \"notaMedia\": %.1f\n", mediasAgentes[i]);
        }
        else
        {
            fprintf(arquivo, "    \"notaMedia\": null\n");
        }
        fprintf(arquivo, "  }%s\n", i < quantidadeAgentes - 1 ? "," : "");
    }
    fprintf(arquivo, "]\n");

    int erro = ferror(arquivo);
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }
    if (erro)
    {
        printf("Erro ao gravar agentes.json!\n");
        return 0;
    }
    return 1;
}

int carregarAgentes(void)
{
    FILE *arquivo = fopen("dados/agentes.json", "r");
    if (arquivo == NULL)
    {
        quantidadeAgentes = 0;
        return 1;
    }

    char linha[1200];
    int indice = 0;
    int erro = 0;
    int fim = 0;

    if (fgets(linha, sizeof(linha), arquivo) == NULL ||strchr(linha, '[') == NULL)
    {
        erro = 1;
    }

    while (erro == 0 && fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strchr(linha, ']') != NULL)
        {
            fim = 1;
            break;
        }
        if (strchr(linha, '{') == NULL || indice >= MAX_AGENTES)
        {
            erro = 1;
            break;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||sscanf(linha, " \"id\": %d", &idsAgentes[indice]) != 1 ||idsAgentes[indice] <= 0)
        {
            erro = 1;
            break;
        }
        for (int i = 0; i < indice; i++)
        {
            if (idsAgentes[i] == idsAgentes[indice])
            {
                erro = 1;
            }
        }
        if (erro) break;

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||sscanf(linha, " \"nome\": \"%80[^\"]\"", nomesAgentes[indice]) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||sscanf(linha, " \"descricao\": \"%1000[^\"]\"", descricaoAgentes[indice]) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||sscanf(linha, " \"categoria\": \"%50[^\"]\"", categoriasAgentes[indice]) != 1 ||
            fgets(linha, sizeof(linha), arquivo) == NULL ||sscanf(linha, " \"instrucoes\": \"%1000[^\"]\"", instrucoesAgentes[indice]) != 1)
        {
            erro = 1;
            break;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL)
        {
            erro = 1;
            break;
        }
        if (strstr(linha, "\"dataCriacao\"") != NULL)
        {
            if (fgets(linha, sizeof(linha), arquivo) == NULL)
            {
                erro = 1;
                break;
            }
        }
        if (sscanf(linha, " \"status\": %d", &statusAgentes[indice]) != 1 ||(statusAgentes[indice] != 0 && statusAgentes[indice] != 1))
        {
            erro = 1;
            break;
        }

        if (fgets(linha, sizeof(linha), arquivo) == NULL)
        {
            erro = 1;
            break;
        }
        if (strstr(linha, "\"notaMedia\": null") != NULL)
        {
            mediasAgentes[indice] = 0.0;
            possuiMediaAgentes[indice] = 0;
        }
        else if (sscanf(linha, " \"notaMedia\": %lf", &mediasAgentes[indice]) == 1 &&mediasAgentes[indice] >= 0.0 && mediasAgentes[indice] <= 5.0)
        {
            possuiMediaAgentes[indice] = 1;
        }
        else
        {
            erro = 1;
            break;
        }
        quantidadesAvaliacoesAgentes[indice] = 0;

        if (fgets(linha, sizeof(linha), arquivo) == NULL ||strchr(linha, '}') == NULL)
        {
            erro = 1;
            break;
        }
        indice++;
    }

    if (!fim || ferror(arquivo))
    {
        erro = 1;
    }
    if (fclose(arquivo) == EOF)
    {
        erro = 1;
    }
    if (erro)
    {
        quantidadeAgentes = 0;
        printf("Erro ao carregar agentes.json!\n");
        return 0;
    }

    quantidadeAgentes = indice;
    return 1;
}