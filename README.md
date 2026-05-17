# DCC059 :: Teoria dos Grafos - Trabalho Prático 1

## 🔹 Grupo G
* **Algoritmo Designado:** Caminho Mínimo de Dijkstra
* **Estrutura de Dados:** Matriz de Adjacência
* **Preferência de Apresentação:** 27/05/2026

### 👥 Integrantes
* Gustavo Bersan Moreira Campos
* Antônio Miguel Batista Teixeira
* Pedro José Santos de Almeida Silva

---

## 🎯 Objetivo do Projeto
O objetivo deste trabalho é implementar a estrutura de representação de grafos por **Matriz de Adjacência** e algoritmos básicos de Teoria dos Grafos, analisando o impacto dessa escolha de estrutura de dados na implementação e eficiência. O sistema é totalmente configurável, permitindo a manipulação de grafos orientados/não orientados e ponderados/não ponderados.

## 📁 Estrutura do Repositório
* `src/`: Contém todo o código-fonte em C++ (`.cpp` e `.hpp`).
  * `Grafo.hpp` - Definição do Tipo Abstrato de Dados (TAD) do Grafo.
  * `Grafo.cpp` - Implementação das operações obrigatórias e do algoritmo de Dijkstra.
  * `main.cpp` - Ponto de entrada do programa, menu interativo e execução de testes.
* `grafos/`: Pasta destinada a armazenar os arquivos de texto (`.txt`) com os grafos de teste.
* `instrucoes.txt`: Instruções detalhadas de compilação e execução do programa.

## 🛠️ Operações Implementadas
1. **Manipulação do Grafo:** Inserção e remoção de vértices/arestas, verificação de existência de aresta, alteração de peso e exibição da matriz.
2. **Informações de Vértices:** Grau do vértice, listagem de vizinhos e verificação de adjacência.
3. **Algoritmo de Dijkstra:** Encontro do caminho mínimo a partir de um vértice de origem para todos os demais (aplicável a grafos ponderados/não ponderados).
4. **Testes Automáticos (`testAll`):** Função que executa e valida todas as operações obrigatórias de forma automatizada.

---
*Trabalho desenvolvido para a disciplina de Teoria dos Grafos - 2026.*
