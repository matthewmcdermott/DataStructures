#ifndef DYNAMIC_ARRAY_LIST_H_
#define DYNAMIC_ARRAY_LIST_H_

#include <iostream>
#include <cassert>

const int DEFAULT_SIZE = 1024;

template <typename T> class List;
template <typename T> std::ostream& operator<<(std::ostream&, const List<T>&);


template <class T>
class List {
   public:
      List(const int&);
      List(const List&);
      
      ~List();
      
      int getSize() const;
      int getCapacity() const;

      bool isEmpty() const;
      bool insert(const T&, const int&);
      bool remove(const int&);
      
      const List& operator=(const List& rhs);

      void display(std::ostream&) const;
      friend std::ostream& operator<< <>(std::ostream&, const List<T>&);
   private:
      T* _items; // array to store list elements
      int _capacity; // current amount of allocated memory
      int _size; // current size of the list stored in _items
};

/*****************************************************************************/
/********************** Constructors *****************************************/
/*****************************************************************************/

/**
 * Default Constructor: construct a list object
 * 
 * Precondition: capacity is a positive integer with default value of 
 *    DEFAULT_SIZE
 * Postcondition: An empty list, with size 0. The list is now a dynamically
 *    allocated array with capacity as its capacity.
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
List<T>::List(const int& capacity=DEFAULT_SIZE) {
   _capacity = capacity;
   _items = new(std::nothrow) T[_capacity];
   _size = 0;
   
   assert(_items != 0);
}

/**
 * Construct a copy of a List object.
 * 
 * Precondition: A copy of originalList is needed. originalList is a const
 *    reference parameter
 * Postcondition: A copy of originalList has been constructed.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
List<T>::List(const List& originalList) {
   _capacity = originalList._capacity;
   _size = originalList._size;
   
   _items = new(std::nothrow) T[_capacity];
   
   assert(_items != 0);
   
   for (int i=0; i<_size; ++i) {
      _items[i] = originalList._items[i];
   }
}

/*****************************************************************************/
/********************** Destruction ******************************************/
/*****************************************************************************/

/**
 * Destroy a list object
 * 
 * Precondition: The life of the object is over.
 * Postcondition: The memory dynamically allocated by the constructor for the
 *    array pointed to by _items has been returned to the heap.
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
List<T>::~List() {
   delete [] _items;
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
   return _capacity;
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
   if (position<0 || position>_size) {
      return false;
   }
   
   if (_size == _capacity) {
      T * copiedItems = new T[_capacity*2];
      for (int i=0; i<_capacity; ++i) {
         copiedItems[i] = _items[i];
      }
      
      delete [] _items;
      
      _items = copiedItems;
      _capacity *= 2;
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
/********************** Operators ********************************************/
/*****************************************************************************/

/**
 * Assign a copy of a list object to the current object
 * 
 * Preconditions: N/A
 * Postconditions: A copy of rhs has been assigned to this object. A const
 *    reference to this list is returned.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
const List<T>& List<T>::operator=(const List& rhs) {
   // verify this is not a self-assignment
   if (this == &rhs) { 
      return *this;
   }
   
   // allocate a new array, if necessary
   if (_capacity != rhs._capacity) {
      delete [] _items;
      
      _capacity = rhs._capacity;
      
      _items = new(std::nothrow) T[_capacity];
      
      assert(_items != 0);
   }
   
   // copy rhs's elements into the new array
   _size = rhs._size;
   for (int i=0; i<_size; ++i) {
      _items[i] = rhs._items[i];
   }
   
   return *this;
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
 * Postcondition: The list represented by the list object has been inserted into
 *    out
 * 
 * Worst-Case Time Comlexity: O(n)
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) {
   list.display(out);
   
   return out;
}

#endif /*DYNAMIC_ARRAY_LIST_H_*/
