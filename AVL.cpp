#include<iostream>
#include<ctime>
#include<queue>
#include<vector>
#include<string>
#include<iomanip>

struct Node {
    int data;
    int height; // AVL ต้องเก็บความสูง
    Node *left, *right;
    Node(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};

class AVL { // เปลี่ยนชื่อจาก BST เป็น AVL
private:
    Node *root;
    int size = 0;

    // --- Helper Functions สำหรับ AVL ---

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

    // หมุนขวา (ใช้เมื่อซ้ายหนักเกิน)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // หมุนซ้าย (ใช้เมื่อขวาหนักเกิน)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // ฟังก์ชันปรับสมดุล (Rebalance)
    Node* rebalance(Node* node, int val) {
        int balance = getBalance(node);

        // Case 1: Left Left (หมุนขวาครั้งเดียว)
        if (balance > 1 && val < node->left->data)
            return rightRotate(node);

        // Case 2: Right Right (หมุนซ้ายครั้งเดียว)
        if (balance < -1 && val > node->right->data)
            return leftRotate(node);

        // Case 3: Left Right (หมุนซ้ายลูกก่อน แล้วค่อยหมุนขวาตัวเอง)
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Case 4: Right Left (หมุนขวาลูกก่อน แล้วค่อยหมุนซ้ายตัวเอง)
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // --- ฟังก์ชันหลักที่ปรับปรุงจาก BST ---

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
            wasInserted = false;
            return node;
        }

        updateHeight(node); // อัปเดตความสูงขณะย้อนกลับ
        return rebalance(node, val); // เช็คและหมุนโหนดถ้าจำเป็น
    }

    // (ส่วนฟังก์ชัน Search, findMin, InOrder ใช้ของเดิมได้เลย)
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

    Node* deleteRecursive(Node* node, int key) {
        if (node == nullptr) return nullptr;

        if (key < node->data) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->data) {
            node->right = deleteRecursive(node->right, key);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left) ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMinRecursive(node->right);
                node->data = temp->data;
                node->right = deleteRecursive(node->right, temp->data);
            }
        }

        if (node == nullptr) return node;

        updateHeight(node);
        // สำหรับ Delete การเช็ค balance จะใช้ getBalance ของลูกแทน val
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* findMinRecursive(Node* node) {
        if (node == nullptr || node->left == nullptr) return node;
        return findMinRecursive(node->left);
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

    // BFS & Structure (ใช้ของเดิมได้เลย)
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

void displayMenu(AVL& tree) {
    int choice, data;
    while (true) {
        // ใช้คำสั่ง clear หน้าจอ (สำหรับ Windows ใช้ cls, สำหรับ Linux/macOS ใช้ clear)
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
    int mode, n, val;

    std::cout << "--- AVL Tree Demonstration ---\n";
    std::cout << "1. Manual Insert\n";
    std::cout << "2. Auto Insert (Sorted Data 1 to N) - To see balancing in action\n";
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
