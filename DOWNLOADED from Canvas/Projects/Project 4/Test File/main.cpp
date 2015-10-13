#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "functions.h"

using namespace std;

void testExpressionChange();
void testRadixSort();
void testChangeBase();

string changeBase(const int&, const int&);
bool isSorted(const vector<string>& v, const int& base);
int getBaseTenValue(const string&, const int&);

template <class T> void insertionsort(vector<T>&);

const int BASE_CHANGE_NUMBER = 100;
const int SMALLEST_BASE_CHANGE = 2;
const int LARGEST_BASE_CHANGE = 16;

const int MINIMUM_MAX_DIGITS = 5;

const bool VERBOSE = false;

int main() {
   srand(time(NULL));
   
   cout << "******* Testing Change Base *********" << endl;
   testChangeBase();
   cout << "*************************************" << endl << endl;
   
   cout << "******* Testing Task 1 **************" << endl;
   testExpressionChange();
   cout << "*************************************" << endl << endl;
   
   cout << "******* Testing Task 2 **************" << endl;
   testRadixSort();
   cout << "*************************************" << endl << endl;
  
   cout << "finished" << endl;
   
   return 0;
}

void testExpressionChange() {
   string postfixExpresssions[] = {
      "ab+cd-*",
      "ab*b+cdb*+/",
      "ab/cd-+",
      "xy*zw/+t*",
      "xy+zw**t-",
      "xy-z+w-",
      "abc-*d+"
   };
   string infixExpressions[] = {
      "((a+b)*(c-d))",
      "(((a*b)+b)/(c+(d*b)))",
      "((a/b)+(c-d))",
      "(((x*y)+(z/w))*t)",
      "(((x+y)*(z*w))-t)",
      "(((x-y)+z)-w)",
      "((a*(b-c))+d)",
   };
   int numexpressions = 7;
   
   for (int i=0; i<numexpressions; ++i) {
      string expression = postfixExpresssions[i];
      string expectedResult = infixExpressions[i];
      string computedResult = getInfixExpression(expression);
     
      bool correct = (expectedResult==computedResult);
      
      cout << "Test " << i << ": ";
      if (correct) {
         cout << "Success" << endl;
      } else {
         cout << "Failure" << endl;
      }
      
      if (VERBOSE) {
         if (!correct) {
            cout << "\tERROR!!!" << endl;
            cout << "\tcomputed: " << computedResult << endl;
            cout << "\texpected: " << expectedResult << endl;
         }
      }
   }
}

void testRadixSort() {
   int numTests = 10;
   
   int minBase = 2;
   int maxBase = 30; 
   
   int minSize = 5;
   int maxSize = 10;
   
   int maxWork = 1000;
   
   for (int i=0; i<numTests; ++i) {
      // determine the base for this test
      int base = rand()%(maxBase-minBase)+minBase;
      
      // determine the instance size for this test
      int instanceSize = rand()%(maxSize-minSize)+minSize;
      
      // determine the maximum numver of allowed digits:
      int maxDigits = (maxWork)/(base+instanceSize);
      if (maxDigits < MINIMUM_MAX_DIGITS) {
         maxDigits = MINIMUM_MAX_DIGITS;
      }
      
      // determine the max allowed value for a number
      int maxValue = pow(base,maxDigits)-1;
      
      // create a vector to hold this instance
      vector<string> v;
      
      // keep track of the largest length value
      int length = 0;
      
      // create the instance
      for (int j=0; j<instanceSize; ++j) {
         // get a value
         int value = rand()%maxValue;
         
         // convert to the expected base
         string baseValue = changeBase(value, base);
         
         // is this the largest length we have seen yet?
         if (baseValue.size()>length) {
            length = baseValue.size();
         }
         
         // add the value to the instance
         v.push_back(baseValue);
      }
      
      // create a copy of the instance
      vector<string> copy = v;
      
      // sort the instance with radix sort
      radixSort(v,length,base);
      
      // verify the instance is sorted
      bool correct = isSorted(v,base);
      
      // verify that each element of original array exists in the sorted array
      if (correct) {
         // look at each element
         for (int i=0; i<instanceSize; ++i) {
            string copyElement = copy[i];
            string originalElement = v[i];
            
            // verify copy is in the original array
            // and original is in copy array
            bool isCopyFound = false;
            bool isOriginalFound = false;
           
            for (int j=0; j<instanceSize; ++j) {
               if (copyElement == v[j]) {
                  isCopyFound = true;
               }
               if (originalElement == copy[j]) {
                  isOriginalFound = true;
               }
            }
            
            if (!isCopyFound || !isOriginalFound) {
               correct = false;
               break;
            }
         }
      }

      cout << "Test " << i << ": ";
      if (correct) {
         cout << "Success" << endl;
      } else {
         cout << "Failure" << endl;
      }
      
      if (VERBOSE) {
         if (!correct) {
            cout << "\tStart = [";
            for (int i=0; i<copy.size(); ++i) {
               cout << copy[i];
               if ((i+1)<copy.size()) {
                  cout << ", ";
               }
            }
            cout << "]" << endl;
            cout << "\t  End = [";
            for (int i=0; i<v.size(); ++i) {
               cout << v[i];
               if ((i+1)<v.size()) {
                  cout << ", ";
               }
            }
            cout << "]" << endl;
         }
      }
   }
}

