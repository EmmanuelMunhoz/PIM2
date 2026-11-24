# Otávio
Persistência e encerramento · 8º integrante

> **Entrada:** painel, avaliação e alterações no Atlas em RAM. **Entrega:** processo encerrado e JSON da demonstração gravado.

## A. Sua missão

Mostre como salvar todo o catálogo atualizado na cópia de demonstração. Explique o que ainda estava em RAM e a diferença entre salvar explicitamente, salvar ao sair e sair sem salvar.

## B. Como começar a falar

> “Até aqui a gente avaliou um agente, cadastrou o Atlas e editou dois campos. Tudo isso apareceu na tela, mas ainda estava na memória. Agora eu vou mandar o programa gravar as mudanças e mostrar o que ficou no arquivo.”

## C. O que mostrar na tela

1. No **Painel administrativo**, escolha **5** Salvar. Confirme **Alterações salvas em dados/agentes.json.** O painel reaparece.
2. Na segunda janela, abra **o JSON da pasta temporária**. Mostre o Atlas Demo com ID **13**, descrição `Descricao revisada por Pedro`, categoria `Categoria revisada` e média `null`. No ID **1**, mostre **12** avaliações e a média persistida.
3. Volte ao terminal. Digite **0** no painel e **0** no principal. O programa encerra sem perguntar porque a pendência foi limpa pelo salvamento.
4. Explique as escolhas do diálogo quando há pendência. **1** tenta salvar e sair, **2** encerra sem gravar o que mudou desde o último salvamento e **0** cancela e volta. A demonstração desse diálogo fica para o ensaio em outra cópia.

<!-- pagebreak -->

## D. O que explicar no código

- **`menus.c`, 12–31 e 257–259 · `salvarAlteracoes(void)`.** A opção **5** chama essa rotina. Ela consulta `alteracoesPendentes`. Sem pendência, informa que não há alterações. Com pendência, chama `salvarAgentes()` e mostra sucesso ou falha. A ação retorna ao painel.
- **`persistencia.c`, 99–138 · `salvarAgentes(void)`.** `fopen(..., "w")` abre para escrita, cria o arquivo se necessário e trunca o conteúdo anterior se a abertura der certo. `fprintf()` escreve no fluxo. O `for` grava todos os agentes ativos. `separador` põe vírgula entre objetos. A média sai como `null` com contagem zero ou como número em `%.17g`.
- **`persistencia.c`, 140–155 · checagem do arquivo.** O código verifica `ferror()` e executa `fclose()` separadamente. Em falha, retorna `0`. Só após sucesso limpa a pendência e devolve `1`.
- **`menus.c`, 35–94 e 129–144 · `confirmarSaida(void)`.** Sem pendência, retorna `1` direto. Com pendência, **1** tenta gravar, **2** autoriza sair sem gravar e **0** cancela. EOF ou erro retorna `-1`. O menu converte a autorização em saída normal.

## E. Explicação pronta para estudar

> “Quando escolho salvar, o programa vê se existe pendência. Como existe, abre o arquivo da demonstração no modo w e escreve um novo array com todos os agentes ativos. A média da avaliação aparece com uma casa na tela, mas a gravação usa até 17 dígitos significativos. Depois de verificar a escrita e o fechamento, o programa limpa a pendência. Por isso, quando eu voltar ao principal e escolher sair, ele encerra direto.”

<!-- pagebreak -->

## F. Perguntas do professor

**1. A opção 5 grava só o Atlas?**\
Ela reescreve o catálogo inteiro. São todos os agentes ativos, com as atualizações em RAM.

**2. Por que `"w"`?**\
Esse modo cria o arquivo se preciso ou trunca o antigo. A rotina escreve o array completo depois de abrir.

**3. O que acontece se a gravação falhar?**\
A pendência fica ativa e o fluxo de menu pode continuar. Se o arquivo já foi truncado, o código não restaura o conteúdo antigo.

**4. Por que verificar `fclose()` também?**\
Uma falha pode surgir na finalização da escrita. O programa precisa fechar o fluxo mesmo se já houver indicação de erro.

**5. Sair sem salvar apaga um salvamento anterior?**\
O disco conserva o último estado gravado. As alterações que só estavam em RAM são perdidas ao encerrar.

**6. Por que `notaMedia` do Atlas é `null`?**\
A contagem dele é zero. Na RAM, a média começa em `0.0`, e o JSON usa `null` para representar ausência de avaliações.

## G. O que não falar

- Evite dizer que gravar em `"w"` só acrescenta registros ou garante recuperação automática em falha.
- Evite dizer que salvar pelo painel encerra o programa ou que sair sem salvar desfaz o que já foi gravado.
- Evite abrir ou regravar o JSON oficial durante a demonstração.

## H. Encerramento

> “Com isso, a gente saiu do JSON, trabalhou com os dados em memória e gravou o catálogo atualizado na cópia. Professor, obrigado. Estamos à disposição para as perguntas.”

**Referência de linhas.** Versão local revisada sobre ab996ce. O preparo da cópia está no guia geral.
