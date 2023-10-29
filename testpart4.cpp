#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    // Estructura de nodo para el Algoritmo de Huffman
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    char symbol;
    double probability;

    TreeNode(char symbol, double probability) : left(nullptr), right(nullptr), symbol(symbol), probability(probability) {}
};

struct CompareNodes {
    bool operator()(const TreeNode* a, const TreeNode* b) const {
        // Comparar los nodos basados en sus probabilidades (frecuencias)
        return a->probability > b->probability;
    }
};

// Función para cifrar un texto mediante un cifrado de sustitución
string cifrarTexto(string texto, string alfabeto, string alfabetoSustitucion) {
    // Implementa el cifrado de sustitución
    string textoCifrado = texto;
    for (int i = 0; i < textoCifrado.length(); i++) {
        char c = textoCifrado[i];
        size_t pos = alfabeto.find(c);
        if (pos != string::npos) {
            textoCifrado[i] = alfabetoSustitucion[pos];
        }
    }
    return textoCifrado;
}

string consultarTextoModificado(TreeNode* raizHuffman, string textoCifrado) {
    if (raizHuffman == nullptr) {
        cout << "No se ha aplicado el Algoritmo de Huffman." << endl;
        return "";
    }

    string textoDecodificado = "";
    TreeNode* nodoActual = raizHuffman;

    for (char c : textoCifrado) {
        if (c == '0') {
            nodoActual = nodoActual->left;
        } else if (c == '1') {
            nodoActual = nodoActual->right;
        }

        if (nodoActual->left == nullptr && nodoActual->right == nullptr) {
            textoDecodificado += nodoActual->symbol;
            nodoActual = raizHuffman;
        }
    }

    cout << "Texto modificado almacenado: " << textoDecodificado << endl;
    return textoDecodificado;
}

// Función para aplicar el Algoritmo de Huffman a un texto
TreeNode* construirArbolHuffman(string texto, string alfabeto) {
    // Implementa el Algoritmo de Huffman
    double frecuencias[26] = {0};
    for (char c : texto) {
        size_t pos = alfabeto.find(c);
        if (pos != string::npos) {
            frecuencias[pos]++;
        }
    }

    priority_queue<TreeNode*, vector<TreeNode*>, CompareNodes> pq;
    for (int i = 0; i < 26; i++) {
        if (frecuencias[i] > 0) {
            pq.push(new TreeNode(alfabeto[i], frecuencias[i]));
        }
    }

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

    return pq.top();
}

int main() {
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    string alfabetoSustitucion = "xyzabcdefghijklmnopqrstuvw";  // Ejemplo de cifrado de sustitución

    string textoOriginal;
    string textoCifrado;
    TreeNode* raizHuffman = nullptr;

    while (true) {
        cout << "Opciones:\n";
        cout << "1. Ingresar texto a modificar.\n";
        cout << "2. Consultar texto a modificar almacenado.\n";
        cout << "3. Aplicar Algoritmo de Huffman.\n";
        cout << "4. Consultar texto modificado almacenado.\n";
        cout << "5. Salir del programa.\n";

        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el texto a modificar: ";
                cin.ignore();
                getline(cin, textoOriginal);
                // Cifrar el texto original
                textoCifrado = cifrarTexto(textoOriginal, alfabeto, alfabetoSustitucion);
                break;

            case 2:
                if (!textoOriginal.empty()) {
                    cout << "Texto a modificar almacenado: " << textoOriginal << endl;
                } else {
                    cout << "No hay texto almacenado." << endl;
                }
                break;

            case 3:
                if (!textoCifrado.empty()) {
                    raizHuffman = construirArbolHuffman(textoCifrado, alfabeto);
                    cout << "Algoritmo de Huffman aplicado y arbol construido." << endl;
                } else {
                    cout << "No hay texto cifrado almacenado." << endl;
                }
                break;

            case 4:
                // Implementa la función para consultar el texto modificado almacenado.
                consultarTextoModificado(raizHuffman, textoCifrado);

            case 5:
                // Limpieza de memoria (liberar nodos del árbol de Huffman si es necesario).
                return 0;

            default:
                cout << "Opción no válida. Por favor, elija una opción válida." << endl;
        }
    }

    return 0;
}
