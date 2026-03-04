#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct TreeNode{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x),left(NULL),right(NULL){}
};
vector<vector<int>> levelOrder(TreeNode* root){
  vector<vector<int>> result;
  if(root == nullptr) return result;

  queue<TreeNode*> q;
  q.push(root);

  while(!q.empty()){
    int size = q.size();
    vector<int> currentLevel;
    for(int i = 0;i < size;i++){
      TreeNode* node = q.front();
      q.pop();
      currentLevel.push_back(node->val);

      if(node->left) q.push(node->left);
      if(node->right) q.push(node->right);
    }
    result.push_back(currentLevel);
  }
  return result;
}
