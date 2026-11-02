# PIM II — CHECKPOINT DE DECISÕES E REESTRUTURAÇÃO

Atualizado: 2026-11-02
Repositório: EmmanuelMunhoz/PIM2
Baseline funcional anterior à reestruturação: `6ea6f002e26c4447082cfdbc1f6ba8622e6a9f17`
Origem: orientações do professor Kotaki relatadas pelo grupo e decisões discutidas.
Estado: S1 encerrada após publicação deste documento; S2 ainda não implementada.

## Regras acadêmicas e limites

- Linguagem C e somente técnicas efetivamente ensinadas nas aulas/materiais do professor.
- Sem `struct` (inclusive `struct tm`), `windows.h`, `MoveFileExA`, APIs de Windows ou bibliotecas externas.
- Vetores paralelos estáticos; respeitar limites de tamanho e capacidade.
- Não confundir requisito confirmado com sugestão técnica; conferir qualquer divergência com enunciado/professor.

## Decisões aprovadas

1. Persistência em apenas `dados/agentes.json`. Os antigos `dados/controle.json` e `dados/avaliacoes.json` serão removidos **somente após implementação e testes**. **Não migrar as notas individuais antigas**: o proprietário decidiu reiniciar as avaliações.
2. Cada agente armazenará `notaMedia` e `quantidadeAvaliacoes`. O cadastro inicia sem nota: média `null` e contagem 0; a avaliação continua no catálogo.
3. Usar média incremental: `novaMedia = (mediaAtual * quantidadeAnterior + notaNova) / (quantidadeAnterior + 1)`. **Manter somente os campos `notaMedia` e `quantidadeAvaliacoes`**, SEM criar `somaNotas`. Exibir a média com `%.1f`. Observação técnica: `%.1f` arredonda a saída, não necessariamente o valor armazenado; persistir `notaMedia` com precisão suficiente (ex.: `%.17g` ao gravar um `double`) para evitar perda por arredondamentos sucessivos. Validar compatibilidade com o parser.
4. Eliminar histórico individual de notas e limite global `MAX_AVALIACOES=1000`; a contagem será por agente. Ao excluir o agente, eliminar também seus agregados de avaliações.
5. Trocar inativação (status 0/1) por exclusão física. Ao excluir, deslocar **todos os vetores paralelos relacionados** para manter os campos alinhados, sem renumerar IDs dos demais agentes.
6. Próximo ID por `maior ID existente + 1` (ou 1 se não houver agentes). IDs dos agentes ativos no arquivo devem ser únicos. Se o maior ID anterior foi excluído, seu número poderá ser reutilizado; a unicidade aqui é dos registros existentes, não histórica.
7. Carregar JSON no início; trabalhar nos vetores globais na RAM; reduzir escritas repetidas no arquivo. **APROVADO PELO PROPRIETÁRIO:** quando o usuário escolher `-1` em qualquer menu ou `0` no menu principal, se houver alterações pendentes perguntar: `1 — Salvar e sair`, `2 — Sair sem salvar`, `0 — Cancelar e voltar ao programa`. Se não houver alterações pendentes, encerrar sem perguntar. Se salvar falhar, não afirmar sucesso nem encerrar como se tivesse salvo. Uma única rotina de gravação do JSON; sem salvamento automático durante cada operação.
8. Criar headers por responsabilidades/módulos, evitando header monolítico, mas cada `.c` pode incluir outros headers necessários; não criar `main.h` artificial.
9. Preservar o comportamento do catálogo, operações administrativas e tratamento de entrada, adaptando o necessário ao novo escopo.

## Diagnóstico da versão-base

