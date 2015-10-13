//   main.cpp (goes with magicSquare.cpp)
//   Written by Matthew McDermott U70910297
//	 This program creates and demonstrates the MagicSquare class
//   and its capabilities.

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "magicSquare.h"

using namespace std;

int main()
{
   //create output.txt to write output to
   ofstream outf("output.txt");
   if (!outf) //check that output.txt actually opened
   {
      cerr << "output.txt could not be opened.  Please try again." << endl;
   }

   //read from input.txt for testing MagicSquare class
   ifstream inf("input.txt");
   if (!inf) //check that input.txt actually opened 
   {
      cerr << "input.txt could not be opened.  Please try again." << endl;
   }  

   //create a magic square using input.txt
   MagicSquare inputSquare;
   int iterations = 0;
   int i = 0;
   inf >> iterations; //put first number from input.txt in iterations variable
   while (i < iterations)
   {
      inf >> inputSquare; //calls overloaded insertion operator


      if (inputSquare.isMagicSquare() == true)
      {
         cout << i << ": is valid" << endl;
      }
      else 
      {
         cout << i << ": is not valid" << endl;
      }
	  i++;
		
   }
	

   //create a magic square object using the default constructor
   MagicSquare defaultSquare;
   //if it is a magic square, print to output.txt
   if (defaultSquare.isMagicSquare() == true) 
   {
      outf << "Default Square: " << endl;
      outf << defaultSquare << endl;
      outf << endl; //blank line
   }

   //create magic squares of sizes 7-25, odd only
   for (int i = 7; i <= 25; i++) 
   {
      MagicSquare square1(i), rotatedSquare(i);
      //if each square is a magic square, print to output.txt
      if (square1.isMagicSquare() == true) 
      {
         outf << "Square " << i << "x" << i << ": " << endl;
         outf << square1 << endl;
         outf << endl; //blank line

         rotatedSquare = square1.rotate();  
         //if the rotated square is a magic square, print to output.txt
         if (rotatedSquare.isMagicSquare() == true) 
         {
            outf << "Rotated Square " << i << "x" << i << ": " << endl;
	    outf << rotatedSquare << endl;
	    outf << endl; //blank line
	 }
         else
	 {
	    rotatedSquare.printSq();
	 }
      }
   }

   return 0;
}
