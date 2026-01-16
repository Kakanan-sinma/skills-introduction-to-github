#include<iostream>
struct Node{
        int data;
        Node *left, *right;
        Node(int val):data(val),left(nullptr),right(nullptr){}
};
class BST{
private:
        Node *root;
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
                if(node == nullptr) return 0;

        }

        Node* findMinRecursive(Node* node){
                if(node == nullptr) return nullptr;
                if(node->left == nullptr) return node;
                else return findMinRecursive(node->left);
        }


public:
        BST():root(nullptr){}
        ~BST(){

        }

        void insert(int val){
                root = insertReucursive(root,val);
        }

        bool search(int val){
                Node* target = searchRecursive(root,val);
                if(target) return true;
        }

        int hight(){
                int treeHight = hightRecursive(root);
                return treeHight;
        }

        void display(){
                inOrderRecusive(root);
        }

        int findMin(){
                if(root == nullptr) return -1;
                return findMinRecursive(root)->data;
        }

};
int main(){

}
