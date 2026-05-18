#include "grafo.hpp"

grafo::grafo(int vertices, bool orientado, bool ponderado){
    this->numVertices = vertices;
    this->orientado = orientado;
    this->ponderado = ponderado;

    matrizAdjacencia.resize(this->numVertices, vector<aresta>(this->numVertices));
}

int grafo::getNumVertices() const{
    return numVertices;
}