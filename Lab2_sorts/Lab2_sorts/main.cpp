#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include "Array1D.h"

#define MAX_NUMS 20

#define DEBUG

using std::cin;
using std::cout;
using std::vector;
using std::rand;
using std::system;

template<typename T>
T & int_BruteBubbleSort(T & data, int length);

template<typename T>
T & int_FlaggedBubbleSort(T & data, int length);

template<typename T>
T & int_SelectionSort(T & data, int length);

template<typename T>
T & int_InsertionSort(T & data, int length);

template<typename T>
T & int_ShellSort(T & data, int length);

int getStepSize(int stepNumber, int length);
int getStepCount(int length);

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
	int_ShellSort<Array1D<int>>(integers_myA_copy, integers_myA_copy.GetLength());

	for (int i = 0; i < MAX_NUMS; i += 1) 
	{
		cout << integers_myA_copy[i] << " ";
	}
	cout << "\nIntegers in sorted my array\n";

	for (int i = 0; i <= getStepCount(MAX_NUMS); i++)
	{
		cout << "Step size " << i << " for " << MAX_NUMS << " elements: " << getStepSize(i, MAX_NUMS) << "\n";
	}
	char garbage;
	cin >> garbage;
}

template<typename T>
T & int_BruteBubbleSort(T & data, int length) 
{
	int unsortedLength = length - 1;
	int swap;
	for (int pass_num = 0; pass_num < length; pass_num++, unsortedLength--)
	{
		for (int index = 0; index < unsortedLength; index++)
		{
			if (data[index] > data[index + 1]) 
			{
				swap = data[index + 1];
				data[index + 1] = data[index];
				data[index] = swap;
			}
		}
	}
	return data;
}

template<typename T>
T & int_FlaggedBubbleSort(T & data, int length) 
{
	bool cont = true;
	int unsortedLength = length - 1;
	int swap;
	for (int pass_num = 0; (cont == true) && pass_num < length; pass_num++, unsortedLength--)
	{
		cont = true;
		for (int index = 0; index < unsortedLength; index++)
		{
			if (data[index] > data[index + 1]) 
			{
				cont = false;
				swap = data[index + 1];
				data[index + 1] = data[index];
				data[index] = swap;
			}
		}
	}
	return data;
}

template<typename T>
T & int_SelectionSort(T & data, int length) 
{
	int index_of_largest = 0;
	int unsortedLength = length;
	int swap;
	for (int pass_num = 0; pass_num < length - 1; pass_num++, unsortedLength--)
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
T & int_InsertionSort(T & data, int length)
{
	int swap;
	int sortedElements = 1;
	bool found = false;
	int insertLocation = 1;
	for (int current = 1; current < length; current++, sortedElements++) 
	{
		swap = data[current];
		for (insertLocation = sortedElements; insertLocation > 0 && swap < data[insertLocation - 1]; insertLocation--)
		{
			data[insertLocation] = data[insertLocation - 1];
		}
		//location set
		data[insertLocation] = swap;
	}
	return data;
}

template<typename T>
T & int_ShellSort(T & data, int length) 
{
	int stepSize = 1;
	int swap;
	int sortedElements = 1;
	for (int stepNum = getStepCount(length); stepNum >= 0; stepNum--) //apply process with each step size
	{
#ifdef DEBUG
		for (int i = 0; i < MAX_NUMS; i += 1)
		{
			cout << data[i] << " ";
		}
		cout << "\n---------------------------\n";
#endif
		stepSize = getStepSize(stepNum, length); 
		for (int base = 0; base <= (length / stepSize); base++) //apply process for each sub array 
		{
			int insertLocation = base + stepSize;
			sortedElements = 1;
			for (int current = base + stepSize; current < length; current += stepSize, sortedElements++) //for each subarray element
			{
				swap = data[current]; //second element of sub array
				for (insertLocation = base + (sortedElements * stepSize); insertLocation > base && swap < data[insertLocation - stepSize]; insertLocation -= stepSize) //looking for insert location
				{
					data[insertLocation] = data[insertLocation - stepSize];
				}
				//location set
				data[insertLocation] = swap;
			}
		}
	}
	return data;
}

int getStepSize(int stepNumber, int length) 
{
	int stepSize = 1;
	int counter = 0;
	for (stepSize = 1; (counter < stepNumber) && ((3 * stepSize) + 1) < length; counter++) 
	{
		stepSize = (3 * stepSize) + 1;
	}
	return stepSize;
}

int getStepCount(int length) 
{
	int stepSize = 1;
	int counter = 0;
	for (stepSize = 1; ((3 * stepSize) + 1) < length; counter++) 
	{
		stepSize = (3 * stepSize) + 1;
	}
	return counter;
}