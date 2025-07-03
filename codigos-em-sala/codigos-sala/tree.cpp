// Pesquisar diferença de um construtor e uma classe orientada a objeto
#include <iostream>

class TreeNode {
    private:
    int data;
    TreeNode* left;
    TreeNode* right;

    public: 
        // construtor
        TreeNode(int val) : data(val), left(nullptr), right(nullptr){}

        // Métodos de acesso
        int getData() const { return data; }
        TreeNode* getLeft() const { return left; }
        TreeNode* getRight() const { return right; }

        void setLeft(TreeNode* node) {left = node;}
        void setRight(TreeNode* node) {right = node;}

        ~TreeNode() {}
        
};

class BinaryTree{
    private:
        TreeNode* root;

        TreeNode* insert (TreeNode* node, int val){
            if(node == nullptr) {
                return new TreeNode(val);
            }
            if(val < node->getData()){
                node-> setLeft(insert(node->getLeft(), val));
            } else if (val > node->getData()){
                node->setRight(insert(node->getRight(), val));
            }
            return node;
        }
        void deleteTree(TreeNode*){}

    public:
    BinaryTree(): root(nullptr) {}

    ~BinaryTree(){
        deleteTree(root);

    }

    void insertVal(int val){
        root = insert(root, val);
    }
};


int main(){
    BinaryTree tree;

    tree.insertVal(5);
    tree.insertVal(10);
    tree.insertVal(8);
}

/*
Pesquisar sobre SmartPointers (ponteiros inteligentes)
*/
