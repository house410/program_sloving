#include <iostream>

using namespace std;

// Ʈ�� ��� Ŭ����
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

// ���� Ʈ�� Ŭ����
class BinaryTree {
private:
    Node* root;  // ��Ʈ ��� ������

    // ��� �߰� ����Լ�
    void insert(Node* node, int data) {
        if (data < node->data) {  // ���ο� �����Ͱ� ���� ��� �����ͺ��� ������
            if (node->left == NULL) {  // ���� �ڽ� ��尡 ������
                Node* newNode = new Node(data);  // ���ο� ��� ����
                newNode->parent = node;  // ���ο� ����� �θ� ���� ���� ����
                node->left = newNode;  // ���� ����� ���� �ڽ� ���� ���ο� ��带 ����
            }
            else {
                insert(node->left, data);  // �̹� ���� �ڽ� ��尡 ������ ���� �ڽ� ��忡�� �ٽ� ��� �߰� �Լ� ȣ��
            }
        }
        else {  // ���ο� �����Ͱ� ���� ��� �����ͺ��� ũ�ų� ������
            if (node->right == NULL) {  // ������ �ڽ� ��尡 ������
                Node* newNode = new Node(data);  // ���ο� ��� ����
                newNode->parent = node;  // ���ο� ����� �θ� ���� ���� ����
                node->right = newNode;  // ���� ����� ������ �ڽ� ���� ���ο� ��带 ����
            }
            else {
                insert(node->right, data);  // �̹� ������ �ڽ� ��尡 ������ ������ �ڽ� ��忡�� �ٽ� ��� �߰� �Լ� ȣ��
            }
        }
    }

    // ������ȸ ����Լ�
    void preOrderTraversal(Node* node) {
        if (node != NULL) {  // ��尡 NULL�� �ƴϸ�
            cout << node->data << " ";  // ���� ��� ������ ���
            preOrderTraversal(node->left);  // ���� �ڽ� ��忡�� �ٽ� ������ȸ �Լ� ȣ��
            preOrderTraversal(node->right); // ������ �ڽ� ��忡�� �ٽ� ������ȸ �Լ� ȣ��
        }
    }

public:
    // ���� Ʈ�� ������
    BinaryTree() {
        this->root = NULL;
    }

    // Ʈ�� ��� �߰� �Լ�
    void insert(int data) {
        if (this->root == NULL) {
            this->root = new Node(data);
        }
        else {
            insert(this->root, data);
        }
    }

    // Ʈ�� ������ȸ �Լ�
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
