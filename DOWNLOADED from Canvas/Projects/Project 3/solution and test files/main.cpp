#include <iostream>
#include <cstdlib>
#include <ctime>

#include "circularLinkedList.h"

using namespace std;

void testListClass();
void testJosephusAlgorithm();

const int LARGE_LIST_SIZE = 1024;

int main() {
   
   srand(time(NULL));
   
   testListClass();
   
   testJosephusAlgorithm();
   
   cout << "finished" << endl;
   
   return 0;
}

void testJosephusAlgorithm() {
   int testSize = 10;
   
   cout << endl << "***** Testing the Josephus Algorithm *****" << endl;
   
   // create list with integer elements
   List<int> intList;
   for (int i=0; i<testSize; ++i) {
      intList.insert(i,i);
   }
   cout << "Integer list created: " << intList << endl;
   
   // run the Josephus Algorithm testSize times
   for (int i=0; i<testSize; ++i) {
      cout << i << ": " << intList.runJospehusAlgorithm() << endl;
   }
   
   // create a list with string elements
   List<string> stringList;
   for (int i=0; i<testSize; ++i) {
      int numCharacters = rand()%testSize+1;
      string result(numCharacters, ('a'+i));
      stringList.insert(result,i);
   }
   cout << "String list created: " << stringList << endl;
   
   // run the Josephus Algorithm testSize times
   for (int i=0; i<testSize; ++i) {
      cout << i << ": " << stringList.runJospehusAlgorithm() << endl;
   }
}

void testListClass() {
   int testSize = 10;
   
   // test the constructor
   cout << "Constructing an integer list." << endl;
   List<int> intList;
   cout << endl;
   
   // test the isEmpty function. Output an empty list, if applicable
   if (intList.isEmpty()) {
      cout << "Empty List: " << intList << endl;
   }
   cout << endl;
   
   // test the insert function
   for (int i=0; i<testSize; ++i) {
      cout << "Inserting " << i << " at position " << (i/2) << ": ";
      if (intList.insert(i,i/2)) {
         cout << intList << endl;
      } else {
         cout << "insertion failed!" << endl;
      }
   }
   cout << endl;
   
   // test the = operator
   cout << "Making a copy of the integer list." << endl;
   List<int> copyList = intList;
   cout << "original list: " << intList << endl;
   cout << "copied list: " << copyList << endl;
   for (int i=0; i<testSize; ++i) {
      cout << "Inserting " << i << " at position " << (i/2) << " into ";
      int index = rand()%2;
      if (index) {
         cout << "original list: ";
         if (intList.insert(i,i/2)) {
            cout << endl;
         } else {
            cout << "insertion failed!" << endl;
         }
      } else {
         cout << "copied list: ";
         if (copyList.insert(i,i/2)) {
            cout << endl;
         } else {
            cout << "insertion failed!" << endl;
         }
      }
      cout << "\toriginal list: " << intList << endl;
      cout << "\tcopied list: " << copyList << endl;
   }
   cout << endl;
   
   // test the isEmpty function. Output yes/no as applicable
   cout << "List empty? " << (intList.isEmpty() ? "Yes" : "No") << endl << endl;
   
   // continue testing the insert function
   cout << "Try to insert at position -1: ";
   if (intList.insert(0,-1)) {
      cout << intList << endl;
   } else {
      cout << "insertion failed!" << endl;
   }
   int size = intList.getSize();
   cout << "Try to insert at position " << (size+1) << ": "; 
   if (intList.insert(-1,size+1)) {
      cout << intList << endl;
   } else {
      cout << "insertion failed!" << endl;
   }
   
   // a first test of the remove function
   cout << "Try to delete at position " << (size+1) << ": ";
   if (intList.remove(size+1)) {
      cout << intList << endl;
   } else {
      cout << "deletion failed!" << endl;
   }
   
   cout << endl;
   
   // test the remove function
   while (!intList.isEmpty()) {
      int index = rand()%intList.getSize();
      
      cout << "Removing the element at position: " << index << ": ";
      intList.remove(index);
      cout << intList << endl;
   }
   cout << "Original List is empty!" << endl;
   cout << "Copied List: " << copyList << endl;
   
   // test the insert function, up to the CAPACITY of the list
   int capacity = intList.getCapacity();
   if (capacity<0) {
      capacity = LARGE_LIST_SIZE;
   }
   cout << "Inserting " << capacity << " integers" << endl;
   for (int i=0; i<capacity; ++i) {
      intList.insert(i,i);
   }
   // one more insertion
   cout << "Attempting to insert one more integer: ";
   if (intList.insert(-1,0)) {
      cout << "insertion succeeded!" << endl;
   } else {
      cout << "insertion failed!" << endl;
   }
}
