#include<iostream>
#include<vector>

using namespace std;

int parent(int i){return (i - 1) / 2;}
int leftChild(int i){return (2 * i) + 1;}
int rightChild(int i){return (2 * i) + 2;}

void shiftUp(int i, vector<int> &arr){
  while(i > 0 && arr[parent(i)] < arr[i]){
    swap(arr[parent(i)],arr[i]);
    i = parent(i);
  }
}
void insert(int p, vector<int> &arr){
  arr.push_bach(p);
  shiftUp(arr.size() - 1, arr);
}

void shiftDown(int i, vector<int> &arr, int size){
  int maxIdex = i;
  int l = leftChild(i);
  if(l < size && arr[maxIndex] < arr[l]) maxIndex = l;
  int r = rightChild(i);
  if(r < size && arr[maxIndex] < arr[r]) maxIndex = r;

  if(maxIndex != i){
    swap(arr[maxIndex], arr[i]);
    shiftDown(maxIndex, arr, size);
}
int pop(vector<int> &arr){
  int size = arr.size();
  if(size == 0) return -1;
  int result = arr[0];
  arr[0] = arr[size - 1];
  arr.pop_back();
  shiftDown(0, arr, arr.size());
  return result;
}

int getMax(vector<int> &arr){
  if(arr.empty()) return -1;
  return arr[0];
}

void printMaxHeap(vector<int> &arr){
  for(int x : arr) cout << x << " ";
  cout << endl;
}

int main(){
  return 0;
}
