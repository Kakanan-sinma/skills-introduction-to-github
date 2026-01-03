#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

// --- สีสำหรับ UI (Linux/macOS Terminal) ---
void reset() { std::cout << "\033[0m"; }
void green() { std::cout << "\033[1;32m"; }
void red()   { std::cout << "\033[1;31m"; }
void blue()  { std::cout << "\033[1;34m"; }
void yellow(){ std::cout << "\033[1;33m"; }
void cyan()  { std::cout << "\033[1;36m"; }

// 1. Data Structure
struct Student {
    int id;
    std::string name;
    float gpa;
    Student(int i, std::string n, float g) : id(i), name(n), gpa(g) {}
    Student() : id(0), name(""), gpa(0.0) {}
};

struct Node {
    Student data;
    Node *next, *prev;
    Node(const Student& s) : data(s), next(nullptr), prev(nullptr) {}
};

// 2. Doubly Linked List for Buckets
class DoublyLinkedList {
private:
    Node *head, *tail;
    int size;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() { clear(); }

    void pushBack(const Student& s) {
        Node* newNode = new Node(s);
        if (!head) head = tail = newNode;
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    bool deleteById(int targetId) {
        Node* current = head;
        while (current) {
            if (current->data.id == targetId) {
                if (current == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                    else tail = nullptr;
                } else if (current == tail) {
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                    else head = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Node* search(int targetId) {
        Node* current = head;
        while (current) {
            if (current->data.id == targetId) return current;
            current = current->next;
        }
        return nullptr;
    }

    void display() {
        Node* current = head;
        if (!current) {
            std::cout << "--- Empty ---";
            return;
        }
        while (current) {
            std::cout << " {ID:" << current->data.id << "|" << current->data.name << "|GPA:" << std::fixed << std::setprecision(2) << current->data.gpa << "}";
            if (current->next) std::cout << " <-> ";
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
};

// 3. Hash Table System
class StudentHashTable {
private:
    static const int TABLE_SIZE = 5;
    DoublyLinkedList table[TABLE_SIZE];
    int hashFunction(int id) { return id % TABLE_SIZE; }

public:
    bool insert(int id, std::string name, float gpa) {
        if (table[hashFunction(id)].search(id)) return false;
        table[hashFunction(id)].pushBack(Student(id, name, gpa));
        return true;
    }

    bool remove(int id) {
        return table[hashFunction(id)].deleteById(id);
    }

    Node* find(int id) {
        return table[hashFunction(id)].search(id);
    }

    void clearAll() {
        for(int i=0; i<TABLE_SIZE; i++) table[i].clear();
    }

    void displayUI() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            blue(); std::cout << "Bucket [" << i << "]: "; reset();
            table[i].display();
            std::cout << "\n";
        }
    }
    bool updateStudent(int id, std::string newName, float newGpa) {
        // 1. หาตำแหน่ง Bucket
        int index = hashFunction(id);
    
        // 2. ใช้ searchNode ที่เรามีอยู่แล้วเพื่อหา Node นั้น
        Node* target = table[index].search(id);
    
        if (target != nullptr) {
           // 3. ถ้าเจอ ก็แค่เปลี่ยนข้อมูล "ไส้ใน"
           target->data.name = newName;
           target->data.gpa = newGpa;
           return true; // บอกระบบว่าแก้สำเร็จ
        }

        return false; // หาไม่เจอ แก้ไม่สำเร็จ
    }
};

// 4. Interactive UI
void menu(StudentHashTable& ht) {
    int choice, id;
    std::string name;
    float gpa;

    while (true) {
        system("clear"); // สำหรับ Linux Mint
        yellow();
        std::cout << "=================================================================\n";
        std::cout << "            STUDENT DATABASE VISUALIZER (HASH TABLE)             \n";
        std::cout << "=================================================================\n";
        reset();

        ht.displayUI();
        
        std::cout << "=================================================================\n";
        green(); std::cout << "1. Add Student     ";
        red();   std::cout << "2. Remove Student    ";
        cyan();  std::cout << "3. Search ID\n";
        yellow();std::cout << "4. Clear Database  ";
        green(); std::cout << "5. Update Data\n";
        reset(); std::cout << "0. Exit\n";
        std::cout << "=================================================================\n";
        std::cout << "Select option: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
            case 1:
                std::cout << "Enter ID: "; std::cin >> id;
                std::cout << "Enter Name: "; std::cin >> name;
                std::cout << "Enter GPA: "; std::cin >> gpa;
                if (!ht.insert(id, name, gpa)) {
                    red(); std::cout << "Error: Duplicate ID!\n"; reset();
                }
                break;
            case 2:
                std::cout << "Enter ID to remove: "; std::cin >> id;
                if (!ht.remove(id)) {
                    red(); std::cout << "Error: ID not found!\n"; reset();
                }
                break;
            case 3:
                std::cout << "Search ID: "; std::cin >> id;
                {
                    Node* res = ht.find(id);
                    if (res) {
                        green(); std::cout << "FOUND: " << res->data.name << " | GPA: " << res->data.gpa << "\n"; reset();
                    } else {
                        red(); std::cout << "NOT FOUND!\n"; reset();
                    }
                }
                break;
            case 4:
                ht.clearAll();
                break;
            case 5:
                std::cout << "Enter ID to update: "; std::cin >> id;
                if (ht.find(id)) {
                    std::cout << "New Name: "; std::cin >> name;
                    std::cout << "New GPA: "; std::cin >> gpa;
                    ht.updateStudent(id, name, gpa); // เรียกฟังก์ชันที่เราสร้างใหม่
                    green(); std::cout << "Update successful!\n"; reset();
                } else {
                    red(); std::cout << "Student ID not found!\n"; reset();
                }
                break;
        }
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }
}

int main() {
    StudentHashTable ht;
    menu(ht);
    return 0;
}
