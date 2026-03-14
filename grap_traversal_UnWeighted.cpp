#include<iostream>
#include<vector>
#include<utility>
#include<queue>

using namespace std;

void addEdgeUndir(vector<vector<int>>>& adj,int u,int v){
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void addEdgeDirec(vector<vector<int>>>& adj,int u,int v){
  adj[u].push_back(v);
}

void addWeightedUndir(vector<vector<pair<int,int>>>& adj,int u,int v,int weight){
  adj[u].push_back({v,weight});
  adj[v].push_back({u,weight});
}

void addWeightedDirec(vector<vector<pair<int,int>>>& adj,int u,int v,int weight){
  adj[u].push_back({v,weight});
}

void bfs(int startNode,vector<vector<int>>& adj,int V){
  vector<bool> visited(V,false);
  queue<int> q;

  visited[startNode] = true;
  q.push(startNode);

  while(!q.empty()){
    int curr = q.front();
    q.pop();
    cout << curr << " ";
    for(int neighbor : adj[curr]){
      if(!visited[neighbor]){
        visited[neighbor] = true;
        q.push(neighbor);
      }
    }
  }
}

void dfsRecursive(int curr,vector<vector<int>& adj,vector<bool>& visited){
  visited[curr] = true;
  cout << curr << " ";

  for(int neighbor : adj[curr]){
    if(!visited[neighbor]){
      dfsRecursive(neighbor,adj,visited);
    }
  }
}

void dfs(int startNode,vector<vector<int>>& adj,int V){
  vector<bool> visited(V,false);
  dfsRecursive(startNode,adj,visited);
}

int main(){
  int V = 5;

  cout << "Undirected Graph" << endl;
  vector<vector<int>> adj1(V);
  for(int i = 0;i < V;i++){
    for(int j = i+1;j < V;j++){
      addEdgeUndir(adj1,i,j);
    }
  }
  cout << "Testing Traversal\n";
  cout << "bfs : "; bfs(0,adj1,V); cout << endl;
  cout << "dfs : "; dfs(0,adj1,V); cout << endl;

  cout << "Directed Graph" << endl;
  vector<vector<int>> adj2(V);
  for(int i = 0;i < V;i++){
    for(int j = i+1;j < V;j++){
      addEdgeUndir(adj2,i,j);
    }
  }
  cout << "Testing Traversal\n";
  cout << "bfs : "; bfs(0,adj2,V); cout << endl;
  cout << "dfs : "; dfs(0,adj2,V); cout << endl;

  cout << endl << "Weighted Undirected Graph" << endl;
  vector<vector<pair<int,int>>> adj3(V);
  for(int i = 0;i < V;i++){
    for(int j = i + 1;j < V;j++){
      int weight = (i + j) * 10;
      addEdgeWeightedUndir(adj3,i,j,weight);
    }
  }

  cout << endl << "Weighted Directed Graph" << endl;
  vector<vector<pair<int,int>>> adj4(V);
  for(int i = 0;i < V;i++){
    for(int j = i + 1;j < V;j++){
      int weight = (i + j) * 10;
      addEdgeWeightedUndir(adj4,i,j,weight);
    }
  }
  return 0;
}
