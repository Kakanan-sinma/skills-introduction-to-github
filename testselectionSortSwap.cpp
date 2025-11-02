#include<iostream>
#include<vector>
#include<chrono>
#include<ctime>
#include<cstdlib>
#include<functional>
#include<cstdio>
#include<string>

using std::cout;
using std::cin;

//Function for Create Data by input : int dataSize
std::vector<int> randomData(int dataSize){
	std::vector<int> random_data;
	for(int i = 0;i < dataSize;++i){
		random_data.push_back(rand()%1000 + 1);
	}
	cout << "\nRandomData";
	return random_data;
}//Function for Display Data by input : const std::vector<int>& data
void showData(const std::vector<int>& data){
	cout << "\n---------------------------------------------------------------------\n";
	for(size_t i = 0;i < data.size();++i){
		cout << data.at(i) << "\t";
		if((i+1)%10 == 0) cout << "\n";
	}
	cout << "\n---------------------------------------------------------------------\n";
}

//Function for Sort Data the last to the most by input : std::vector<int>& data
void selectionSortSwapped(std::vector<int>& data){
	size_t n = data.size();
	for(int i = 0;i < n-1;i++){
		int min_index = i;
		for(int j = i+1;j < n;j++){
			if(data[j] < data[min_index]){
				min_index = j;
			}
		}
		int temp = data[i];
		data[i] = data[min_index];
		data[min_index] = temp;
	}
}

//Function for measureTime
template <typename T>
void checkTime(void(*func)(T&),T& data,const std::string& funcName){
	auto start = std::chrono::steady_clock::now();
	func(data);
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	cout << "\nTime taken for " << funcName << " : " << duration.count() << " MicroSec";
}

int main(){
	int input_num;
	std::vector<int> testData;
	cout << "Enter Integer : ";
	cin >> input_num;
	srand(time(0));

	testData = randomData(input_num);
	showData(testData);
	checkTime(selectionSortSwapped,testData,"selectionSortSwapped");
	showData(testData);

	return 0;
}
