#include "function.hpp"
#include <iostream>
#include <unordered_map>
#include <queue>

// Estructura para comparar nodos basándose en sus probabilidades
struct CompareNodes {
    bool operator()(TreeNode* left, TreeNode* right) {
        return left->probability > right->probability;
    }
};

// Función para construir el árbol de Huffman y devolver la raíz
TreeNode* buildHuffmanTree(const char* symbols, const double* probabilities, int numSymbols) {
    // Crear nodos hoja y agregarlos a la cola de prioridad (min heap)
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, CompareNodes> minHeap;
    for (int i = 0; i < numSymbols; ++i) {
        TreeNode* newNode = new TreeNode(symbols[i], probabilities[i]);
        minHeap.push(newNode);
    }

    // Construir el árbol de Huffman
    while (minHeap.size() > 1) {
        TreeNode* left = minHeap.top();
        minHeap.pop();

        TreeNode* right = minHeap.top();
        minHeap.pop();

        double combinedProbability = left->probability + right->probability;
        TreeNode* internalNode = new TreeNode('\0', combinedProbability);

        internalNode->left = left;
        left->parent = internalNode;

        internalNode->right = right;
        right->parent = internalNode;

        minHeap.push(internalNode);
    }

    // La raíz del árbol de Huffman es el último elemento en la cola de prioridad
    return minHeap.top();
}

// Función para asignar códigos binarios a los símbolos basándose en el árbol de Huffman
void assignHuffmanCodes(TreeNode* root, std::unordered_map<char, std::string>& huffmanCodes, std::string currentCode = "") {
    if (root) {
        if (root->symbol != '\0') {
            huffmanCodes[root->symbol] = currentCode;
        }
        assignHuffmanCodes(root->left, huffmanCodes, currentCode + "0");
        assignHuffmanCodes(root->right, huffmanCodes, currentCode + "1");
    }
}

int main() {
    char symbols[] = "abcdefghijklmnopqrstuvwxyz";
    double probabilities[] = {0.83, 0.22, 0.03, 0.16, 0.41, 0.80, 0.72, 0.78, 0.73, 0.38,
                               0.99, 0.97, 0.73, 0.75, 0.02, 0.29, 0.99, 0.68, 0.65, 0.85,
                               0.87, 0.11, 0.97, 0.35, 0.22, 0.07, 0.68};

    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);

    // Construir el árbol de Huffman
    TreeNode* huffmanRoot = buildHuffmanTree(symbols, probabilities, numSymbols);

    // Asignar códigos de Huffman a los símbolos
    std::unordered_map<char, std::string> huffmanCodes;
    assignHuffmanCodes(huffmanRoot, huffmanCodes);

    // Mostrar los códigos de Huffman asignados a cada símbolo
    std::cout << "Codigos de Huffman:\n";
    for (const auto& pair : huffmanCodes) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    // Limpiar la memoria
    // Asegúrate de tener una función adecuada en tu clase TreeNode para eliminar el árbol
    delete huffmanRoot;

    return 0;
}
