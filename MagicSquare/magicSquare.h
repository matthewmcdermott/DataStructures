//  magicSquare.h
//  Written by Matthew McDermott U70910297
//  This file contains the declarations for the
//  magicSquare class that are defined in "magicSquare.cpp"

#ifndef MAGICSQUARE_H
#define MAGICSQUARE_H

class MagicSquare
{
public:
	MagicSquare();
	MagicSquare(const int& n);
	bool isMagicSquare();
	MagicSquare rotate();
	void printSq();
	void setN(int);
	int square[100][100];
	

	//overloaded functions
	friend std::ostream& operator<< (std::ostream&, MagicSquare&);
	friend std::istream& operator>> (std::istream&, MagicSquare&);

private:
	int n;
	void generateMagicSquare();
};



#endif
