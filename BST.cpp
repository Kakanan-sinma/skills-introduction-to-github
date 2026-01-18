#include<iostream>
#include<ctime>
#include<queue>
#include<vector>
#include<string>
#include<iomanip>
struct Node{
        int data;
        Node *left, *right;
        Node(int val):data(val),left(nullptr),right(nullptr){}
};
class BST{
private:
        Node *root;
        int size = 0;
        Node* insertRecursive(Node* node,int val,bool &wasInserted){
                if(node == nullptr){
			wasInserted = true;
			return new Node(val);
		}
                if(val < node->data){
			node->left = insertRecursive(node->left,val,wasInserted);
                }else if(val > node->data){
			node->right = insertRecursive(node->right,val,wasInserted);
		}else{
			wasInserted = false;
		}
                return node;
        }
        Node* searchRecursive(Node* node,int val){
                if(node == nullptr || val == node->data) return node;
                if(val < node->data) return searchRecursive(node->left,val);
                else  return searchRecursive(node->right,val);
	}
        void inOrderRecursive(Node* node){
                if(node == nullptr) return;
                inOrderRecursive(node->left);
                std::cout << node->data << " ";
                inOrderRecursive(node->right);
        }
        int heightRecursive(Node* node){
                if(node == nullptr) return -1;
                int leftHeight = heightRecursive(node->left);
                int rightHeight = heightRecursive(node->right);
                return 1 + std::max(leftHeight,rightHeight);
        }
        Node* findMinRecursive(Node* node){
                if(node == nullptr) return nullptr;
                if(node->left == nullptr) return node;
                return findMinRecursive(node->left);
        }
        Node* findMaxRecursive(Node* node){
                if(node == nullptr) return nullptr;
                if(node->right == nullptr) return node;
                return findMaxRecursive(node->right);
        }
        Node* deleteNode(Node* node,int key){
                if(node == nullptr) return nullptr;
                if(key < node->data){
                        node->left = deleteNode(node->left,key);
                }else if(key > node->data){
                        node->right = deleteNode(node->right,key);
                }else{
                        if(node->left == nullptr){
                                Node* temp = node->right;
                                delete node;
                                return temp;
                        }else if(node->right == nullptr){
                                Node* temp = node->left;
                                delete node;
                                return temp;
                        }
                        Node* temp = findMinRecursive(node->right);
                        node->data = temp->data;
                        node->right = deleteNode(node->right,temp->data);
                }
                return node;
        }
	Node* deleteRecursive(Node* node,int key){
		if(node == nullptr) return nullptr;
		if(key < node->data){
			node->left = deleteRecursive(node->left,key);
		}else if(key > node->data){
			node->right = deleteRecursive(node->right,key);
		}else{
			if(node->left == nullptr){
				Node* temp = node->right;
				delete node;
				return temp;
			}else if(node->right == nullptr){
				Node* temp = node->left;
				delete node;
				return temp;
			}
			Node* temp = findMinRecursive(node->right);
			node->data = temp->data;
			node->right = deleteRecursive(node->right,temp->data);
		}
		return node;
	}
        void clearRecursive(Node* node){
                if(node == nullptr) return;
                clearRecursive(node->left);
                clearRecursive(node->right);
                delete node;
        }
public:
        BST():root(nullptr){}
        ~BST(){
                clearRecursive(root);
                root = nullptr;
        }
        void insert(int val){
		bool wasInserted = false;
                root = insertRecursive(root,val,wasInserted);
		if(wasInserted) size++;
        }
        bool search(int val){
                return searchRecursive(root,val) != nullptr;
        }
        int height(){
                return heightRecursive(root);
        }
        void display(){
                inOrderRecursive(root);
                std::cout << std::endl;
        }
        int findMin(){
                if(root == nullptr) return -1;
                return findMinRecursive(root)->data;
        }
        int findMax(){
                if(root == nullptr) return -1;
                return findMaxRecursive(root)->data;
        }
        void remove(int val){
                if(search(val)){
                        root = deleteRecursive(root,val);
                        size--;
                }
        }
        int getSize(){return size;}
	void clearTree(){
		clearRecursive(root);
		root = nullptr;
		size = 0;
	}
	void bfs(){
		if(root == nullptr) return;
		std::queue<Node*> q;
		q.push(root);

		while(!q.empty()){
			Node* current = q.front();
			q.pop();

			std::cout << current->data << " ";

			if(current->left != nullptr){
				q.push(current->left);
			}
			if(current->right != nullptr){
				q.push(current->right);
			}
		}
		std::cout << std::endl;
	}

