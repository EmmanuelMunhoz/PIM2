# Gleison
Painel administrativo e cadastro · 4º integrante

> **Entrada:** painel, 12 agentes. **Entrega:** painel com Atlas Demo em RAM, ID 13, e mudanças pendentes.

## A. Sua missão

Apresente o painel, cadastre o agente usado pelos próximos colegas e explique como o programa escolhe sua posição e seu ID.

## B. Como começar a falar

> “Este é o painel administrativo. Por aqui eu posso cadastrar, listar, fazer buscas e salvar. Vou cadastrar o Atlas Demo. A gente vai usar esse mesmo registro para mostrar a edição e a busca por ID.”

## C. O que mostrar na tela

1. Aponte **1** Cadastrar, **2** Listar, **3** Buscar por ID, **4** Buscar por nome e **5** Salvar. Cite **0** para voltar e **-1** para pedir encerramento.
2. Digite **1**, preencha os quatro campos e pressione Enter após cada valor.
   - **Nome** `Atlas Demo`
   - **Descrição** `Agente de teste da apresentacao`
   - **Categoria** `Demonstracao`
   - **Instruções** `Responda com exemplos simples`
3. Mostre **Cadastro realizado com sucesso!**, o **ID 13** e a mensagem de cadastro em RAM.
4. Entregue o computador a Pedro Negrelli no painel. A avaliação anterior e o cadastro estão pendentes.

<!-- pagebreak -->

## D. O que explicar no código

- **`menus.c`, 199–272 · `menuAdm(void)`.** Lê e valida a opção. O `switch` chama cadastro, lista, buscas ou salvamento. O caso **1**, linhas 241–243, chama `cadastrarAgente()`. O laço reapresenta o painel após o cadastro. Retorno `0` volta ao principal, e `-1` pede encerramento.
- **`cadastro.c`, 45–66 · `cadastrarAgente(void)`.** `indice = quantidadeAgentes` indica a primeira posição livre. `maior` é calculado percorrendo os IDs ativos. A capacidade ou um maior ID de pelo menos 999999 impede a inclusão.
- **`cadastro.c`, 68–101 · escrita em RAM.** Cada chamada a `pedirCampo()` recebe o destino, a capacidade e o rótulo. Qualquer retorno diferente de `1` cancela. Após os quatro campos aceitos, define `maior + 1`, média `0.0` e contagem `0`, incrementa `quantidadeAgentes` e ativa `alteracoesPendentes`. A função é `void`.
- **`cadastro.c`, 9–41 · `textoValido(const char texto[])` e `pedirCampo(char destino[], int capacidade, const char rotulo[])`.** `pedirCampo()` chama `lerEntrada()` e valida a string. Devolve `1` ao aceitar, `0` ao recusar e `-1` em fim ou erro de leitura. `textoValido()` rejeita vazio, aspas duplas, barra invertida ou byte abaixo de 32.

## E. Explicação pronta para estudar

> “Os 12 agentes ocupam os índices de zero a onze. Então a primeira posição livre é a 12. O programa passa a linha certa de cada vetor para ler nome, descrição, categoria e instruções. Depois de aceitar tudo, vê que o maior ID ativo é 12 e cria o ID 13. Ele começa com zero avaliações. Só então o código aumenta a quantidade de agentes e marca a pendência. Por isso o Atlas já aparece na lista, mesmo com o JSON ainda igual ao do início.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. O cadastro devolve o ID criado?**\
A função é `void`. Grava o ID no vetor e o mostra na confirmação.

**2. O ID é a quantidade de agentes mais um?**\
O ID vem do maior ID ativo mais um. A quantidade indica a primeira posição livre.

**3. E se o terceiro campo for inválido?**\
O cadastro cancela e a quantidade continua igual. Campos já escritos podem ficar na posição ainda fora da faixa ativa.

**4. Por que passar a capacidade do campo?**\
Os campos têm espaços diferentes. A leitura usa esse limite e reserva o terminador da string.

**5. Um agente novo recebeu uma avaliação de nota zero?**\
A média em RAM começa em `0.0`, mas a contagem é zero. A ficha mostra **Sem avaliações**, e o JSON gravará `null` para a média.

**6. Um ID excluído pode reaparecer?**\
Se o maior ID ativo for removido, o cálculo seguinte usa o maior restante. O sistema não mantém um contador histórico separado.

## G. O que não falar

- Evite dizer que cadastrar salva automaticamente ou que o ID é a posição na lista.
- Evite dizer que um cadastro cancelado limpa os campos já lidos da posição inativa.
- Evite atribuir ao painel contas individuais ou permissões diferentes por pessoa.

## H. Passagem de palavra

> “O Atlas já está disponível na listagem. O Pedro Negrelli vai abrir a ficha dele e mostrar como uma edição muda o vetor certo.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
