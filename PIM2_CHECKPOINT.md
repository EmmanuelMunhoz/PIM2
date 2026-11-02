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

1. Persistência em apenas `dados/agentes.json`. Os antigos `dados/controle.json` e `dados/avaliacoes.json` serão removidos **somente após migração e testes**, nunca antecipadamente.
2. Cada agente armazenará `notaMedia` e `quantidadeAvaliacoes`. O cadastro inicia sem nota: média `null` e contagem 0; a avaliação continua no catálogo.
3. Usar média incremental: `novaMedia = (mediaAtual * quantidadeAnterior + notaNova) / (quantidadeAnterior + 1)`. Mostrar 1 casa decimal. **Pendente:** formato de armazenamento que preserve precisão suficiente entre execuções; não arredondar a cada atualização sem avaliar o erro acumulado.
4. Eliminar histórico individual de notas e limite global `MAX_AVALIACOES=1000`; a contagem será por agente. Ao excluir o agente, eliminar também seus agregados de avaliações.
5. Trocar inativação (status 0/1) por exclusão física. Ao excluir, deslocar **todos os vetores paralelos relacionados** para manter os campos alinhados, sem renumerar IDs dos demais agentes.
6. Próximo ID por `maior ID existente + 1` (ou 1 se não houver agentes). IDs dos agentes ativos no arquivo devem ser únicos. Se o maior ID anterior foi excluído, seu número poderá ser reutilizado; a unicidade aqui é dos registros existentes, não histórica.
7. Carregar JSON no início; trabalhar nos vetores globais na RAM; reduzir escritas repetidas no arquivo. **Pendente:** decidir interface final de salvar manualmente, comportamento da saída e gestão de alterações não salvas.
8. Criar headers por responsabilidades/módulos, evitando header monolítico, mas cada `.c` pode incluir outros headers necessários; não criar `main.h` artificial.
9. Preservar o comportamento do catálogo, operações administrativas e tratamento de entrada, adaptando o necessário ao novo escopo.

## Diagnóstico da versão-base

- Branch: `main`. Commit `6ea6f00`, publicado em 02/11/2026, contém comentários e formatação em 8 arquivos `.c` após revisão de diff, sem alteração funcional identificada.
- Arquivos atuais: `main.c`, `menus.c`, `entrada.c`, `autenticacao.c`, `cadastro.c`, `consultas.c`, `persistencia.c`, `dados.c`, `functions.h`, `README.md`, três arquivos JSON.
- Dados atuais publicados: 20 agentes IDs 1–20; próximo ID 21; três avaliações individuais (ID 3 recebe 5 e 3, média 4.0; ID 4 recebe 0, média 0.0). **Preservar essas diferenças na migração**: zero avaliação e nota zero não são equivalentes.
- O diff anterior foi revisado; a compilação e os testes da versão recém-publicada ainda devem ser executados e registrados antes de alegar validação funcional nova.

## Cronograma e critérios

- [x] **S1 — Baseline e decisões (02/11):** verificar Git remoto/local, revisar diff, publicar versão-base e checkpoint.
- [ ] **S2 — Esquema JSON final (02/11):** definir campos, null, precisão média e estratégia de migração.
- [ ] **S3 — Média incremental (03/11):** implementar e testar primeira nota, zero, repetição e recarga.
- [ ] **S4 — IDs sem controle.json (03/11):** testar buracos, exclusão do maior e catálogo vazio.
- [ ] **S5 — Exclusão física (04/11):** deslocar todos os vetores e testar primeiro/meio/último agente.
- [ ] **S6 — Persistência única (04/11):** carregar/gravar somente agentes.json e migrar dados sem perdas.
- [ ] **S7 — Salvar controlado (05/11):** saída/salvar manual/erro de gravação definidos e testados.
- [ ] **S8 — Headers modulares (05/11):** includes e protótipos corretos, compilação limpa.
- [ ] **S9 — Menus/documentação (06/11):** remover fluxos obsoletos e atualizar README.
- [ ] **S10 — Auditoria e regressões (06–07/11):** testar cenários e arquivo persistido.
- [ ] **S11 — Conferência acadêmica (08–09/11):** aderência aos slides e apresentação.
- [ ] **S12 — Revisão final (10–11/11):** entrega, documentação e conferência de links.

## Modo de trabalho

Para cada etapa: diagnóstico → mudança mínima → compilar → testar → revisar diff → aprovação → commit → atualizar checkpoint.
Não alterar código durante S1; não apagar dados originais até migração ser demonstrada.
As datas são metas de planejamento e podem ser ajustadas.
