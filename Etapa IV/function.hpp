#include <iostream>
// Binary Tree Node
struct TreeNode {
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    char symbol;
    double probability;

    TreeNode(char symbol, double probability);
};

// Priority Queue Node
struct PriorityQueueNode {
    TreeNode* treeNode;

    PriorityQueueNode(TreeNode* treeNode);
};

// Minimum Heap (Priority Queue)
class MinHeap {
private:
    PriorityQueueNode** heapArray;
    int capacity;
    int size;

    void heapify(int index);

public:
    MinHeap(int capacity);
    ~MinHeap();

    void insert(TreeNode* treeNode);
    TreeNode* extractMin();
    bool isEmpty();
};
// Implementation of TreeNode
TreeNode::TreeNode(char symbol, double probability)
    : parent(nullptr), left(nullptr), right(nullptr), symbol(symbol), probability(probability) {}

// Implementation of PriorityQueueNode
PriorityQueueNode::PriorityQueueNode(TreeNode* treeNode) : treeNode(treeNode) {}

// Implementation of MinHeap
MinHeap::MinHeap(int capacity) : capacity(capacity), size(0) {
    heapArray = new PriorityQueueNode*[capacity];
}

MinHeap::~MinHeap() {
    delete[] heapArray;
}

void MinHeap::heapify(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heapArray[left]->treeNode->probability < heapArray[smallest]->treeNode->probability)
        smallest = left;

    if (right < size && heapArray[right]->treeNode->probability < heapArray[smallest]->treeNode->probability)
        smallest = right;

    if (smallest != index) {
        std::swap(heapArray[index], heapArray[smallest]);
        heapify(smallest);
    }
}

void MinHeap::insert(TreeNode* treeNode) {
    if (size == capacity) {
        std::cerr << "Heap is full. Cannot insert more elements.\n";
        return;
    }

    PriorityQueueNode* newNode = new PriorityQueueNode(treeNode);
    heapArray[size] = newNode;

    int currentIndex = size;
    int parentIndex = (currentIndex - 1) / 2;

    while (currentIndex > 0 && heapArray[currentIndex]->treeNode->probability < heapArray[parentIndex]->treeNode->probability) {
        std::swap(heapArray[currentIndex], heapArray[parentIndex]);
        currentIndex = parentIndex;
        parentIndex = (currentIndex - 1) / 2;
    }

    size++;
}

TreeNode* MinHeap::extractMin() {
    if (isEmpty()) {
        std::cerr << "Heap is empty. Cannot extract minimum element.\n";
        return nullptr;
    }

    TreeNode* minNode = heapArray[0]->treeNode;
    heapArray[0] = heapArray[size - 1];
    size--;

    heapify(0);

    return minNode;
}

bool MinHeap::isEmpty() {
    return size == 0;
}