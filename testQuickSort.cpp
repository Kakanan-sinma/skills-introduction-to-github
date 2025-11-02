#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<chrono>
#include<functional>

using std::cout;

int partition(std::vector<int>& data, int low, int high);
void quickSort(std::vector<int>& data, int low, int high);

std::vector<int> randomData(int dataSize){
	std::vector<int> random_data;
	for(int i = 0;i < dataSize; ++i){
		random_data.push_back(rand()%1000 + 1);
	}
	cout << "\nRandomData created.";
	return random_data;
}

void showData(const std::vector<int>& data){
	cout << "\n----------------------------------------------------------------------------\n";
	if(data.empty()){
		cout << "Data is empty.\n";
		return;
	}
	for(size_t i = 0;i < data.size();++i){
		cout << data.at(i) << "\t";
		if((i+1)%10 == 0) cout << "\n";
	}
	if(data.size() % 10 != 0) cout << "\n";
	cout << "\n----------------------------------------------------------------------------\n";
}

void quickSort(std::vector<int>& data,int low , int high){
	if(low < 0 || high < 0 || low >= high || low >= data.size() || high >= data.size()){
		return;
	}
	if(low < high){
		int pivotIndex = partition(data,low,high);
		quickSort(data,low,pivotIndex - 1);
		quickSort(data,pivotIndex + 1,high);
	}
}

int partition(std::vector<int>& data,int low,int high){
	int pivot = data[high];
	int i = low - 1;

	for(int j = low;j < high;j++){
		if(data[j] <= pivot){
			i++;
			std::swap(data[i],data[j]);
		}
	}
	std::swap(data[i+1],data[high]);
	return i + 1;
}

template<typename T>
void checkTime(const std::function<void()>& func, const std::string& funcName){
	auto start = std::chrono::steady_clock::now();
	func();
	auto end = std::chrono::steady_clock::now();
	auto duration = std:: chrono::duration_cast<std::chrono::microseconds>(end-start);
	cout << "\nTime taken for **" << funcName << "** : " << duration.count() << " MicroSec\n";
}
int main(){
	size_t input_num;
	int low,high;

	std::vector<int> testData;
	srand(time(0));

	do{
		cout << "Enter integer for creating members of Data : ";
		if(!(std::cin >> input_num)){
			std::cin.clear();
			std::cin.ignore(10000,'\n');
			cout << "Invalid input. Please enter a positive integer.\n";
			continue;
		}
		if(input_num <=0){
			cout << "Data size must be greater than 0.\n";
			continue;
		}
		cout << "Enter low index (start for QuickSort,usually 0) : ";
		std::cin >> low;
		cout << "Enter high index (end for QuickSort,usually " << input_num - 1 << ") : ";
		std::cin >>high;
	}while(input_num <= 0 || low < 0 || high >= (int)input_num || low >= high);

	testData = randomData(input_num);
	cout << "\nData before QuickSort:";
	showData(testData);

	auto quickSortFunc = std::bind(quickSort,std::ref(testData),low,high);
	checkTime<std::vector<int>>(quickSortFunc, "quickSort");
	cout << "\nData after QuickSort:";
	showData(testData);

	return 0;
}
