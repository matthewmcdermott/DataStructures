#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "magicSquare.h"

using namespace std;

const string OUTPUT_FILE_NAME = "output.txt";
const string INPUT_FILE_NAME = "input.txt";

const int FIRST_TEST_SIZE = 7;
const int LAST_TEST_SIZE = 25;

void magicSquareTestAndOutput(const MagicSquare&, ofstream&);
void magicSquareTestWithRotateAndOutput(const MagicSquare&, ofstream&);

int main() {
   
   // open the output file stream
   ofstream out;
   out.open(OUTPUT_FILE_NAME.c_str());
   if (out.fail()) {
      cout << "failed to open " << OUTPUT_FILE_NAME << endl;
      return 1;
   }
   
   // generate a magic square using the default constructor
   MagicSquare defaultMagicSquare;
   magicSquareTestAndOutput(defaultMagicSquare, out);
   
   // generate and test magic squares using the parameterize constructor
   for (int i=FIRST_TEST_SIZE; i<=LAST_TEST_SIZE; i=i+2) {
      MagicSquare magicSquare(i);
      magicSquareTestWithRotateAndOutput(magicSquare, out);
   }
   
   // close the output file stream
   out.close();
   
   // open the input file stream
   ifstream in;
   in.open(INPUT_FILE_NAME.c_str());
   if (in.fail()) {
      cout << "failed to open " << INPUT_FILE_NAME << endl;
      return 1;
   }
   
   // read and test the input file
   int numInstances;
   in >> numInstances;
   
   // object to hold each magic square
   MagicSquare inputMagicSquare;
   
   // test each instance from the input file
   for (int i=0; i<numInstances; ++i) {
      in >> inputMagicSquare;
      
      cout << i << ": ";
      if (inputMagicSquare.isMagicSquare()) {
         cout << "is valid" << endl;
      } else {
         cout << "is not valid" << endl;
      }
   }
   
   // close the input file stream
   in.close();
   
   return 0;
}

void magicSquareTestAndOutput(const MagicSquare& magicSquare, ofstream& out) {
   if (magicSquare.isMagicSquare()) {
      out << magicSquare << endl;
   }
}

void magicSquareTestWithRotateAndOutput(const MagicSquare& magicSquare,
                                        ofstream& out) {
   magicSquareTestAndOutput(magicSquare, out);
   
   MagicSquare rotatedSquare = magicSquare.rotate();
   
   magicSquareTestAndOutput(rotatedSquare, out);
}