int getBaseTenValue(const string& number, const int& base) {
   int result = 0;
   
   int contributionFactor = 1;
   
   for (int i=0; i<number.size(); ++i) {
      // get the current character
      char digit = number[number.size()-i-1];
      
      // determine the value for this character
      int digitValue = 0;
      if (digit>='0' && digit<='9') {
         digitValue = 10-('9' - digit)-1;
      } else if (digit>='A' && digit<='Z') {
         digitValue = 26-('Z' - digit)-1+10;
      }
      
      // determine the amount this value contributed to the overall number
      int contribution = digitValue*contributionFactor;
      
      // add this to the result
      result += contribution;
      
      // increase the contribution factor
      contributionFactor *= base;
   }
   
   return result;
}

bool isSorted(const vector<string>& v, const int& base) {
   for (int i=1; i<v.size(); ++i) {
      int left = getBaseTenValue(v[i-1],base);
      int right = getBaseTenValue(v[i],base);
     
      if (left>right) {
         if (VERBOSE) {
            cout << left << " > " << right << endl;
            cout << v[i-1] << " > " << v[i] << endl;
         }
         return false;
      }
   }
   
   return true;
}

void testChangeBase() {
   for (int i=SMALLEST_BASE_CHANGE; i<=LARGEST_BASE_CHANGE; ++i) {
      
      string changedBase = changeBase(BASE_CHANGE_NUMBER, i);
      int valueResult = getBaseTenValue(changedBase, i);
      
      if (VERBOSE) {
         cout << BASE_CHANGE_NUMBER << " in base " << i;
         cout << " is " << changedBase;
         cout << " and has base-10 value of " << valueResult << endl;
      } else {
         cout << "Test " << i << ": ";
         if (BASE_CHANGE_NUMBER==valueResult) {
            cout << "Success" << endl;
         } else {
            cout << "Failure" << endl;
         }
      }
   }
}

string changeBase(const int& number, const int& base) {
   
   if (number==0) {
      return "0";
   }
   
   stack<char> remainders;
   
   int value = number;
   
   while(value>0) {
      int remainder = value%base;
      
      char remainderCharacter;
      if (remainder<10) {
         remainderCharacter = '0' + remainder;
      } else {
         remainderCharacter = 'A' + (remainder-10);
      }
      
      remainders.push(remainderCharacter);
      value = value/base;
   }
   
   string result = "";
   while (!remainders.empty()) {
      result.push_back(remainders.top());
      remainders.pop();
   }
   
   return result;
}

template <class T>
void insertionsort(vector<T>& items) {
   for (int i=1; i<items.size(); ++i) {
      int j=i;
      T temp = items[i];
      while (j>0 && temp < items[j-1]) {
         items[j]=items[j-1];
         --j;
      }
      items[j] = temp;
   }
}