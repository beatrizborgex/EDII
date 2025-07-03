#include <iostream>
using namespace std;

// Classe que representa um nó de uma árvore binária de busca
class TreeNode {
private:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Retorna o nó com menor valor a partir de um nó (usado na deleção)
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

public:
    // Construtor
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

    // Destrutor recursivo
    ~TreeNode() {
        delete left;
        delete right;
    }

    // Altura da árvore a partir do nó atual
    int height() {
        int hLeft = left ? left->height() : 0;
        int hRight = right ? right->height() : 0;
        return 1 + max(hLeft, hRight);
    }

    // Retorna o fator de balanceamento (altura esquerda - altura direita)
    int getBalance() {
        int hLeft = left ? left->height() : 0;
        int hRight = right ? right->height() : 0;
        return hLeft - hRight;
    }

    // Rotação simples para a direita
    TreeNode* rotateRight() {
        TreeNode* newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        return newRoot;
    }

    // Rotação simples para a esquerda
    TreeNode* rotateLeft() {
        TreeNode* newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        return newRoot;
    }

    // Balanceamento AVL
    TreeNode* balance() {
        int bf = getBalance();

        // Caso esquerda pesada
        if (bf > 1) {
            if (left && left->getBalance() < 0)
                left = left->rotateLeft(); // caso em L
            return rotateRight();         // caso em linha
        }

        // Caso direita pesada
        if (bf < -1) {
            if (right && right->getBalance() > 0)
                right = right->rotateRight(); // caso em L
            return rotateLeft();              // caso em linha
        }

        return this; // já está balanceado
    }

    // Inserção com balanceamento
    TreeNode* insert(int value) {
        if (value < data) {
            if (!left) left = new TreeNode(value);
            else left = left->insert(value);
        } else {
            if (!right) right = new TreeNode(value);
            else right = right->insert(value);
        }

        return balance();
    }

    // Deleção com balanceamento AVL
    TreeNode* deleteNode(int key) {
        if (key < data && left)
            left = left->deleteNode(key);
        else if (key > data && right)
            right = right->deleteNode(key);
        else if (key == data) {
            // Sem filho esquerdo
            if (!left) {
                TreeNode* temp = right;
                right = nullptr;
                delete this;
                return temp;
            }

            // Sem filho direito
            if (!right) {
                TreeNode* temp = left;
                left = nullptr;
                delete this;
                return temp;
            }

            // Dois filhos: substitui pelo menor da subárvore direita
            TreeNode* temp = minValueNode(right);
            data = temp->data;
            right = right->deleteNode(temp->data);
        }

        return balance();
    }

    // Impressão em formato de árvore (visual)
    void printTree(const string& prefix = "", bool isLeft = true) {
        if (right)
            right->printTree(prefix + (isLeft ? "│   " : "    "), false);

        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << data << endl;

        if (left)
            left->printTree(prefix + (isLeft ? "    " : "│   "), true);
    }

    // Percursos básicos
    void preOrder() {
        cout << data << " ";
        if (left) left->preOrder();
        if (right) right->preOrder();
    }

    void inOrder() {
        if (left) left->inOrder();
        cout << data << " ";
        if (right) right->inOrder();
    }

    void postOrder() {
        if (left) left->postOrder();
        if (right) right->postOrder();
        cout << data << " ";
    }

    // Busca de valor
    bool search(int key) {
        if (data == key) return true;
        if (key < data && left) return left->search(key);
        if (key > data && right) return right->search(key);
        return false;
    }

    // Limpa todos os nós filhos
    void clear() {
        if (left) {
            left->clear();
            delete left;
            left = nullptr;
        }
        if (right) {
            right->clear();
            delete right;
            right = nullptr;
        }
    }

    // Mínimo e máximo
    int getMin() {
        return left ? left->getMin() : data;
    }

    int getMax() {
        return right ? right->getMax() : data;
    }

    // Contagem
    int countNodes() {
        int total = 1;
        if (left) total += left->countNodes();
        if (right) total += right->countNodes();
        return total;
    }

    int countLeaves() {
        if (!left && !right) return 1;
        int leaves = 0;
        if (left) leaves += left->countLeaves();
        if (right) leaves += right->countLeaves();
        return leaves;
    }
};

int main() {
    TreeNode* root = new TreeNode(50);

    root = root->insert(30);
    root = root->insert(20);
    root = root->insert(40);
    root = root->insert(70);
    root = root->insert(60);
    root = root->insert(80);

    cout << "Árvore AVL - Balanceada\n";
    root->printTree();

    int valueToDelete;
    cout << "Digite um valor para deletar: ";
    cin >> valueToDelete;

    root = root->deleteNode(valueToDelete);

    cout << "\nÁrvore após deletar " << valueToDelete << ":\n";
    root->printTree();

    cout << "\nMenor valor: " << root->getMin() << endl;
    cout << "Maior valor: " << root->getMax() << endl;

    cout << "Total de nós: " << root->countNodes() << endl;
    cout << "Total de folhas: " << root->countLeaves() << endl;

    return 0;
}
