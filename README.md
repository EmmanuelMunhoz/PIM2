# PIM II — Catálogo de Agentes de Inteligência Artificial

Projeto acadêmico desenvolvido em **linguagem C** para o **Projeto Integrado Multidisciplinar II (PIM II) da UNIP**.

## Sobre o projeto

O **AI Agent Registry** é uma aplicação de console destinada a organizar e consultar um catálogo de agentes de inteligência artificial. Cada agente possui identificador, nome, descrição, categoria, instruções de uso e informações de avaliação.

O projeto reúne conceitos de programação estruturada estudados ao longo do semestre, como funções, estruturas condicionais e de repetição, vetores, matrizes, manipulação de strings e leitura e escrita de arquivos.

## Funcionalidades

- **Catálogo de agentes:** visualização dos agentes cadastrados e de suas informações.
- **Avaliações:** atribuição de notas inteiras de 0 a 5, com apresentação da média e do total de avaliações.
- **Painel administrativo:** acesso mediante autenticação para cadastrar, consultar, editar e excluir agentes.
- **Pesquisas:** localização de agentes por identificador ou por nome.
- **Persistência:** carregamento do catálogo ao iniciar e salvamento das alterações em arquivo JSON.
- **Controle de alterações:** aviso ao encerrar quando existem modificações ainda não salvas.

## Organização e funcionamento

A implementação foi dividida em módulos `.c` e seus respectivos arquivos de declaração `.h`, separados por responsabilidades como menus, entrada de dados, cadastro, consultas, autenticação, médias e persistência.

Os registros são mantidos em **vetores paralelos na memória** durante a execução. Um mesmo índice identifica os dados de um agente nos diferentes vetores, sem utilização de `struct`.

O arquivo **`dados/agentes.json`** contém o catálogo persistido. O programa lê esse arquivo na inicialização; alterações feitas durante o uso são mantidas em memória até o salvamento. A leitura e a escrita do JSON foram implementadas com funções da biblioteca padrão de C, seguindo o formato esperado pela aplicação, sem dependências de bibliotecas JSON externas.

## Como executar

É necessário ter um compilador de C, como o GCC, disponível no computador. No terminal, na pasta raiz do projeto, compile os arquivos-fonte:

```bash
gcc -std=c99 -Wall -Wextra main.c menus.c entrada.c autenticacao.c cadastro.c consultas.c persistencia.c dados.c medias.c -o pim2
```

Depois execute o programa:

**Windows (PowerShell):**
```powershell
.\pim2.exe
```

**Linux/macOS:**
```bash
./pim2
```

Execute a aplicação a partir da **raiz do projeto**, mantendo a pasta `dados` e o arquivo `dados/agentes.json` no local esperado. O painel administrativo requer a autenticação prevista no programa.

## Contexto acadêmico

Este repositório apresenta a implementação do PIM II, com foco na aplicação prática dos fundamentos de C e na organização de um sistema de cadastro e consulta com persistência de dados. A aplicação é executada em terminal e não possui interface web.

**Instituição:** Universidade Paulista (UNIP)  
**Disciplina/projeto:** Projeto Integrado Multidisciplinar II (PIM II)
