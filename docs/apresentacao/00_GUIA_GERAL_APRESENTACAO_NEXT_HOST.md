# Guia geral da apresentação
PIM II · NEXT HOST · UNIP

> **Ponto de partida:** menu principal aberto, 12 agentes na cópia de demonstração e nenhuma alteração pendente. Um único processo deve permanecer aberto até Otávio encerrar.

## Ordem e passagem do computador

| Ordem e responsável | O que faz na demonstração | Tela entregue e estado da RAM |
|---|---|---|
| **1. Emmanuel** | Mostra `main()`, a carga e os vetores paralelos. Abre o programa na pasta de demonstração. | **Principal** → Kauan. 12 agentes, sem pendências. |
| **2. Kauan** | Abre o catálogo **1**, escolhe o agente **1**, avalia com nota **5** e confirma **1**. Volta com **0**, **0**. | **Principal** → Little Pepper. ConectaRH 360 tem 12 avaliações e média exibida de 4.1. Alteração pendente. |
| **3. Little Pepper** | Usa **2** e erra três vezes. No principal, usa **2** novamente e informa a senha em privado. | **Painel** → Gleison. A avaliação segue pendente. |
| **4. Gleison** | Usa **1** e cadastra `Atlas Demo` com os quatro campos do roteiro. | **Painel** → Pedro Negrelli. 13 agentes em RAM. ID **13**, índice **12** e avaliação pendente. |
| **5. Pedro Negrelli** | Usa **2**, seleciona **13** na lista, edita a **Descrição**. Volta com **0**, **0**, **0**. | **Painel** → Pedrinho. Avaliação, cadastro e descrição estão pendentes. |
| **6. Pedrinho** | Busca ID **999999** para mostrar ausência. Busca ID **13** e edita a **Categoria**. Volta com **0**, **0**. | **Painel** → Marcos. As quatro alterações seguem pendentes. |
| **7. Marcos** | Usa **4**, pesquisa `Conecta`, abre resultado **2**, ID **7**. Usa **0** na ficha. | **Painel** → Otávio. Os dados pendentes permanecem iguais. |
| **8. Otávio** | Usa **5** para salvar. Mostra o JSON da demonstração. Volta com **0** e sai com **0**. | **Processo encerrado**. A cópia tem 13 agentes com as alterações gravadas. |

**Combinado de palco.** Cada pessoa entrega o teclado na tela indicada. Use o roteiro individual para ensaiar as falas. Até Otávio, evite **5** no painel, **-2** na lista pública e **-1** nas telas de navegação. O **0** volta um nível, exceto no menu principal, onde significa Sair.

<!-- pagebreak -->

## Preparação da cópia de demonstração

Use o PowerShell na raiz do repositório local atualizado. Os comandos criam uma pasta temporária exclusiva, extraem só o catálogo de 12 agentes registrado no Git e compilam os arquivos C locais. A saída do programa e todo salvamento ficam nessa pasta. Use o mesmo computador no ensaio e na apresentação, com o GCC disponível.

```powershell
$demo = Join-Path ([IO.Path]::GetTempPath()) ("PIM2-Demo-" + [guid]::NewGuid())
New-Item -ItemType Directory -Path $demo | Out-Null
$zip = Join-Path $demo "catalogo-inicial.zip"
git archive --format=zip --output=$zip ab996ce6274d807450e71a11dfee8650a9d2a2ae dados/agentes.json
if ($LASTEXITCODE -ne 0) { throw "Falha ao extrair o catálogo de demonstração." }
Expand-Archive -LiteralPath $zip -DestinationPath $demo
$catalogo = Join-Path $demo "dados\agentes.json"
$agentes = Get-Content -Raw -Encoding UTF8 -LiteralPath $catalogo | ConvertFrom-Json
if ($agentes.Count -ne 12 -or $agentes[0].id -ne 1) {
    throw "O catálogo inicial da demonstração deve ter 12 agentes."
}
$fontes = @(Get-ChildItem -File -Filter "*.c" | ForEach-Object { $_.FullName })
gcc -std=c99 -Wall -Wextra @fontes -o (Join-Path $demo "pim2-demo.exe")
if ($LASTEXITCODE -ne 0) { throw "Falha de compilação." }
Set-Location -LiteralPath $demo
Get-Location
chcp 65001
.\pim2-demo.exe
```

- **Confira a pasta de trabalho** impressa por `Get-Location`. Ela deve ser `PIM2-Demo-...` no diretório temporário. O programa resolve `dados/agentes.json` a partir dessa pasta.
- **Use um ensaio novo a cada passagem completa.** Repetir o preparo cria outra pasta com 12 agentes e evita acumular avaliações e cadastros de testes anteriores.
- **Prepare a projeção.** Deixe a janela do terminal, os trechos de código necessários e uma segunda janela para ler o JSON da cópia. A pessoa responsável pela senha deve interromper a projeção durante a entrada válida e cobrir qualquer eco antes de voltar ao terminal. Projete `autenticacao.c` a partir da linha 15, sem abrir a linha da credencial.

