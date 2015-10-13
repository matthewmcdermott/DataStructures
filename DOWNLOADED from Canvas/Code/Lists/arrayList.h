#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <iostream>

const int CAPACITY = 1024;

template <typename T> class List;
template <typename T> std::ostream& operator<<(std::ostream&, const List<T>&);

template <class T>
class List {
   public:
      List();
      
      int getSize() const;
      int getCapacity() const;

      bool isEmpty() const;
      bool insert(const T&, const int&);
      bool remove(const int&);

      void display(std::ostream&) const;
      friend std::ostream& operator<< <>(std::ostream&, const List<T>&);
   private:
      T _items[CAPACITY]; // array to store list elements
      int _size; // current size of the list stored in _items
};

/*****************************************************************************/
/********************** Constructors *****************************************/
/*****************************************************************************/

/**
 * Default Constructor
 * 
 * Precondition: N/A
 * Postcondition: An empty list, with size indicated as 0
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
List<T>::List() {
   _size = 0;
}

/*****************************************************************************/
/********************** Accessors ********************************************/
/*****************************************************************************/

/**
 * Get the size of a list object
 * 
 * Precondition: N/A
 * Postcondition: The number of elements held in the list is returned.
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
int List<T>::getSize() const {
   return _size;
}

/**
 * Get the capacity of a list object.
 * 
 * Precondition: N/A
 * Postcondition: The capacity of the list is returned
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
int List<T>::getCapacity() const {
   return CAPACITY;
}

/**
 * Check if a list is empty
 * 
 * Precondition: N/A
 * Postcondition: Return true if list is empty and false otherwise
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
bool List<T>::isEmpty() const {
   return _size==0;
}

/*****************************************************************************/
/********************** Functions ********************************************/
/*****************************************************************************/

/**
 * Insert an item into the list at the specified position
 * 
 * Preconditions: item is the value to be inserted; there is room in the array;
 *    0 <= position <= size
 * Postcondition: item is inserted into the list at the specified position.
 * 
 * Worst-case Time Complexity: O(n)
 */
template <class T>
bool List<T>::insert(const T& item, const int& position) {
   if (_size == CAPACITY) {
      return false;
   }
   
   if (position<0 || position>_size) {
      return false;
   }
   
   // shift elements to the right to make space for the new element
   for (int i=_size; i>position; --i) {
      _items[i] = _items[i-1];
   }
   
   // put the new element in the correct position
   _items[position]=item;
   
   // increment the size of the current list
   ++_size;
   
   return true;
}

/**
 * Remove the item at the specified position
 * 
 * Preconditions: The list is not empty and 0 <= position < size
 * Postconditions: element at the specified position has been removed.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
bool List<T>::remove(const int& position) {
   // verify we can delete an element
   if (_size==0) {
      return false;
   }
   
   // verify this is a valid item to delete
   if (position<0 || position>=_size) {
      return false;
   }
   
   // shift the array left
   for (int i=position; i<_size; ++i) {
      _items[i]=_items[i+1];
   }
   
   --_size;
   
   return true;
}

/*****************************************************************************/
/********************** Input/Output *****************************************/
/*****************************************************************************/

/**
 * Output the list
 * 
 * Precondition: The ostream, out, is open.
 * Postcondition: The list represented by this List object has been inserted
 *    into out.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
void List<T>::display(std::ostream& out) const {
   for (int i=0; i<_size; ++i) {
      out << _items[i];
      if (i+1<_size) {
         out << " ";
      }
   }
}

/**
 * Output operator for a list object
 * 
 * Precondition: The ostream, out, is open
 * Postcondition: The list represented by the list object has been inserted 
 *    into out
 * 
 * Worst-Case Time Comlexity: O(n)
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) {
   list.display(out);
   
   return out;
}

#endif /*ARRAY_LIST_H_*/
