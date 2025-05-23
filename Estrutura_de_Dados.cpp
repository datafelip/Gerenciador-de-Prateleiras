#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>
using namespace std;
 
struct No {
    int indice_livro;
    No* proximo;
};
 
bool isEmpty(No* topo) {
    bool vazia;
    if (topo == nullptr) {
        vazia = true;
    } else {
        vazia = false;
    }
    return vazia;
}
 
bool verificar_pilha_cheia(int tamanhoAtual, int capacidadeMaxima) {
    return tamanhoAtual >= capacidadeMaxima;
}
 
void empilhar_livro(No*& topo, int codigo) {
    No* novo = new No;
    novo->indice_livro = codigo;
    novo->proximo = topo;
    topo = novo;
}
 
void enfileirar_lista_espera(No*& frente, No*& tras, int codigo) {
    No* novo = new No;
    novo->indice_livro = codigo;
    novo->proximo = nullptr;
    if (tras == nullptr) {
        frente = tras = novo;
    } else {
        tras->proximo = novo;
        tras = novo;
    }
}
 
bool desenfileirar(No*& frente, No*& tras, int& codigo) {
    if (frente == nullptr) {
        return false;
    }
    No* temp = frente;
    codigo = temp->indice_livro;
    frente = frente->proximo;
    if (frente == nullptr) {
        tras = nullptr;
    }
    delete temp;
    return true;
}
 
bool desempilhar_livro(No*& topo, int& codigo) {
    if (isEmpty(topo)) {
        return false;
    }
    No* temp = topo;
    codigo = temp->indice_livro;
    topo = topo->proximo;
    delete temp;
    return true;
}
 
bool verificar_codigo_existente(No* topo1, No* topo2, int codigo) {
    for (No* temp = topo1; temp != nullptr; temp = temp->proximo) {
        if (temp->indice_livro == codigo) {
            return true;
        }
    }
    for (No* temp = topo2; temp != nullptr; temp = temp->proximo) {
        if (temp->indice_livro == codigo) {
            return true;
        }
    }
    return false;
}
 
void exibir_fila_espera(No* frente, const string& nome) {
    cout << nome << " (Frente -> Tras): ";
    if (isEmpty(frente)) {
        cout << "Vazio\n";
        system("Pause");
        return;
    }
    No* atual = frente;
    while (atual != nullptr) {
        cout << atual->indice_livro;
        if (atual->proximo != nullptr) {
            cout << " -> ";
        }
        atual = atual->proximo;
    }
    cout << "\n";
}
 
void exibir_conteudo_pilhas(No* topo, const string& nome) {
    cout << nome << " (Topo -> Base): ";
    if (isEmpty(topo)) {
        cout << "Vazia\n";
        return;
    }
    No* atual = topo;
    while (atual != nullptr) {
        cout << atual->indice_livro;
        if (atual->proximo != nullptr) cout << " -> ";
        atual = atual->proximo;
    }
    cout << "\n";
}
 
int contar_livros(No* topo) {
    int cont = 0;
    No* atual = topo;
    while (atual != nullptr) {
        cont++;
        atual = atual->proximo;
    }
    return cont;
}
 
int menuPrincipal() {
    int opcao;
    cout << setw(20) << "\nMenu de Opções" << endl;
    cout << "1 - Inserir livro\n"
         << "2 - Remover livro\n"
         << "3 - Ver conteúdo das prateleiras\n"
         << "4 - Ver Lista de Espera\n"
         << "5 - Sair\n";
    cout << "Digite ==>: ";
    cin >> opcao;
if (cin.fail() || opcao < 1 || opcao > 5) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Entrada inválida!!!\n";
        system("pause");
        system("cls");
        return -1;
    }
    return opcao;
}
 
int main() {
    SetConsoleOutputCP(CP_UTF8);
    const int capacidadeMaxima = 1;
    No* fila_livros_espera = nullptr;
    No* fim_fila = nullptr;
    No* prateleira1 = nullptr;
    No* prateleira2 = nullptr;
    bool continuar = true;
    while (continuar) {
        system("cls");
        int opcao = menuPrincipal();
        switch (opcao) {
            case 1: {
                int codigo;
                cout << "Digite o código do livro: ";
                cin >> codigo;
                if (verificar_codigo_existente(prateleira1, prateleira2, codigo)) {
                    cout << "Código do livro já existe na pilha.\n";
                } else {
                    if (!verificar_pilha_cheia(contar_livros(prateleira1), capacidadeMaxima)) {
                        empilhar_livro(prateleira1, codigo);
                        cout << "Livro inserido na Prateleira 1.\n";
                    } else if (!verificar_pilha_cheia(contar_livros(prateleira2), capacidadeMaxima)) {
                        empilhar_livro(prateleira2, codigo);
                        cout << "Livro inserido na Prateleira 2.\n";
                    } else {
                        enfileirar_lista_espera(fila_livros_espera, fim_fila, codigo);
                        cout << "Prateleiras lotadas! Livro inserido na fila de espera.\n";
                    }
                }
                system("pause");
                break;
            }
 
            case 2: {
                int escolha, codigo;
                cout << "Deseja retirar livro de qual prateleira? (1 ou 2): ";
                cin >> escolha;
                if (escolha == 1) {
                    if (desempilhar_livro(prateleira1, codigo))
                        cout << "Livro com código: " << codigo << " removido da Prateleira 1.\n";
                    else
                        cout << "Prateleira 1 está vazia.\n";
                } else if (escolha == 2) {
                    if (desempilhar_livro(prateleira2, codigo))
                        cout << "Livro com código: " << codigo << " removido da Prateleira 2.\n";
                    else
                        cout << "Prateleira 2 está vazia.\n";
                } else {
                    cout << "Prateleira inválida!\n";
                    break;
                }
 
                if (!verificar_pilha_cheia(contar_livros(prateleira1), capacidadeMaxima) && fila_livros_espera != nullptr) {
                    int livroFila;
                    if (desenfileirar(fila_livros_espera, fim_fila, livroFila)) {
                        empilhar_livro(prateleira1, livroFila);
                        cout << "Livro da fila com código " << livroFila << " inserido na Prateleira 1.\n";
                    }
                } else if (!verificar_pilha_cheia(contar_livros(prateleira2), capacidadeMaxima) && fila_livros_espera != nullptr) {
                    int livroFila;
                    if (desenfileirar(fila_livros_espera, fim_fila, livroFila)) {
                        empilhar_livro(prateleira2, livroFila);
                        cout << "Livro da fila com código " << livroFila << " inserido na Prateleira 2.\n";
                    }
                }
                system("pause");
                break;
            }
 
            case 3:
                cout << "\nConteúdo das Prateleiras:\n";
                exibir_conteudo_pilhas(prateleira1, "Prateleira 1");
                exibir_conteudo_pilhas(prateleira2, "Prateleira 2");
                system("pause");
                break;
 
            case 4:
                cout << "\nLista de Espera dos Livros:\n";
                exibir_fila_espera(fila_livros_espera, "Fila de Espera");
                system("pause");
                break;
 
            case 5:
                cout << "Saindo..\n";
                continuar = false;
                break;
        }
    }
 
    int memoria;
    while (desempilhar_livro(prateleira1, memoria));
    while (desempilhar_livro(prateleira2, memoria));
    while (desenfileirar(fila_livros_espera, fim_fila, memoria));
 
    cout << "Programa encerrado. Memória liberada.\n";
    return 0;
}