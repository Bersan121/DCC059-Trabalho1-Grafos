#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Estrutura para representar cada célula da Matriz de Adjacência
struct aresta {
    bool existe = false;
    int peso = 0;
};

class grafo {
private:
    int numVertices;
    bool orientado;
    bool ponderado;
    vector<std::vector<aresta>> matrizAdjacencia;

public:
    // Construtor
    grafo(int vertices, bool orientado, bool ponderado);

    // Manipulação do grafo
    void inserirVertice();
    void removerVertice(int v);
    void inserirAresta(int u, int v, int peso = 1);
    void removerAresta(int u, int v);
    bool verificarExisteAresta(int u, int v) const;
    void alterarPesoAresta(int u, int v, int novoPeso);
    void exibirGrafo() const;
    int getNumVertices() const;
    int getPonderado() const;

    // Leitura do arquivo
    static grafo carregarDeArquivo(const std::string& nomeArquivo, bool orientado, bool ponderado);

    // Informações sobre vértices
    int calcularGrauVertice(int v) const;
    vector<int> listarVizinhosVertice(int v) const;
    bool verificarAdjacentes(int u, int v) const;

    // Algoritmo Caminho mínimo de Dijkstra
    void dijkstra(int origem) const;

    // Função de teste
    static void testAll();
};

#endif