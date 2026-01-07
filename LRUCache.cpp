#include<iostream>
#include<iomanip>
#include<vector>
#include<string>

struct Part{
        int id;
        std::string name;
        float price;
        Part(int i,std::string n,float p):id(i),name(n),price(p){}
        Part():id(0),name(""),price(0.0){}
};

struct Node{
        Part data;
        Node *next,*prev;
        Node(const Part& p):data(p),next(nullptr),prev(nullptr){}
};

class DoublyLinkedList{
private:
        Node *head,*tail;
        int size;
public:
        DoublyLinkedList():head(nullptr),tail(nullptr),size(0){}
	~DoublyLinkedList(){clear();}

        Node* getHead(){return head;}

        Node* pushBack(const Part& p){
                Node* newNode = new Node(p);
                if(!head){
                        head = tail = newNode;
                }else{
                        newNode->prev = tail;
                        tail->next = newNode;
                        tail = newNode;
                }
                size++;
                return tail;
        }

	Node* pushFront(const Part& p){
		Node* newNode = new Node(p);
		if(!head){
			head = tail = newNode;
		}else{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
		return head;
	}

        Node* findPart(int targetId){
                Node* current = head;
                while(current){
                        if(current->data.id == targetId) return current;
                        current = current->next;
                }
                return nullptr;
        }
        void displayAll(){
                Node* current = head;
                while(current){
                        std::cout << "[ID:" << current->data.id
                                << "|" << current->data.name
                                << "|" << current->data.price << "]";
                        if(current->next) std::cout << " ";
                        current = current->next;
                }
                return;
        }
        bool deleteById(int targetId){
                Node* current = head;
                while(current){
                        if(current->data.id == targetId){
                                if(current == head && current == tail){
                                        head = tail = nullptr;
                                }
                                else if(current == head){
                                        head = head->next;
                                        head->prev = nullptr;
                                }else if(current == tail){
                                        tail = tail->prev;
                                        tail->next = nullptr;
                                }else{
                                        current->next->prev = current->prev;
                                        current->prev->next = current->next;
                                }
                                delete current;
                                size--;
                                return true;
                        }
                        current = current->next;
                }
                return false;
        }

        bool moveToHead(int targetId){
                Node* current = head;
                while(current){
                        if(current->data.id == targetId){
                                if(current == head) return true;
                                if(current == tail){
                                        tail = tail->prev;
                                        tail->next = nullptr;
                                }
                                else{
                                        current->prev->next = current->next;
                                        current->next->prev = current->prev;
                                }
                                current->next = head;
                                current->prev = nullptr;
                                head->prev = current;
                                head = current;
                                return true;
                        }
                        current = current->next;
                }
                return false;
        }

        int popTail(){
                if(!tail) return -1;
                Node* temp = tail;
                int idTail = tail->data.id;
                if(head == tail){
                        head = tail = nullptr;
                }else{
                        tail = tail->prev;
                        tail->next = nullptr;
                }
                delete temp;
                size--;
                return idTail;
        }

	void clear(){
		Node* current = head;
		while(current != nullptr){
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		head = tail = nullptr;
		size = 0;
	}

};

class HashTable{
private:
        struct HashEntry{
                int key;
                Node* mainListNode;
                HashEntry* next;

                HashEntry(int k,Node* n):key(k),mainListNode(n),next(nullptr){}
        };

        static const int TABLE_SIZE = 10;
        HashEntry* table[TABLE_SIZE];

        int hashFunction(int key){return key%TABLE_SIZE;}

public:
        HashTable(){
                for(int i = 0;i < TABLE_SIZE;i++){table[i] = nullptr;}
        }
	~HashTable(){
		for(int i = 0;i < TABLE_SIZE;i++){
			HashEntry* current = table[i];
			while(current != nullptr){
				HashEntry* nextNode = current->next;
				delete current;
				current = nextNode;
			}
			table[i] = nullptr;
		}
	}

        void insert(int key,Node* nodePtr){
                int index = hashFunction(key);
                HashEntry* newEntry = new HashEntry(key,nodePtr);
                newEntry->next = table[index];
                table[index] = newEntry;
        }

        Node* search(int key){
                int index = hashFunction(key);
                HashEntry* current = table[index];
                while(current){
                        if(current->key == key) return current->mainListNode;
                        current = current->next;
                }
                return nullptr;
        }

        bool remove(int key){
                int index = hashFunction(key);
                HashEntry* current = table[index];
                HashEntry* prev = nullptr;

                while(current != nullptr){
                        if(current->key == key){
                                if(prev == nullptr){
                                        table[index] = current->next;
                                }else{
                                        prev->next = current->next;
                                }
                                delete current;
                                return true;
                        }
                        prev = current;
                        current = current->next;
                }
                return false;
        }
};

class LRUCache{
private:
        int capacity;
	int currentSize = 0;
        DoublyLinkedList list;
        HashTable table;
public:
        LRUCache(int cap):capacity(cap),currentSize(0){}

        void getPart(int id){
                Node* node = table.search(id);
                if(!node){
                        std::cout << "Part ID " << id << " not found in cache.\n";
                        return;
                }
                list.moveToHead(id);
                std::cout << "Accessed: " << node->data.name << " (Moved to Front)\n";
        }

        void putPart(int id,std::string name,float price){
                Node* existingNode = table.search(id);

                if(existingNode){
                        existingNode->data.name = name;
                        existingNode->data.price = price;
                        list.moveToHead(id);
                }else{
                        if(currentSize >= capacity){
                                int removedId = list.popTail();
                                table.remove(removedId);
                                currentSize--;
                                std::cout << "Cache full! Remove ID: " << removedId << "\n";
                        }

                        Part newPart(id,name,price);
                        Node* newNode = list.pushFront(newPart);
                        table.insert(id,newNode);
                        currentSize++;
                }
        }

        void displayCache(){
                std::cout << "Current Catch(Newest -> Oldest): ";
                list.displayAll();
                std::cout << std::endl;
        }
};
