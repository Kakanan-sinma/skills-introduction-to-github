#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<chrono>
#include<string>
#include<functional>

using std::cout;
using std::cin;

std::vector<int> randomData(int dataSize){
	std::vector<int> random_data;
	for(int i = 0;i < dataSize;++i){
		random_data.push_back(rand()%1000 + 1);
	}
	cout << "\nRandomData";
	return random_data;
}

void showData(const std::vector<int>& data){
	cout << "\n----------------------------------------------------------------------\n";
	for(size_t i = 0;i < data.size();++i){
		cout << data.at(i) << "\t";
		if((i+1)%10 == 0) cout << "\n";
	}
	cout << "\n----------------------------------------------------------------------\n";
}

void insertionSort(std::vector<int>& data){
	size_t n = data.size();
	for(int i = 1;i < n;i++){
		int insertIndex = i;
		int currentValue = data[i];
		int j = i-1;

		while(j >= 0 && data[j] > currentValue){
			data[j+1] = data[j];
			insertIndex = j;
			j--;
		}
		data[insertIndex] = currentValue;
	}
}

template<typename T>
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
	cout << "Enter Integer: ";
	cin >> input_num;
	srand(time(0));

	testData = randomData(input_num);
	showData(testData);
	checkTime(insertionSort,testData,"insertionSort");
	showData(testData);

	return 0;
}
