# Pedro Negrelli
Listagem administrativa e edição · 5º integrante

> **Entrada:** painel, Atlas Demo cadastrado em RAM. **Entrega:** painel, descrição do Atlas atualizada e pendente.

## A. Sua missão

Abra a lista administrativa, selecione o Atlas, altere a descrição e mostre a ficha atualizada. Explique como uma edição muda o vetor certo.

## B. Como começar a falar

> “O Gleison acabou de cadastrar o Atlas. Vou abrir a lista para mostrar que ele já aparece e editar a descrição. Assim dá para acompanhar exatamente onde o novo texto foi parar.”

## C. O que mostrar na tela

1. No painel, digite **2**. Na listagem, localize `Atlas Demo` no fim e aponte a posição exibida **13** e o ID **13**.
2. Digite **13** na lista. Na **Ficha administrativa**, aponte a descrição inicial `Agente de teste da apresentacao`.
3. Escolha **1** Editar, depois **2** Descrição. Digite `Descricao revisada por Pedro` e pressione Enter.
4. Mostre **Alteração registrada na memória RAM.** O menu de edição reaparece. Use **0** para voltar à ficha e mostrar a descrição nova.
5. Use **0** na ficha para voltar à lista e **0** na lista para voltar ao painel. Entregue o teclado a Pedrinho. A avaliação, o cadastro e a descrição ainda estão pendentes.

<!-- pagebreak -->

## D. O que explicar no código

- **`consultas.c`, 186–243 · `listarAgentesAdm(void)`.** Percorre a faixa ativa e imprime posição, ID, nome, categoria e avaliações. `escolha - 1` converte a opção em índice. Chama `fichaAgenteAdm()`. Quando a ficha devolve `0`, a lista reaparece. A lista devolve `0` ao painel e propaga `-1` para encerramento ou fim de leitura.
- **`consultas.c`, 246–301 · `fichaAgenteAdm(int indiceAgente)`.** Confere a faixa do índice e usa o mesmo índice para exibir os campos. A opção **1** chama `editarAgente(indiceAgente)`. A ficha reaparece após a volta normal da edição. A própria ficha devolve `0` para voltar ou para índice inválido, e propaga `-1`.
- **`cadastro.c`, 105–195 · `editarAgente(int indiceAgente)`.** `destino` é um ponteiro, isto é, guarda o endereço do campo a editar. A opção **2** escolhe `descricaoAgentes[indiceAgente]` e sua capacidade. `novoTexto` recebe a entrada temporária. Se for válida e diferente, `strcpy()` copia para o campo e ativa a pendência. Retorna `1` ao voltar à ficha, `0` para índice inválido e `-1` ao pedir saída ou terminar a leitura.

## E. Explicação pronta para estudar

> “A opção 13 da lista vira o índice 12. Na ficha, quando escolho editar a descrição, o programa aponta para a linha 12 do vetor de descrições. O novo texto é lido em um espaço temporário. Se ele for válido e diferente, a função copia esse texto para a linha do agente e marca a pendência. Ao voltar para a ficha, ela lê o mesmo índice e já mostra a descrição atualizada. O ID e os outros campos continuam como estavam.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. Por que `escolha - 1`?**\
A tela numera de 1 em diante. Os índices do vetor começam em 0.

**2. O que guarda `destino`?**\
O endereço do primeiro byte do campo selecionado. Isso permite que a mesma rotina copie para descrição, nome, categoria ou instruções.

**3. O que acontece se digitar o mesmo texto?**\
`strcmp()` retorna `0`. A edição não copia o campo nem cria uma nova alteração, e uma pendência anterior continua como estava.

**4. Por que a capacidade depende do campo?**\
As linhas das matrizes têm tamanhos diferentes. O programa limita a leitura ao campo escolhido.

**5. Por que `0` no menu Editar devolve `1`?**\
O `0` é a opção digitada. O `1` é o retorno interno de `editarAgente()` para voltar à ficha.

**6. A descrição já está no JSON depois dessa tela?**\
A edição altera a RAM. A gravação só acontece quando uma ação de salvamento chama o escritor.

## G. O que não falar

- Evite dizer que editar a descrição substitui o agente inteiro.
- Evite usar o ID como índice, mesmo quando o número exibido coincide com o ID.
- Evite afirmar que a edição já foi gravada no arquivo.

## H. Passagem de palavra

> “A descrição já apareceu na ficha. Agora o Pedrinho vai encontrar esse mesmo agente usando o ID e vai editar a categoria.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
