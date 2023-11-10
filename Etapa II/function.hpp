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

//MIN Heapisize
//creando swap
void swap(tree* T, tree* smallest){
    tree* aux = new tree;
    aux->symbol = T->symbol;
    aux->probability = T->probability;
    aux->left = T->left;
    aux->right = T->right;
    aux->parent = T->parent;

    T->symbol = smallest->symbol;
    T->probability = smallest->probability;
    T->left = smallest->left;
    T->right = smallest->right;
    T->parent = smallest->parent;

    smallest->symbol = aux->symbol;
    smallest->probability = aux->probability;
    smallest->left = aux->left;
    smallest->right = aux->right;
    smallest->parent = aux->parent;
}

void MinHeapify(tree* T){
    tree* smallest = T;
    if(T->left != NULL && T->left->probability < smallest->probability){
        smallest->probability = T->left->probability;
    }
    if(T->right != NULL && T->right->probability < smallest->probability){
        smallest->probability = T->right->probability;
    }
    if(smallest != T){
        swap(T, smallest);
        MinHeapify(smallest);
    }
}

void allMinHeapify(tree* T){
    if(T->left != NULL){
        allMinHeapify(T->left);
    }
    if(T->right != NULL){
        allMinHeapify(T->right);
    }
    MinHeapify(T);
}

void insertPriorityQueue(tree* T, tree* new_node){
    if(is_empty(T)){
        root = new_node;
    }else{
        insert(T, new_node);
        allMinHeapify(root);
    }
}

void showPriorityQueue(tree* T){
    if(!is_empty(T)){
        std::cout << T->symbol << " " << T->probability << std::endl;
        showPriorityQueue(T->left);
        showPriorityQueue(T->right);
    }
}


#endif 