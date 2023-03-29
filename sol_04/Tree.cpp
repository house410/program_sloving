#include <iostream>

using namespace std;

// 트리 노드 클래스
class Node {
public:
    int data;  
    Node* parent;  
    Node* left;  
    Node* right;  

    Node(int data) {  
        this->data = data;  
        this->parent = NULL;  
        this->left = NULL;  
        this->right = NULL;  
    }
};

// 이진 트리 클래스
class BinaryTree {
private:
    Node* root;  // 루트 노드 포인터

    // 노드 추가 재귀함수
    void insert(Node* node, int data) {
        if (data < node->data) {  // 새로운 데이터가 현재 노드 데이터보다 작으면
            if (node->left == NULL) {  // 왼쪽 자식 노드가 없으면
                Node* newNode = new Node(data);  // 새로운 노드 생성
                newNode->parent = node;  // 새로운 노드의 부모를 현재 노드로 설정
                node->left = newNode;  // 현재 노드의 왼쪽 자식 노드로 새로운 노드를 설정
            }
            else {
                insert(node->left, data);  // 이미 왼쪽 자식 노드가 있으면 왼쪽 자식 노드에서 다시 노드 추가 함수 호출
            }
        }
        else {  // 새로운 데이터가 현재 노드 데이터보다 크거나 같으면
            if (node->right == NULL) {  // 오른쪽 자식 노드가 없으면
                Node* newNode = new Node(data);  // 새로운 노드 생성
                newNode->parent = node;  // 새로운 노드의 부모를 현재 노드로 설정
                node->right = newNode;  // 현재 노드의 오른쪽 자식 노드로 새로운 노드를 설정
            }
            else {
                insert(node->right, data);  // 이미 오른쪽 자식 노드가 있으면 오른쪽 자식 노드에서 다시 노드 추가 함수 호출
            }
        }
    }

    // 전위순회 재귀함수
    void preOrderTraversal(Node* node) {
        if (node != NULL) {  // 노드가 NULL이 아니면
            cout << node->data << " ";  // 현재 노드 데이터 출력
            preOrderTraversal(node->left);  // 왼쪽 자식 노드에서 다시 전위순회 함수 호출
            preOrderTraversal(node->right); // 오른쪽 자식 노드에서 다시 전위순회 함수 호출
        }
    }

public:
    // 이진 트리 생성자
    BinaryTree() {
        this->root = NULL;
    }

    // 트리 노드 추가 함수
    void insert(int data) {
        if (this->root == NULL) {
            this->root = new Node(data);
        }
        else {
            insert(this->root, data);
        }
    }

    // 트리 전위순회 함수
    void preOrderTraversal() {
        preOrderTraversal(this->root);
        cout << endl;
    }
};

int main() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    tree.insert(4);
    tree.insert(6);

    cout << "Pre-order Traversal: ";
    tree.preOrderTraversal();

    return 0;
}
