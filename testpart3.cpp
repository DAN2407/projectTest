#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    char symbol;
    double probability;

    TreeNode(char symbol, double probability) : parent(nullptr), left(nullptr), right(nullptr), symbol(symbol), probability(probability) {}
};

struct CompareNodes {
    bool operator()(TreeNode* lhs, TreeNode* rhs) {
        return lhs->probability > rhs->probability;
    }
};

int main() {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    double probabilities[] = {0.83, 0.22, 0.03, 0.16, 0.41, 0.80, 0.72, 0.78, 0.73, 0.38, 0.99, 0.97, 0.73, 0.75, 0.02, 0.29, 0.99, 0.68, 0.65, 0.85, 0.87, 0.11, 0.97, 0.35, 0.22, 0.07, 0.68 };

    TreeNode* nodes[26];

    for (int i = 0; i < 26; i++) {
        nodes[i] = new TreeNode(alphabet[i], probabilities[i]);
    }

    // Crear una cola de prioridad (min-heap) para ordenar los nodos por probabilidad.
    priority_queue<TreeNode*, vector<TreeNode*>, CompareNodes> pq;

    for (int i = 0; i < 26; i++) {
        pq.push(nodes[i]);
    }

    // Aplicar el algoritmo de Huffman
    while (pq.size() > 1) {
        TreeNode* left = pq.top();
        pq.pop();
        TreeNode* right = pq.top();
        pq.pop();

        TreeNode* parent = new TreeNode('\0', left->probability + right->probability);
        parent->left = left;
        parent->right = right;
        left->parent = parent;
        right->parent = parent;

        pq.push(parent);
    }

    // El último nodo en la cola de prioridad es la raíz del árbol de Huffman
    TreeNode* huffmanTreeRoot = pq.top();

    // Limpieza de memoria (liberar los nodos que ya no son necesarios)
    for (int i = 0; i < 26; i++) {
        delete nodes[i];
    }

    //mostar el algoritmo de huffman
    cout << "Huffman tree:" << endl;
    cout << "Root: " << huffmanTreeRoot->probability << endl;
    cout << "Left: " << huffmanTreeRoot->left->probability << endl;
    cout << "Right: " << huffmanTreeRoot->right->probability << endl;
    cout << "Left-Left: " << huffmanTreeRoot->left->left->probability << endl;
    cout << "Left-Right: " << huffmanTreeRoot->left->right->probability << endl;
    cout << "Right-Left: " << huffmanTreeRoot->right->left->probability << endl;
    cout << "Right-Right: " << huffmanTreeRoot->right->right->probability << endl;

    


    return 0;
}
