#include "grafo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

// =========================================================
// CONSTRUTOR E CARREGAMENTO (Padrão do Grupo)
// =========================================================

grafo::grafo(int numVertices, bool orientado, bool ponderado){
    this->numVertices = numVertices;
    this->orientado = orientado;
    this->ponderado = ponderado;

    this->matrizAdjacencia.resize(this->numVertices, vector<aresta>(this->numVertices));
}

grafo grafo::carregarDeArquivo(const string& nomeArquivo, bool orientado, bool ponderado){
    ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()){
        cout << "Erro ao abrir o arquivo.\nCriando grafo vazio." << endl;
        return grafo(0, orientado, ponderado);
    }

    string linha;
    int maxVertice = -1;
    struct DadosAresta {
        int u, v, peso;
    };
    vector<DadosAresta> arestasLidas;

    //Início da leitura
    while(getline(arquivo, linha)){
        if(linha.empty())
            continue;
        stringstream ss(linha);
        int u, v, peso = 1;
        if(ss >> u >> v){
            if(ponderado)
                ss >> peso;
            arestasLidas.push_back({u, v, peso});
            maxVertice = max({maxVertice, u, v});
        }
        else{
            cout << "Erro na leitura da linha do arquivo:" << endl;
            cout << linha;
        }
    }

    //Criar o grafo
    grafo g(maxVertice+1, orientado, ponderado);

    for(size_t i = 0; i < arestasLidas.size(); ++i) {
        g.inserirAresta(arestasLidas[i].u, arestasLidas[i].v, arestasLidas[i].peso);
    }
    cout << "Grafo carregado de " << nomeArquivo << endl;
    return g;
}

void grafo::exibirGrafo() const{
    cout << endl << "Matriz de Adjacencia" << endl;
    cout << "   ";
    for(int i = 0; i < numVertices; i++)
        cout << setw(4) << i;
    cout << endl;

    for(int i = 0; i < numVertices; i++){
        cout << setw(2) << i << " ";
        for(int j = 0; j < numVertices; j++){
            if(matrizAdjacencia[i][j].existe){
                if(ponderado)
                    cout << setw(4) << matrizAdjacencia[i][j].peso;
                else
                    cout << setw(4) << "1";
            }
            else
                cout << setw(4) << ".";
        }
        cout << endl;
    }
}

void grafo::inserirVertice(){
    for(int i = 0; i < numVertices; i++){
        matrizAdjacencia[i].push_back(aresta());
    }
    numVertices++;
    matrizAdjacencia.push_back(vector<aresta>(numVertices));
    cout << "Vertice " << numVertices - 1 << " inserido com sucesso!" << endl;
}

void grafo::removerVertice(int v){
    if (v < 0 || v >= numVertices) return;

    for(int i = 0; i < numVertices; i++){
        matrizAdjacencia[i].erase(matrizAdjacencia[i].begin() + v);
    }

    matrizAdjacencia.erase(matrizAdjacencia.begin() + v);
    numVertices--;

    cout << "Vertice " << v << " removido com sucesso!" << endl;
}

void grafo::inserirAresta(int u, int v, int peso){
    if(u < 0 || v < 0){
        cout << "Operacao invalida!"<< endl;
    }
    else if(u >= numVertices){
        if(u == v){
            cout << "Vertice " << u << " sera criados na posicao " << numVertices << endl;
            this->inserirVertice();
            this->inserirAresta(numVertices -1, numVertices -1, peso);
        }
        else{
            cout << "Vertice " << u << " sera criado na posicao " << numVertices << endl;
            this->inserirVertice();
            this->inserirAresta(numVertices -1, v, peso);
        }
    }
    else if(v >= numVertices){
        cout << "Vertice " << v << " sera criado na posicao " << numVertices << endl;
        this->inserirVertice();
        this->inserirAresta(u, numVertices -1, peso);
    }
    else{
        matrizAdjacencia[u][v].existe = true;
        if(ponderado)
            matrizAdjacencia[u][v].peso = peso;
        else
            matrizAdjacencia[u][v].peso = 1;
            
        if(!orientado){
            matrizAdjacencia[v][u].existe = true;
            if(ponderado)
                matrizAdjacencia[v][u].peso = peso;
            else
                matrizAdjacencia[v][u].peso = 1;
        }
        cout << "Aresta inserida com sucesso!" << endl;
    }
}

void grafo::removerAresta(int u, int v){
    if(u < 0 || v < 0 || u >= numVertices || v >= numVertices){
        cout << "Índices inválidos" << endl;
        return;
    }

    if(!verificarExisteAresta(u, v)){
        cout << "Não existe aresta entre os vértices " << u << " e " << v << endl;
        return;
    }

    matrizAdjacencia[u][v].existe = false;
    matrizAdjacencia[u][v].peso = 0;

    if(!orientado){
        matrizAdjacencia[v][u].existe = false;
        matrizAdjacencia[v][u].peso = 0;
    }

    cout << "Aresta removida com sucesso!" << endl;
}

bool grafo::verificarExisteAresta(int u, int v) const{
    if(u < 0 || v < 0 || u >= numVertices || v >= numVertices){
        return false;
    }
    return matrizAdjacencia[u][v].existe;
}

void grafo::alterarPesoAresta(int u, int v, int novoPeso){
    if(verificarExisteAresta(u, v)){
        matrizAdjacencia[u][v].peso = novoPeso;
    }
    else{
        cout << "Aresta não existe!" << endl;
        return;
    }

    if(!orientado){
        matrizAdjacencia[v][u].peso = novoPeso;
    }

    cout << "Peso alterado com sucesso!" << endl;
}

int grafo::calcularGrauVertice(int v) const{
    if (v < 0 || v >= numVertices) return 0;
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

vector<int> grafo::listarVizinhosVertice(int v) const{
    vector<int> vizinhos;
    if (v < 0 || v >= numVertices) return vizinhos;
    
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencia[v][i].existe) {
            vizinhos.push_back(i);
        }
    }
    return vizinhos;
}

bool grafo::verificarAdjacentes(int u, int v) const{
    return verificarExisteAresta(u, v);
}

void grafo::dijkstra(int origem) const{
    if (origem >= numVertices || origem < 0) {
        cout << "Origem invalida!\n";
        return;
    }

    vector<int> distancias(numVertices, 1e9); 
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
                int pesoAresta = matrizAdjacencia[u][v].peso;
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

int grafo::getNumVertices() const{
    return this->numVertices;
}

int grafo::getPonderado() const{
    return this->ponderado;
}
