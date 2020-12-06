# Gerenciador de Projetos

[![Licença](https://img.shields.io/github/license/tastyigniter/TastyIgniter.svg?label=License&style=flat-square)](https://github.com/tastyigniter/TastyIgniter/blob/master/LICENSE.txt)

[Gerenciador de Projetos](https://github.com/VniciusMiranda/ed1-EC-2020-1) é uma aplicação de terminal exclusiva para linux, que visa ser um meio de organizar atividades, de modo a acompanhar o progresso de projetos. A medida que vamos evoluindo na área de computação cada vez mais surgem ideias de novos projetos a serem feitos de modo que torna dificil organizar as demandas de cada projeto. Tendo isso vista, o Gerenciador de projetos é uma proposta de solução para essa problematica.

### Documentação

A estrutura de organização de projetos será a seguinte:

* Todo projeto será composto de listas de tarefas
* Cada lista de tarefa será composto por atividades

#### Projetos

* Cadastrar Projetos;
* Excluir Projetos;
* Visualizar lista de tarefas do projeto;
* Definir colaboradores do projeto;

#### Lista de Tarefas

* Cadastrar lista de tarefas;
* Excluir lista de tarefas;
* Visualizar atividades de uma lista de tarefas;
* Mudar a posição da lista de tarefa;
* Mudar descrição da lista de tarefa;

#### Atividades

* Adicionar atividade a lista de tarefas;
* Excluir atividade da lista de tarefas;
* Mudar descrição e titulo;
* Mudar posição/prioridade da atividade dentro da lista;

#### Visualizar Algoritmos de Sorting

* Escolher um algoritmo de sorting (bubble sorting, merge sort, quick sort, heap sorting);
* Escolher um tamanho de array;
* visualizar algoritmo em ação;

OBS:Essa funcionalidade podera ou não ser implementada de acordo com o andamento das outras demandas.

### Depêndencias
O Gerenciador de projetos utilizará a linguagem de programação C e a biblioteca visual ncurses.

### Como Compilar e Rodar
Dentro do  diretório *project*, siga as seguintes instruções.

Crie os diretórios "executable" e "obj":

```
mkdir executable/ obj/
```

Compile o código usando make:
```
make
```

agora apenas rode o executavel e seja feliz :)
```
./executable/project-organizer
```

### Autores

* Victor Eduardo Iscava Moreira;
* Vinicius Medeiros Miranda;

alunos de Engenharia de Computação, da Universidade Federal de Goiás.
