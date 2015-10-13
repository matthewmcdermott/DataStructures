#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#include <ostream>

/**
 * The MagicSquare class is used to hold a Magic Square object.
 * 
 * A Magic Square is an nxn marix in which each of the integers 1,2,3,...,n^2
 * appears exactly once. All column sums, row sums, and diagonal sums are equal.
 * 
 * This class can create a magic square for any odd integer n.
 * This class can hold any magic square and can determine if is a valid 
 * magic square.
 */
class MagicSquare{
   public:
      MagicSquare();
      MagicSquare(const int&);
      MagicSquare(int**, const int&);
      MagicSquare(const MagicSquare&);
      
      ~MagicSquare();
      
      int** getMagicSquare() const;
      int getSize() const;
      
      friend std::ostream& operator<<(std::ostream&, const MagicSquare&);
      friend std::istream& operator>>(std::istream&, MagicSquare&);
      
      const MagicSquare& operator=(const MagicSquare&);
      
      bool isMagicSquare() const;
      
      MagicSquare rotate() const;
   private:
      int _size;
      int** _square;
      
      void generateMagicSquare();
};

#endif /*MAGIC_SQUARE_H*/
