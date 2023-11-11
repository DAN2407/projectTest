#include <iostream>
#include "function.hpp"

int main() {
    char symbol[] = "abcdefghijklmnopqrstuvwxyz";    
    double probabilities[] = {0.83, 0.22, 0.03, 0.16, 0.41, 0.80, 0.72, 0.78, 0.73, 0.38, 0.99, 0.97, 0.73, 0.75, 0.02, 0.29, 0.99, 0.68, 0.65, 0.85, 0.87, 0.11, 0.97, 0.35, 0.22, 0.07, 0.68};

     // Crear nodos para cada símbolo del alfabeto latino junto con sus probabilidades
    tree *nodes[26];
    for (int i = 0; i < 26; i++) {
        nodes[i] = create_node(symbol[i], probabilities[i]);
    }

    //mostrar  nodos
    for (int i = 0; i < 26; i++) {
        std::cout << nodes[i]->symbol << " " << nodes[i]->probability << std::endl;
    }

    // Crear una cola de prioridad (montículo de mínimo)
    create_priority_queue(symbol, probabilities);


    // Insertar los nodos en la cola de prioridad
    for (int i = 0; i < 26; i++) {
        insert(root, nodes[i]);
    }

    // Mostrar la cola de prioridad, tanto symbol como probability
    show_priority_queue(root);
    




    

}
