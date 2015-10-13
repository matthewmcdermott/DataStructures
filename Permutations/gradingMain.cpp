#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cassert>

#include "permutations.h"

using namespace std;

const string START = "start";
const string END = "end";
const string INPUT_FILE_NAME = "input.txt";
const string OUTPUT_FILE_NAME = "output.txt";

const int TEST_ARRAY_SIZE=5;
int INTEGER_ARRAY[] = {99,21,42,74,20};
double DOUBLE_ARRAY[] = {5.6,1.2,7.8,3.4,9.11};
string STRING_ARRAY[] = {"aaa","ddd","bbb","eee","ccc"};


// testing function prototypes
void testOutputArrayFunction(ostream&);
void testFactorialFunction();
void testOutputPermutations(ostream&);
template <class T> 
void individualOutputPermutationsTest(T*, const int&, ostream&);
long computeFactorial(const int&);

int main() {
   
   ofstream out;
   out.open(OUTPUT_FILE_NAME.c_str());
   if (out.fail()) {
      cout << "failed to open " << OUTPUT_FILE_NAME << endl;
      exit(1);
   }
  
   testOutputArrayFunction(out);
   
   testFactorialFunction();
   
   testOutputPermutations(out);

   out.close();
   
   cout << "finished" << endl;

   return 0;
}

template <class T> 
void individualOutputPermutationsTest(T* items,const int& size,ostream& out) {
   static int count = 0;
   
   out << "start test " << count << endl << endl;
   outputPermutations(items,size,out);
   out << endl;
   ++count;
   out << "end test" << endl << endl;
}

void testOutputPermutations(ostream& out) {
   int count=0;
   
   for (int i=1; i<TEST_ARRAY_SIZE; ++i) {
      if(i==3) {
         individualOutputPermutationsTest(INTEGER_ARRAY,i,cout);
         individualOutputPermutationsTest(DOUBLE_ARRAY,i,cout);
         individualOutputPermutationsTest(STRING_ARRAY,i,cout);
      } else {
         individualOutputPermutationsTest(INTEGER_ARRAY,i,out);
         individualOutputPermutationsTest(DOUBLE_ARRAY,i,out);
         individualOutputPermutationsTest(STRING_ARRAY,i,out);
      }
   }
}

void testFactorialFunction() {
   for (int i=1; i<15; ++i) {
      long myResult = computeFactorial(i);
      long studentResult = factorial(i);
      if (myResult!=studentResult) {
         cout << "FACTORIAL FUNCTION FAILED ITS TEST" << endl;
      }
   }
   
   cout << "Factorial function passed its test" << endl;
}

void testOutputArrayFunction(ostream& out) {  
   
   
   for (int i=1; i<TEST_ARRAY_SIZE; ++i) {
      if(i==1) {
         outputArray(INTEGER_ARRAY,i,cout);
         cout << endl;
         outputArray(DOUBLE_ARRAY,i,cout);
         cout << endl;
         outputArray(STRING_ARRAY,i,cout);
         cout << endl;
      } else {
         outputArray(INTEGER_ARRAY,i,out);
         out<<endl;
         outputArray(DOUBLE_ARRAY,i,out);
         out << endl;
         outputArray(STRING_ARRAY,i,out);
         out << endl;
      }
   }
}

long computeFactorial(const int& n) {
   if (n==0) {
      return 1;
   }
   
   return n*computeFactorial(n-1);
}
