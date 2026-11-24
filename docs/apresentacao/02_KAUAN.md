# Kauan
Catálogo público e avaliação · 2º integrante

> **Entrada:** menu principal, 12 agentes. **Entrega:** menu principal, avaliação do ID 1 pendente na RAM.

## A. Sua missão

Mostre como um visitante abre o catálogo, lê a ficha e avalia um agente. Use uma nota concreta para explicar a média incremental.

## B. Como começar a falar

> “Com os dados carregados, já dá para navegar pelo catálogo. Vou abrir a ficha do primeiro agente e dar uma nota para mostrar o que muda na hora, antes de salvar.”

## C. O que mostrar na tela

1. No principal, digite **1** para abrir o catálogo.
2. Aponte `ConectaRH 360`, ID **1**, média **4.0** e **11** avaliações. Digite **1** para abrir a ficha.
3. Mostre os campos. Digite **1** para **Avaliar agente**, informe a nota **5** e digite **1** para **Confirmar**.
4. Mostre a confirmação de registro em RAM e a ficha atualizada com média **4.1** e **12** avaliações.
5. Digite **0** na ficha e **0** na lista. Entregue o teclado a Little Pepper no principal. A nota segue pendente.

<!-- pagebreak -->

## D. O que explicar no código

- **`consultas.c`, 11–78 · `catalogoAgentes(void)`.** O `for` percorre a faixa ativa. A tela imprime `i + 1` para começar a numeração em 1. A seleção usa `escolha - 1` para recuperar o índice. **0** na lista devolve `0` ao principal. **-1** ou fim de leitura propaga `-1`.
- **`consultas.c`, 79–183 · ficha e confirmação.** A ficha está no laço interno. `lerEntrada()` lê o texto, e `validarEntrada(entrada, 5)` aceita nota entre **0 e 5**. `opcaoConfirmacao` decide a ação. **1** chama `registrarAvaliacao(indice, nota)`. Depois da tentativa, a ficha reaparece.
- **`persistencia.c`, 159–180 · `registrarAvaliacao(int indiceAgente, int nota)`.** Checa o índice, a faixa da nota e o limite da contagem. Passa a média atual, o total anterior `n` e a nota a `calcularNovaMedia()`. Atualiza a média, a contagem e a pendência. Retorna `1` ao registrar e `0` se recusar.
- **`medias.c`, 4–12 · `calcularNovaMedia(double mediaAtual, int quantidadeAnterior, int novaNota)`.** Devolve `double`. Com total zero, a primeira nota já é a média. Nos demais casos, calcula `(média anterior × total anterior + nota) / (total anterior + 1)`. A ficha exibe com `%.1f`.

## E. Explicação pronta para estudar

> “A opção 1 usa o índice zero e abre o ConectaRH. Para avaliar, escolho uma nota e confirmo. Antes havia 11 avaliações com média 4. Quatro vezes onze dá 44, que é o total representado pela média antiga. Somo a nota 5 e divido pelo novo total, 12. Isso dá 49 dividido por 12, que aparece como 4.1 na tela. A contagem também muda para 12. As duas atualizações estão em memória e ficam pendentes até o salvamento.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. Que agente a opção `1` abre?**\
Abre a posição `0`. Na cópia de demonstração, é ConectaRH 360, ID 1.

**2. A ficha pública tem uma função separada?**\
Ela é o laço interno de `catalogoAgentes()`. **0** na ficha quebra esse laço e volta à lista.

**3. `0` cancela a nota?**\
No prompt da nota, `0` é nota válida. Na confirmação, `0` cancela a avaliação.

**4. E se a média ainda não existe?**\
Com contagem zero, a primeira nota confirmada vira a média. O total passa a um.

**5. O valor perde precisão por aparecer como `4.1`?**\
`%.1f` formata a tela. O valor continua em `double`, e a gravação no JSON usa `%.17g`.

**6. Dá para consultar todas as notas anteriores?**\
O programa guarda média e quantidade. Esse agregado basta para atualizar a média, mas não permite recuperar cada nota.

## G. O que não falar

- Evite chamar a posição da lista de ID.
- Evite afirmar que confirmar a nota já salva no disco.
- Evite dizer que o histórico de notas existe ou que a média fica armazenada com uma casa.

## H. Passagem de palavra

> “A avaliação ficou em memória. Agora o Little Pepper vai mostrar como funciona o acesso ao painel administrativo.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
