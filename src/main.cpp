#include <iostream>
#include "Grafo.hpp"

void exibirMenu() {
    cout << "\n====== MENU PRINCIPAL ======\n";
    cout << "1. Executar testes automáticos (testAll)\n";
    cout << "2. Exibir Grafo Atual\n";
    cout << "3. Executar Algoritmo de Dijkstra\n";
    cout << "4. Inserir Vértice\n";
    cout << "5. Remover Vértice\n";
    cout << "6. Inserir Aresta\n";
    cout << "7. Remover Aresta\n";
    cout << "0. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    string caminho;
    int ori, pond;
    cout << "Digite o caminho/nome do arquivo .txt: ";
    cin >> caminho;
    cout << "O grafo é orientado? (1-Sim, 0-Não): ";
    cin >> ori;
    cout << "O grafo é ponderado? (1-Sim, 0-Não): ";
    cin >> pond;
    grafo g = grafo::carregarDeArquivo(caminho, ori == 1, pond == 1);
    g.exibirGrafo();

    int opcao = -1;
    while (opcao != 0) {
        exibirMenu();
        if (!(cin >> opcao)) {
            cout << "Entrada inválida! Encerrando.\n";
            break;
        }

        switch (opcao) {
            case 1:
                g.testAll();
                break;
            case 2:
                g.exibirGrafo();
                break;
            case 3: {
                int orig;
                cout << "Digite o vértice de origem para o Dijkstra (0 a " << g.getNumVertices() - 1 << "): ";
                cin >> orig;
                g.dijkstra(orig);
                break;
            }
            case 4:
                g.inserirVertice();
                break;
            case 5: {
                int v;
                cout << "Digite o índice do vértice a remover: ";
                cin >> v;
                g.removerVertice(v);
                break;
            }
            case 6: {
                int u, v, p = 1;
                cout << "Digite o vértice de origem u: ";
                cin >> u;
                cout << "Digite o vértice de destino v: ";
                cin >> v;
                if(g.getPonderado()){
                    cout << "Digite o peso: ";
                    cin >> p;
                }
                g.inserirAresta(u, v, p);
                break;
            }
            case 7: {
                int u, v;
                cout << "Digite o vértice de origem u: ";
                cin >> u;
                cout << "Digite o vértice de destino v: ";
                cin >> v;
                g.removerAresta(u, v);
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    }

    return 0;
}
