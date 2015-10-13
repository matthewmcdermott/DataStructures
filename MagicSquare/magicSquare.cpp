//	magicSquare.cpp
//	Created my Matt MCDermott U70910297
//	Contains the definitions for functions and data members
//	of the class magicSquare as previously declared in
// 	 "magicSquare.h".

#include <iostream>
#include "magicSquare.h"
using std::ostream;
using std::cout;
using std::endl;
using std::istream;

//default constructor, 5x5
MagicSquare::MagicSquare()
{
   setN(5);
   generateMagicSquare();
}

//constructor with n parameters, size nxn
MagicSquare::MagicSquare(const int& n) 
{
	setN(n);
	generateMagicSquare();
}

//function to print magic squares with odd integer
void MagicSquare::printSq() 
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << square[i][j] << "  ";
			if (j >= n-1)
			{
				cout << endl;
			}
		}
	}
}

//Function to set private data member n
void MagicSquare::setN(int num)
{
	n = num;
}

//Function to generate the magic square
void MagicSquare::generateMagicSquare()
{

	//initialize all values of the square array to zero
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			square[x][y] = 0;
		}
	}
	
	int i = 0;			//declare row variable
	int j = n / 2;		//declare column variable

	for (int k = 1; k <= (n*n); ++k)
	{
		square[i][j] = k; //set first variable in top middle

		i--;  //move up a row
		j++;  //move right one column

		if (((i < 0) && (j >= n)) || (square[i][j] > 0)) //if cursor moves out of the top right or there is already a value 
		{
			i += 2;		//move down two rows
			j -= 1;	//move left one column
		}
		else if (i < 0)  //if cursor moves above the magic square
		{
			i = n - 1;
		}
		else if (j >= n)  //if cursor moves to the right of the magic square
		{
			j = 0;
		}

	}



}

//overloading operator << to output a magicSquare to ostream
ostream& operator<< (ostream& out, MagicSquare& square1)
{
	out << square1.n << endl;
	for (int i = 0; i < square1.n; i++)
	{
		for (int j = 0; j < square1.n; j++)
		{
			out << square1.square[i][j] << "  ";
			if (j >= square1.n - 1)
			{
				out << endl;
			}
		}
	}
	return out;
}

//overloading operator >> to take input from istream to a Magic Square
istream& operator>> (istream& in, MagicSquare& square1)
{
	int num;
	in >> num;
	square1.setN(num);
	for (int i = 0; i < square1.n; i++)
	{
		for (int j = 0; j < square1.n; j++)
		{
			in >> square1.square[i][j];
			
		}
	}
	return in;
}

//function to check if a given array is a magic square
bool MagicSquare::isMagicSquare()
{
	int testSum; //variable to check each sum against the first sum
	int firstSum = 0; //represents the sum expected for everything to match

	//get first row sum for comparison to other sums
	for (int j = 0; j < n; j++)
	{
		firstSum += square[0][j];
	}
	

	//test row sums
	for (int i = 0; i < n; i++)
	{
		testSum = 0;
		for (int j = 0; j < n; j++)
		{
			testSum += square[i][j];
		}
		
		if (testSum != firstSum)
		{
			return false;
		}
	}

	//test column sums
	for (int i = 0; i < n; i++)
	{
		testSum = 0;
		for (int j = 0; j < n; j++)
		{
			testSum += square[j][i];
		}
		
		if (testSum != firstSum)
		{
			return false;
		}
	}

	//check diagonal sum from top left to bottom right
	testSum = 0;
	for (int i = 0; i < n; i++)
	{
		testSum += square[i][i];
	}
	
	if (testSum != firstSum)
	{
		return false;
	}

	//check diagonal sum from top right to bottom left
	testSum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i + j) == (n - 1)) //checks if the indexes add to n-1
			{
				testSum += square[i][j];
            //Check if any value in the square is equal to zero.
				if ( square[i][j] == 0 )
				  return false;
			}
		}
	}
	
	if (testSum != firstSum)
	{
		return false;
	}

	return true;
}

//Function to rotate the magic square 90 degrees to the right.
MagicSquare MagicSquare::rotate()
{
	MagicSquare newSquare(n);
	int k = n - 1;
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			newSquare.square[j][k] = square[i][j];
		}
		k--; //Decrement k.
	}


	return newSquare;
}