- Branch: `main`. Commit `6ea6f00`, publicado em 02/11/2026, contém comentários e formatação em 8 arquivos `.c` após revisão de diff, sem alteração funcional identificada.
- Arquivos atuais: `main.c`, `menus.c`, `entrada.c`, `autenticacao.c`, `cadastro.c`, `consultas.c`, `persistencia.c`, `dados.c`, `functions.h`, `README.md`, três arquivos JSON.
- Dados atuais publicados: 20 agentes IDs 1–20; próximo ID 21; três avaliações individuais (ID 3 recebe 5 e 3, média 4.0; ID 4 recebe 0, média 0.0). **Decisão explícita do proprietário em 02/11:** manter os agentes, DESCARTAR as avaliações antigas na nova versão; todos os agentes iniciam com `"notaMedia": null` e `"quantidadeAvaliacoes": 0`. Não migrar notas antigas. Preservar backup da base anterior para recuperação se necessário.
- O diff anterior foi revisado; a compilação e os testes da versão recém-publicada ainda devem ser executados e registrados antes de alegar validação funcional nova.

## Decisões do proprietário — 02/11/2026 (prevalecem sobre propostas anteriores)

- Não criar `somaNotas` nem um terceiro campo agregado: os únicos campos de avaliação por agente são `notaMedia` e `quantidadeAvaliacoes`.
- A apresentação usa `%.1f`; o valor persistido não deve ser limitado artificialmente a uma casa decimal só porque a exibição é assim.
- Não migrar as três avaliações históricas; zerar todos os contadores e definir média como `null` na versão nova.
- Após implementar, executar rodada de avaliação **no console do VS Code**, avaliando **cada um dos 20 agentes ao menos três vezes** (mínimo 60 avaliações). Esse ensaio será executado e verificado, não declarado como concluído antecipadamente.
- Fluxo de saída **APROVADO**: se existirem alterações pendentes, `1 — Salvar e sair`, `2 — Sair sem salvar`, `0 — Cancelar e voltar ao programa`, acionado por `-1` ou `0` no menu principal. Sem alterações pendentes, encerrar diretamente.
- Prioridade: concluir implementação, testes e documentação **em 02/11/2026**, com verificações reais; cronograma abaixo é histórico e está sendo replanejado para hoje.

## Cronograma e critérios

- [x] **S1 — Baseline e decisões (02/11):** verificar Git remoto/local, revisar diff, publicar versão-base e checkpoint.
- [ ] **S2 — Esquema JSON final (02/11):** definir campos `notaMedia`/`quantidadeAvaliacoes`, serialização precisa e reset das avaliações.
- [ ] **S3 — Média incremental (prioridade 02/11):** implementar e testar primeira nota, zero, repetição e recarga.
- [ ] **S4 — IDs sem controle.json (prioridade 02/11):** testar buracos, exclusão do maior e catálogo vazio.
- [ ] **S5 — Exclusão física (prioridade 02/11):** deslocar todos os vetores e testar primeiro/meio/último agente.
- [ ] **S6 — Persistência única (prioridade 02/11):** carregar/gravar somente agentes.json, manter agentes e reiniciar avaliações conforme decisão do proprietário.
- [ ] **S7 — Salvar controlado (prioridade 02/11):** saída/salvar manual/erro de gravação definidos e testados.
- [ ] **S8 — Headers modulares (prioridade 02/11):** includes e protótipos corretos, compilação limpa.
- [ ] **S9 — Menus/documentação (prioridade 02/11):** remover fluxos obsoletos e atualizar README.
- [ ] **S10 — Auditoria e regressões (prioridade 02/11):** testar cenários e arquivo persistido.
- [ ] **S11 — Conferência acadêmica (prioridade 02/11):** aderência aos slides e apresentação.
- [ ] **S12 — Revisão final (prioridade 02/11):** entrega, documentação e conferência de links.

## Modo de trabalho

Para cada etapa: diagnóstico → mudança mínima → compilar → testar → revisar diff → aprovação → commit → atualizar checkpoint.
Não alterar código durante S1; não apagar dados originais até migração ser demonstrada.
Datas anteriores preservadas apenas como histórico de planejamento; o proprietário solicitou antecipação para 02/11/2026. Não afirmar conclusão sem verificações.
