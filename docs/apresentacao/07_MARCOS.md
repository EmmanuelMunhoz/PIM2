# Marcos
Busca por nome · 7º integrante

> **Entrada:** painel administrativo com alterações pendentes. **Entrega:** painel, mesmas pendências.

## A. Sua missão

Use um trecho de nome que retorne dois agentes. Mostre como o programa encontra as ocorrências e usa a posição do resultado para abrir a ficha correta.

## B. Como começar a falar

> “Quando eu lembro só de um pedaço do nome, posso buscar pelo trecho. Vou usar Conecta, porque está no nome de dois agentes da nossa base, e abrir o segundo resultado.”

## C. O que mostrar na tela

1. No painel, digite **4** para **Buscar por nome**.
2. Digite `Conecta`, com **C maiúsculo**, e confirme com Enter.
3. Mostre os dois resultados na ordem do catálogo. **1** é **ConectaRH 360**, ID **1**. **2** é **ConectaSocial Pro**, ID **7**.
4. Digite **2**. Mostre a ficha administrativa de **ConectaSocial Pro** e aponte o ID **7**.
5. Digite **0** na ficha. O programa volta ao painel. Passe a Otávio sem salvar. A pesquisa não acrescenta pendência.

<!-- pagebreak -->

## D. O que explicar no código

- **`consultas.c`, 382–417 · `buscarAgentePorNome(void)`.** `trecho` recebe uma linha. Vazio ou leitura longa informa nome inválido. As strings exatas `"0"` e `"-1"` são detectadas com `strcmp()` e retornam `0` para voltar ou `-1` para pedir saída. EOF ou erro também retorna `-1`.
- **`consultas.c`, 420–440 · `strstr()` e mapa de posições.** `strstr(nomesAgentes[i], trecho)` devolve o endereço da primeira ocorrência ou `NULL` quando não acha. O laço guarda cada índice encontrado em `posicoes` e incrementa `encontrados`. Neste exemplo, `posicoes[0] = 0` e `posicoes[1] = 6`. Se não achar, mostra a mensagem e devolve `0`.
- **`consultas.c`, 446–471 · escolha e ficha.** O código valida a opção até o número de resultados. A opção **2** usa `posicoes[2 - 1]`. O valor `6` é guardado em `indiceAgente` e passado a `fichaAgenteAdm()`. A busca devolve o retorno da ficha. Escolha inválida na lista retorna `0` sem mensagem adicional.
- **`menus.c`, 253–255 e 266–271.** O painel chama a busca pela opção **4**. Retorno normal reapresenta o painel.

## E. Explicação pronta para estudar

> “O programa passa pelo vetor de nomes e pergunta se cada string contém o trecho Conecta. A função usada é strstr. Se ela achar, devolve o endereço da ocorrência, e o código usa isso para guardar o índice do agente. A lista de resultados tem uma numeração própria. O meu segundo resultado é a posição 1 do vetor de resultados. Ali está guardado o índice 6 do catálogo, que abre a ficha do ID 7.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. Preciso digitar o nome inteiro?**\
Um trecho já serve. `strstr()` busca uma sequência de bytes que pode estar em qualquer parte do nome.

**2. O trecho `conecta` dá o mesmo resultado?**\
A busca é literal e distingue maiúsculas de minúsculas. Para esta demonstração, digite `Conecta`.

**3. Qual é a diferença entre `strcmp()` e `strstr()`?**\
`strcmp()` compara strings inteiras e devolve zero na igualdade. `strstr()` procura um trecho e devolve endereço ou `NULL`.

**4. Por que guardar as posições em outro vetor?**\
Porque a lista de resultados tem uma numeração própria. `posicoes` permite voltar de cada opção ao índice do catálogo.

**5. O que acontece se não houver ocorrência?**\
O programa apresenta **Nenhum agente encontrado.** e devolve `0` ao painel.

**6. A opção 2 abriu o ID 2?**\
A opção 2 abriu o segundo resultado. O índice recuperado é 6, cujo ID é 7.

## G. O que não falar

- Evite dizer que a busca ignora acentos ou caixa, ordena nomes ou procura em descrição e categoria.
- Evite tratar a posição do resultado como ID ou índice original.
- Evite dizer que voltar da ficha reapresenta os resultados. O retorno desta busca leva ao painel.

## H. Passagem de palavra

> “A busca só localizou o agente. Agora o Otávio vai mostrar como o grupo grava as alterações feitas desde o começo e encerra o programa.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
