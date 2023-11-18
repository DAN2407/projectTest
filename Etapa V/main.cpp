#include "function.hpp"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <iomanip>
using namespace std;

// Estructura para comparar nodos basándose en sus probabilidades
struct CompareNodes {
    bool operator()(TreeNode* left, TreeNode* right) {
        return left->probability > right->probability;
    }
};

// Función para construir el árbol de Huffman y devolver la raíz
TreeNode* buildHuffmanTree(const char* symbols, const double* probabilities, int numSymbols) {
    // Crear nodos hoja y agregarlos a la cola de prioridad (min heap)
    priority_queue<TreeNode*, vector<TreeNode*>, CompareNodes> minHeap;
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
void assignHuffmanCodes(TreeNode* root, unordered_map<char, string>& huffmanCodes, string currentCode = "") {
    if (root) {
        if (root->symbol != '\0') {
            huffmanCodes[root->symbol] = currentCode;
        }
        assignHuffmanCodes(root->left, huffmanCodes, currentCode + "0");
        assignHuffmanCodes(root->right, huffmanCodes, currentCode + "1");
    }
}

void displayHuffmanTree(TreeNode* root, int indent = 0) {
    if (root) {
        if (root->right) {
            displayHuffmanTree(root->right, indent + 4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (root->right) cout << " /\n" << setw(indent) << ' ';
        cout << root->symbol << "\n ";
        if (root->left) {
            cout << setw(indent) << ' ' << " \\\n";
            displayHuffmanTree(root->left, indent + 4);
        }
    }
}


// Function to encrypt text using a substitution alphabet
string encryptText(const string& text, const unordered_map<char, char>& substitutionAlphabet) {
    string encryptedText;
    for (char ch : text) {
        if (substitutionAlphabet.find(ch) != substitutionAlphabet.end()) {
            encryptedText += substitutionAlphabet.at(ch);
        } else {
            encryptedText += ch;
        }
    }
    return encryptedText;
}

// Function to display the menu and get user's choice
int displayMenu() {
    int choice;
    cout << "\n----- Menu -----\n";
    cout << "1. Enter text to modify\n";
    cout << "2. Consult stored text to modify\n";
    cout << "3. Apply Huffman Algorithm\n";
    cout << "4. Consult stored modified text\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    // Assigned alphabet (substitution key)1
    unordered_map<char, char> substitutionAlphabet = {
        {'m', '0'}, {'u', '1'}, {'r', '2'}, {'c', '3'}, {'i', '4'},
        {'e', '5'}, {'l', '6'}, {'a', '7'}, {'g', '8'}, {'o', '9'},
    };

    string originalText;
    string modifiedText;

    while (true) {
        int choice = displayMenu();

        switch (choice) {
            case 1:
                cout << "Enter text to modify: ";
                cin.ignore(); // Clear input buffer
                getline(cin, originalText);
                modifiedText = encryptText(originalText, substitutionAlphabet);
                cout << "Text modified successfully.\n";
                break;

            case 2:
                if (originalText.empty()) {
                    cout << "No text stored to modify.\n";
                } else {
                    cout << "Stored text to modify: " << originalText << "\n";
                }
                break;

            case 3:
                if (originalText.empty()) {
                    cout << "No text stored to apply Huffman Algorithm.\n";
                } else {
                    // Build Huffman Tree
                    TreeNode* huffmanRoot = buildHuffmanTree(originalText.c_str(), nullptr, originalText.length());

                    // Display Huffman Tree
                    cout << "\n----- Huffman Tree -----\n";
                    displayHuffmanTree(huffmanRoot);

                    // Clean up allocated memory
                    delete huffmanRoot;

                    cout << "Huffman Algorithm applied successfully.\n";
                }
                break;

            case 4:
                if (modifiedText.empty()) {
                    cout << "No modified text stored.\n";
                } else {
                    cout << "Stored modified text: " << modifiedText << "\n";
                }
                break;

            case 5:
                cout << "Exiting the program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
