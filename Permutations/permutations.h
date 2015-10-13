// permutations.h
// Written by Matthew McDermott U70910297
// The permutations function recusively generates all n!
// permutations of a set of n elements.

#include <iostream>

using std::endl;
using std::ostream;
using std::cout;

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

//A function to output an array of type T.
template <class T>
void outputArray(T* items, const int& size, ostream& out)
{
	for (int i = 0; i < size; i++)
	{
		out << items[i] << " ";
	}
	out << endl;
}

//A function to calculate the factorial of an int.
long factorial(const int& n)
{
	if (n <= 1) return 1;

	return n*factorial(n - 1);
}

//A function to swap the value of an array with its neighbor
template <class T>
void switchValues(T* left, T* right)
{
	T temp = *left;
	*left = *right;
	*right = temp;
}

template <class T>
void permutation(T* items, int currentIndex, int size, int* number_of_permutations, ostream& out)
{
	//base case
	if (currentIndex == size)
	{
		outputArray(items, size, out);
		(*number_of_permutations)--; //decrement number of permutations
	}
	else
	{
		//Find all permutations recurisvely until the base case
		for (int i = currentIndex; i < size; i++)
		{
			switchValues(&items[currentIndex], &items[i]);

			permutation(items, currentIndex + 1, size, number_of_permutations, out);

			switchValues(&items[currentIndex], &items[i]);
		}
		
	}
}

//A function to check that all permutations were found.
bool allFound(int* number_of_permutations)
{
	if (*number_of_permutations != 0)
	{
		return false;
	}

	return true;
}

//A function to output all permutations of an array with a given size.
template <class T>
void outputPermutations(T* items, const int& size, ostream& out)
{
	int number_of_permutations = factorial(size); //used to count each printed-
	int* numPerm = &number_of_permutations;		  //permutation
	
	permutation(items, 0, size, numPerm, out);

	//Checking that all permutations were found.
	if (allFound(&number_of_permutations) == true)
	{
		out << "All permutations were found." << endl;
		out << endl;
	}
	else
	{
		out << "Some permutations are missing and were not found." << endl;
		out << endl;
	}
		
}



#endif
