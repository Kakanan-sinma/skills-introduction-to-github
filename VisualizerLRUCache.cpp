#include <iostream>
#include <iomanip>
#include <string>

// --- ฟังก์ชันจัดการสีสำหรับ UI ---
void reset() { std::cout << "\033[0m"; }
void red() { std::cout << "\033[31m"; }
void green() { std::cout << "\033[32m"; }
void yellow() { std::cout << "\033[33m"; }
void blue() { std::cout << "\033[34m"; }
void cyan() { std::cout << "\033[36m"; }
void magenta() { std::cout << "\033[35m"; }

// --- โครงสร้างข้อมูลพื้นฐาน ---
struct Part {
    int id;
    std::string name;
    float price;
    Part(int i, std::string n, float p) : id(i), name(n), price(p) {}
    Part() : id(0), name(""), price(0.0) {}
};

struct Node {
    Part data;
    Node *next, *prev;
    Node(const Part& p) : data(p), next(nullptr), prev(nullptr) {}
};

// --- ส่วนจัดการลำดับข้อมูล (Doubly Linked List) ---
class DoublyLinkedList {
private:
    Node *head, *tail;
    int size;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() { clear(); }

    Node* getHead() { return head; }
    int getSize() { return size; }

    Node* pushFront(const Part& p) {
        Node* newNode = new Node(p);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
        return head;
    }

    void moveToHead(Node* node) {
        if (!node || node == head) return;
        if (node == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;
    }

    int popTail() {
        if (!tail) return -1;
        Node* temp = tail;
        int idTail = tail->data.id;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
        return idTail;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    void displayAll() {
        Node* current = head;
        while (current) {
            std::cout << "[ID:" << current->data.id << "|" << current->data.name << "]";
            if (current->next) {
                yellow(); std::cout << " <-> "; reset();
            }
            current = current->next;
        }
    }
};

// --- ส่วนช่วยค้นหา (Hash Table) ---
class HashTable {
private:
    struct HashEntry {
        int key;
        Node* mainListNode;
        HashEntry* next;
        HashEntry(int k, Node* n) : key(k), mainListNode(n), next(nullptr) {}
    };
    static const int TABLE_SIZE = 10;
    HashEntry* table[TABLE_SIZE];
    int hashFunction(int key) { return key % TABLE_SIZE; }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashEntry* current = table[i];
            while (current) {
                HashEntry* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
    }

    void insert(int key, Node* nodePtr) {
        int index = hashFunction(key);
        HashEntry* newEntry = new HashEntry(key, nodePtr);
        newEntry->next = table[index];
        table[index] = newEntry;
    }

    Node* search(int key) {
        int index = hashFunction(key);
        HashEntry* current = table[index];
        while (current) {
            if (current->key == key) return current->mainListNode;
            current = current->next;
        }
        return nullptr;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        HashEntry* current = table[index];
        HashEntry* prev = nullptr;
        while (current) {
            if (current->key == key) {
                if (!prev) table[index] = current->next;
                else prev->next = current->next;
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
};

// --- ระบบ LRU Cache ---
class LRUCache {
private:
    int capacity;
    DoublyLinkedList list;
    HashTable table;
public:
    LRUCache(int cap) : capacity(cap) {}

    void getPart(int id) {
        Node* node = table.search(id);
        if (!node) {
            red(); std::cout << "\nResult: Part ID " << id << " NOT FOUND in Cache!\n"; reset();
            return;
        }
        list.moveToHead(node);
        green(); std::cout << "\nResult: Found '" << node->data.name << "' (Updated to MRU)\n"; reset();
    }

    void putPart(int id, std::string name, float price) {
        Node* existingNode = table.search(id);
        if (existingNode) {
            existingNode->data.name = name;
            existingNode->data.price = price;
            list.moveToHead(existingNode);
            green(); std::cout << "\nResult: Updated existing Part ID " << id << "\n"; reset();
        } else {
            if (list.getSize() >= capacity) {
                int removedId = list.popTail();
                table.remove(removedId);
                magenta(); std::cout << "\n[Eviction] Cache Full! Removed ID: " << removedId << " (Least Recently Used)\n"; reset();
            }
            Part newPart(id, name, price);
            Node* newNode = list.pushFront(newPart);
            table.insert(id, newNode);
            green(); std::cout << "\nResult: Inserted new Part ID " << id << "\n"; reset();
        }
    }

    void displayUI() {
        yellow();
        std::cout << "\n[ CACHE STATUS ] Capacity: " << capacity << " | Used: " << list.getSize() << "\n";
        reset();
        blue(); std::cout << "  (Newest/MRU) "; reset();
        list.displayAll();
        blue(); std::cout << " (Oldest/LRU)\n"; reset();
        std::cout << "-----------------------------------------------------------------\n";
    }
};

// --- เมนูหลัก ---
void menu(LRUCache& cache) {
    int choice, id;
    std::string name;
    float price;

    while (true) {
        system("clear"); // เปิดใช้สำหรับ Linux
        std::cout << "\n\n";
        magenta();
        std::cout << "=================================================================\n";
        std::cout << "               LRU CACHE SYSTEM VISUALIZER                       \n";
        std::cout << "=================================================================\n";
        reset();

        cache.displayUI();

        std::cout << " 1. Put Part (Add/Update) \n";
        std::cout << " 2. Get Part (Search/Access)\n";
        std::cout << " 0. Exit Program\n";
        std::cout << "-----------------------------------------------------------------\n";
        std::cout << "Select Option: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 0) break;

        if (choice == 1) {
            std::cout << "Enter ID: "; std::cin >> id;
            std::cout << "Enter Name: "; std::cin >> name;
            std::cout << "Enter Price: "; std::cin >> price;
            cache.putPart(id, name, price);
        } else if (choice == 2) {
            std::cout << "Enter ID to Access: "; std::cin >> id;
            cache.getPart(id);
        }
    }
}

int main() {
    int cap;
    std::cout << "Set Cache Capacity: ";
    std::cin >> cap;
    
    LRUCache myCache(cap > 0 ? cap : 3);
    menu(myCache);
    
    return 0;
}
