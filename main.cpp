#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

struct Node {
    string data;
    int width;
    int deep = -1;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* createNode(string data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->width = data.length();
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


int calculateWidth(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftWidth = calculateWidth(root->left);
    int rightWidth = calculateWidth(root->right);

    root->width = root->width + leftWidth + rightWidth;

    return root->width;
}

void getArray(vector<Node*> *array, Node* root) {
    if (root != nullptr) {
        array->push_back(root);

        getArray(array, root->left);
        getArray(array, root->right);
    }
}

void printTree(Node* head) {
    int* maxDeep;

    std::function<void(Node*, int)> getDeep;
    getDeep = [maxDeep, &getDeep](Node* tree, int cur) {
        if (tree == nullptr)
            return 0;

        if (*maxDeep < cur)
            *maxDeep = cur;

        tree->deep = cur;
        getDeep(tree->left, cur + 1);
        getDeep(tree->right, cur + 1);
    };

    getDeep(head, 0);

    std::function<void(Node*, std::vector<std::vector<int>>&, int, int)> fillMatrix;
    fillMatrix = [&fillMatrix](Node* cur, std::vector<std::vector<int>>& matrix, int pos, int add) {
        if (cur == nullptr)
            return;

        matrix[cur->deep][pos] = cur->width;
        int newAdd = add / 2;

        fillMatrix(cur->left, matrix, pos - add + newAdd, newAdd);
        fillMatrix(cur->right, matrix, pos + add - newAdd, newAdd);
    };

    int maxLength = (int)std::pow(2, *maxDeep + 1) - 1;
    std::vector<std::vector<int>> matrix(*maxDeep + 1, std::vector<int>(maxLength, 0));

    fillMatrix(head, matrix, maxLength / 2, maxLength / 2);

    for (int row = 0; row < *maxDeep + 1; row++) {
        for (int col = 0; col < maxLength; col++) {
            int value = matrix[row][col];

            if (value == 0)
                std::cout << ' ';
            else
                std::cout << value;
        }
        std::cout << '\n';
    }
}

int main() {
    Node* root = createNode("Test");
    root->left = createNode("Wd");
    root->right = createNode("Flex");
    root->left->left = createNode("Chi");

    calculateWidth(root);

    printTree(root);

    return 0;
}
