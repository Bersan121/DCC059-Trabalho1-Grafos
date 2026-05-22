#include "grafo.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

// =========================================================
// PARTE DO SEU COLEGA (Estrutura Básica Corrigida para double)
// =========================================================
grafo::grafo(int numVertices, bool orientado, bool ponderado){
    this->numVertices = numVertices;
    this->orientado = orientado;
    this->ponderado = ponderado;
    this->matrizAdjacencia.resize(this->numVertices, vector<aresta>(this->numVertices));
}

int grafo::getNumVertices() const{ return this->numVertices; }
int grafo::getPonderado() const{ return this->ponderado; }

grafo grafo::carregarDeArquivo(const string& nomeArquivo, bool orientado, bool ponderado){
    ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()){
        cout << "Erro ao abrir o arquivo.\nCriando grafo vazio." << endl;
        return grafo(0, orientado, ponderado);
    }

    string linha;
    int maxVertice = -1;
    struct DadosAresta {
        int u, v;
        double peso;
    };
    vector<DadosAresta> arestasLidas;

    while(getline(arquivo, linha)){
        if(linha.empty()) continue;
        stringstream ss(linha);
        int u, v;
        double peso = 1.0;
        if(ss >> u >> v){
            if(ponderado) ss >> peso;
            arestasLidas.push_back({u, v, peso});
            maxVertice = max({maxVertice, u, v});
        } else {
            cout << "Erro na leitura da linha do arquivo: " << linha << endl;
        }
    }

    grafo g(maxVertice + 1, orientado, ponderado);
    for(size_t i = 0; i < arestasLidas.size(); ++i) {
        g.inserirAresta(arestasLidas[i].u, arestasLidas[i].v, arestasLidas[i].peso);
    }
    cout << "Grafo carregado de " << nomeArquivo << endl;
    return g;
}

void grafo::exibirGrafo() const{
    cout << endl << "Matriz de Adjacencia" << endl;
    cout << "   ";
    for(int i = 0; i < numVertices; i++) cout << setw(5) << i;
    cout << endl;

    for(int i = 0; i < numVertices; i++){
        cout << setw(2) << i << " ";
        for(int j = 0; j < numVertices; j++){
            if(matrizAdjacencia[i][j].existe){
                if(ponderado) cout << setw(5) << matrizAdjacencia[i][j].peso;
                else cout << setw(5) << "1";
            }
            else cout << setw(5) << ".";
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

void grafo::inserirAresta(int u, int v, double peso){
    if(u < 0 || v < 0){
        cout << "Operacao invalida!"<< endl;
    }
    else if(u >= numVertices){
        if(u == v){
            cout << "Vertice " << u << " sera criado na posicao " << numVertices << endl;
            this->inserirVertice();
            this->inserirAresta(numVertices -1, numVertices -1, peso);
        } else {
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
    else {
        matrizAdjacencia[u][v].existe = true;
        matrizAdjacencia[u][v].peso = ponderado ? peso : 1.0;
        if(!orientado){
            matrizAdjacencia[v][u].existe = true;
            matrizAdjacencia[v][u].peso = ponderado ? peso : 1.0;
        }
        cout << "Aresta inserida com sucesso!" << endl;
    }
}

void grafo::removerAresta(int u, int v){
    if(u < 0 || v < 0 || u >= numVertices || v >= numVertices){
        cout << "Indices invalidos" << endl;
        return;
    }
    if(!verificarExisteAresta(u, v)){
        cout << "Nao existe aresta entre os vertices " << u << " e " << v << endl;
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
    if(u < 0 || v < 0 || u >= numVertices || v >= numVertices) return false;
    return matrizAdjacencia[u][v].existe;
}

void grafo::alterarPesoAresta(int u, int v, double novoPeso){
    if(verificarExisteAresta(u, v)){
        matrizAdjacencia[u][v].peso = novoPeso;
        if(!orientado) matrizAdjacencia[v][u].peso = novoPeso;
        cout << "Peso alterado com sucesso!" << endl;
    } else {
        cout << "Aresta nao existe!" << endl;
    }
}

void grafo::testAll(){
    cout << endl << "===== TESTE AUTOMATICO DO GRUPO =====" << endl;
    grafo obj(0, false, true); // True no fim para poder testar pesos
    obj.inserirVertice();
    obj.inserirAresta(0, obj.getNumVertices() - 1, 7.5);
    obj.alterarPesoAresta(0, obj.getNumVertices() - 1, 20.3);
    obj.removerAresta(0, obj.getNumVertices() - 1);
    obj.removerVertice(obj.getNumVertices() - 1);
    cout << "===== FIM DOS TESTES =====" << endl;
}

// =========================================================
// SUA PARTE (Injetada com sucesso no código principal)
// =========================================================

int grafo::calcularGrauVertice(int v) const {
    if (v < 0 || v >= numVertices) return 0;

    int grauEntrada = 0, grauSaida = 0;
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencia[v][i].existe) grauSaida++;
        if (matrizAdjacencia[i][v].existe) grauEntrada++;
    }
    return orientado ? (grauSaida + grauEntrada) : grauSaida;
}

vector<int> grafo::listarVizinhosVertice(int v) const {
    vector<int> vizinhos;
    if (v < 0 || v >= numVertices) return vizinhos;
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencia[v][i].existe) vizinhos.push_back(i);
    }
    return vizinhos;
}

bool grafo::verificarAdjacentes(int u, int v) const {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) return false;
    return matrizAdjacencia[u][v].existe;
}

void grafo::dijkstra(int origem) const {
    if (origem < 0 || origem >= numVertices) {
        cout << "Erro: Vertice de origem " << origem << " invalido!" << endl;
        return;
    }

    const double INF = 1e9;
    vector<double> distancias(numVertices, INF);
    vector<int> predecessores(numVertices, -1);
    vector<bool> visitados(numVertices, false);

    distancias[origem] = 0;

    for (int i = 0; i < numVertices; i++) {
        int u = -1;
        double min_dist = INF;
        
        for (int j = 0; j < numVertices; j++) {
            if (!visitados[j] && distancias[j] < min_dist) {
                min_dist = distancias[j];
                u = j;
            }
        }

        if (u == -1) break;
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

    cout << endl << "=====================================================" << endl;
    cout << "          RESULTADO DO ALGORITMO DE DIJKSTRA         " << endl;
    cout << "=====================================================" << endl;
    cout << "Vertice de Origem: " << origem << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << left << setw(10) << "Destino" << setw(15) << "Distancia" << "Caminho Mais Curto" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << left << setw(10) << i;
        if (distancias[i] == INF) {
            cout << setw(15) << "Inalcancavel" << "-" << endl;
        } else {
            cout << setw(15) << distancias[i];
            string caminho = to_string(i);
            int atual = predecessores[i];
            while (atual != -1) {
                caminho = to_string(atual) + " -> " + caminho;
                atual = predecessores[atual];
            }
            cout << caminho << endl;
        }
    }
    cout << "=====================================================" << endl;
}