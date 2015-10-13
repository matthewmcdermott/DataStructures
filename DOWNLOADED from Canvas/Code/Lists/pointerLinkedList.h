#ifndef POINTER_LINKED_LIST_H_
#define POINTER_LINKED_LIST_H_

#include <iostream>

template <typename T> class List;
template <typename T> std::ostream& operator<<(std::ostream&, const List<T>&);

template <class T>
class List {
   private:
      class Node {
         public:            
            T data;
            Node * next;
      };
   public:
      List();
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
      Node * _first; // pointer to the first element of the linked list
      int _size; // the number of elements stored in the linked list
      
      bool copyList(Node *, Node * &);
      bool deleteList(Node *);
};

/*****************************************************************************/
/********************** Constructors *****************************************/
/*****************************************************************************/

/**
 * Default Constructor: construct a list object
 * 
 * Precondition: N/A
 * Postcondition: An empty list, with size 0, is created.
 * 
 * Worst-Case Time Complexity: O(1)
 */
template <class T>
List<T>::List() {
   _first = 0;
   _size = 0;
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
   // initialize an empty list
   _first = 0;
   _size = originalList._size;
   
   // copy the original list
   copyList(originalList._first, _first);
}

/*****************************************************************************/
/********************** Destruction ******************************************/
/*****************************************************************************/

/**
 * Destroy a list object
 * 
 * Precondition: The life of the object is over.
 * Postcondition: The memory dynamically allocated by the linked list has been
 *    returned to the heap.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
List<T>::~List() {
   deleteList(_first);
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
   // verify that this is an acceptable position
   if (position<0 || position>_size) {
      return false;
   }
   
   // create a new node with the specified data
   Node * newNode = new Node;
   newNode->data = item;
   newNode->next = 0;
   
   // if this is the new head, then update _first
   if (position==0) {
      if (_first==0) {
         _first = newNode;
      } else {
         newNode->next=_first;
         _first = newNode;
      }
   } else {
      // go to the appropriate position in the linked list to insert the item
      Node * predPtr = _first;
      for (int i=1; i<position; ++i) {
         predPtr = predPtr->next;
      }
      
      // insert the new element
      newNode->next = predPtr->next;
      predPtr->next = newNode;
   }
   
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
      Node * ptr = _first;
      _first = _first->next;
      delete ptr;
   } else {
   
      // go to the appropriate position in the linked list to delete the item
      Node * ptr = _first;
      Node * predPtr;
      for (int i=0; i<position; ++i) {
         predPtr = ptr;
         ptr = ptr->next;
      }
      
      // bypass the item to be deleted
      predPtr->next = ptr->next;
      
      // free the memory for the item to be deleted
      delete ptr;
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
   
   _size = rhs._size;
   
   // copy rhs's elements into a new list
   copyList(rhs->_first,_first);
   
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
   Node * ptr = _first;
   while (ptr != 0) {
      out << ptr->data << " ";
      ptr=ptr->next;
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
 * Copy a linked list
 * 
 * Precondition: originalList is the list to be copied
 * Postcondition: copiedList points to a copy of originalList
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
bool List<T>::copyList(Node * originalListFirst, Node * &copiedListFirst) {
   // if the original list is empty, then simply delete the anything held in
   // the copied list
   if (originalListFirst == 0) {
      deleteList(copiedListFirst);
      return true;
   }
   
   // if there is already a list held where the copied list should go, then 
   // delete that list
   deleteList(copiedListFirst);
   
   // copy the data from the first node
   copiedListFirst = new Node;
   copiedListFirst->data = originalListFirst->data;
   copiedListFirst->next = 0;
   
   // create a pointer to the current location in each list
   Node * originalPtr = originalListFirst;
   Node * copiedPtr = copiedListFirst;
   
   // copy the data in the remaining nodes
   while (originalPtr->next!=0) {
      copiedPtr->next = new Node;
      originalPtr = originalPtr->next;
      copiedPtr = copiedPtr->next;
      
      copiedPtr->data = originalPtr->data;
      copiedPtr->next = 0;
   }
   
   copiedPtr->next = 0;
   
   return true;
}

/**
 * Delete a linked list
 * 
 * Precondition: The life of the linked list is over
 * Postcondition: The memory dynamically allocated by each node of the linked
 *    list is returned to the heap.
 * 
 * Worst-Case Time Complexity: O(n)
 */
template <class T>
bool List<T>::deleteList(Node * firstPtr) {
   if (firstPtr == 0) {
      return true;
   }
   
   Node * ptr = firstPtr;
   
   while (ptr != 0) {
      Node * tempPtr = ptr;
      ptr = ptr->next;
      delete tempPtr;
   }
   
   firstPtr = 0;
   
   return true;
}

#endif /*POINTER_LINKED_LIST_H_*/