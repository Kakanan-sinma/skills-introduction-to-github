#include<iostream>
struct Node{
        int data;
        Node *left, *right;
        Node(int val):data(val),left(nullptr),right(nullptr){}
};
class BST{
private:
        Node *root;
        int size = 0;
        Node* insertRecursive(Node* node,int val){
                if(node == nullptr) return new Node(val);
                if(val < node->data) node->left = insertRecursive(node->left,val);
                else node->right = insertRecursive(node->right,val);
                return node;
        }
        Node* searchRecursive(Node* node,int val){
                if(node == nullptr || val == node->data) return node;
                if(val < node->data) return searchRecursive(node->left,val);
                else if (val > node->data) return searchRecursive(node->right,val);
        }
        void inOrderRecursive(Node* node){
                if(node == nullptr) return;
                inOrderRecursive(node->left);
                std::cout << node->data;
                inOrderRecursive(node->right);
        }
        int hightRecursive(Node* node){
                if(node == nullptr) return -1;
                int leftHight = hightRecursive(node->left);
                int rightHight = hightRecursive(node->right);
                return 1 + std::max(leftHight,rightHight);
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
                root = insertRecursive(root,val);
                size++;
        }
        bool search(int val){
                return searchRecursive(root,val) != nullptr;
        }
        int hight(){
                return hightRecursive(root);
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
};
int main(){

}
