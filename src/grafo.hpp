#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <string>

struct aresta {
    bool existe = false;
    double peso = 0.0;
};

class grafo {
private:
    int numVertices;
    bool orientado;
    bool ponderado;
    std::vector<std::vector<aresta>> matrizAdjacencia;

    // Função auxiliar para aumentar a matriz automaticamente
    void expandirMatriz(int novoTamanho);

public:
    grafo(bool orientado = false, bool ponderado = true, int numVertices = 0);

    void carregarDeArquivo(const std::string& nomeArquivo);
    void exibirGrafo() const;
    
    void inserirVertice(int v);
    void removerVertice(int v);
    void inserirAresta(int u, int v, double peso = 1.0);
    void removerAresta(int u, int v);
    void alterarPesoAresta(int u, int v, double peso);
    bool verificarAresta(int u, int v) const;
    bool saoAdjacentes(int u, int v) const;
    int grauVertice(int v) const;
    std::vector<int> listarVizinhos(int v) const;
    
    void dijkstra(int origem) const;
};

#endif