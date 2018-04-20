#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include "Array1D.h"

#define MAX_NUMS 1000

using std::cin;
using std::cout;
using std::vector;
using std::rand;
using std::system;

template<typename T>
T & int_BruteBubbleSort(T & data, int length);

template<typename T>
T & int_FlaggedBubbleSort(T & data, int length);

int main() 
{
	vector <int> integers_v;
	Array1D<int> integers_myA(MAX_NUMS);
	int integers_A[MAX_NUMS];

	srand(time(NULL));
	int place = 0;
	for (int i = 0; i < MAX_NUMS; i++) 
	{
		place = rand() % 1000;
		integers_v.push_back(rand() % 1000);
		integers_myA[i] = rand() % 1000;
		integers_A[i] = rand() % 1000;
	}

//	for (int i = 0; i < 10000; i += 1000) 
//	{
//		cout << integers_v[i] << " ";
//	}
//	cout << "\nA sampling of vector ints\n";
//	
	for (int i = 0; i < MAX_NUMS; i += 1) 
	{
		cout << integers_myA[i] << " ";
	}
	cout << "\nIntegers in my array before sorting\n";

//	for (int i = 0; i < 10000; i += 1000) 
//	{
//		cout << integers_A[i] << " ";
//	}
//	cout << "\nA sampling of native array ints\n";

//	cout << "\n---- End of Data ----\n";

	Array1D<int> integers_myA_copy(integers_myA);
	int_BruteBubbleSort<Array1D<int>>(integers_myA_copy, integers_myA_copy.GetLength());

	for (int i = 0; i < MAX_NUMS; i += 1) 
	{
		cout << integers_myA_copy[i] << " ";
	}
	cout << "\nIntegers in sorted my array\n";

	char garbage;
	cin >> garbage;
}

template<typename T>
T & int_BruteBubbleSort(T & data, int length) 
{
	int index_of_largest = 0;
	int unsortedLength = length;
	int swap;
	for (int pass_num = 0; pass_num < length; pass_num++, unsortedLength--)
	{
		for (int index = 0; index < unsortedLength; index++)
		{
			if (data[index_of_largest] < data[index]) 
			{
				index_of_largest = index;
			}
		}
		//place largest at end
		swap = data[index_of_largest];
		data[index_of_largest] = data[unsortedLength - 1];
		data[unsortedLength - 1] = swap;
		index_of_largest = 0;
	}
	return data;
}

template<typename T>
T & int_FlaggedBubbleSort(T & data, int length) 
{
	int index_of_largest = 0;
	int unsortedLength = length;
	int swap;
	int done = true;
	for (int pass_num = 0; done == true && pass_num < length; pass_num++, unsortedLength--)
	{
		done = true;
		for (int index = 0; index < unsortedLength; index++)
		{
			if (data[index_of_largest] < data[index]) 
			{
				index_of_largest = index;
				done = false;
			}
		}
		//place largest at end
		swap = data[index_of_largest];
		data[index_of_largest] = data[unsortedLength - 1];
		data[unsortedLength - 1] = swap;
		index_of_largest = 0;
	}
	return data;
}
