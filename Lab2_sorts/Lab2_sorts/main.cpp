/* Author: Garret Fechter
	Date Created: 4/19/2018
	Purpose: Demonstrate various sorting algorithms
	Modifications: 4/20/2018 - added n^2 sorts
				   4/21/2018 - added nlogn sorts
				   4/23/2018 - added IO and documentation
*/


#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include "Array1D.h"
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
using std::fixed;
using std::setprecision;
using std::right;
using std::setw;
using std::left;
using std::ios;
#define DEBUG
//#define MAX_NUMS 20000
using std::cin;
using std::cout;
using std::vector;
using std::rand;
using std::system;
using std::ofstream;

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
T & int_MergeSort(T & data, T & newData, int length);

template<typename T>
void int_MergeSort(T & data, T & tempArray, int leftIndex, int lightIndex);

template<typename T>
void int_Merge(T & data, T & tempArray, int left, int right, int rightEnd);

template<typename T>
T & int_QuickSort(T & data, int length);

template<typename T>
void int_QuickSort(T & data, int first, int last);

void runSorts(int * data, int length, ofstream & fout);

template<typename T>
void runSorts(T & data, T & data_copy, int length, ofstream & fout);

int main(int argc, char *argv[])
{
	int num_of_elements = 10000;//the number of elements
	if (argc < 2)
	{
		cout << "Using default length of 10000 elements for sorts.\n";
	}
	else
	{
		num_of_elements = std::stoi(argv[1]);
	}

	vector <int> integers_v;//vector container for data
	Array1D<int> integers_myA(num_of_elements);//Array1D container for data
	int *integers_A = new int[num_of_elements];//native array container for data

	srand(time(NULL));
	int place = 0;//the data to place at each locatio n
	for (int i = 0; i < num_of_elements; i++)
	{
		place = rand() % 1000;
		integers_v.push_back(place);
		integers_myA[i] = place;
		integers_A[i] = place;
	}

	std::ofstream fout;//the out file stream to write to
	fout.open("sort_results.txt", std::ofstream::out);

	if (fout.is_open())
	{
		cout << "----- Beginning sorts using native array container -----\n";
		fout << "----- Beginning sorts using native array container -----\n";
		runSorts(integers_A, num_of_elements, fout);

		cout << "----- Beginning sorts using vector container -----\n";
		fout << "----- Beginning sorts using vector container -----\n";
		vector<int> integers_v_copy;//copy of vector data
		runSorts(integers_v, integers_v_copy, num_of_elements, fout);

		cout << "----- Beginning sorts using my Array1D container -----\n";
		fout << "----- Beginning sorts using my Array1D container -----\n";
		Array1D<int> integers_myA_copy(integers_myA);//copy of Array1D data
		runSorts(integers_myA, integers_myA_copy, num_of_elements, fout);

		cout << "\n----- Sorts Complete -----\n";
		fout << "\n----- Sorts Complete -----\n";

		char garbage;//just a character to input to wait before ending output
		cin >> garbage;
	}
	else
		cout << "FATAL ERROR: could not open sorted_results.txt\n";
	delete[] integers_A;
}

/*
	Function: runSorts
	Purpose: Runs a bunch of sorts, using an int * as data container
	Entry: Takes data with allocated ints of length length
		fout is an OPENED ofstream
	Exit: Writes to cout and fout
*/
void runSorts(int * data, int length, ofstream & fout)
{
	//create copy
	int * data_copy = new int[length];//copy of int* data
	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//BRUTE BUBBLE
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();//time right now
	int_BruteBubbleSort<int *>(data_copy, length);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();//end of time
	std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);//elapsed time
	cout << "Every 1000 elements from the sorted data from int_BruteBubbleSort:\n";
	fout << "Every 1000 elements from the sorted data from int_BruteBubbleSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_BruteBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_BruteBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//FLAGGED BUBBLE
	start = std::chrono::steady_clock::now();
	int_FlaggedBubbleSort<int *>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_FlaggedBubbleSort:\n";
	fout << "Every 1000 elements from the sorted data from int_FlaggedBubbleSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_FlaggedBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_FlaggedBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//SELECTION SORT
	start = std::chrono::steady_clock::now();
	int_SelectionSort<int *>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_SelectionSort:\n";
	fout << "Every 1000 elements from the sorted data from int_SelectionSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_SelectionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_SelectionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//INSERTION SORT
	start = std::chrono::steady_clock::now();
	int_InsertionSort<int *>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_InsertionSort:\n";
	fout << "Every 1000 elements from the sorted data from int_InsertionSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_InsertionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_InsertionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//SHELL SORT
	start = std::chrono::steady_clock::now();
	int_ShellSort<int *>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_ShellSort:\n";
	fout << "Every 1000 elements from the sorted data from int_ShellSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_ShellSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_ShellSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//HEAP SORT
	start = std::chrono::steady_clock::now();
	int_HeapSort<int *>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_HeapSort:\n";
	fout << "Every 1000 elements from the sorted data from int_HeapSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n";
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_HeapSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_HeapSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//MERGE SORT
	start = std::chrono::steady_clock::now();
	int *temp_data = new int[length];//temporary data that merge sort needs 
	int_MergeSort<int *>(data_copy, temp_data, length);
	delete[] temp_data;
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_MergeSort:\n";
	fout << "Every 1000 elements from the sorted data from int_MergeSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_MergeSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_MergeSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	for (int i = 0; i < length; i++)
	{
		data_copy[i] = data[i];
	}
	//QUICK SORT
	start = std::chrono::steady_clock::now();
	int_QuickSort<int *>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_QuickSort:\n";
	fout << "Every 1000 elements from the sorted data from int_QuickSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_QuickSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_QuickSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	delete[] data_copy;
}

