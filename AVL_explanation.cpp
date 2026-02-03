#include<iostream>
#include<ctime>
#include<queue>
#include<vector>
#include<string>
#include<iomanip>
#include<algorithm>

struct Node {
    int data;
    int height;
    Node *left, *right;
    Node(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};

class AVL {
private:
    Node *root;
    int size = 0;

    // --- Helper Functions ---

    int getHeight(Node* n) {
        return (n == nullptr) ? -1 : n->height;
    }

    int getBalance(Node* n) {
        return (n == nullptr) ? 0 : getHeight(n->left) - getHeight(n->right);
    }

    void updateHeight(Node* n) {
        if (n != nullptr) {
            n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // ฟังก์ชัน Rebalance ตัวเดียวที่ใช้ได้ทั้ง Insert และ Delete
    Node* rebalance(Node* node) {
        if (node == nullptr) return nullptr;

        updateHeight(node);
        int balance = getBalance(node);

        // Case: Left Heavy (หนักซ้าย)
        if (balance > 1) {
            // ถ้าลูกซ้ายหนักขวา (LR Case) ต้องหมุนซ้ายลูกก่อน
            if (getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        // Case: Right Heavy (หนักขวา)
        if (balance < -1) {
            // ถ้าลูกขวาหนักซ้าย (RL Case) ต้องหมุนขวาลูกก่อน
            if (getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    // --- Recursive Functions ---

    Node* insertRecursive(Node* node, int val, bool &wasInserted) {
        if (node == nullptr) {
            wasInserted = true;
            return new Node(val);
        }

        if (val < node->data) {
            node->left = insertRecursive(node->left, val, wasInserted);
        } else if (val > node->data) {
            node->right = insertRecursive(node->right, val, wasInserted);
        } else {
            wasInserted = false; // ค่าซ้ำ ไม่ทำการเพิ่ม
            return node;
        }

        return rebalance(node);
    }

    Node* deleteRecursive(Node* node, int key) {
        if (node == nullptr) return nullptr;

        if (key < node->data) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->data) {
            node->right = deleteRecursive(node->right, key);
        } else {
            // กรณีเจอ Node ที่ต้องการลบ
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left) ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp; // คัดลอกค่าจากลูกมาใส่ตัวเอง
                }
                delete temp;
            } else {
                // กรณีมีลูก 2 คน: หาตัวน้อยสุดฝั่งขวามาแทน
                Node* temp = findMinRecursive(node->right);
                node->data = temp->data;
                node->right = deleteRecursive(node->right, temp->data);
            }
        }

        if (node == nullptr) return nullptr;
        return rebalance(node);
    }

    Node* findMinRecursive(Node* node) {
        if (node == nullptr || node->left == nullptr) return node;
        return findMinRecursive(node->left);
    }

    Node* searchRecursive(Node* node, int val) {
        if (node == nullptr || val == node->data) return node;
        if (val < node->data) return searchRecursive(node->left, val);
        else return searchRecursive(node->right, val);
    }

    void inOrderRecursive(Node* node) {
        if (node == nullptr) return;
        inOrderRecursive(node->left);
        std::cout << node->data << " ";
        inOrderRecursive(node->right);
    }

    void clearRecursive(Node* node) {
        if (node == nullptr) return;
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }

public:
    AVL() : root(nullptr) {}
    ~AVL() { clearRecursive(root); }

    void insert(int val) {
        bool wasInserted = false;
        root = insertRecursive(root, val, wasInserted);
        if (wasInserted) size++;
    }

    void remove(int val) {
        if (search(val)) {
            root = deleteRecursive(root, val);
            size--;
        }
    }

    bool search(int val) { return searchRecursive(root, val) != nullptr; }
    int getSize() { return size; }
    int height() { return getHeight(root); }
    void display() { inOrderRecursive(root); std::cout << std::endl; }

    void bfs() {
        if (root == nullptr) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front(); q.pop();
            std::cout << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    void printTreeStructure() {
        if (root == nullptr) return;
        std::queue<Node*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int nodesInLevel = q.size();
            std::cout << "Level " << level << ": ";
            for (int i = 0; i < nodesInLevel; i++) {
                Node* current = q.front(); q.pop();
                if (current != nullptr) {
                    std::cout << "[" << current->data << "] ";
                    q.push(current->left);
                    q.push(current->right);
                } else std::cout << "[_] ";
            }
            std::cout << std::endl;
            level++;
            bool more = false;
            std::queue<Node*> t = q;
            while(!t.empty()){ if(t.front()){more=true; break;} t.pop(); }
            if(!more) break;
        }
    }
};

// --- Main Menu System ---

void displayMenu(AVL& tree) {
    int choice, data;
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        std::cout << "\n=============================================================\n";
        std::cout << "                AVL Tree (Self-Balancing) Menu\n";
        std::cout << "=============================================================\n";
        std::cout << "Current In-order List:\n";
        tree.display();
        std::cout << "Tree Size : " << tree.getSize() << std::endl;
        std::cout << "Tree Height: " << tree.height() << " (Balanced!)" << std::endl;
        std::cout << "=============================================================\n";

        std::cout << "1. Insert   2. Search   3. Remove\n";
        std::cout << "4. BFS      5. Structure (Level-by-Level)\n";
        std::cout << "0. Exit\n";
        std::cout << "=============================================================\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
            case 1:
                std::cout << "Enter data to insert: ";
                std::cin >> data;
                tree.insert(data);
                break;
            case 2:
                std::cout << "Enter data to search: ";
                std::cin >> data;
                if (tree.search(data)) std::cout << ">> Found " << data << " in the tree.\n";
                else std::cout << ">> " << data << " not found.\n";
                break;
            case 3:
                std::cout << "Enter data to remove: ";
                std::cin >> data;
                tree.remove(data);
                break;
            case 4:
                std::cout << "BFS Traversal: ";
                tree.bfs();
                break;
            case 5:
                tree.printTreeStructure();
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }
}

int main() {
    AVL tree;
    int mode, n;

    std::cout << "--- AVL Tree Demonstration ---\n";
    std::cout << "1. Manual Insert\n";
    std::cout << "2. Auto Insert (Sorted Data 1 to N)\n";
    std::cout << "Select mode: ";
    std::cin >> mode;

    if (mode == 2) {
        std::cout << "Enter N: ";
        std::cin >> n;
        for (int i = 1; i <= n; i++) {
            tree.insert(i);
        }
    }

    displayMenu(tree);
    return 0;
}
