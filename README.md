# AI Agent Registry

### Catálogo e Gerenciador de Configurações de Agentes de Inteligência Artificial

**Projeto Integrado Multidisciplinar II (PIM II)** · **Análise e Desenvolvimento de Sistemas** · **Universidade Paulista (UNIP)**

---

## Sobre o projeto

O **AI Agent Registry** é um sistema de console desenvolvido em **linguagem C** para organizar, consultar e gerenciar configurações de agentes de Inteligência Artificial em um catálogo centralizado.

Um agente pode representar uma configuração voltada, por exemplo, ao atendimento ao cliente, ao apoio financeiro ou à revisão de código. O catálogo reúne informações como identificação, nome, instruções e nota, facilitando a consulta e a manutenção dos registros.

**O objetivo é gerenciar as configurações dos agentes, não executar modelos de IA ou depender de serviços externos de inteligência artificial.**

## Funcionalidades do sistema

### Gerenciamento dos agentes

- Cadastro de novos agentes.
- Listagem e consulta dos registros cadastrados.
- Pesquisa por identificador (ID) e por nome.
- Visualização dos dados completos de um agente.
- Edição e exclusão de registros.
- Navegação entre os menus e encerramento do sistema.

### Regras fundamentais

| Informação | Regra |
| --- | --- |
| Capacidade do catálogo | Até **50 agentes** |
| Identificador | **Único** para cada agente |
| Nome | Até **80 caracteres** |
| Script / instruções | Até **1.000 caracteres**, incluindo espaços |
| Nota | Valor de **0 a 5** |

O programa deve tratar situações como dados inválidos, identificadores repetidos, catálogo vazio, buscas sem resultados e tentativas de ultrapassar a capacidade definida.

### Recursos complementares do catálogo

A proposta também contempla a organização por categorias, a consulta de avaliações e classificações dos agentes e a distinção entre consulta ao catálogo e funções administrativas.

## Organização técnica

A implementação utiliza os princípios de **Programação Estruturada em C**, incluindo:

- Funções com responsabilidades definidas, parâmetros e retornos.
- Estruturas condicionais e de repetição.
- **Vetores paralelos** para representar os dados dos agentes, preservando a correspondência entre suas posições.
- Validação de entradas e tratamento de situações excepcionais.
- **Persistência em arquivos**, permitindo gravar e recuperar os registros entre execuções.
- Código-fonte organizado e comentado para facilitar manutenção e compreensão.

## Modelagem de dados e integração acadêmica

Além da aplicação em C, o PIM II contempla a **modelagem de banco de dados** do catálogo, com diagrama entidade-relacionamento (DER), definição de atributos e restrições, dicionário de dados, scripts SQL e consultas de exemplo.

A modelagem relacional integra a documentação acadêmica e **não pressupõe conexão direta entre o programa em C e um servidor de banco de dados**.

O trabalho também relaciona conhecimentos de Engenharia de Software Ágil, Redes de Computadores, testes e validação, uso responsável de Inteligência Artificial e aspectos éticos e sociais associados ao sistema.

## Finalidade acadêmica

Este projeto foi desenvolvido no contexto do **PIM II do curso de Análise e Desenvolvimento de Sistemas da UNIP**, com foco na aplicação prática dos conhecimentos adquiridos nas disciplinas e no desenvolvimento colaborativo de uma solução organizada, documentada e verificável.

---

**AI Agent Registry · PIM II · UNIP**
