#include <iostream>
using namespace std;

struct TreeNode {
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    char symbol;
    double probability;

    TreeNode(char symbol, double probability) : parent(nullptr), left(nullptr), right(nullptr), symbol(symbol), probability(probability) {}
};

int main() {
    // Alfabeto latino
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    // Probabilidades asociadas a cada símbolo (ejemplo)
    double probabilities[] = {0.83, 0.22, 0.03, 0.16, 0.41, 0.80, 0.72, 0.78, 0.73, 0.38, 0.99, 0.97, 0.73, 0.75, 0.02, 0.29, 0.99, 0.68, 0.65, 0.85, 0.87, 0.11, 0.97, 0.35, 0.22, 0.07 };

    // Crear nodos para cada símbolo del alfabeto latino
    TreeNode* nodes[26];
    for (int i = 0; i < 26; i++) {
        nodes[i] = new TreeNode(alphabet[i], probabilities[i]);
    }

    // Ejemplo de acceso a los atributos de un nodo
    for (int i = 0; i < 26; i++) {
        std::cout << "Symbol: " << nodes[i]->symbol << ", Probability: " << nodes[i]->probability << std::endl;
    }

    // Limpieza de memoria (recuerda liberar la memoria cuando no se necesiten los nodos)
    for (int i = 0; i < 26; i++) {
        delete nodes[i];
    }

    //priority queue
    


    return 0;
}
