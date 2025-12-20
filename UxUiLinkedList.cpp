#include<iostream>
class Node{
private:
	int data;
	Node *next;
public:
	Node(int val):data(val),next(nullptr){}
	friend class LinkedList;
};
class LinkedList{
private:
	Node *head;
public:
	LinkedList():head(nullptr){}
	~LinkedList(){
		Node *current = head;
		Node *nextNode = nullptr;
		while(current != nullptr){
			nextNode = current->next;
			delete current;
			current = nextNode;
		}
		head = nullptr;
	}
//1 insertAtHead
	void insertAtHead(int data){
		Node *newNode = new Node(data);
		newNode->next = head;
		head = newNode;
	}
//2 insertAtTail
	void insertAtTail(int data){
		Node *newNode = new Node(data);
		if(head == nullptr){
			head = newNode;
			return;
		}
		Node *current = head;
		while(current->next != nullptr){
			current = current->next;
		}
		current->next = newNode;
	}
//3 insertAtPosition
	void insertAtPosition(int data,int position){
		if(position <= 0){
			std::cout << "Invalid position\n";
			return;
		}
		if(position == 1){
			insertAtHead(data);
			return;
		}
		Node *current = head;
		for(int i = 1;current != nullptr && i < position-1;++i){
			current = current->next;
		}
		if(current == nullptr){
			std::cout << "Position out of bound\n";
			return;
		}
		Node *newNode = new Node(data);
		newNode->next = current->next;
		current->next = newNode;
	}


//4 deleteAtHead
	void deleteAtHead(){
		if(head == nullptr){
			std::cout << "List is empty\n";
			return;
		}
		Node *temp = head;
		head = head->next;
		delete temp;
	}
//5 deleteAtTail
	void deleteAtTail(){
		if(head == nullptr){
			std::cout << "List is empty\n";
			return;
		}
		Node *current = head;
		if(current->next == nullptr){
			delete current;
			return;
		}
		while(current->next->next != nullptr){
			current = current->next;
		}
		delete current->next;
		current->next = nullptr;
	}
//6 search
	bool search(int key){
		Node *current = head;
		while(current != nullptr){
			if(current->data == key){
				return true;
			}
			current = current->next;
		}
		return false;
	}
//7 getDataAtPosition
	int getDataAtPosition(int position){
		if(position <= 0){
			throw std::out_of_range("Position nust be positive\n");
		}
		Node *current = head;
		for(int i = 1;current != nullptr && i < position;++i){
			current = current->next;
		}
		if(current == nullptr){
				throw std::out_of_range("Position out of bounds\n");
		}
		return current->data;
	}
//8 isEmpty
	bool isEmpty() const{
		return head == nullptr;
	}
	int getSize() const{
		int count = 0;
		Node *current = head;
		while(current != nullptr){
			count++;
			current = current->next;
		}
		return count;
	}
//9 display
	void display(){
		Node *current = head;
		if(current == nullptr){
			std::cout << "Empty List";
		}
		while(current != nullptr){
			std::cout << "[" << current->data << "]";
			if(current->next != nullptr){
				std::cout << " -> ";
			}
			current = current->next;
		}
		std::cout << std::endl;
	}
};
//10 displayMenu
void displayMenu(LinkedList& list){
	int choice,data,position,key;
	while(true){
		system("clear");

		std::cout << "\n=============================================================\n";
		std::cout << "		Linked List Operations Menu\n";
		std::cout << "\n=============================================================\n";
		std::cout << "Current List: ";
		list.display();
		std::cout << "Size: " << list.getSize() << "\n";
		std::cout << "\n=============================================================\n";


		std::cout << "1.Insert at Head  2.Insert at Tail  3.Insert at Position\n";
		std::cout << "4.Delete at Head  5.Delete at Tail  6.Search for an element\n";
		std::cout << "7.Get Data        0.Exit\n";
		std::cout << "\n=============================================================\n";
		std::cout << "Enter your choice: ";
		if(!(std::cin >> choice)){
			std::cin.clear();
			std::cin.ignore(10000,'\n');
			choice = -1;
			continue;
		}
		if(choice == 0 ) break;
		switch(choice){
			case 1:
				std::cout << "Data: ";std::cin >> data;
				list.insertAtHead(data);
				break;
			case 2:
				std::cout << "Data: ";std::cin >> data;
				list.insertAtTail(data);
				break;
			case 3:
				std::cout << "Data: ";std::cin >> data;
				std::cout << "Pos : ";std::cin >> position;
				list.insertAtPosition(data,position);
				break;
			case 4:
				list.deleteAtHead();
				break;
			case 5:
				list.deleteAtTail();
				break;
			case 6:
				std::cout << " Enter key to search: ";
				std::cin >> key;
				if(list.search(key)){
					std::cout << "Key " << key << " found in the list\n";
				}else{
					std::cout << "Key " << key << " not found\n";
				}
				break;
			case 7:
				std::cout << "Enter position to get data(1-based index): ";
				std::cin >> position;
				try{
					int val = list.getDataAtPosition(position);
					std::cout << "Data at position " << position << " is: " << val << std::endl;
				}catch(const std::out_of_range& e){
					std::cerr << "Error: " << e.what() << std::endl;
				}
				break;
			case 8:
				std::cout << "\n--- Current List ---\n";
				list.display();
				std::cout << "----------------------\n";
				break;
			case 9:
				std::cout << "Current size of list: " << list.getSize() << " members\n";
				break;
			case 0:
				std::cout << "Exiting program Thank you!\n";
				break;
			default:
				std::cout << "Invalid choice. Please try again\n";
				break;
		}
		if(choice != 8){
			std::cout << "\nPress Enter to continue...";
			std::cin.ignore(10000,'\n');
			std::cin.get();
		}
	}
}

int main(){
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(NULL);

	LinkedList list;
	displayMenu(list);

	return 0;
}

