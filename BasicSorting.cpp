#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include<string>
#include<functional>
#include<algorithm>
#include<cmath>

//1.buubleSort
template<typename T>
void bubbleSort(std::vector<T>& data){
	size_t n = data.size();
	if(n < 2) return;
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

//2.selectionSortShifting
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

//3.selectionSortSwap
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
		if(min_index != i) std::swap(data[i],data[min_index]);
	}
}

//4.insertionSort
template<typename T>
void insertionSort(std::vector<T>& data){
	size_t n = data.size();
	for(size_t i = 1;i < n;i++){
		size_t insertIndex = i;
		T current_value = data[i];
		int j = (int)i-1;

		while(j >= 0 && data[j] > current_value){
				data[j+1] = data[j];
				insertIndex = (size_t)j;
				j--;
		}
		data[insertIndex] = current_value;
	}
}

//5.quickSort
template<typename T>
void quickSort(std::vector<T>& data,int low,int high);
template<typename T>
int partition(std::vector<T>& data,int low,int high);

template<typename T>
void quickSort(std::vector<T>& data,int low,int high){
	if(low < high){
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
template<typename T>
void quickSortWrapper(std::vector<T>& data){
	if(!data.empty()){
		quickSort(data,0,data.size()-1);
	}
}

//6.countinSort
void countingSort(std::vector<int>& data,int n){
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
void countingSortWrapper(std::vector<int>& data){
	if(!data.empty()){
		int n = data.size();
		countingSort(data,n);
	}
}

//7.radixSort
void countingSortByDigit(std::vector<int>& data,int exp){
	int n = data.size();
	std::vector<int> output(n);
	std::vector<int> count(10,0);

	for(int x : data){
		int digit = (x/exp)%10;
		count[digit]++;
	}
	for(int i = 1;i < 10;i++){
		count[i] += count[i-1];
	}
	for(int i = n-1;i >= 0;i--){
		int digit = (data[i] / exp) % 10;
		output[count[digit] - 1] = data[i];
		count[digit]--;
	}
	data = output;
}
void radixSort(std::vector<int>& data){
	if(data.empty()) return;
	int max_val = *std::max_element(data.begin(),data.end());
	for(int exp = 1;max_val/exp > 0;exp *= 10){
		countingSortByDigit(data,exp);
	}
}
void radixSortWrapper(std::vector<int>& data){
	radixSort(data);
}

//8.mergeSort
void mergeSort(std::vector<double>& data,int start,int end);
void merge(std::vector<double>& data,int start,int mid,int end);

void mergeSort(std::vector<double>& data,int start,int end){
	if(start < end){
		int mid = start+(end-start)/2;
		mergeSort(data,start,mid);
		mergeSort(data,mid+1,end);
		merge(data,start,mid,end);
	}
}
void merge(std::vector<double>& data,int start,int mid,int end){
	int n1 = mid-start+1;
	int n2 = end-mid;

	std::vector<double> left(n1);
	std::vector<double> right(n2);

	for(int i = 0;i < n1;i++)
		left[i] = data[start+i];
	for(int j =0;j < n2;j++)
		right[j] = data[mid+1+j];

	int i = 0;
	int j = 0;
	int k = start;

	while(i < n1 && j < n2){
		if(left[i] <= right[j]){
			data[k] = left[i];
			i++;
		}else{
			data[k] = right[j];
			j++;
		}
		k++;
	}
	while(j < n2){
		data[k] = right[j];
		j++;
		k++;
	}
}
void mergeSortWrapper(std::vector<double>& data){
	if(!data.empty()){
		mergeSort(data,0,data.size()-1);
	}
}

//9.iterativeMergeSort
void merge01(double left[], int leftSize, double right[], int rightSize, double result[]) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] < right[j]) {
            result[k++] = left[i++];
        } else {
            result[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        result[k++] = left[i++];
    }

    while (j < rightSize) {
        result[k++] = right[j++];
    }
}

void mergeSort01(std::vector<double>& arr) {
    int length = arr.size();
    if (length <= 1) return;

    for (int step = 1; step < length; step *= 2) {
        for (int i = 0; i < length; i += 2 * step) {
            int start = i;
            int mid = std::min(i + step, length);
            int end = std::min(i + 2 * step, length);
            int leftSize = mid - start;
            int rightSize = end - mid;
            std::vector<double> left_buffer(leftSize);
            std::vector<double> right_buffer(rightSize);
            std::vector<double> merged_buffer(leftSize + rightSize);
            std::copy(arr.begin() + start, arr.begin() + mid, left_buffer.begin());
            std::copy(arr.begin() + mid, arr.begin() + end, right_buffer.begin());
            merge01(left_buffer.data(), leftSize,
                  right_buffer.data(), rightSize,
                  merged_buffer.data());
            std::copy(merged_buffer.begin(), merged_buffer.end(), arr.begin() + start);
        }
    }
}

void iterativeMergeSortWrapper(std::vector<double>& data) {
    mergeSort01(data);
}

//create Data of integer
std::vector<int> createData_int(size_t dataSize){
	std::vector<int> random_data;
	for(size_t i = 0;i < dataSize;i++){
		random_data.push_back(rand()%100000 + 1);
	}
	std::cout << "\nCreated integer Data\n";
	return random_data;
}

//create Data of double
std::vector<double> createData_double(size_t dataSize){
	std::vector<double> random_data;
	for(size_t i = 0;i < dataSize;i++){
		random_data.push_back(1.0+(double)rand()/RAND_MAX*99999.0);
	}
	std::cout << "\nCreated double Data\n";
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
	std::vector<int> testData_int2 = createData_int(input_number);
	checkTime(bubbleSort,testData_int2,"bubbleSort");
//	showData(testData_int2);

	std::vector<std::string> testData_string2 = createData_string(input_number);
	checkTime(bubbleSort,testData_string2,"bubbleSort");
//	showData(testData_string2);
//2
	std::vector<int> testData_int3 = createData_int(input_number);
	checkTime(selectionSortShifting,testData_int3,"selectionSortShifting");
//	showData(testData_int3);

	std::vector<std::string> testData_string3 = createData_string(input_number);
	checkTime(selectionSortShifting,testData_string3,"selectionSortShifting");
//	showData(testData_string3);
//3
	std::vector<int> testData_int4 = createData_int(input_number);
	checkTime(selectionSortSwap,testData_int4,"selectionSortSwap");
//	showData(testData_int4);

	std::vector<std::string> testData_string4 = createData_string(input_number);
	checkTime(selectionSortSwap,testData_string4,"selectionSortSwap");
//	showData(testData_string4);
//4
	std::vector<int> testData_int1 = createData_int(input_number);
	checkTime(insertionSort,testData_int1,"insertionSort");
//	showData(testData_int1);

	std::vector<std::string> testData_string1 = createData_string(input_number);
	checkTime(insertionSort,testData_string1,"insertionSort");
//	showData(testData_string1);
//5
	std::vector<int> testData_int5 = createData_int(input_number);
	checkTime(quickSortWrapper,testData_int5,"quickSort");
//	showData(testData_int5);

	std::vector<std::string> testData_string5 = createData_string(input_number);
	checkTime(quickSortWrapper,testData_string5,"quickSort");
//	showData(testData_string5);
//6
	std::vector<int> testData_int6 = createData_int(input_number);
	checkTime(countingSortWrapper,testData_int6,"countingSort");
//	showData(testData_int6);
//7
	std::vector<int> testData_int7 = createData_int(input_number);
	checkTime(radixSortWrapper,testData_int7,"radixSort");
//	showData(testData_int7);
//8
	std::vector<double> testData_double8 = createData_double(input_number);
	checkTime(mergeSortWrapper,testData_double8,"mergeSort");
//	showData(testData_double8);
//9
	std::vector<double> testData_double9 = createData_double(input_number);
	checkTime(iterativeMergeSortWrapper,testData_double9,"iterativeMergeSort");
//	showData(testData_double9);

	return 0;
}