<!-- pagebreak -->

## Dados de teste e conferência

- **Kauan.** `ConectaRH 360`, ID **1**, parte da média **4.0** e de **11** avaliações. Com nota **5** confirmada, a ficha fica com **4.1** e **12** avaliações. O cálculo é `49 / 12`, e `%.1f` só arredonda a exibição.
- **Gleison.** Preencha **Nome** `Atlas Demo`, **Descrição** `Agente de teste da apresentacao`, **Categoria** `Demonstracao` e **Instruções** `Responda com exemplos simples`. O ID gerado é **13**. O índice é **12** e o agente começa sem avaliações.
- **Pedro Negrelli.** Troque a descrição para `Descricao revisada por Pedro`. **Pedrinho.** Troque a categoria para `Categoria revisada`. Os exemplos de entrada são ASCII para evitar depender da configuração de digitação de acentos no console.
- **Marcos.** `Conecta` retorna, na ordem, **1. ConectaRH 360** e **2. ConectaSocial Pro**. O resultado **2** abre o ID **7**, que ocupa o índice **6**.
- **Otávio.** A opção **5** deve mostrar `Alterações salvas em dados/agentes.json.`. Na segunda janela, use o caminho completo da cópia e confira **13** registros, os dois campos editados do Atlas Demo, `notaMedia: null` no Atlas e **12** avaliações no ID **1**. O número gravado da média tem mais casas que o número da ficha.

## Como recuperar a demonstração

**Opção ou texto inválido.** Leia a mensagem e retome a partir da tela atual. Se o cadastro for cancelado, volte à opção **1** do painel e preencha os quatro campos. Em edição, use **0** no menu de edição para voltar à ficha.

**ID 13 ou resultados esperados ausentes.** Confira se Gleison recebeu a confirmação de cadastro. Procure o Atlas na lista. Se já existir com outro ID, use o ID exibido e diga por que o valor divergiu. Se a base inteira divergir, abra uma cópia nova e retome a partir do último estado conhecido, usando as falas para explicar as etapas puladas.

**Saída antes da hora.** Na pergunta de pendência, use **0** para cancelar. Se o processo já encerrou, reabra na mesma pasta. Só as mudanças já salvas voltam na carga. Para reconstruir as pendências, repita somente as operações necessárias.

**Falha de salvamento.** O programa segue aberto e conserva a pendência. Confira se a cópia de demonstração está gravável. Se não houver tempo para corrigir, explique a falha, use o trecho do escritor e encerre a demonstração sem afirmar que o arquivo foi salvo.

<!-- pagebreak -->

## Ensaio de exclusão e saída sem salvar

Faça este ensaio em **outra cópia temporária**, fora da sequência principal, depois de criar o Atlas Demo.

1. No painel, use **3**, informe o ID do Atlas e escolha **2** na ficha. Na confirmação, escolha **1**. A ficha sai e a busca retorna ao painel.
2. Abra **2** no painel e confira que a lista perdeu o Atlas. A exclusão compacta os vetores em RAM se houver registros posteriores. **0** volta ao painel.
3. Para testar a persistência da exclusão, use **5** e inspecione apenas o JSON dessa pasta. Para testar descarte, repita em cópia separada após gravar o Atlas, exclua em RAM, use **0** do painel e **0** no principal. Na confirmação, escolha **2**. Ao reabrir, o Atlas continua no arquivo.
4. No palco, Otávio salva uma vez pelo painel. Com a pendência limpa, o próximo **0** no principal encerra sem diálogo. Explique que, se uma pendência existir, **1** salva e sai, **2** sai sem gravar as mudanças desde o último salvamento e **0** cancela a saída.

## Versão de referência

Os números de linha e as telas dos roteiros correspondem ao **código local revisado**, sobre o commit `ab996ce6274d807450e71a11dfee8650a9d2a2ae`. Quando o guia foi preparado, as melhorias de código ainda estavam locais, inclusive a média com uma casa e o novo prompt de senha. Um checkout público só com a documentação pode mostrar mensagens, formatação e números de linha anteriores. O catálogo inicial da demonstração vem do commit acima, independentemente dos dados na árvore de trabalho.

O manual técnico **NEXT HOST - Manual Interno Completo**, de 187 páginas, é referência de estudo complementar. Em caso de diferença de texto ou numeração, use os trechos indicados nos roteiros e o código local compilado para a apresentação.

## Roteiros individuais

1. [Emmanuel](01_EMMANUEL.md) · Inicialização e arquitetura
2. [Kauan](02_KAUAN.md) · Catálogo e avaliação
3. [Little Pepper](03_LITTLE_PEPPER.md) · Autenticação
4. [Gleison](04_GLEISON.md) · Painel e cadastro
5. [Pedro Negrelli](05_PEDRO_NEGRELLI.md) · Listagem e edição
6. [Pedrinho](06_PEDRINHO.md) · Busca por ID
7. [Marcos](07_MARCOS.md) · Busca por nome
8. [Otávio](08_OTAVIO.md) · Persistência e encerramento
