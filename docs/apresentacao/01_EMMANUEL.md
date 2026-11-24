# Emmanuel
Inicialização e arquitetura · 1º integrante

> **Entrada:** terminal preparado na pasta de demonstração. **Entrega:** menu principal, 12 agentes e nenhuma alteração pendente.

## A. Sua missão

Abra a apresentação. Explique o que é o NEXT HOST e mostre como um arquivo vira um catálogo na memória. A sua parte termina quando aparece o menu principal.

## B. Como começar a falar

> “Professor, este é o NEXT HOST, nosso catálogo de agentes de inteligência artificial. Ele guarda nome, descrição, categoria, instruções e avaliações de cada agente. Eu vou mostrar de onde esses dados vêm e como o programa coloca tudo na memória antes de abrir o menu.”

## C. O que mostrar na tela

1. Com a cópia de demonstração preparada conforme o guia geral, mostre `main.c`. Aponte `carregarAgentes()` e `menu()`, nessa ordem.
2. Na segunda janela, mostre o começo do JSON da demonstração. Aponte o ID **1**, o nome `ConectaRH 360`, a média e a contagem.
3. Mostre os vetores em `dados.c`. Use o índice **0** para seguir o mesmo agente nos vetores de ID, nome, média e total.
4. Execute o programa na pasta de demonstração. Se ele já estiver aberto, mostre o menu e mantenha o mesmo processo.
5. Entregue o teclado a Kauan no principal. Ele vai usar **1** para abrir o catálogo.

<!-- pagebreak -->

## D. O que explicar no código

- **`main.c`, 6–27 · `main(void)`.** `retorno` guarda o resultado de `carregarAgentes()`. Se for `0`, imprime a falha e encerra com `1`. Após carga bem-sucedida, chama `menu()`. O `-1` do menu vira saída `1` no processo. A saída normal de `main()` é `0`.
- **`persistencia.c`, 13–54 · `carregarAgentes(void)`.** `fopen(..., "r")` abre o arquivo para leitura. `arquivo` representa o fluxo aberto. `marcador` acompanha a abertura do array e os limites dos objetos. Falha de abertura ou ausência da estrutura esperada resulta em `0`.
- **`persistencia.c`, 56–94 · leitura e retorno.** `fscanf()` preenche a posição `indiceAgente`. `&idsAgentes[indiceAgente]` é o endereço onde a função escreve o inteiro. Uma linha da matriz de nomes já indica onde escrever a string. São **sete campos mais o fechamento**. `sscanf()` tenta converter a média lida como texto. Após reconhecer o fim do array, a rotina publica a quantidade, limpa a pendência e retorna `1`.
- **`dados.c`, 4–12, e `dados.h`, 5–23 · armazenamento.** Cada vetor guarda um campo. O mesmo índice liga os campos. Os vetores globais existem durante a execução, e `quantidadeAgentes` delimita as posições usadas. Capacidade do catálogo é **50**.

## E. Explicação pronta para estudar

> “Quando o programa começa, o main chama a função de leitura. No índice zero, eu tenho o ID 1 em um vetor, o nome ConectaRH 360 em outro, a média 4 em outro e a contagem 11 em outro. O índice em comum junta essas informações. Depois que a carga confirma o fim do array, a quantidade de agentes fica disponível para as outras funções. O arquivo pode ser fechado porque os dados já estão na RAM. Os menus trabalham com essa cópia. É por isso que dá para alterar dados durante a execução e decidir depois quando gravar.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. Qual a primeira função chamada em `main()`?**\
`carregarAgentes()`. Se ela devolve `0`, o menu nem é aberto.

**2. Por que os vetores são paralelos?**\
A posição `i` identifica o mesmo agente em todos eles. A descrição do índice `i` pertence ao nome do índice `i`.

**3. Por que `fscanf()` precisa do `&` para o ID?**\
Ela recebe o endereço do inteiro e escreve ali. O valor atual por si só não indica onde escrever.

**4. O que significam as oito atribuições?**\
Sete campos do agente e um caractere de fechamento. O programa ainda verifica se esse caractere é `}`.

**5. O que acontece na pasta errada?**\
O caminho é relativo à pasta de trabalho. Se `dados/agentes.json` não existir ali, a carga devolve `0` e `main()` encerra com erro.

**6. Os 12 registros ocupam toda a capacidade?**\
Há espaço para 50 agentes. O código percorre só a faixa ativa, que começa com 12 registros nesta cópia.

## G. O que não falar

- Evite chamar `fscanf()` de leitor universal de JSON. O código espera uma sequência específica de chaves.
- Evite igualar ID e índice. O primeiro agente tem ID **1** e índice **0**.
- Evite dizer que fechar o arquivo apaga os vetores ou que alterar a RAM já grava o arquivo.

## H. Passagem de palavra

> “Agora que o catálogo está carregado, o Kauan vai mostrar como qualquer usuário consegue consultar um agente e registrar uma avaliação.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
