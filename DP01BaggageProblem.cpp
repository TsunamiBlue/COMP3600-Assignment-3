#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstring>
#include<vector>
#include<algorithm>

#include<ctime>
using namespace std;


vector<int> DynamicSearch(const std::vector<std::vector<int>>& cost, int money) {
	vector<int> invalidCombination (1, -1);
	vector<vector<int> > previousState(money + 1, invalidCombination);
	vector<int> indexRecord;

	// init the first state for Markov chain
	for (int i = 0; i < cost[0].size(); ++i) {
		if (previousState[cost[0][i]] == invalidCombination){
		vector<int> tmp;
		tmp.push_back(i);
		previousState[cost[0][i]] = tmp; }
	}
	/*for (int i = 0; i < previousState.size(); i++) {
		for (int j = 0; j < previousState[i].size(); j++) {
			cout << previousState[i][j] << " ";
		}
		cout << endl;
	}*/
	// give out the next state for Markov chain
	vector<vector<int> >currentState(money + 1);
	for (int i = 1; i < cost.size(); ++i) {
		// clear last state
		fill(currentState.begin(), currentState.end(), invalidCombination);
		for (int j = 0; j < cost[i].size(); ++j) {
			for (int k = cost[i][j]; k <= money; ++k) {
				if (previousState[k - cost[i][j]]==invalidCombination) continue;
				if (currentState[k] == invalidCombination) {
					vector<int> tmp = previousState[k - cost[i][j]];
					tmp.push_back(j);
					currentState[k]=tmp;
				}
			}
		}
		// current state assigned as previous
		swap(currentState, previousState);
	}
	for (int i = previousState.size()-1; i >=0; i--) {
		if (previousState[i][0]!= -1) {
			return previousState[i];
		}
	}
	return invalidCombination;
}

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

	clock_t startAlgorithmTime, endAlgorithmTime;
	long double totalAlgorithmTime;

	int money;
	int total_kind;
	fin >> money >> total_kind;
	vector<vector<int> > A;

	// loading data
	for (int i = 0; i < total_kind; i++) {
		int sub_kind;
		fin >> sub_kind;
		vector<int> singleCategory;
		for (int j = 0; j < sub_kind; j++) {
			int tmp;
			fin >> tmp;
			singleCategory.push_back(tmp);
		}
		A.push_back(singleCategory);
	}
	/*for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}*/
	startAlgorithmTime = clock();
	vector<int> ans = DynamicSearch(A, money);
	endAlgorithmTime = clock();


	int sum = 0;
	for (int i = 0; i < A.size(); i++) {
		sum += A[i][ans[i]];
	}
	cout << sum<<" ";
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i]+1 << " ";
	}

	cout << endl;
	cout << (long double)((long double)endAlgorithmTime - (long double)startAlgorithmTime)*1000 / CLOCKS_PER_SEC << "ms" << endl;

	return 0;
}