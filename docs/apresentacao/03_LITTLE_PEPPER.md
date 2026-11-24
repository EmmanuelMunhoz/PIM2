# Little Pepper
Autenticação · 3º integrante

> **Entrada:** menu principal, avaliação pendente. **Entrega:** painel administrativo, mesma avaliação pendente.

## A. Sua missão

Mostre acesso negado após três tentativas e, em seguida, um novo acesso bem-sucedido. Projete só o trecho de comparação e controle das tentativas.

## B. Como começar a falar

> “A parte pública fica disponível no menu principal. Para entrar no painel administrativo, o programa pede uma senha. Vou errar de propósito três vezes para mostrar como ele encerra essa tentativa de acesso e volta ao menu.”

## C. O que mostrar na tela

1. No principal, digite **2**. Confira o prompt **Informe a senha de administrador:**.
2. Digite três entradas de teste incorretas, preparadas no ensaio. Mostre o contador indo para **2**, **1** e **0**, o acesso negado e a volta ao principal.
3. Digite **2** novamente. Pause a projeção enquanto a pessoa responsável informa a senha em privado. A leitura normal pode ecoar o texto. Antes de voltar, retire da área projetada a linha em que a entrada apareceu.
4. Mostre **Acesso permitido!** se a linha puder ser exibida sem revelar a entrada. Caso contrário, retome pelo **Painel administrativo**.
5. Passe o teclado a Gleison. A avaliação anterior continua pendente.

<!-- pagebreak -->

## D. O que explicar no código

- **`autenticacao.c`, 15–29 · leitura e comparação em `autenticarAdm(void)`.** `senhaDigitada[20]` recebe a entrada. `lerEntrada(senhaDigitada, sizeof(senhaDigitada))` respeita a capacidade, com espaço para `'\0'`. `strcmp()` devolve `0` se as duas strings forem iguais. O `&&` só executa essa comparação se `retorno == 1`. O acesso permitido devolve `1`.
- **`autenticacao.c`, 30–37 · contador.** `tentativas` começa em 3 a cada chamada. Senha diferente ou linha longa cai no decremento. Quando o laço acaba, imprime acesso negado e devolve `0`. O `-1` de leitura retorna antes de descontar tentativa.
- **`entrada.c`, 62–103 · `lerEntrada(char entrada[], int capacidade)`.** `fgets()` lê a linha, e a rotina remove a quebra quando ela cabe. Devolve `1` para leitura aceita, `0` para excesso ou capacidade insuficiente e `-1` para EOF sem linha ou erro. EOF indica o fim do fluxo de entrada.
- **`menus.c`, 166–188 · ligação com o painel.** O caso **2** chama `autenticarAdm()`. Somente `1` chama `menuAdm()`. O `0` volta ao principal. O `-1` segue para o tratamento de encerramento.

Projete um recorte começando na **linha 15** ou apenas as linhas **25–33**. Confira antes que a linha da declaração da senha esteja fora da área visível.

## E. Explicação pronta para estudar

> “A função recebe a senha digitada como texto e só compara se conseguiu ler a linha corretamente. O strcmp devolve zero quando o texto digitado é igual ao esperado. Se falhar, tira uma tentativa e mostra quantas restam. No fim das três, o retorno é zero e o principal aparece de novo. Quando entro outra vez pela opção 2, a função começa uma nova contagem. A senha correta devolve 1, que é o sinal para o menu chamar o painel.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. Quantas tentativas são permitidas?**\
Até três por chamada. Uma nova solicitação de acesso começa outra contagem.

**2. O que o `0` de `strcmp()` significa?**\
Igualdade. `autenticarAdm()` devolve `1` no sucesso segundo seu próprio contrato.

**3. Por que usar `&&`?**\
Se a leitura não devolve `1`, a condição já é falsa e a comparação é pulada.

**4. O que acontece com uma senha longa demais?**\
A leitura volta com `0` e desconta uma tentativa. Há 19 bytes úteis no buffer, pois um é reservado para o terminador.

**5. EOF conta como tentativa errada?**\
EOF sem linha ou erro na leitura devolve `-1` antes do decremento.

**6. Isso bloqueia quem pedir acesso novamente?**\
O limite vale por acesso. O código não guarda contador acumulado ou bloqueio persistente.

## G. O que não falar

- Evite divulgar a credencial, projetar sua declaração ou deixar visível o texto digitado.
- Evite afirmar que há mascaramento, contas individuais ou proteção completa contra força bruta.
- Evite dizer que negar acesso grava ou descarta a avaliação anterior.

## H. Passagem de palavra

> “O acesso foi permitido. Agora o Gleison vai apresentar o painel e cadastrar o agente que vamos usar nas próximas etapas.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
