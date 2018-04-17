#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include "Array1D.h"

#define MAX_NUMS

using std::cin;
using std::cout;
using std::vector;
using std::rand;
using std::system;

int main() 
{
	vector <int> integers_v;
	Array1D<int> integers_myA(10000);
	int integers_A[10000];

	srand(time(NULL));
	int place = 0;
	for (int i = 0; i < 10000; i++) 
	{
		place = rand() % 1000;
		integers_v.push_back(rand() % 1000);
		integers_myA[i] = rand() % 1000;
		integers_A[i] = rand() % 1000;
	}

	for (int i = 0; i < 10000; i += 1000) 
	{
		cout << integers_v[i] << " ";
	}
	cout << "\nA sampling of vector ints\n";
	
	for (int i = 0; i < 10000; i += 1000) 
	{
		cout << integers_myA[i] << " ";
	}
	cout << "\nA sampling of Array1D ints\n";

	for (int i = 0; i < 10000; i += 1000) 
	{
		cout << integers_A[i] << " ";
	}
	cout << "\nA sampling of native array ints\n";

	cout << "\n---- End of Data ----\n";
	char garbage;
	cin >> garbage;
}

