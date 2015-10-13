#include "magicSquare.h"

#include <iostream>
#include <cassert>

using namespace std;

/**
 * The following constants are used to set default values
 */
const int DEFAULT_SIZE = 5;
const int INVALID_VALUE = -1;

/**
 * The default constructor
 * 
 * Preconditions: n/a
 * Postconditions: creates a magic square object with n=5.
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
MagicSquare::MagicSquare() {
   _size = DEFAULT_SIZE;
   generateMagicSquare();
}

/**
 * A constructor which creates a magic square of the given size
 * 
 * Preconditions: size is a positive, odd integer
 * Postconditions: creates a magic square object of the indicated size
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
MagicSquare::MagicSquare(const int& size) {
   _size = size;
   generateMagicSquare();
}

/**
 * A constructor which creates a magic square from the input matrix
 * 
 * Preconditions: matrix is an nxn magic square matrix. n is a postive integer
 * which denotes the size of the matrix
 * Postconditions: creates a magic square object using the input matrix.
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
MagicSquare::MagicSquare(int** square, const int& n) {
   _size = n;
   
   _square = new int*[_size];
   for (int i=0; i<_size; ++i) {
      _square[i] = new int[_size];
      for (int j=0; j<_size; ++j) {
         _square[i][j] = square[i][j];
      }
   }
}

/**
 * Construct a copy of a MagicSquare object.
 * 
 * Precondition: A copy of originalSquare is needed. originalSquare is a const
 *   reference paramenter
 * Postcondition: A copy of originalSquare has been constructed.
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
MagicSquare::MagicSquare(const MagicSquare& originalSquare) {
   _size = originalSquare._size;
   
   _square = new int*[_size];
   for (int i=0; i<_size; ++i) {
      _square[i] = new int[_size];
      for (int j=0; j<_size; ++j) {
         _square[i][j] = originalSquare._square[i][j];
      }
   }
}

/**
 * A destructor to free memory used by a magic square object
 * 
 * Preconditions: the life of the MagicSquare object is over
 * Postcondition: the memory dynamically allocated by the constructor for the
 *    matrix pointed to by the MagicSquare has been returned to the heap
 * 
 * Worst-Case Time Complexity: O(n)
 */
MagicSquare::~MagicSquare() {
   for (int i=0; i<_size; ++i) {
      delete [] _square[i];
   }
   
   delete [] _square;
}

/**
 * Return a copy of the magic square matrix.
 * 
 * Note this function is only included to help me make test cases and it would
 * not be included with any production release of the magic square class.
 * 
 * Precondition: N/A
 * Postcondition: Return a copy of the magic square matrix
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
int** MagicSquare::getMagicSquare() const {
   int** result = new int*[_size];
   
   for (int i=0; i<_size; ++i) {
      result[i] = new int[_size];
      for (int j=0; j<_size; ++j) {
         result[i][j] = _square[i][j];
      }
   }
   
   return result;
}

/**
 * Get the size of this magic square object
 * 
 * Precondition: N/A
 * Postcondition: Returns the size of the matrix
 * 
 * Worst-Case Time Complexity: O(1)
 */
int MagicSquare::getSize() const {
   return _size;
}

/**
 * Generate the magic square object
 * 
 * Precondition: _size is a postive odd integer
 * Postcondition: This object now has an nxn magic square matrix
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
void MagicSquare::generateMagicSquare() {
   // verify that we can generate the requested magic square
   assert(_size>0);
   
   if (_size%2==0) {
      return;
   }
   
   // allocate space and initialize the magic square
   _square = new int*[_size];
   for (int i=0; i<_size; ++i) {
      _square[i] = new int[_size];
      for (int j=0; j<_size; ++j) {
         _square[i][j] = INVALID_VALUE;
      }
   }
   
   // get the location of the first integer
   int row = 0;
   int col = _size/2;
   // set the first integer
   _square[row][col]=1;
   
   // set the remaining integers
   for (int i=2; i<=(_size*_size); ++i) {
      int prevRow = row;
      int prevCol = col;
      
      if (row==0 && col==_size-1) {
         ++row;
      } else {
         --row;
         ++col;
         
         if (row < 0) {
            row = _size-1;
         } 
         
         if (col>=_size) {
            col = 0;
         }
      }
      
      // if the new location is already taken, then adjust accordingingly
      if (_square[row][col]!=INVALID_VALUE) {
         row = prevRow+1;
         col = prevCol;
      }
      while(_square[row][col]!=INVALID_VALUE) {
         ++row;
      }
      
      _square[row][col]=i;
   }
}

/**
 * Overloaded output operator
 * 
 * Preconditions: The ostream, out, is open. m is a valid magic square object.
 * Postconditions: the magic square is output with the size on a single line
 *   and then the nxn matrix on the next n lines where each line contains n
 *   integers seperated by one space each
 * 
 * Worst-Case Time Complexity: O(n^2)
 */
