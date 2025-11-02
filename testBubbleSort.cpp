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

//Fuction for Create Data by input : int dataSize
std::vector<int> randomData(int dataSize){
	std::vector<int> random_data;
	for(int i = 0;i < dataSize;++i){
		random_data.push_back(rand()%1000 + 1);
	}
	cout << "\nRandomData";
	return random_data;
}

//Fuction for Display Data by input : const std::vector<int>& data
void showData(const std::vector<int>& data){
	cout << "\n-----------------------------------------------------------------------------\n";
	for(size_t i = 0;i < data.size();++i){
		cout << data.at(i) << "\t";
		if((i+1)%10 == 0) cout << "\n";
	}
	cout << "\n-----------------------------------------------------------------------------\n";
}

void bubbleSort(std::vector<int>& data){
	int temp;
	size_t n = data.size();
	if(n < 2) return;
	for(int i = 0;i < n-1;++i){
		bool swapped = false;
		for(int j = 0;j < n - i - 1;++j){
			if(data[j] > data[j+1]){
				temp = data[j+1];
				data[j+1] = data[j];
				data[j] = temp;
				swapped = true;
			}
		}
		if(!swapped) break;
	}
}

template<typename T>
void checkTime(void(*func)(T&),T& data,const std::string& funcName){
	auto start = std::chrono::steady_clock::now();
	func(data);
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	cout << "\nTime take for " << funcName << " : " << duration.count() << " MicroSec";
}

int main(){
	int input_num;
	std::vector<int> testData;
	cout << "Enter Integer : ";
	cin >> input_num;
	srand(time(0));

	testData = randomData(input_num);
	showData(testData);
	checkTime(bubbleSort,testData,"bubbleSort");
	showData(testData);

	return 0;
}
















