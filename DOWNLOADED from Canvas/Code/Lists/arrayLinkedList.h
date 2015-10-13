#ifndef ARRAY_LINKED_LIST_H_
#define ARRAY_LINKED_LIST_H_

#include <iostream>
#include <cassert>

const int DEFAULT_SIZE = 1024;
const int NULL_VALUE = -1; // a nonexistent location

template <typename T> class List;
template <typename T> std::ostream& operator<<(std::ostream&, const List<T>&);

template <class T>
class List {
   private:
      class Node {
         public: 
            Node() { next = NULL_VALUE; };
            Node(const int& nextIndex) { next = nextIndex; };
            T data;
            int next;
      };
   public:
      List(const int&);
      List(const List&);
      
      ~List();
     
      int getSize() const;
      int getCapacity() const;
      
      bool isEmpty() const;
      bool insert(const T&, const int&);
      bool remove(const int&);
      
      const List& operator=(const List&);
      
      void display(std::ostream&) const;
      friend std::ostream& operator<< <>(std::ostream&, const List<T>&);
   private:
      Node * _items; // array to store list elements
      int _size; // the number of elements stored in the linked list
      int _capacity; // current amount of allocated memory
      
      // _first is a pointer to the first element of the linked list
      // (i.e., an index into the array)
      int _first;
      
      // _firstNewNodeIndex is a pointer to the first unused element of the
      // array that has been allocated.
      int _firstNewNodeIndex;
      
      int getNewNodeIndex();
      
      bool createCopyOfList(Node *, Node * &, const int&);
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
   _size = 0;
   _first = NULL_VALUE;
   
   _items = new(std::nothrow) Node[_capacity];
   assert(_items != 0);
   
   _firstNewNodeIndex=0;
   for (int i=0; i<_capacity; ++i) {
      if (i+1<_capacity) {
         _items[i] = Node(i+1);
      } else {
         _items[i] = Node(NULL_VALUE);
      }
   }
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
   _size = originalList._size;
   _capacity = originalList._capacity;
   _first = originalList._first;
   _firstNewNodeIndex = originalList._firstNewNodeIndex;
   
   createCopyOfList(originalList._items, _items, originalList._capacity);
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
 * Note that this function is only provided for compatability with other list
 * implementations.
 * 
 * Precondition: N/A
 * Postcondition: -1 is returned since a pointer based linked list has no
 *    predefined capacity
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
int List<T>::getCapacity() const {
   return -1;
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
   // check if this is a valid position
   if (position<0 || position>_size) {
      return false;
   }
   
   // determine if we need to grow the array
   if (_size == _capacity) {
      Node * copiedItems = new Node[_capacity*2];
      for (int i=0; i<_capacity; ++i) {
         copiedItems[i] = _items[i];
         if (i+_capacity+1<(_capacity+1)) {
            copiedItems[i+_capacity] = Node(i+_capacity+1);
         } else {
            copiedItems[i+_capacity] = Node(NULL_VALUE);
         }
      }
      
      delete [] _items;
      
      _firstNewNodeIndex = _capacity;
      _items = copiedItems;
      _capacity *= 2;
   }
   
   // determine the location of the new node
   int newNodeIndex = getNewNodeIndex();
   _items[newNodeIndex].data = item;
   
   // if this is the new head, then update _first;
   if (position==0) {
      _items[newNodeIndex].next = _first;
      _first = newNodeIndex;
      ++_size;
      return true;
   }
   
   // go the correct position in the linked list
   int currentPosition = _first;
   int previousPosition = NULL_VALUE;
   for (int i=0; i<position; ++i) {
      previousPosition = currentPosition;
      currentPosition = _items[currentPosition].next;
   }   
   
   // update the pointers to add the new item
   _items[previousPosition].next = newNodeIndex;
   _items[newNodeIndex].next = currentPosition;
   
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
   
   // the first item is a special case
   if (position==0) {
      int firstIndex = _first;
      _first = _items[_first].next;
      _items[firstIndex].next = _firstNewNodeIndex;
      _firstNewNodeIndex = firstIndex;
   } else {
      // go the correct position in the linked list
      int currentPosition = _first;
      int previousPosition = NULL_VALUE;
      for (int i=0; i<position; ++i) {
         previousPosition = currentPosition;
         currentPosition = _items[currentPosition].next;
      }   
      
      _items[previousPosition].next = _items[currentPosition].next;
      _items[currentPosition].next = _firstNewNodeIndex;
      _firstNewNodeIndex = currentPosition;
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
   
   _capacity = rhs._capacity;
   _first = rhs._first;
   _firstNewNodeIndex = rhs._firstNewNodeIndex;
   _size = rhs._size;
   
   // copy rhs's elements into a new list
   createCopyOfList(rhs._items, _items, _capacity);
   
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
   int currentPosition = _first;
   for (int i=0; i<_size; ++i) {
      out << _items[currentPosition].data;
      if (i+1<_size) {
         out << " ";
      }
      currentPosition = _items[currentPosition].next;
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

/*****************************************************************************/
/********************** Private Functions ************************************/
/*****************************************************************************/

/**
 * Returns the index of the next new node. Repositions the pointer to the next
 * new node
 * 
 * Precondition: There are available nodes in the linked list.
 * Postcondition: An index of an available node is returned. That index is now
 *    allocated as a used node
 *
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
int List<T>::getNewNodeIndex() {
   if (_firstNewNodeIndex==NULL_VALUE) {
      return NULL_VALUE;
   }
   
   int nodeIndex = _firstNewNodeIndex;
   _firstNewNodeIndex = _items[_firstNewNodeIndex].next;
   
   return nodeIndex;
}

/**
 * Copy a linked list
 * 
 * Precondition: originalList is the list to be copied. copiedList is 
 *   where the copy should be located.
 * Postcondition: copiedList points to a copy of originalList
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
bool List<T>::createCopyOfList(Node * originalList, 
                               Node * &copiedList,
                               const int& capacity) {
   if (copiedList == 0) {
      delete [] copiedList;
   }
   
   copiedList = new Node[capacity];
   
   for (int i=0; i<capacity; ++i) {
      copiedList[i] = originalList[i];
   }
   
   return true;
}

#endif /*ARRAY_LINKED_LIST_H_*/