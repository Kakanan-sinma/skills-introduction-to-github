#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include<functional>
#include<string>

//insertionSort
template<typename T>
void insertionSort(std::vector<T>& data){
	size_t n = data.size();
	for(int i = 1;i < n;i++){
		size_t insertIndex = i;
		T currentValue = data[i];
		int j = (int)i-1;

		while(j >= 0 && data[j] > currentValue){
			data[j+1] = data[j];
			insertIndex = (size_t)j;
			j--;
		}

		data[insertIndex] = currentValue;
	}
}

//bubbleSort
template<typename T>
void bubbleSort(std::vector<T>& data){
	size_t n = data.size();
	for(size_t i = 0;i < n-1;i++){
		bool swapped = false;
		for(size_t j = 0;j < n-i-1;j++){
			if(data[j] > data[j+1]){
				std::swap(data[j],data[j+1]);
				swapped = true;
			}
		}
		if(!swapped) break;
	}
}

//selectionSortShifting
template<typename T>
void selectionSortShifting(std::vector<T>& data){
	size_t n = data.size();
	for(size_t i = 0;i < n-1;i++){
		size_t min_index = i;
		for(size_t j = i+1;j < n;j++){
			if(data[j] < data[min_index]){
				min_index = j;
			}
		}
		if(min_index != i){
			T min_value = data[min_index];
			for(size_t k = min_index;k > i;k--){
				data[k] = data[k-1];
			}
			data[i] = min_value;
		}
	}
}

//selectionSortSwap
template<typename T>
void selectionSortSwap(std::vector<T>& data){
	size_t n = data.size();
	for(size_t i = 0;i < n-1;i++){
		size_t min_index = i;
		for(size_t j = i+1;j < n;j++){
			if(data[j] < data[min_index]){
				min_index = j;
			}
		}
		std::swap(data[i],data[min_index]);
	}
}

//quickSort
template<typename T>
void quickSort(std::vector<T>& data,int low,int high);
template<typename T>
int partition(std::vector<T>& data,int low,int high);

template<typename T>
void quickSort(std::vector<T>& data,int low,int high){
	if(low<high){
		int pivotIndex = partition(data,low,high);
		quickSort(data,low,pivotIndex-1);
		quickSort(data,pivotIndex+1,high);
	}
}
template<typename T>
int partition(std::vector<T>& data,int low,int high){
	const T pivot = data[high];
	int i = low-1;

	for(int j = low;j < high;j++){
		if(data[j] <= pivot){
			i++;
			std::swap(data[i],data[j]);
		}
	}
	std::swap(data[i+1],data[high]);
	return i+1;
}
	//quickSort wrapper
template<typename T>
void quickSortWrapper(std::vector<T>& data){
	if(!data.empty()){
		quickSort(data,0,data.size() - 1);
	}
}
//countingSort
void countionSort(std::vector<int>& data,int n){
	int max_val = data[0];
	for(int i = 1;i < n;i++){
		if(data[i] > max_val){
			max_val = data[i];
		}
	}
	std::vector<int> count(max_val+1,0);

	for(int i = 0;i < n;i++){
		count[data[i]]++;
	}

	int index = 0;
	for(int i = 0;i <= max_val;i++){
		while(count[i] > 0){
			data[index++] = i;
			count[i]--;
		}
	}
}
	//countingSort wrapper
void countingSortWrapper(std::vector<int>& data){
	if(!data.empty()){
		int n = data.size();
		countingSort(data,n);
	}
}


//create Data of integer
std::vector<int> createData_int(size_t dataSize){
	std::vector<int> random_data;
	for(size_t i = 0;i < dataSize;i++){
		random_data.push_back(rand()%1000 + 1);
	}
	std::cout << "\nCreated integer Data\n";
	return random_data;
}

//create Data of string
std::string CHARACTERS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string createString(size_t stringlength){
	std::string random_string;
	for(size_t i = 0;i < stringlength;i++){
		random_string += CHARACTERS[rand()%CHARACTERS.length()];;
	}
	return random_string;
}
std::vector<std::string> createData_string(size_t dataSize){
	std::vector<std::string> random_data;
	for(size_t i = 0;i < dataSize;i++){
		std::string randomString = createString(5);
		random_data.push_back(randomString);
	}
	std::cout << "\nCreated String Data\n";
	return random_data;
}

//display Data
template<typename T>
void showData(std::vector<T>& data){
	for(int i = 0;i < data.size();i++){
		std::cout << data.at(i) << "\t";
		if((i+1)%10 == 0) std::cout << "\n";
	}
}

//measure Time
template<typename T>
void checkTime(void (*func)(std::vector<T>&),std::vector<T>& data,const std::string& funcName){
	auto start = std::chrono::steady_clock::now();
	func(data);
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	std::cout << "Time taken for " << funcName << " : " << duration.count() << " Microseconds\n";
}

//main
int main(){
	int input_number;
	std::cout << "Enter integer to be members of Data : ";
	std::cin >> input_number;

	srand(time(0));
//1
	std::vector<int> testData_int1 = createData_int(input_number);
	showData(testData_int1);
	checkTime(insertionSort,testData_int1,"insertionSort");
	showData(testData_int1);

	std::vector<std::string> testData_string1 = createData_string(input_number);
	showData(testData_string1);
	checkTime(insertionSort,testData_string1,"insertionSort");
	showData(testData_string1);
//2
	std::vector<int> testData_int2 = createData_int(input_number);
	showData(testData_int2);
	checkTime(bubbleSort,testData_int2,"bubbleSort");
	showData(testData_int2);

	std::vector<std::string> testData_string2 = createData_string(input_number);
	showData(testData_string2);
	checkTime(bubbleSort,testData_string2,"bubbleSort");
	showData(testData_string2);
//3
	std::vector<int> testData_int3 = createData_int(input_number);
	showData(testData_int3);
	checkTime(selectionSortShifting,testData_int3,"selectionSortShifting");
	showData(testData_int3);

	std::vector<std::string> testData_string3 = createData_string(input_number);
	showData(testData_string3);
	checkTime(selectionSortShifting,testData_string3,"selectionSortShifting");
	showData(testData_string3);
//4
	std::vector<int> testData_int4 = createData_int(input_number);
	showData(testData_int4);
	checkTime(selectionSortSwap,testData_int4,"selectionSortSwap");
	showData(testData_int4);

	std::vector<std::string> testData_string4 = createData_string(input_number);
	showData(testData_string4);
	checkTime(selectionSortSwap,testData_string4,"selectionSortSwap");
	showData(testData_string4);
//5
	std::vector<int> testData_int5 = createData_int(input_number);
	showData(testData_int5);
	checkTime(quickSortWrapper,testData_int5,"quickSort");
	showData(testData_int5);

	std::vector<std::string> testData_string5 = createData_string(input_number);
	showData(testData_string5);
	checkTime(quickSortWrapper,testData_string5,"quickSort");
	showData(testData_string5);


	return 0;
}
