#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include "Array1D.h"

#define MAX_NUMS 20000

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

template<typename T>
T & int_HeapSort(T & data, int length);

template<typename T>
T & siftDown(T & data, int start, int end);

template<typename T>
T & int_MergeSort(T & data, int length);

template<typename T>
void int_MergeSort(T & data, T & tempArray, int leftIndex, int lightIndex);

template<typename T>
void int_Merge(T & data, T & tempArray, int left, int right, int rightEnd);

template<typename T>
T & int_QuickSort(T & data, int length);

template<typename T>
void int_QuickSort(T & data, int first, int last);

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
	int_QuickSort<Array1D<int>>(integers_myA_copy, integers_myA_copy.GetLength());

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

template<typename T>
T & int_HeapSort(T & data, int length) 
{
	//first, heapify
	for (int start = (length - 2) / 2; start >= 0; start--)
	{
		siftDown(data, start, length - 1);
	}
//#ifdef DEBUG
//	cout << "\n---------------------------\n";
//	for (int i = 0; i < MAX_NUMS; i += 1)
//	{
//		cout << data[i] << " ";
//	}
//	cout << "\n---------------------------\n";
//#endif
	int end = length - 1;
	int swapInt;
	while (end > 0) 
	{
		//swap root and last element
		swapInt = data[0];
		data[0] = data[end];
		data[end] = swapInt;
		end--;
		siftDown(data, 0, end);
	}
	return data;
}

template<typename T>
T & siftDown(T & data, int start, int end) 
{
	int child;
	int root = start;
	int swapIndex;
	int swapInt;
	bool notDone = true;
	while ((root * 2) + 1 <= end && notDone)
	{
		child = (root * 2) + 1;
		swapIndex = root;
		if (data[swapIndex] < data[child])
			swapIndex = child;
		if (child + 1 <= end && data[swapIndex] < data[child + 1])
			swapIndex = child + 1;
		if (swapIndex == root) 
		{
			notDone = false;
		}
		else 
		{
			swapInt = data[root];
			data[root] = data[swapIndex];
			data[swapIndex] = swapInt;
			root = swapIndex;
		}
	}
	return data;
}

template<typename T>
T & int_MergeSort(T & data, int length) 
{
	T newData(data);
	int_MergeSort(data, newData, 0, length - 1);
	return data;
}

template<typename T>
void int_MergeSort(T & data, T & tempArray, int left, int right) 
{
	int mid;
	if (left < right) 
	{
		mid = (left + right) / 2;
		int_MergeSort(data, tempArray, left, mid);
		int_MergeSort(data, tempArray, mid + 1, right);
		int_Merge(data, tempArray, left, mid + 1, right);
	}
}

template<typename T>
void int_Merge(T & data, T & tempArray, int left, int right, int rightEnd) 
{
	int leftEnd = right - 1;
	int tempPos = left;
	int NumElements = rightEnd - left + 1;
	int rightC = right;
	int leftC = left;
	while (leftC <= leftEnd && rightC <= rightEnd) {
		if (data[leftC] <= data[rightC])
		{
			tempArray[tempPos] = data[leftC];
			tempPos++;
			leftC++;
		}
		else
		{
			tempArray[tempPos] = data[rightC];
			tempPos++;
			rightC++;
		}
	}
	if (leftC > leftEnd) 
	{
		while (rightC <= rightEnd) 
		{
			tempArray[tempPos] = data[rightC];
			tempPos++;
			rightC++;
		}
	}
	else if (rightC > rightEnd) 
	{
		while (leftC <= leftEnd) 
		{
			tempArray[tempPos] = data[leftC];
			tempPos++;
			leftC++;
		}
	}
	for (int index = left; index <= rightEnd; index++) 
	{
		data[index] = tempArray[index];
	}
}

template<typename T>
T & int_QuickSort(T & data, int length) 
{
	int max = 0;
	int swapInt;
	if (length >= 2) 
	{
		for (int i = 0; i < length; i++) 
		{
			if (data[max] < data[i])
				max = i;
		}
		swapInt = data[length - 1];
		data[length - 1] = data[max];
		data[max] = swapInt;
		int_QuickSort(data, 0, length - 1);
	}
	return data;
}

template<typename T>
void int_QuickSort(T & data, int first, int last) 
{
	int msmall = first + 1;
	int large = last;
	int pivot = data[first];//worst case if sorted
	int swapInt;
	while (msmall <= large) 
	{
		while (msmall <= last && data[msmall] < pivot)
			msmall++;
		while (large >= 0 && data[large] > pivot)
			large--;
		if (msmall < large)
		{
			swapInt = data[msmall];
			data[msmall] = data[large];
			data[large] = swapInt;
			msmall++;
			large--;
		}
		else
			msmall++;
	}
	swapInt = data[large];
	data[large] = data[first];
	data[first] = swapInt;
	if (first < large - 1)
		int_QuickSort(data, first, large - 1);
	if (last > large + 1)
		int_QuickSort(data, large + 1, last);
}