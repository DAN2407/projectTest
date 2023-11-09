#include <iostream>
#include <queue>

struct TreeNode {
    char symbol;
    double probability;

    TreeNode(char symbol, double probability) : symbol(symbol), probability(probability) {}

    // Sobrecarga del operador '<' para la comparación en la cola de prioridad
    bool operator<(const TreeNode& other) const {
        return probability > other.probability; // Montículo de mínimos
    }
};

int main() {
    // Valores de probabilidad para los símbolos
    double probabilities[] = {0.83, 0.22, 0.03, 0.16, 0.41, 0.80, 0.72, 0.78, 0.73, 0.38, 0.99, 0.97, 0.73, 0.75, 0.02, 0.29, 0.99, 0.68, 0.65, 0.85, 0.87, 0.11, 0.97, 0.35, 0.22, 0.07, 0.68};

    // Alfabeto latino
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    // Crear nodos para cada símbolo del alfabeto latino junto con sus probabilidades
    std::vector<TreeNode> nodes;
    for (int i = 0; i < 27; i++) {
        nodes.push_back(TreeNode(alphabet[i], probabilities[i]));
    }

    // Crear una cola de prioridad (montículo de mínimos)
    std::priority_queue<TreeNode> minHeap;

    // Insertar los nodos en la cola de prioridad
    for (const TreeNode& node : nodes) {
        minHeap.push(node);
    }

    // Ejemplo de acceso a los nodos en orden de prioridad
    while (!minHeap.empty()) {
        TreeNode topNode = minHeap.top();
        std::cout << "Symbol: " << topNode.symbol << ", Probability: " << topNode.probability << std::endl;
        minHeap.pop();
    }

    return 0;
}