/*
	Function: runSorts
	Purpose: Runs a bunch of sorts, using templated data container
		(must have [], copy ctor, assignment ctor)
	Entry: Takes data with allocated ints of length length
		fout is an OPENED ofstream
	Exit: Writes to cout and fout.
*/
template<typename T>
void runSorts(T & data, T & data_copy, int length, ofstream & fout)
{
	data_copy = data;
	//BRUTE BUBBLE
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();//time right now
	int_BruteBubbleSort<T>(data_copy, length);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();//end of time 
	std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);//elapsed time
	cout << "Every 1000 elements from the sorted data from int_BruteBubbleSort:\n";
	fout << "Every 1000 elements from the sorted data from int_BruteBubbleSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_BruteBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_BruteBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//FLAGGED BUBBLE
	data_copy = data;
	start = std::chrono::steady_clock::now();
	int_FlaggedBubbleSort<T>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_FlaggedBubbleSort:\n";
	fout << "Every 1000 elements from the sorted data from int_FlaggedBubbleSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_FlaggedBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_FlaggedBubbleSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//SELECTION SORT
	data_copy = data;
	start = std::chrono::steady_clock::now();
	int_SelectionSort<T>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_SelectionSort:\n";
	fout << "Every 1000 elements from the sorted data from int_SelectionSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n";
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_SelectionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_SelectionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//INSERTION SORT
	data_copy = data;
	start = std::chrono::steady_clock::now();
	int_InsertionSort<T>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_InsertionSort:\n";
	fout << "Every 1000 elements from the sorted data from int_InsertionSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_InsertionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_InsertionSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//SHELL SORT
	data_copy = data;
	start = std::chrono::steady_clock::now();
	int_ShellSort<T>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_ShellSort:\n";
	fout << "Every 1000 elements from the sorted data from int_ShellSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_ShellSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_ShellSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//HEAP SORT
	data_copy = data;
	start = std::chrono::steady_clock::now();
	int_HeapSort<T>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_HeapSort:\n";
	fout << "Every 1000 elements from the sorted data from int_HeapSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_HeapSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_HeapSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//MERGE SORT
	data_copy = data;
	start = std::chrono::steady_clock::now();
	T temp_data(data_copy);
	int_MergeSort<T>(data_copy, temp_data, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_MergeSort:\n";
	fout << "Every 1000 elements from the sorted data from int_MergeSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_MergeSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_MergeSort " << elapsed.count() << " microseconds with " << length << " elements.\n";

	//QUICK SORT
	data_copy = data;
	start = std::chrono::steady_clock::now();
	int_QuickSort<T>(data_copy, length);
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Every 1000 elements from the sorted data from int_QuickSort:\n";
	fout << "Every 1000 elements from the sorted data from int_QuickSort:\n";
	for (int i = 0; i < length; i += 1000)
	{
		cout << data_copy[i] << " ";
		fout << data_copy[i] << " ";
		if ((i + 1) % 10000 == 0)
		{
			cout << "\n"; 
			fout << "\n";
		}
	}
	cout << "\n";
	fout << "\n";
	cout << "It took int_QuickSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
	fout << "It took int_QuickSort " << elapsed.count() << " microseconds with " << length << " elements.\n";
}

