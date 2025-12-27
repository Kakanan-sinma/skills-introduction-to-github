#include<iostream>
class StackNode{
public:
	int data;
	StackNode *next;
	StackNode(int val):data(val),next(nullptr){}
};
class Stack{
private:
	StackNode* top;
public:
	Stack():top(nullptr){}
//Push
	void push(int val){
		StackNode *newNode = new StackNode(val);
		newNode->next = top;
		top = newNode;
		std::cout << val << " pushed to stack\n";
	}
//Pop
	void pop(){
		if(isEmpty()){
			std::cout << "Stack Underflow!\n";
			return;
		}
		StackNode *temp = top;
		top = top->next;
		std::cout << temp->data << " popped from stack\n";
		delete temp;
	}
//Peek
	int peek(){
		if(!isEmpty()) return top->data;
		return -1;
	}
//isEmpty
	bool isEmpty(){
		return top == nullptr;
	}
//display
	void display(){
		StackNode *current = top;
		if(current == nullptr){
			std::cout << "Stack is empty\n";
		}
		int i = 0;
		while(current != nullptr){
			std::cout << "[" << current->data << "]";
			if(current->next != nullptr){
				std::cout << "\t";
				i++;
				if(i%8 == 0) std::cout << "\n";
			}
			current = current->next;
		}
		std::cout << std::endl;
	}
};
// displayMenu
void displayMenu(Stack& stack){
	int choice,data;
	while(true){
		system("clear");

		std::cout << "\n=============================================================\n";
		std::cout << "		        Stack Operations Menu\n";
		std::cout << "\n=============================================================\n";
		std::cout << "Current List:\n";
		stack.display();
		std::cout << "\n=============================================================\n";

		std::cout << "1.Push  2.Pop  3.Peek\n";
		std::cout << "4.isEmpty   0.Exit\n";
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
				stack.push(data);
				break;
			case 2:
				stack.pop();
				break;
			case 3:
				std::cout << "Peek : " << stack.peek();
				break;
			case 4:
				if(stack.isEmpty()){
					std::cout << "Is empty\n";
				}else{
					std::cout << "Is not empty\n";
				}
				break;
			case 0:
				std::cout << "Exiting program Thank you!\n";
				break;
			default:
				std::cout << "Invalid choice. Please try again\n";
				break;
		}
		if(choice != 0){
			std::cout << "\nPress Enter to continue...";
			std::cin.ignore(10000,'\n');
			std::cin.get();
		}
	}
}


int main(){
	Stack stack;
	displayMenu(stack);
	return 0;
}
