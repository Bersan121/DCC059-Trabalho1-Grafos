#include "grafo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

// Construtor
grafo::grafo(bool orientado, bool ponderado, int numVertices) {
    this->orientado = orientado;
    this->ponderado = ponderado;
    this->numVertices = numVertices;
    matrizAdjacencia.resize(numVertices, vector<aresta>(numVertices));
}

void grafo::expandirMatriz(int novoTamanho) {
    if (novoTamanho <= numVertices) return;
    for (int i = 0; i < numVertices; i++) {
        matrizAdjacencia[i].resize(novoTamanho);
    }
    matrizAdjacencia.resize(novoTamanho, vector<aresta>(novoTamanho));
    numVertices = novoTamanho;
}

void grafo::carregarDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << "\n";
        return;
    }

    string linha;
    int maxVertice = -1;
    vector<pair<pair<int, int>, double>> arestasLidas;

    while (getline(arquivo, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        int u, v;
        double peso = 1.0;

        if (ss >> u >> v) {
            if (ponderado) ss >> peso;
            arestasLidas.push_back({{u, v}, peso});
            maxVertice = max({maxVertice, u, v});
        }
    }
    arquivo.close();

    expandirMatriz(maxVertice + 1);
    for (size_t i = 0; i < arestasLidas.size(); i++) {
        inserirAresta(arestasLidas[i].first.first, arestasLidas[i].first.second, arestasLidas[i].second);
    }
    cout << "Grafo carregado com sucesso (" << numVertices << " vertices).\n";
}

void grafo::exibirGrafo() const {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrizAdjacencia[i][j].existe) {
                cout << setw(5) << matrizAdjacencia[i][j].peso;
            } else {
                cout << setw(5) << ".";
            }
        }
        cout << "\n";
    }
}

void grafo::inserirVertice(int v) {
    if (v >= numVertices) {
        expandirMatriz(v + 1);
    }
}

void grafo::removerVertice(int v) {

}

void grafo::inserirAresta(int u, int v, double peso) {
    int maxReq = max(u, v);
    if (maxReq >= numVertices) expandirMatriz(maxReq + 1);

    matrizAdjacencia[u][v].existe = true;
    matrizAdjacencia[u][v].peso = peso;

    if (!orientado) {
        matrizAdjacencia[v][u].existe = true;
        matrizAdjacencia[v][u].peso = peso;
    }
}

void grafo::removerAresta(int u, int v) {

}

void grafo::alterarPesoAresta(int u, int v, double peso) {

}

bool grafo::verificarAresta(int u, int v) const {
    
}

bool grafo::saoAdjacentes(int u, int v) const {
    return verificarAresta(u, v);
}

int grafo::grauVertice(int v) const {
    if (v >= numVertices) return 0;
    int grau = 0;
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencia[v][i].existe) grau++;
    }
    if (orientado) {
        for (int i = 0; i < numVertices; i++) {
            if (matrizAdjacencia[i][v].existe) grau++;
        }
    }
    return grau;
}

vector<int> grafo::listarVizinhos(int v) const {
    vector<int> vizinhos;
    if (v >= numVertices) return vizinhos;
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencia[v][i].existe) {
            vizinhos.push_back(i);
        }
    }
    return vizinhos;
}

void grafo::dijkstra(int origem) const {
    if (origem >= numVertices || origem < 0) {
        cout << "Origem invalida!\n";
        return;
    }

    vector<double> distancias(numVertices, 1e9);
    vector<int> predecessores(numVertices, -1);
    vector<bool> visitados(numVertices, false);

    distancias[origem] = 0;

    for (int i = 0; i < numVertices; i++) {
        int u = -1;
        for (int j = 0; j < numVertices; j++) {
            if (!visitados[j] && (u == -1 || distancias[j] < distancias[u])) {
                u = j;
            }
        }

        if (distancias[u] == 1e9) break;
        visitados[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (matrizAdjacencia[u][v].existe && !visitados[v]) {
                double pesoAresta = matrizAdjacencia[u][v].peso;
                if (distancias[u] + pesoAresta < distancias[v]) {
                    distancias[v] = distancias[u] + pesoAresta;
                    predecessores[v] = u;
                }
            }
        }
    }

    cout << "\n=====================================================\n";
    cout << "         RESULTADO DO ALGORITMO DE DIJKSTRA          \n";
    cout << "=====================================================\n";
    cout << "Vertice de Origem: " << origem << "\n";
    cout << "-----------------------------------------------------\n";
    cout << "Destino   Distancia      Caminho Mais Curto\n";
    cout << "-----------------------------------------------------\n";

    for (int i = 0; i < numVertices; i++) {
        cout << left << setw(10) << i;
        if (distancias[i] == 1e9) {
            cout << setw(15) << "Inatingivel" << "-\n";
        } else {
            cout << setw(15) << distancias[i];
            vector<int> caminho;
            for (int at = i; at != -1; at = predecessores[at]) {
                caminho.push_back(at);
            }
            reverse(caminho.begin(), caminho.end());
            for (size_t j = 0; j < caminho.size(); j++) {
                cout << caminho[j] << (j == caminho.size() - 1 ? "" : " -> ");
            }
            cout << "\n";
        }
    }
    cout << "=====================================================\n";
}