	void printTreeStructure() {
    		if (root == nullptr) {
        		std::cout << "Tree is empty." << std::endl;
        		return;
    		}

  		std::queue<Node*> q;
    		q.push(root);

    		std::cout << "\n--- Tree Structure (Level by Level) ---" << std::endl;

		int level = 0;
	    	while (!q.empty()) {
	        	int nodesInLevel = q.size(); // นับว่าชั้นนี้มีกี่โหนด
	        	std::cout << "Level " << level << ": ";

	       		 // วนลูปดึงเฉพาะโหนดในชั้นปัจจุบันออกมาให้หมด
	        	for (int i = 0; i < nodesInLevel; i++) {
	            		Node* current = q.front();
	            		q.pop();

	            		if (current != nullptr) {
	                		std::cout << "[" << current->data << "] ";

			                // ใส่ลูกลงไปรอในคิว (ซึ่งจะเป็นของชั้นถัดไป)
			                q.push(current->left);
			                q.push(current->right);
				} else {
			                std::cout << "[_] "; // แสดงช่องว่างถ้าไม่มีโหนด
			        }
	        	}
	        	std::cout << std::endl;
	        	level++;

	      	  	// ตรวจสอบว่าในคิวมีแต่ nullptr หรือไม่ ถ้าใช่ให้หยุด (เพื่อไม่ให้ Loop ค้าง)
	        	bool hasMoreNodes = false;
	        	std::queue<Node*> tempQ = q;
	        	while(!tempQ.empty()){
	            		if(tempQ.front() != nullptr) { hasMoreNodes = true; break; }
	            		tempQ.pop();
	        	}
	        	if(!hasMoreNodes) break;
    		}
   		std::cout << "---------------------------------------" << std::endl;
	}

};

void displayMenu(BST& tree){
	int choice,data;
	while(true){
		system("clear");

		std::cout << "\n=============================================================\n";
		std::cout << "		        BST Operations Menu\n";
		std::cout << "=============================================================\n";
		std::cout << "Current List:\n";
		tree.display();
		std::cout << "tree Size : " << tree.getSize() << std::endl;
		std::cout << "tree Hight: " << tree.height();
		std::cout << "\n=============================================================\n";

		std::cout << "1.insert  2.search  3.findMin\n";
		std::cout << "4.findMax 5.remove  6.clearTree\n";
		std::cout << "7.BFS     8.StructT 0.Exit\n";
		std::cout << "=============================================================\n";
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
				tree.insert(data);
				break;
			case 2:
				std::cout << "Data: ";std::cin >> data;
				if(tree.search(data)){
					std::cout << "Is here\n";
				}else{
					std::cout << "Is not here\n";
				}
				break;
			case 3:
				std::cout << "Min : " << tree.findMin() << std::endl;
				break;
			case 4:
				std::cout << "Max : " << tree.findMax() << std::endl;
				break;
/*			case 10:
				try{
					std::cout << "Peek : " << stack.peek();
				}catch(const std::runtime_error& e){
					std::cout << "Error: " << e.what();
				}
				break;
*/
			case 5:
				std::cout << "Data: ";std::cin >> data;
				tree.remove(data);
				break;
			case 6:
				tree.clearTree();
				break;
			case 7:
				std::cout << "BFS (Level-Order): ";
				tree.bfs();
				break;
			case 8:
				tree.printTreeStructure();
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
	srand(time(0));
	BST tree;
	int amountOfData;
	std::cout << "Enter amount of data : ";std::cin >> amountOfData;

	for(int i = 0;i < amountOfData;i++){
		int randomInt = rand()%100+1;
		tree.insert(randomInt);
	}
	displayMenu(tree);
	return 0;
}
