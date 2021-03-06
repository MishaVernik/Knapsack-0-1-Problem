// KnapSack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

void printElemnts(int, int *, int *, int, int, int **);
void knapSack(int, int *, int *, int);
void createTestCase(const char*, int, int, int);

/* 
	Function: knapSack
	Returns the maximum value that can be put in a knapsack of capacity W 
 

	@param W, knapsack weights
	@param wt, array of weights
	@param val, array of values
	@param n, number of elements in array

*/
void knapSack(int W, int *wt, int *val, int n) {

	int i, w;
	int **K = new int*[n + 1];
	for (int i = 0; i <= n; i++)
		K[i] = new int[W + 1];

	for (i = 0; i <= n; i++) {

		for (w = 0; w <= W; w++) {
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}
	cout << "Knapsack weights : " << W << endl;
	//cout << K[n][W] << endl;
	printElemnts(W, wt, val, n, K[n][W], K);
	for (int i = 0; i <= n; i++)
		delete K[i];
	delete K;
}
/*
	Function: printElemnts
	Returns the maximum value that can be put in a knapsack of capacity W


	@param W, knapsack weights
	@param wt, array of weights
	@param val, array of values
	@param n, number of elements in array
	@param K, table [][] with results. The last index [n][W] contains the answer

*/

void printElemnts(int W, int *wt, int *val, int n, int result, int **K) {
	int w = W, i;
	int *arr = new int[n];
	int count = 0;
	for (i = n; i > 0 && result > 0; i--) {

		if (result == K[i - 1][w])
			continue;
		else {
			arr[count] = i;
			//cout << wt[i - 1] << " ";
			result = result - val[i - 1];
			w = w - wt[i - 1];
			count++;
		}
	}
	cout << "Number of elements : " << count << "\nMax value : " << K[n][W] << endl;
	sort(arr, arr + count);
	for (int j = 0; j < count; j++)
		cout << "Index in vector : " << arr[j] << "\nElement: " << val[arr[j] - 1] << endl;
}
 

int main() {
 
	ifstream in("knapsack1024.in");

	int n = 0;
	int w = 0;
	in >> n >> w;
	int *val = new int[n];
	int *weights = new int[n];

	for (int i = 0; i < n; i++) {
		in >> val[i];
	}
	for (int i = 0; i < n; i++) {
		in >> weights[i];
	}

	knapSack(w, weights, val, n);

	delete val;
	delete weights;
	in.close();
 
	return 0;
}

/*
	Function: createTestCase
	The fucntion creates a file, which contains knapsack data


	@param fileName, file name
	@param weight, array of weights
	@param maxValue, max value that can be in an array
	@param n, number of elements

*/
void createTestCase(const char* fileName, int n, int weight, int maxValue) {

	srand(time(0));

	ofstream out(fileName);
	out << n << endl;
	maxValue = (maxValue * 5) / 7;
	int rnd = rand() % maxValue;
	out << rnd << endl;
	for (int i = 0; i < 1024; i++) {
		out << rand() % maxValue << " ";
	}
	for (int i = 0; i < 1024; i++) {
		out << rand() % maxValue << " ";
	}
	out.close();
}