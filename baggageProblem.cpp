#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstring>

using namespace std;

long long multiplication(int* length, int index) {
	if (index == 0) {
		return length[index];
	}
	else {
		return length[index] * multiplication(length, index - 1);
	}
	
}

int accumulation(int* length, int index) {
	if (index == 0) {
		return length[index];
	}
	else {
		return length[index] * accumulation(length, index - 1);
	}
	
}

int calculateCost(int** A,int* length,int totalKind,int* currentIndexArray,int Money) {
	int ans = 0;
	for (int i = 0; i < totalKind; i++) {
		ans += A[i][currentIndexArray[i]];
	}
	if (ans>Money) {
		return -1;
	}
	else {
		return ans;
	}
}

//int** CartesianProduct(int** A, int** B, int* length,int currentIndex) {
//	int aSubSize = accumulation(length, currentIndex);
//	int bSubSize = 1;
//	int aSize = multiplication(length, currentIndex);
//	int bSize = length[currentIndex + 1];
//	int q = 0;
//
//	int** ans = new int* [aSize * bSize];
//	for (int i = 0; i < aSize; i++) {
//		for (int j = 0; j < bSize; j++) {
//			int* tmp = new int[aSubSize + bSubSize];
//			memcpy(tmp, A[i], aSubSize*4);
//			memcpy(tmp + aSize, B[i], bSubSize * 4);
//			ans[q] = tmp;
//			q++;
//		}
//	}
//	return ans;
//}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Error: Input file not specified or too many arguments" << endl << "Usage: Program FileName" << endl;
		return -1;
	}
	ifstream fin(argv[1]);
	// Check if file has been opened properly
	if (!fin.is_open()) {
		cout << "Error: input file cannot be opened" << endl;
		return -1;
	}

	// Your program
	int money;
	int total_kind;
	fin >> money >> total_kind;
	int** A=new int*[total_kind];
	int** indexA = new int* [total_kind];
	int* length = new int[total_kind];

	// loading data
	for (int i = 0; i < total_kind; i++) {
		int sub_kind;
		fin >> sub_kind;
		length[i] = sub_kind;
		A[i] = new int[sub_kind];
		indexA[i] = new int[sub_kind];
		for (int j = 0; j < sub_kind; j++) {
			fin >> A[i][j];
			indexA[i][j]=j;
		}
	}
	// start brute forcing
	int* currentIndexArray = new int[total_kind];
	int maximumCost = 0;
	int* maximumBuyList = new int[total_kind];
		//init 2 array
	memset(currentIndexArray, 0, total_kind*4);
	//cout << multiplication(length, total_kind - 1) << endl;
	for (int i = 0; i < multiplication(length, total_kind - 1);i++) {
		for (int j = 0; j < total_kind;) {
			currentIndexArray[j]++;
			if (currentIndexArray[j] < length[j]) {
				j = 0;
				break;
			}
			else {
				currentIndexArray[j] = 0;
				j++;
			}
		}
		/*cout << "current buy list: ";
		for (int i = 0; i < total_kind; i++) {
			cout << currentIndexArray[i] << " ";
		}*/
		int currentCost = calculateCost(A, length, total_kind, currentIndexArray, money);
		/*cout << "current money cost: " << currentCost << " with budget:" << money << endl;*/
		if (currentCost > maximumCost) {
			maximumCost = currentCost;
			std::copy(currentIndexArray,currentIndexArray+total_kind,maximumBuyList);
		}
	}
	cout << maximumCost<<" ";
	for (int i = 0; i < total_kind; i++) {
		cout << maximumBuyList[i]+1 << " ";
	}
	cout << endl;
	//int** ans = new int*[multiplication(length,total_kind)];
	//for (int i = 1; i < total_kind; i++) {
	//	int** tmp = new int* [length[i]];
	//	for (int j = 0; j < length[i]; j++) {
	//		int* oneElement = new int[1];
	//		oneElement[0] = indexA[i][j];
	//		tmp[j] = oneElement;
	//	}
	//	ans = CartesianProduct(ans,tmp,length,i);
	//}
	//int maximum = 0;
	//for (int i = 0; i < multiplication(length, total_kind); i++) {
	//	cout << ans[i][0] << endl;
	//}


	return 0;
}
