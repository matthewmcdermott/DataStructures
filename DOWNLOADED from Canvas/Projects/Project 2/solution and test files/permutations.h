#ifndef PERMUTATIONS_H_
#define PERMUTATIONS_H_

#include <iostream>
#include <cstdlib>
#include <cassert>

// function prototypes
template <class T> void outputArray(T*, const int&, std::ostream&);
long factorial(const int&);
template <class T> void outputPermutations(T*, const int&, std::ostream&);
template <class T> void outputPermutations(T*, const int&, T*, const int&, 
                                           int&, std::ostream&);

/**
 * A recursive function to compute n!
 * 
 * Precondition: n is a positive integer
 * Postcondition: n! is returned
 * 
 * Worst-Case Time Complexity: O(n!)
 */
long factorial(const int& n) {
   // verify that n is a positive integer
   if (n<1) {
      return -1;
   }
   
   // base case
   if (n==1) {
      return 1;
   }
   
   // recursive step
   return n*factorial(n-1);
}

/**
 * A function to output all permutations of an array.
 * 
 * Precondition: items is an array, of type T, with size items. 
 *    The ostream, out, is open
 * Postcondition: All permutations have been output to out.
 * 
 * Worst-Case Time Complexity: O(n!)
 * Worst-Case Space Complexity: O(n^2)
 */
template <class T>
void outputPermutations(T* items, const int& size, std::ostream& out) {
   // allocate space to the permutations array
   T* result = new T[1];
   
   // put the first element into the array
   result[0] = items[0];

   // this variable will keep track of the total number of permutations that
   // the recursive function outputs
   int count=0;
   
   // a recursive function to output all arrays
   outputPermutations(items, size, result, 1, count,out);
   
   // verify that all n! permutations were output
   int expected = factorial(size);
   assert(count==expected);

   // free the memory used by the dynamically allocated array
   delete [] result;
}

/**
 * A helper function for outputing all permtuations of an array
 * 
 * Precondition: items is an array, of type T, with size items - this is the
 *    array that we are outputing permutations of. T* result is a partial 
 *    solution with the first resultSize items already in it.
 *    outputCount is a reference variable that we use to count the total 
 *    number of permutations that have been output.
 *    The ostream, out, is open
 * Postcondition: All permutations have been output to out.
 * 
 * Worst-Case Time Complexity: O(n!)
 * Worst-Case Space Complexity: O(n^2)
 */
template <class T>
void outputPermutations(T* items, 
                        const int& size, 
                        T* result, 
                        const int& resultSize,
                        int& outputCount,
                        std::ostream& out) {
   
   // base case
   if (resultSize==size) {
      outputArray(result, resultSize, out);
      ++outputCount;
      return;
   }
   
   // for each possible insert position in the results array
   for (int insertPosition=0; insertPosition<=resultSize; ++insertPosition) {
      
      // allocate space for the larger array
      T* nextResult = new T[resultSize+1];
      
      // put the items in the larger array
      for (int j=0; j<resultSize+1; ++j) {
         if (j<insertPosition) { // before the insertion position
            nextResult[j]=result[j];
         } else if (j==insertPosition) { // at the insertion position
            nextResult[j]=items[resultSize];
         } else { // after the insertion position
            nextResult[j]=result[j-1];
         }
      }
      
      // make a recursive call on this larger array
      outputPermutations(items,size,nextResult,resultSize+1,outputCount,out);
      
      // free the allocated memory
      delete [] nextResult;
   }
}

/**
 * Output an array to an ostream
 * 
 * Precondition: The ostream, out, is open. items has size items in it.
 * Postcondition: Each of the items has be output to out - with one space 
 *    between each item.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
void outputArray(T* items, const int& size, std::ostream& out) {
   for (int i=0; i<size; ++i) {
      out << items[i] << " ";
   }
   out << std::endl;
}

#endif /*PERMUTATIONS_H_*/
