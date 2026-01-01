#include<iostream>
#include<iomanip>
#include<vector>
#include<ctime>
struct Node{
	int data;
	Node* next;
	Node* prev;
	Node(int val):data(val),next(nullptr),prev(nullptr){}
};
class DoublyLinkedList{
private:
	Node* head;
	Node* tail;
	int size;
public:
//constructor
	DoublyLinkedList():head(nullptr),tail(nullptr),size(0){}
//destructor
	~DoublyLinkedList(){clear();}
//pushBack
	void pushBack(int val){
		Node* newNode = new Node(val);
		if(!head){
			head = tail = newNode;
		}else{
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}
//pushFront
	void pushFront(int val){
		Node* newNode = new Node(val);
		if(!head){
			head = tail = newNode;
		}else{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			size++;
		}
	}
//insertAt
	void insertAt(int index,int val){
		if(index < 0 || index > size){
			std::cout << "Index out of bound\n";
			return;
		}
		if(index == 0){
			pushFront(val);
			return;
		}
		if(index == size){
			pushBack(val);
			return;
		}
		Node* newNode = new Node(val);
		Node* current;
		if(index < size/2){
			current = head;
			for(int i = 0;i < index-1 && current != nullptr;++i){
				current = current->next;
			}
		}else{
			current = tail;
			for(int i = size-1;i > index-1 && current != nullptr;--i){
				current = current->prev;
			}
		}
		Node* nextNode = current->next;

		newNode->next = nextNode;
		newNode->prev = current;
		nextNode->prev = newNode;
		current->next = newNode;
		size++;
	}
//popFront
	void popFront(){
		if(head != nullptr){
			Node* temp = head;
			head = head->next;
			delete temp;

			if(head != nullptr){head->prev = nullptr;}
			else{tail = nullptr;}
			size--;
		}
	}
//popBack
	void popBack(){
		if(tail != nullptr){
			Node* temp = tail;
			tail = tail->prev;
			delete temp;

			if(tail != nullptr){tail->next = nullptr;}
			else{head = nullptr;}
			size--;
		}
	}
//deleteAt
	void deleteAt(int index){
		if(index < 0 || index >= size){
			std::cout << "Index out of bound\n";
			return;
		}
		if(index == 0){popFront();return;}
		if(index == size-1){popBack();return;}

		Node* current;
		if(index < size/2){
			current = head;
			for(int i = 0;i < index && current != nullptr;++i){
				current = current->next;
			}
		}else{
			current = tail;
			for(int i = size-1;i > index && current != nullptr;--i){
				current = current->prev;
			}
		}
		Node* prevNode = current->prev;
		Node* nextNode = current->next;

		if(prevNode) prevNode->next = nextNode;
		if(nextNode) nextNode->prev = prevNode;
		delete current;
		size--;
	}
//getSize
	int getSize(){return size;}
//isEmpty
	bool isEmpty(){return size == 0;}
//clear
	void clear(){
		while(head != nullptr){
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		size = 0;
	}
//getAt
	int getAt(int index){
		if(index < 0 || index >= size){
			throw std::out_of_range("Index out of bound\n");
		}
		Node* current;
		if(index < size/2){
			current = head;
			for(int i = 0;i < index && current != nullptr;i++){
				current = current->next;
			}
		}else{
			current = tail;
			for(int i = size-1;i > index && current != nullptr;i--){
				current = current->prev;
			}
		}
		return current->data;
	}
//indexOf
	std::vector<int> indexOf(int val){
		Node* current = head;
		std::vector<int> result;
		int index = 0;
		while(current != nullptr){
			if(current->data == val){
				result.push_back(index);
			}
			current = current->next;
			index++;
		}
		return result;
	}
//contains
	bool contains(int val){
		Node* current = head;
		while(current != nullptr){
			if(current->data == val){
				return true;
			}
			current = current->next;
		}
		return false;
	}
//displayForward
	void displayForward(){
		Node* current = head;
		int i = 0;
		while(current){
			std::cout << "[" << std::setw(3) << current->data << "]";
			if(current->next != nullptr) std::cout << " <-> ";
			if(++i%7 == 0) std::cout << "\n";
			current = current->next;
		}
		std::cout << " -> NULL\n";
	}
//displayReverse
	void displayReverse(){
		Node* current = tail;
		int i = 0;
		while(current){
			std::cout << "[" << std::setw(3) << current->data << "]";
			if(current->next != nullptr) std::cout << " <-> ";
			if(++i%8 == 0) std::cout << "\n";
			current = current->prev;
		}
		std::cout << " -> NULL\n";
	}
//reverse
	void reverse(){
		if(!head || !head->next) return;

		Node* current = head;
		while(current != nullptr){
			std::swap(current->next,current->prev);
			current = current->prev;
		}
		std::swap(head,tail);
	}
//insertAlot
	void insertAlot(int amount){
		for(int i = 0;i < amount;i++){
			int randomNumber = rand()%1000+1;
			pushBack(randomNumber);
		}
	}
};

void resetColor(){std::cout << "\033[0m";}
void green(){std::cout << "\033[1;32m";}
void red(){std::cout << "\033[1;31m";}
void blue(){std::cout << "\033[1;34m";}
void yellow(){std::cout << "\033[1;33m";}

void displayMenu(DoublyLinkedList& list){
	int choice,data,index,amount;
	std::vector<int> result;
	while(true){
		system("clear");

		std::cout << "\n=================================================================\n";
		yellow();
		std::cout << "            DOUBLY LINKED LIST VISUALIZER (Interactive)\n";
		resetColor();
		std::cout << "=================================================================\n";

		std::cout << "Current List Status:\n";
		blue();
		list.displayForward();
		resetColor();
		std::cout << "Size: " << list.getSize()
			<< " | Empty: " << (list.isEmpty() ? "Yes" : "No") << "\n";
		std::cout << "=================================================================\n";

		green(); std::cout << "[1-3] INSERTION:\n";resetColor();
		std::cout << "1.PushFront   2.PushBack   3.InsertAt\n";
		red(); std::cout << "[4-6] DELETION:\n";resetColor();
		std::cout << "4.PopFront    5.PopBack    6.DeleteAt\n";
		blue(); std::cout << "[7-9] UTILITY:\n";resetColor();
		std::cout << "7.Reverse     8.Search     9.Clear\n";
		std::cout << "10.getAt      11.indexOf   12.insertAlot\n";
		yellow(); std::cout << "[0] EXIT:\n";resetColor();
		std::cout << "0.Exit Program\n";
		std::cout << "=================================================================\n";
		std::cout << "Enter your choice: ";

		if(!(std::cin >> choice)){
			std::cin.clear();
			std::cin.ignore(10000,'\n');
			continue;
		}
		if(choice == 0) break;
		switch(choice){
			case 1:
				std::cout << "Enter Data: ";std::cin >> data;
				list.pushFront(data);
				break;
			case 2:
				std::cout << "Enter Data: ";std::cin >> data;
				list.pushBack(data);
				break;
			case 3:
				std::cout << "Enter Index (0-" << list.getSize() << "): ";
				std::cin >> index;
				std::cout << "Enter Data: ";std::cin >> data;
				list.insertAt(index,data);
				break;
			case 4:
				list.popFront();
				std::cout << "PopFront successfully...\n";
				break;
			case 5:
				list.popBack();
				std::cout << "PopBack successfully...\n";
				break;
			case 6:
				std::cout << "Enter Index (0-" << list.getSize()-1 << "): ";
				std::cin >> index;
				list.deleteAt(index);
				break;
			case 7:
				list.reverse();
				std::cout << "List has been reversed!\n";
				break;
			case 8:
				std::cout << "Enter Value to search: ";std::cin >> data;
				if(list.contains(data)){
					green();std::cout << "Found! Value " << data
					<< " is in the list.\n";resetColor();
				}else{
					red();std::cout << "Not Found!\n";resetColor();
				}
				break;
			case 9:
				list.clear();
				yellow();std::cout << "List cleared!\n";resetColor();
				break;
			case 10:
				std::cout << "Enter Index (0-" << list.getSize() << "): ";
				std::cin >> index;
				std::cout << "Value of index : " << index << " is "
				<< list.getAt(index);
				break;
/*
			case 11:
				std::cout << "Check data,Is it here?\nEnter Value : ";
				std::cin >> data;
				std::cout << "Contain : "
					<< (list.contains(data) ? "Yes":"No") << "\n";
				break;
*/
			case 11:
				std::cout << "Where are indexes?\nEnter Value : ";
				std::cin >> data;
				result = list.indexOf(data);
				if(result.empty()){
					std::cout << "Value not found.\n";
				}else{
					for(const int& val:result){
						std::cout << "found at index : " << val << "\n";
					}
				}
				break;
			case 12:
				std::cout << "Enter amount of value for push to list : ";
				std::cin >> amount;
				list.insertAlot(amount);
				break;
			default:
				std::cout << "Invalid choice!\n";
		}
		std::cout << "\nPress Enter to continue...";
		std::cin.ignore(10000,'\n');
		std::cin.get();
	}
}
int main(){
	srand(time(0));
	DoublyLinkedList list;
	displayMenu(list);
	return 0;
}
