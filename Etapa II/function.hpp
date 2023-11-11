#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>

enum order {IN,PRE,POST};

typedef struct node {
    char symbol;
    double probability;
    struct node *left;
    struct node *right;
    struct node *parent;

} tree;

tree* root = NULL;

bool is_empty(tree *T) {
    return T == NULL;
}

tree *create_node(char symbol, double probability) {
    tree *new_node = new tree;
    new_node->symbol = symbol;
    new_node->probability = probability;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

void insert_aux(tree* T, tree* new_node) {
    if (T->probability > new_node->probability) {
        if (T->left == NULL) {
            T->left = new_node;
        } else {
            insert_aux(T->left, new_node);
        }
    } else {
        if (T->right == NULL) {
            T->right = new_node;
        } else {
            insert_aux(T->right, new_node);
        }
    }
}

void insert (tree* T, tree* new_node) {
    if (is_empty(T)) {
        root = new_node;
    } else {
        insert_aux(T, new_node);
    }
}

void show_pre_order(tree *T) {
    if (!is_empty(T)) {
        std::cout << T->symbol << " ";
        show_pre_order(T->left);
        show_pre_order(T->right);
    }
}

void show_in_order(tree *T) {
    if (!is_empty(T)) {
        show_in_order(T->left);
        std::cout << T->symbol << " ";
        show_in_order(T->right);
    }
}

void show_post_order(tree *T) {
    if (!is_empty(T)) {
        show_post_order(T->left);
        show_post_order(T->right);
        std::cout << T->symbol << " ";
    }
}

void priority_queue (tree* T, order o){
    if(o == IN){
        show_in_order(T);
    }else if(o == PRE){
        show_pre_order(T);
    }else if(o == POST){
        show_post_order(T);
    }
}

void show_priority_queue(tree* T){
    priority_queue(T, PRE);
    std::cout << std::endl;
}
//crear priority queue (montículo de mínimo)
void create_priority_queue(char symbol[], double probabilities[]) {
    // Crear nodos para cada símbolo del alfabeto latino junto con sus probabilidades
    tree *nodes[26];
    for (int i = 0; i < 26; i++) {
        nodes[i] = create_node(symbol[i], probabilities[i]);
    }

    // Insertar los nodos en la cola de prioridad
    for (int i = 0; i < 26; i++) {
        insert(root, nodes[i]);
    }
}

//crear Min Heap
void min_heapify(tree* T){
    if(!is_empty(T)){
        if(T->left != NULL){
            if(T->probability > T->left->probability){
                tree* aux = T->left;
                T->left = T;
                T = aux;
            }
        }
        if(T->right != NULL){
            if(T->probability > T->right->probability){
                tree* aux = T->right;
                T->right = T;
                T = aux;
            }
        }
        min_heapify(T->left);
        min_heapify(T->right);
    }
}

void create_min_heap(char symbol[], double probabilities[]){
    // Crear nodos para cada símbolo del alfabeto latino junto con sus probabilidades
    tree *nodes[26];
    for (int i = 0; i < 26; i++) {
        nodes[i] = create_node(symbol[i], probabilities[i]);
    }

    // Insertar los nodos en la cola de prioridad
    for (int i = 0; i < 26; i++) {
        insert(root, nodes[i]);
    }
    min_heapify(root);
}



//MIN Heapisize
//creando swap

#endif 