/*
	Function: BruteBubbleSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_BruteBubbleSort(T & data, int length)
{
	int unsortedLength = length - 1;//the unsorted length
	int swap;//temp space for swapping
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

/*
	Function: FlaggedBubbleSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_FlaggedBubbleSort(T & data, int length)
{
	bool cont = true;//flag whether or not complete
	int unsortedLength = length - 1;//the # of unsorted elements
	int swap;//temp space to swap data around
	for (int pass_num = 0; (cont == true) && pass_num < length; pass_num++, unsortedLength--)
	{
		cont = false;
		for (int index = 0; index < unsortedLength; index++)
		{
			if (data[index] > data[index + 1])
			{
				cont = true;
				swap = data[index + 1];
				data[index + 1] = data[index];
				data[index] = swap;
			}
		}
	}
	return data;
}

/*
	Function: int_SelectionSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_SelectionSort(T & data, int length)
{
	int index_of_largest = 0;//the index of the largest element
	int unsortedLength = length;//# of unsorted elements
	int swap;//space to swap data around
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

/*
	Function: int_InsertionSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_InsertionSort(T & data, int length)
{
	int swap;//sapce to swap data
	int sortedElements = 1;//# of sorted elements
	int insertLocation = 1;//the location to insert data
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

/*
	Function: int_ShellSort
	Purpose: Sorts data using algorithm of name. Shell sizes specified
		as 3h + 1 series (1, 4, 13, etc)
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_ShellSort(T & data, int length)
{
	int stepSize = 1;//current step size
	int swap;//space to swap data 
	int sortedElements = 1;//# of sorted elements
	for (int stepNum = getStepCount(length); stepNum >= 0; stepNum--) //apply process with each step size
	{
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


/*
	Function: getStepSize
	Purpose: Gets the step size specified by the stepnumber and the length of the array
		(using 3h + 1 step sizes)
	Entry: -
	Exit: -
*/
int getStepSize(int stepNumber, int length)
{
	int stepSize = 1;//tjhe first step size
	int counter = 0;//count up to step number in series
	for (stepSize = 1; (counter < stepNumber) && ((3 * stepSize) + 1) < length; counter++)
	{
		stepSize = (3 * stepSize) + 1;
	}
	return stepSize;
}

/*
	Function: getStepCount
	Purpose: Gets the number of steps needed for shell sort (using 3h + 1 step sizes)
	Entry: -
	Exit: -
*/
int getStepCount(int length)
{
	int stepSize = 1;//1st step size
	int counter = 0;//counter until step size right before length
	for (stepSize = 1; ((3 * stepSize) + 1) < length; counter++)
	{
		stepSize = (3 * stepSize) + 1;
	}
	return counter;
}

/*
	Function: int_HeapSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_HeapSort(T & data, int length)
{
	//first, heapify
	for (int start = (length - 2) / 2; start >= 0; start--)
	{
		siftDown(data, start, length - 1);
	}
	int end = length - 1;//aka last
	int swapInt;//space to swap an int
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

/*
	Function: siftDown
	Purpose: Performs one pass of the heapsort making the heap algorithm
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & siftDown(T & data, int start, int end)
{
	int child;//child of the root
	int root = start;//aka first
	int swapIndex;//space to swap index
	int swapInt;//space to swap int
	bool notDone = true;//conitnue while not done (when first = the top)
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

/*
	Function: int_MergeSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_MergeSort(T & data, T & newData, int length)
{
	int_MergeSort(data, newData, 0, length - 1);
	return data;
}

/*
	Function: int_MergeSort
	Purpose: Recursively splits data into little arrays
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
void int_MergeSort(T & data, T & tempArray, int left, int right)
{
	int mid;//middle of the array
	if (left < right)
	{
		mid = (left + right) / 2;
		int_MergeSort(data, tempArray, left, mid);
		int_MergeSort(data, tempArray, mid + 1, right);
		int_Merge(data, tempArray, left, mid + 1, right);
	}
}

/*
	Function: int_Merge
	Purpose: Merges two lists together (after being separated by mergesort_
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
void int_Merge(T & data, T & tempArray, int left, int right, int rightEnd)
{
	int leftEnd = right - 1;//left end of data
	int tempPos = left;//tempoaray position
	int NumElements = rightEnd - left + 1;//# of elements
	int rightC = right;//mutable right bounds
	int leftC = left;//mutable left bounds
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

/*
	Function: int_QuickSort
	Purpose: Sorts data using algorithm of name
	Entry: Existing data is in data. must have [] operator
	Exit: Sorts the data in data
*/
template<typename T>
T & int_QuickSort(T & data, int length)
{
	int max = 0;//highest # in array
	int swapInt;//space to swap ints around
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

/*
	Function: int_QuickSort
	Purpose: The recursive part of quicksort need to implement it
	Entry: Existing data is in data. must have [] operator. First and last
		are inclusive left/right bounds
	Exit: Sorts the data in data
*/
template<typename T>
void int_QuickSort(T & data, int first, int last)
{
	int msmall = first + 1;//aka small, pointer going right  (small is already defined)
	int large = last;//the large pointer coming left
	int pivot = data[first];//worst case if sorted
	int swapInt;//space to swap ints around
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