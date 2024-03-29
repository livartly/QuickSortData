// QuickSortData.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Author: Liv Weaver
//October 13, 2019, Algorithms, Prof. Beth Allen
//This program performs the following actions:
//Prompts the user for the name of input and output text files
//Promps the user for the number of words to be printed per line
//Reads up to 1000 words from given input file and places each word into an array of strings
//Sorts the array of words using quick sort
//Prints the sorted data into an output file in a number of specified columns

//File path used for testing: C:\Users\Liv\Documents\GitHub\QuickSortData\QuickSortData\TestInput.txt

#include "pch.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <clocale>

using namespace std;

//Function prototypes 
void swap(string* a, string* b);
int partition(string array[], int low, int high);
void quickSort(string arr[], int low, int high);
void printArray(string array[], int size, int wordsPerLine, string outputFileName);
int ignoreCase(string sInput, string pivot);


int main()
{
	cout << "Welcome to Quick Sort Data!\n";
	cout << "Please enter the file path of your input file:\n";

	char filename[500]; // Filename character array
	int wordsPerLine; // Number of words to be printed per line, read in from user
	ifstream inputFile;
	string outputFile;
	cin.getline(filename, 500);
	inputFile.open(filename);

	if (!inputFile.is_open())
	{
		cout << "Unable to open file.\n";
		exit(EXIT_FAILURE);
	}
	else // Read words from file into array of strings 
	{
		char word[50]; // Up to 50 char per word
		string wordArray[1000]; //Array of strings to hold each word
		int wordCount = 0;

		inputFile >> word;
		while (inputFile.good()) // While we haven't reached the end of the file 
		{
			inputFile >> word;
			if (wordCount < 1000)
			{
				wordArray[wordCount] = word;
				wordCount++;
			}
		}
		cout << "Please enter the file path of your output file:\n";
		cin >> outputFile;

		// Get number of words per line from user
		cout << wordCount << " words were found in the file: " << filename << " \n";
		cout << "How many words per line should be printed? \n";
		cin >> wordsPerLine;
		cout << "You have entered " << wordsPerLine << " words per line.\n";

		//cout << "Test Print: \n";
		//int x = 0;
		//while (x < wordCount)
		//{
		//	cout << wordArray[x] << "\n";
		//	x++;
		//}

		// Sort array of strings using quick sort
		quickSort(wordArray, 0, wordCount - 1);

		// Print sorted array
		printArray(wordArray, wordCount, wordsPerLine, outputFile);
		cout << "\n";
	}

	return 0;
}

// Swap function swaps to string pointers 
// @param a is string pointer of first string
// @param a is string pointer of second string
void swap(string* a, string* b)
{
	string t = *a;
	*a = *b;
	*b = t;
}

// IgnoreCase function converts all characters in a string to lower case to compare them
// Returns 1 if pivot value is less than or equal to string
// @param array is the array passed in to be sorted
// @param low is the starting index of array
// @param high is the ending index of array
int ignoreCase(string sInput, string pivot)
{
	unsigned int length;
	unsigned int position = 0;
	char ch;
	string temp;
	length = sInput.length();

	while (position < length)
	{
		ch = tolower(sInput.at(position)); // Convert each character in string to lowercase
		temp = temp + ch; // Append converted character to string
		position++;
	}

	// If pivot value is less than or equal to string return 1
	if (pivot < temp)
	{
		return 1;
	}
	else
		return 0;
}

// Partion function chooses pivot value and returns the index of the pivot 
// Lower elems are sorted left, higher are sorted right
// @param array is the array passed in to be sorted
// @param low is the starting index of array
// @param high is the ending index of array
int partition(string array[], int low, int high)
{
	string pivot = array[high];
	int i = (low - 1);  // Smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		if (ignoreCase(array[j], pivot) != 0) // If current element is smaller than or equal to pivot element
		{
			i++; // Smaller element index increment 
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}

// Quick sort function
// @param array is the array passed in to be sorted
// @param low is the starting index of array
// @param high is the ending index of array
void quickSort(string array[], int low, int high)
{
	if (low < high)
	{
		int part = partition(array, low, high);

		// Elements before partition
		quickSort(array, low, part - 1);

		// Elements after partion
		quickSort(array, part + 1, high);
	}
}

// Print arry of strings
// @param array is the array passed in to be printed
// @param size is the size of the array
// @param wordsPerLine is the number of words the user has input to be printed per line
void printArray(string array[], int size, int wordsPerLine, string outputFileName)
{
	ofstream outfile(outputFileName);
	int i;
	for (i = size; i > 0; i--)
	{
		outfile << array[i] + ",       ";
		if (i % wordsPerLine == 0)
		{
			outfile << "\n";
		}
	}
	cout << "End of program.\n";
	outfile.close();
}

