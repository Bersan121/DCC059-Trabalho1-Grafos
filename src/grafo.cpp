#include "grafo.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

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

    for(int i = 0; i < arestasLidas.size(); ++i) {
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

    if(verificarExisteAresta(u, v)){
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

    if(u < 0 || v < 0){
        return false;
    }

    else{
        if(matrizAdjacencia[u][v].existe){
            return true;
        }

    return false;
    }
}

void grafo::alterarPesoAresta(int u, int v, int novoPeso){

    if(verificarExisteAresta(u, v)){
        matrizAdjacencia[u][v].peso = novoPeso;
    }
    else
    {
        cout << "Aresta não existe!" << endl;
        return;
    }

    if(orientado){
        matrizAdjacencia[v][u].peso = novoPeso;
    }

    cout << "Peso alterado com sucesso!" << endl;
}

void grafo::testAll(){
    cout << endl;
    cout << "===== TESTE AUTOMATICO =====" << endl;

    grafo obj(0, false, false);

    cout << endl << "Grafo inicial:" << endl;
    obj.exibirGrafo();

    cout << endl << "Inserindo vertice..." << endl;
    obj.inserirVertice();
    obj.exibirGrafo();

    cout << endl << "Inserindo aresta 0 -> ultimo vertice..." << endl;
    obj.inserirAresta(0, obj.getNumVertices() - 1, 7);
    obj.exibirGrafo();

    cout << endl << "Alterando peso..." << endl;
    obj.alterarPesoAresta(0, obj.getNumVertices() - 1, 20);
    obj.exibirGrafo();

    cout << endl << "Removendo aresta..." << endl;
    obj.removerAresta(0, obj.getNumVertices() - 1);
    obj.exibirGrafo();

    cout << endl << "Removendo ultimo vertice..." << endl;
    obj.removerVertice(obj.getNumVertices() - 1);
    obj.exibirGrafo();

    cout << endl << "===== FIM DOS TESTES =====" << endl;
}

int grafo::calcularGrauVertice(int v) const{
    //Bloco 3
    return 0;
}

vector<int> grafo::listarVizinhosVertice(int v) const{
    //Bloco 3
    vector<int> vizinhos;
    return vizinhos;
}

bool grafo::verificarAdjacentes(int u, int v) const{
    //Bloco 3
    return 0;
}

void grafo::dijkstra(int origem) const{
    //Bloco 3
}

int grafo::getNumVertices() const{
    return this->numVertices;
}

int grafo::getPonderado() const{
    return this->ponderado;
}
