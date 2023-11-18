#include "function.hpp"
#include <iostream>

int main() {
    char symbols[] = "abcdefghijklmnopqrstuvwxyz";
    double probabilities[] = {0.83, 0.22, 0.03, 0.16, 0.41, 0.80, 0.72, 0.78, 0.73, 0.38,
                               0.99, 0.97, 0.73, 0.75, 0.02, 0.29, 0.99, 0.68, 0.65, 0.85,
                               0.87, 0.11, 0.97, 0.35, 0.22, 0.07, 0.68};

    // Create TreeNode instances based on the symbols and probabilities
    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);

    MinHeap minHeap(numSymbols);

    for (int i = 0; i < numSymbols; ++i) {
        TreeNode* newNode = new TreeNode(symbols[i], probabilities[i]);
        minHeap.insert(newNode);
    }

    // print the symbols and probabilities
    std::cout << "Symbols and probabilities:" << std::endl;
    for (int i = 0; i < numSymbols; ++i) {
        std::cout << minHeap.extractMin()->symbol << " ";
        std::cout << minHeap.extractMin()->probability << " ";
    }
    std::cout << std::endl;

    //
    

    return 0;
}