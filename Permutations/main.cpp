// main.cpp    
// Written by Matthew McDermott U70910297
// This is the main file to test permutations.h
// and demonstrate finding all permutations of an array recursively.

#include <iostream>
#include "permutations.h"

using namespace std;

int main()
{
	//test with an array of chars
	char charItems[] = "Matthew";
	int charSize = 7;

	outputPermutations(charItems, charSize, cout);

	//test with an array of ints
	int intItems[] = { 1, 2, 3, 4,5 };
	int intSize = 5;

	outputPermutations(intItems, intSize, cout);

	//test with an array of doubles
	double dblItems[] = { 1.55, 3.65, 1265.6543, 0.31415 };
	int dblSize = 4;

	outputPermutations(dblItems, dblSize, cout);

	return 0;
}
