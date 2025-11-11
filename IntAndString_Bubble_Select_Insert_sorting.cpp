#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
#include<chrono>

//create string data
const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::string generateRandomString(size_t length){
	std::string random_string;
	for(size_t i = 0;i < length;i++){
		random_string += CHARACTERS[rand() % CHARACTERS.length()];
	}
	return random_string;
}
std::vector<std::string> createData(int dataSize){
	std::vector<std::string> randomData;
	for(int i = 0;i < dataSize;i++){
		std::string randomString = generateRandomString(12);
		randomData.push_back(randomString);
	}
	std::cout << "\nCreated String Data\n";
	return randomData;
}

//creat integer data
std::vector<int> createData_int(size_t dataSize){
	std::vector<int> random_integer;
	for(size_t i = 0;i < dataSize;i++){
		random_integer.push_back(rand()%1000 + 1);
	}
	std::cout << "\nCreated Integer Data\n";
	return random_integer;
}

//display data
template<typename T>
void showData(std::vector<T>& data){
	for(int i = 0;i < data.size();i++){
		std::cout << data[i] << "\t";
		if((i+1)%5 == 0) std::cout << "\n";
	}
}

//selectionShifting
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

//selectionSwap
template<typename T>
void selectionSort_Swap(std::vector<T>& data){
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
        int temp;
        size_t n = data.size();
        if(n < 2) return;
        for(size_t i = 0;i < n-1;++i){
                bool swapped = false;
                for(size_t j = 0;j < n-i-1;++j){
                        if(data[j] > data[j+1]){
				std::swap(data[j],data[j+1]);
                                swapped = true;
                        }
                }
		if(!swapped) break;
        }
}

//checktime
template<typename T>
	void checkTime(void (*func)(std::vector<T>&),std::vector<T>& data,const std::string& funcName){
	auto start = std::chrono::steady_clock::now();
	func(data);
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	std::cout << "\nTime taken for " << funcName << " : " << duration.count() << " Microseconds\n";
}

int main(){
	int input_number;
	std::cout << "Enter integer to be members of data : ";
	std::cin >> input_number;
	srand(time(0));

//1
	std::vector<std::string> testStringData1;
	testStringData1 = createData(input_number);
	showData(testStringData1);
	checkTime(insertionSort,testStringData1,"insertionSort");
	showData(testStringData1);

	std::vector<int> testIntData1;
	testIntData1 = createData_int(input_number);
	showData(testIntData1);
	checkTime(insertionSort,testIntData1,"insertionSort");
	showData(testIntData1);
//2
	std::vector<std::string> testStringData2;
	testStringData2 = createData(input_number);
	showData(testStringData2);
	checkTime(bubbleSort,testStringData2,"bubbleSort");
	showData(testStringData2);

	std::vector<int> testIntData2;
	testIntData2 = createData_int(input_number);
	showData(testIntData2);
	checkTime(bubbleSort,testIntData2,"bubbleSort");
	showData(testIntData2);
//3
	std::vector<std::string> testStringData3;
	testStringData3 = createData(input_number);
	showData(testStringData3);
	checkTime(selectionSortShifting,testStringData3,"selectionSortShifting");
	showData(testStringData3);

	std::vector<int> testIntData3;
	testIntData3 = createData_int(input_number);
	showData(testIntData3);
	checkTime(selectionSortShifting,testIntData3,"selectionSortShifting");
	showData(testIntData3);
//4
	std::vector<std::string> testStringData4;
	testStringData4 = createData(input_number);
	showData(testStringData4);
	checkTime(selectionSort_Swap,testStringData4,"selectionSortSwap");
	showData(testStringData4);

	std::vector<int> testIntData4;
	testIntData4 = createData_int(input_number);
	showData(testIntData4);
	checkTime(selectionSort_Swap,testIntData4,"selectionSortSwap");
	showData(testIntData4);

	return 0;
}
