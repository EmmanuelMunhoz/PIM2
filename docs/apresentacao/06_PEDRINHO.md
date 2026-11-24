# Pedrinho
Busca por ID · 6º integrante

> **Entrada:** painel, Atlas Demo cadastrado e com descrição revisada. **Entrega:** painel, categoria do Atlas atualizada em RAM.

## A. Sua missão

Mostre primeiro uma busca sem resultado e depois abra o Atlas pelo ID. Use um exemplo numérico para explicar o que é ID, o que é posição e por que a busca percorre o vetor.

## B. Como começar a falar

> “Na lista eu escolho uma posição. Nesta busca eu digito o ID que pertence ao agente. Vou procurar um ID que não existe e depois o ID 13, que é o do Atlas.”

## C. O que mostrar na tela

1. No painel, digite **3**. Informe **999999**. Mostre **Agente não encontrado.** e o retorno ao painel.
2. Digite **3** de novo e informe **13**. Mostre a ficha do `Atlas Demo` e a descrição que Pedro Negrelli editou.
3. Aponte no código a comparação `idsAgentes[i] == escolha`. Nesta cópia, o **ID 13** é achado em **`i = 12`**.
4. Na ficha, escolha **1** Editar e **3** Categoria. Digite `Categoria revisada`. Use **0** para voltar à ficha e mostre a categoria nova.
5. Use **0** na ficha. A busca retorna diretamente ao painel. Entregue o teclado a Marcos com as alterações pendentes.

<!-- pagebreak -->

## D. O que explicar no código

- **`consultas.c`, 338–369 · `buscarAgentePorId(void)`.** `entrada[20]` guarda o texto. `validarEntrada(entrada, 999999)` devolve o número ou um código de controle. **0** volta, **-1** encerra o fluxo e `-2` interno gera **ID inválido**. Linha longa volta com `0`.
- **`consultas.c`, 370–379 · comparação.** O `for` percorre os índices ativos. `escolha` é o ID digitado. Se `idsAgentes[i]` for igual, chama `fichaAgenteAdm(i)` e devolve o retorno dela. Se o laço acabar sem achar, avisa e retorna `0`.
- **`menus.c`, 249–251 e 266–271.** O painel chama a busca na opção **3**. Quando a busca devolve `0`, o laço continua. O `-1` é propagado.
- **`consultas.c`, 295–301, e `cadastro.c`, 105–195 · edição.** A ficha passa à edição o índice achado. A opção de categoria direciona `destino` à linha de `categoriasAgentes`. A cópia de um texto válido e diferente ativa a pendência.

## E. Explicação pronta para estudar

> “ID é um valor guardado com os dados do agente. Índice é o número da posição dentro do vetor. No nosso teste, digitei ID 13. O programa passa pelos IDs até achar 13 na posição 12 e abre a ficha passando 12. Para ver a diferença, imaginem IDs 8, 14 e 26 nos índices 0, 1 e 2. Se eu excluir o ID 14, os vetores são compactados. O ID 26 continua 26, mas agora está no índice 1. Por isso a busca testa a igualdade em cada posição ativa.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. Qual a diferença entre ID 13 e índice 12?**\
O ID identifica o Atlas. O índice indica onde seus campos estão nos vetores nesta execução.

**2. Por que não usar `ID - 1` diretamente?**\
Os IDs podem ter lacunas, e uma exclusão desloca os registros. O cálculo só funcionaria por coincidência em certos dados.

**3. `999999` é um ID inválido?**\
É um número válido para a busca, mas está ausente nesta cópia. Texto como `abc` seria entrada inválida.

**4. Qual é o custo da busca?**\
Ela pode comparar até a quantidade de agentes ativos. Para quando acha a primeira igualdade ou quando termina a faixa.

**5. O que a busca devolve quando abre a ficha?**\
Devolve o resultado de `fichaAgenteAdm(i)`. Ao voltar da ficha normalmente, a busca devolve `0` e o painel reaparece.

**6. A busca altera registros?**\
Ela localiza e abre a ficha. A alteração mostrada é feita pela edição chamada a partir da ficha.

## G. O que não falar

- Evite dizer que o programa acessa `idsAgentes[13]` quando o usuário digita 13.
- Evite chamar a busca de binária ou dizer que os IDs são renumerados após exclusão.
- Evite dizer que abrir a ficha de ID volta a uma lista de resultados. A busca por ID volta ao painel.

## H. Passagem de palavra

> “Pelo ID, encontrei uma ficha exata. O Marcos vai mostrar como a busca por nome encontra várias fichas usando só parte do texto.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
