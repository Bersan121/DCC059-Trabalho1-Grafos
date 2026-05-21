#include <iostream>
#include "Grafo.hpp"

void exibirMenu() {
    cout << endl << "====== MENU PRINCIPAL ======" << endl;
    cout << "1. Executar testes automaticos (testAll)" << endl;
    cout << "2. Exibir Grafo Atual" << endl;
    cout << "3. Executar Algoritmo de Dijkstra" << endl;
    cout << "4. Inserir Vertice" << endl;
    cout << "5. Remover Vertice" << endl;
    cout << "6. Inserir Aresta" << endl;
    cout << "7. Remover Aresta" << endl;
    cout << "8. Alterar peso Aresta" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    string caminho;
    int ori, pond;
    cout << "Digite o caminho/nome do arquivo .txt: ";
    cin >> caminho;
    cout << "O grafo e orientado? (1-Sim, 0-Nao): ";
    cin >> ori;
    cout << "O grafo e ponderado? (1-Sim, 0-Nao): ";
    cin >> pond;
    grafo g = grafo::carregarDeArquivo(caminho, ori == 1, pond == 1);
    g.exibirGrafo();

    int opcao = -1;
    while (opcao != 0) {
        exibirMenu();
        if (!(cin >> opcao)) {
            cout << "Entrada invalida! Encerrando." << endl;
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
                cout << "Digite o vertice de origem para o Dijkstra (0 a " << g.getNumVertices() - 1 << "): ";
                cin >> orig;
                g.dijkstra(orig);
                break;
            }
            case 4:
                g.inserirVertice();
                break;
            case 5: {
                int v;
                cout << "Digite o indice do vertice a remover: ";
                cin >> v;
                g.removerVertice(v);
                break;
            }
            case 6: {
                int u, v, p = 1;
                cout << "Digite o vertice de origem u: ";
                cin >> u;
                cout << "Digite o vertice de destino v: ";
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
                cout << "Digite o vertice de origem u: ";
                cin >> u;
                cout << "Digite o vertice de destino v: ";
                cin >> v;
                g.removerAresta(u, v);
                break;
            }
            case 8: {
                int u, v, peso;
                cout << "Digite o vertice de origem u da aresta que deseja modificar: ";
                cin >> u;
                cout << "Digite o vertice de destino v da aresta que deseja modificar: ";
                cin >> v;
                cout << "Digite o novo peso: ";
                cin >> peso;
                g.alterarPesoAresta(u, v, peso);
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    }

    return 0;
}
