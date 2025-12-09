#include<iostream>
class Node{
private:
	int data;
	Node* next;
public:
	Node(int val):data(val),next(nullptr){}
	friend class LinkedList;
};
class LinkedList{
private:
	Node* head;
public:
	LinkedList():head(nullptr){}
	~LinkedList(){
		Node* current = head;
		Node* nextNode = nullptr;
		while(current != nullptr){
			nextNode = current->next;
			delete current;
			current = nextNode;
		}
		head = nullptr;
	}
	void insertAtHead(int data){
		Node* newNode = new Node(data);
		newNode->next = head;
		head = newNode;
		std::cout << "add " << data << " in head of list" << std::endl;
	}
	void display(){
		Node* current = head;
		if(current == nullptr){
			std::cout << "empty list" << std::endl;
			return;
		}
		std::cout << "list: ";
		while(current != nullptr){
			std::cout << current->data;
			if(current->next != nullptr){
				std::cout << " -> ";
			}
			current = current->next;
		}
		std::cout << std::endl;
	}
};
int main(){
	LinkedList list;
	list.insertAtHead(30);
	list.insertAtHead(20);
	list.insertAtHead(10);

	list.display();

	return 0;
}