ostream& operator<<(ostream& out, const MagicSquare& m) {
   out << m._size << endl;
   for (int i=0; i<m._size; ++i) {
      for (int j=0; j<m._size; ++j) {
         out << m._square[i][j] << " ";
      }
      out << endl;
   }
   
   return out;
}

/**
 * Overloaded output operator
 * 
 * Preconditions: The istream, in, is open and it contains a
 *   Magic Square object where the first integer is the size of the magic
 *   square (on a line by itself). Each of the next n lines contain n
 *   integers, seperated by one space each (representing the nxn matrix).
 * Postconditions: m holds the magic square from the input stream
 * 
 * Worst-Case Time Complexity: O(n^2)
 */
istream& operator>>(istream& in, MagicSquare& m) {
   in >> m._size;
   
   // allocate space for the magic square and input each integer
   m._square = new int*[m._size];
   for (int i=0; i<m._size; ++i) {
      m._square[i] = new int[m._size];
      for (int j=0; j<m._size; ++j) {
         in >> m._square[i][j];
      }
   }
   
   return in;
}

/**
 * Assign a copy of a magic square object to the current object
 * 
 * Precondition: N/A
 * Postcondition: A copy of rhs has been assigned to this object. A const
 *    reference to this list is returned.
 * 
 * Worst-Case Time Complexity: O(n^2)
 * Worst-Case Space Complexity: O(n^2)
 */
const MagicSquare& MagicSquare::operator=(const MagicSquare& rhs) {
   // verify that this is not a self-assignment
   if (this == &rhs) {
      return *this;
   }
   
   // allocate a new array, if necessary
   if (_size != rhs._size) {
      for (int i=0; i<_size; ++i) {
         delete [] _square[i];
      }
      delete [] _square;
      
      _size = rhs._size;
      
      _square = new int*[_size];
      for (int i=0; i<_size; ++i) {
         _square[i] = new int[_size];
      }
   }
   
   for (int i=0; i<_size; ++i) {
      for (int j=0; j<_size; ++j) {
         _square[i][j] = rhs._square[i][j];
      }
   }
   
   return *this;
}

/**
 * Determine whether the object holds a valid magic square
 * 
 * Precondition: this object is not null
 * Postcondition: return true if the object is a magic square and false 
 *    otherwise
 * 
 * Worst-Case Time Complexity: O(n^2)
 */
bool MagicSquare::isMagicSquare() const {
   int sizeSquared = _size*_size;

   // verify each number appears exactly one time
   bool* appears = new bool[sizeSquared+1];
   for (int i=0; i<=sizeSquared; ++i) {
      appears[i] = false;
   }
   for (int i=0; i<_size; ++i) {
      for (int j=0; j<_size; ++j) {
         int value = _square[i][j];
         if (value<1 || value>sizeSquared) {
            return false;
         }
         if (appears[value]) {
            return false;
         }
         appears[value] = true;
      }
   }
   for (int i=1; i<=sizeSquared; ++i) {
      if (!appears[i]) {
         return false;
      }
   }
   delete [] appears;
   
   // verify all the sums are the same
   int expectedSum = 0;
   for (int i=0; i<_size; ++i) {
      expectedSum += _square[i][0];
   }
  
   int sumDiag1 = 0;
   int sumDiag2 = 0;
   for (int i=0; i<_size; ++i) {
      int sumRow = 0;
      int sumCol = 0;
      for (int j=0; j<_size; ++j) {
         sumRow += _square[i][j];
         sumCol += _square[j][i];
      }
      
      if (sumRow!=expectedSum) {
         return false;
      }
      
      if (sumCol!=expectedSum) {
         return false;
      }
      
      sumDiag1 += _square[i][i];
      sumDiag2 += _square[_size-1-i][i];
   }
   
   if (sumDiag1!=expectedSum) {
      return false;
   }
   
   if (sumDiag2!=expectedSum) {
      return false;
   }
   
   return true;  
}

/**
 * Create a new magic square that is this magic square rotated by 90^0
 * 
 * Precondition: this is a magic square object
 * Postcondition: a new magic square object representing this magic square
 *    object rotated by 90^0
 * 
 * Worst-Case Time Complexity: O(n^2)
 */
MagicSquare MagicSquare::rotate() const {
   // allocate space for the new magic square
   int** resultSquare = new int*[_size];
   for (int i=0; i<_size; ++i) {
      resultSquare[i] = new int[_size];
   }
   
   // copy the rotated square   
   for (int i=0; i<_size; ++i) {
      for (int j=0; j<_size; ++j) {
         int newI = j;
         int newJ = _size-i-1;
         resultSquare[newI][newJ] = _square[i][j];
      }
   }
   
   return MagicSquare(resultSquare,_size);
}
