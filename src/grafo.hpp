#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Estrutura atualizada para double (exigência do professor)
struct aresta {
    bool existe = false;
    double peso = 0.0; 
};

class grafo {
private:
    int numVertices;
    bool orientado;
    bool ponderado;
    vector<std::vector<aresta>> matrizAdjacencia;

public:
    grafo(int vertices, bool orientado, bool ponderado);

    // Manipulação do grafo (Parte do seu colega)
    void inserirVertice();
    void removerVertice(int v);
    void inserirAresta(int u, int v, double peso = 1.0);
    void removerAresta(int u, int v);
    bool verificarExisteAresta(int u, int v) const;
    void alterarPesoAresta(int u, int v, double novoPeso);
    void exibirGrafo() const;
    int getNumVertices() const;
    int getPonderado() const;
    static grafo carregarDeArquivo(const std::string& nomeArquivo, bool orientado, bool ponderado);
    static void testAll();

    // Informações sobre vértices (Sua Parte - Bloco 3)
    int calcularGrauVertice(int v) const;
    vector<int> listarVizinhosVertice(int v) const;
    bool verificarAdjacentes(int u, int v) const;
    void dijkstra(int origem) const;
};

#endif