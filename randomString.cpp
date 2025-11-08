#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
#include<chrono>

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
	std::cout << "RandomData creation finished.\n";
	return randomData;
}

template<typename T>
void showData(std::vector<T>& data){
	for(int i = 0;i < data.size();i++){
		std::cout << data[i] << "\t";
		if((i+1)%5 == 0) std::cout << "\n";
	}
}

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

	std::vector<std::string> testStringData;
	testStringData = createData(input_number);
	showData(testStringData);
	checkTime(selectionSortShifting,testStringData,"selectionSortShifting");
	showData(testStringData);

	return 0;
}
