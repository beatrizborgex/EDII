#include <iostream>
using namespace std;

// Estrutura básica do nó da ABB
struct Node {
    int data;
    Node* left;
    Node* right;
    int count; // Para o exercício 4

    Node(int value) : data(value), left(nullptr), right(nullptr), count(1) {}
};

// Classe da Arvore Binária de Busca (ABB)
class BST {
private:
    Node* root;

    // Função auxiliar para inserir um nó
    Node* inserir(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->data) {
            node->left = inserir(node->left, value);
        } else {
            node->right = inserir(node->right, value);
        }
        node->count = 1 + getCount(node->left) + getCount(node->right);
        return node;
    }

    // Função auxiliar para contar nós
    int getCount(Node* node) {
        return node ? node->count : 0;
    }

    // Função auxiliar para verificar similaridade estrutural
    bool estruturalmenteSimilar(Node* a, Node* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return estruturalmenteSimilar(a->left, b->left) && estruturalmenteSimilar(a->right, b->right);
    }

    // Função auxiliar para imprimir visualmente a ABB
    void imprimirVisual(Node* node, int nivel) {
        if (node) {
            imprimirVisual(node->right, nivel + 1);
            for (int i = 0; i < nivel; i++) cout << "    ";
            cout << node->data << "\n";
            imprimirVisual(node->left, nivel + 1);
        }
    }

    // Função auxiliar para converter a ABB em lista encadeada ordenada
    void converterParaListaEncadeada(Node* node, Node*& head) {
        if (!node) return;
        converterParaListaEncadeada(node->right, head);  // Primeiro percorre a direita
        node->right = head;  // Define o próximo elemento na lista encadeada
        if (head) head->left = nullptr;  // Remove o ponteiro esquerdo no novo elemento
        head = node;  // Atualiza a cabeça da lista encadeada
        converterParaListaEncadeada(node->left, head);  // Por fim, percorre a esquerda
    }

    // Função auxiliar para encontrar o k-ésimo menor elemento
    int encontrarKthElemento(Node* node, int k) {
        int leftCount = getCount(node->left);
        if (k == leftCount + 1) return node->data;  // Encontrou o elemento
        if (k <= leftCount) return encontrarKthElemento(node->left, k);
        return encontrarKthElemento(node->right, k - leftCount - 1);
    }

public:
    BST() : root(nullptr) {}

    void inserir(int value) {
        root = inserir(root, value);
    }

    bool estruturalmenteSimilar(BST& outraArvore) {
        return estruturalmenteSimilar(this->root, outraArvore.root);
    }

    void imprimirVisual() {
        imprimirVisual(root, 0);
    }

    Node* converterParaListaEncadeada() {
        Node* head = nullptr;
        converterParaListaEncadeada(root, head);
        return head;
    }

    void exibirListaEncadeada(Node* head) {
        while (head) {
            cout << head->data << " -> ";
            head = head->right;
        }
        cout << "NULL\n";
    }

    int encontrarKthElemento(int k) {
        return encontrarKthElemento(root, k);
    }
};

int main() {
    BST arvore1, arvore2, arvore3;

    // Arvore 1
    arvore1.inserir(10);
    arvore1.inserir(5);
    arvore1.inserir(15);

    // Arvore 2 - Estrutura similar à Arvore 1
    arvore2.inserir(20);
    arvore2.inserir(10);
    arvore2.inserir(30);

    // Arvore 3 - Estrutura diferente
    arvore3.inserir(8);
    arvore3.inserir(3);
    arvore3.inserir(12);

    cout << "\nImpressao Visual da Arvore 1:\n";
    arvore1.imprimirVisual();

    cout << "\nImpressao Visual da Arvore 2:\n";
    arvore2.imprimirVisual();

    cout << "\nImpressao Visual da Arvore 3:\n";
    arvore3.imprimirVisual();

    cout << "\nArvore 1 e Arvore 2 sao estruturalmente similares? "
         << (arvore1.estruturalmenteSimilar(arvore2) ? "Sim" : "Não") << endl;
    
    cout << "Arvore 1 e Arvore 3 sao estruturalmente similares? "
         << (arvore1.estruturalmenteSimilar(arvore3) ? "Sim" : "Não") << endl;

    // Exercício 3 - Converter para Lista Encadeada e exibir
    Node* lista = arvore1.converterParaListaEncadeada();
    cout << "\nLista Encadeada Ordenada (Arvore 1):\n";
    arvore1.exibirListaEncadeada(lista);

    // Exercício 4 - Encontrar k-ésimo menor elemento
    cout << "\n3º menor elemento da Arvore 1: " << arvore1.encontrarKthElemento(3) << "\n";

    return 0;
}


// Qual o custo do melhor caso e do pior caso ?