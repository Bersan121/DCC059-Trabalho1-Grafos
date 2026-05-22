#include <iostream>
#include <vector>
#include <algorithm>
#include "grafo.hpp"

using namespace std;

void testAll() {
    grafo gNaoOrientado(false);
    grafo gOrientado(true);

    int passou = 0;
    int falhou = 0;
    int excecoes = 0;

    std::cout << "==================================================\n";
    std::cout << "              BATERIA DE TESTES \n";
    std::cout << "==================================================\n\n";

    // --- PARTE A: NÃO ORIENTADO ---
    std::cout << "--------------------------------------------------\n";
    std::cout << "      Fase 1: Testando Grafo Nao Orientado        \n";
    std::cout << "--------------------------------------------------\n\n";

    std::cout << "[TESTE] Inserindo vertices iniciais (0 a 5)...\n";
    try {
        for (int i = 0; i <= 5; i++) gNaoOrientado.inserirVertice(i);
        std::cout << "  STATUS: PASSOU\n\n"; passou++;
    } catch (...) { std::cout << "  STATUS: FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Inserindo malha de arestas...\n";
    try {
        gNaoOrientado.inserirAresta(0, 1, 1.5);
        gNaoOrientado.inserirAresta(0, 2, 2.0);
        gNaoOrientado.inserirAresta(1, 2, 1.0);
        gNaoOrientado.inserirAresta(2, 3, 3.5);
        gNaoOrientado.inserirAresta(3, 4, 4.0);
        gNaoOrientado.inserirAresta(4, 5, 2.5);
        gNaoOrientado.inserirAresta(3, 5, 5.0);
        std::cout << "  STATUS: PASSOU\n\n"; passou++;
    } catch (...) { std::cout << "  STATUS: FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar existencia da aresta existente (0, 1):\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta(0, 1);
        if (obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar existencia na direcao inversa (1, 0):\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta(1, 0);
        if (obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar aresta inexistente entre vertices existentes (0, 5):\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta(0, 5);
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar vertices invalidos/inexistentes (99, 100):\n";
    try {
        bool obtido = gNaoOrientado.verificarAresta(99, 100);
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Alterar peso da aresta (2, 3) para 9.9:\n";
    try {
        gNaoOrientado.alterarPesoAresta(2, 3, 9.9);
        std::cout << "  STATUS:         PASSOU\n\n"; passou++;
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Calcular grau do vertice 2 (Conectado a 0, 1 e 3):\n";
    try {
        int obtido = gNaoOrientado.grauVertice(2);
        if (obtido == 3) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Calcular grau de vertice inexistente (99):\n";
    try {
        int obtido = gNaoOrientado.grauVertice(99);
        if (obtido == 0) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Listar vizinhos do vertice 3:\n";
    try {
        std::vector<int> obtido = gNaoOrientado.listarVizinhos(3);
        std::sort(obtido.begin(), obtido.end()); 
        bool correto = (obtido.size() == 3 && obtido[0] == 2 && obtido[1] == 4 && obtido[2] == 5);
        if (correto) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar se 4 e 5 de forma bidirecional sao adjacentes:\n";
    try {
        bool dir1 = gNaoOrientado.saoAdjacentes(4, 5);
        bool dir2 = gNaoOrientado.saoAdjacentes(5, 4);
        if (dir1 && dir2) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Remover aresta (3, 4):\n";
    try {
        gNaoOrientado.removerAresta(3, 4);
        bool aindaExisteDireto = gNaoOrientado.verificarAresta(3, 4);
        bool aindaExisteInverso = gNaoOrientado.verificarAresta(4, 3);
        if (!aindaExisteDireto && !aindaExisteInverso) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Remover vertice 2 (Remocao de No Central):\n";
    try {
        gNaoOrientado.removerVertice(2);
        bool adj02 = gNaoOrientado.saoAdjacentes(0, 2);
        bool adj12 = gNaoOrientado.saoAdjacentes(1, 2);
        int grauRestante0 = gNaoOrientado.grauVertice(0);
        if (!adj02 && !adj12 && grauRestante0 == 1) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }


    // --- PARTE B: ORIENTADO ---
    std::cout << "--------------------------------------------------\n";
    std::cout << "        Fase 2: Testando Grafo Orientado          \n";
    std::cout << "--------------------------------------------------\n\n";

    std::cout << "[TESTE] Inserindo vertices iniciais (0 a 5)...\n";
    try {
        for (int i = 0; i <= 5; i++) gOrientado.inserirVertice(i);
        std::cout << "  STATUS: PASSOU\n\n"; passou++;
    } catch (...) { std::cout << "  STATUS: FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Inserindo malha direcionada de arcos...\n";
    try {
        gOrientado.inserirAresta(0, 1, 1.0);
        gOrientado.inserirAresta(1, 2, 2.0);
        gOrientado.inserirAresta(2, 0, 3.0);
        gOrientado.inserirAresta(2, 3, 1.5);
        gOrientado.inserirAresta(3, 4, 2.5);
        gOrientado.inserirAresta(4, 5, 3.5);
        gOrientado.inserirAresta(5, 3, 4.5);
        std::cout << "  STATUS: PASSOU\n\n"; passou++;
    } catch (...) { std::cout << "  STATUS: FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar existencia da aresta direcionada existente (0, 1):\n";
    try {
        bool obtido = gOrientado.verificarAresta(0, 1);
        if (obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar existencia na direcao inversa (1, 0):\n";
    try {
        bool obtido = gOrientado.verificarAresta(1, 0);
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar arco inexistente entre vertices existentes (0, 5):\n";
    try {
        bool obtido = gOrientado.verificarAresta(0, 5);
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar vertices invalidos no Orientado (99, 100):\n";
    try {
        bool obtido = gOrientado.verificarAresta(99, 100);
        if (!obtido) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Verificar Adjacencia Unidirecional (2, 3) vs (3, 2):\n";
    try {
        bool dir1 = gOrientado.saoAdjacentes(2, 3);
        bool dir2 = gOrientado.saoAdjacentes(3, 2);
        if (dir1 && !dir2) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Remover arco direcionado (4, 5):\n";
    try {
        gOrientado.removerAresta(4, 5);
        bool aindaExiste = gOrientado.verificarAresta(4, 5);
        if (!aindaExiste) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Remover vertice 3 (Ponto de articulacao):\n";
    try {
        gOrientado.removerVertice(3);
        bool adj23 = gOrientado.saoAdjacentes(2, 3);
        bool adj53 = gOrientado.saoAdjacentes(5, 3);
        if (!adj23 && !adj53) { std::cout << "  STATUS:         PASSOU\n\n"; passou++; }
        else { std::cout << "  STATUS:         FALHOU\n\n"; falhou++; }
    } catch (...) { std::cout << "  STATUS:         FALHOU\n\n"; excecoes++; }

    std::cout << "[TESTE] Exibir estado impresso dos grafos finais:\n";
    try {
        std::cout << ">> GRAFO NAO ORIENTADO RESULTANTE:\n";
        gNaoOrientado.exibirGrafo(); 
        std::cout << "\n>> GRAFO ORIENTADO RESULTANTE:\n";
        gOrientado.exibirGrafo();
        std::cout << "--------------------------------------------------\n";
        std::cout << "  STATUS:         PASSOU\n\n"; passou++;
    } catch (...) { std::cout << "  STATUS:         FALHOU \n\n"; excecoes++; }

    std::cout << "==================================================\n";
    std::cout << "         RESUMO FINAL DA BATERIA DE TESTES        \n";
    std::cout << "==================================================\n";
    std::cout << "  TESTES QUE PASSARAM: " << passou << "\n";
    std::cout << "  TESTES QUE FALHARAM: " << falhou << "\n";
    std::cout << "  EXCECOES CAPTURADAS: " << excecoes << "\n";
    std::cout << "  TOTAL DE CASOS TESTADOS: " << (passou + falhou + excecoes) << "\n";
    std::cout << "==================================================\n\n";
}

int main() {
    grafo* gAtual = nullptr;
    int opcao = -1;

    string arquivo;
    int ehOrientado, ehPonderado;
    
    cout << "Digite o caminho/nome do arquivo .txt: ";
    cin >> arquivo;
    cout << "O grafo e orientado? (1-Sim, 0-Nao): ";
    cin >> ehOrientado;
    cout << "O grafo e ponderado? (1-Sim, 0-Nao): ";
    cin >> ehPonderado;

    gAtual = new grafo(ehOrientado == 1, ehPonderado == 1);
    gAtual->carregarDeArquivo(arquivo);

    while (opcao != 0) {
        cout << "\n====== MENU PRINCIPAL ======\n";
        cout << "1. Executar testes automaticos (testAll)\n";
        cout << "2. Exibir Grafo Atual\n";
        cout << "3. Executar Algoritmo de Dijkstra\n";
        cout << "4. Inserir Vertice\n";
        cout << "5. Remover Vertice\n";
        cout << "6. Inserir Aresta\n";
        cout << "7. Remover Aresta\n";
        cout << "8. Alterar peso Aresta\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                testAll();
                break;
            case 2:
                cout << "\nMatriz de Adjacencia:\n";
                gAtual->exibirGrafo();
                break;
            case 3: {
                int origem;
                cout << "Digite o vertice de origem para o Dijkstra: ";
                cin >> origem;
                gAtual->dijkstra(origem);
                break;
            }
            case 4: {
                int v;
                cout << "Digite o id do novo vertice: ";
                cin >> v;
                gAtual->inserirVertice(v);
                cout << "Vertice inserido/expandido!\n";
                break;
            }
            case 5: {
                int v;
                cout << "Digite o id do vertice a remover: ";
                cin >> v;
                gAtual->removerVertice(v);
                cout << "Vertice removido!\n";
                break;
            }
            case 6: {
                int u, v;
                double peso = 1.0;
                cout << "Origem e Destino (ex: 0 1): ";
                cin >> u >> v;
                cout << "Peso: ";
                cin >> peso;
                gAtual->inserirAresta(u, v, peso);
                cout << "Aresta inserida!\n";
                break;
            }
            case 7: {
                int u, v;
                cout << "Origem e Destino (ex: 0 1): ";
                cin >> u >> v;
                gAtual->removerAresta(u, v);
                cout << "Aresta removida!\n";
                break;
            }
            case 8: {
                int u, v;
                double peso;
                cout << "Origem e Destino (ex: 0 1): ";
                cin >> u >> v;
                cout << "Novo Peso: ";
                cin >> peso;
                gAtual->alterarPesoAresta(u, v, peso);
                cout << "Peso alterado!\n";
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }
    }

    delete gAtual;
    return 0;
}