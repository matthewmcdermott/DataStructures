#ifndef CIRCULAR_LINKED_LIST_H_
#define CIRCULAR_LINKED_LIST_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>

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
      
      T runJospehusAlgorithm();
      
      const List& operator=(const List&);
      
      void display(std::ostream&) const;
      friend std::ostream& operator<< <>(std::ostream&, const List<T>&);
   private:
      Node * _first; // pointer to the first element of the linked list
      
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
   if (_first == 0) {
      return 0;
   }
   
   Node * ptr = _first;
   int size = 0;
   
   do {
      ptr = ptr->next;
      ++size;
   } while (ptr != _first);
   
   return size;
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
   return _first==0;
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
   if (position<0) {
      return false;
   }
   
   // create a new node with the specified data
   Node * newNode = new Node;
   newNode->data = item;
   newNode->next = 0;
   
   
   if (_first == 0) { // a single element is a special case
      
      newNode->next = newNode;
      _first = newNode;
      
   } else { // the general case
   
      // go the appropriate position in the linked list to insert the item
      Node * predPtr = _first;
      for (int i=0; i<position-1; ++i) {
         predPtr = predPtr->next;
         if (predPtr==_first) {
            return false;
         }
      }
      
      // insert the new element
      newNode->next = predPtr->next;
      predPtr->next = newNode;
   }
   
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
   if (_first==0) {
      return false;
   }
   
   // verify this is a valid item to delete
   if (position<0) {
      return false;
   }
   
   // go to the appropriate position in the linked list to delete the item
   Node * ptr = _first->next;
   Node * predPtr = _first;
   for (int i=1; i<position; ++i) {
      predPtr = ptr;
      ptr = ptr->next;
      if (predPtr==_first) {
         return false;
      }
   }
   
   // if the size is one element (i.e., the node points to itself)
   if (ptr==predPtr) {
      
      delete _first;
      _first = 0;
      
   } else {
      
      predPtr->next = ptr->next;
      delete ptr;
      
   }
   
   return true;
}

template <class T>
T List<T>::runJospehusAlgorithm() {   
   // if the list is empty return a garbage value
   if (_first == 0) {
      T garbage;
      return garbage;
   }
   
   // determine the initial size of the list
   int size = getSize();
   int remainingNodes = size;
   
   // this function should not modify the object in order to determine
   // the Josephus Item so we must make a copy of the list
   Node * copyOfList = 0;
   copyList(_first, copyOfList);
   
   Node * listStart = copyOfList;
   Node * ptr = copyOfList;
   Node * predPtr = copyOfList;
   
   // remove nodes until only one node remains
   while (remainingNodes>1) {
      int startLocation = rand()%remainingNodes;
      int numCount = rand()%(size*2);
      
      ptr = listStart;
      
      // go the the start node
      for (int i=0; i<startLocation; ++i) {
         predPtr = ptr;
         ptr = ptr->next;
      }
      
      // from the start node, iterate to the node to remove
      for (int i=0; i<numCount; ++i) {
         predPtr = ptr;
         ptr = ptr->next;
      }
      
      // check if we did not move at all - in which case we need to walk the
      // list
      if (ptr==listStart) {
         do {
            predPtr = ptr;
            ptr = ptr->next;
         } while (ptr != listStart);
         
         listStart = listStart->next;
      }
      
      // delete the specified node
      predPtr->next = ptr->next;
      delete ptr;
      
      // decrement the number of remaining nodes
      --remainingNodes;
   }
   
   T data = listStart->data;
   
   delete listStart;
   
   return data;
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
   if (_first==0) {
      return;
   }
   
   Node * ptr = _first;
   do {
      out << ptr->data << " ";
      ptr=ptr->next;
   } while (ptr != _first);
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
   // if there is already a list held where the copied list should go, then 
   // delete that list
   deleteList(copiedListFirst);
   
   // if the original list is empty, then we are done
   if (originalListFirst == 0) {
      return true;
   }
   
   // copy the data from the first node
   copiedListFirst = new Node;
   copiedListFirst->data = originalListFirst->data;
   copiedListFirst->next = 0;
   
   // create a pointer to the current location in each list
   Node * originalPtr = originalListFirst;
   Node * copiedPtr = copiedListFirst;
   
   // copy the data in the remaining nodes
   while (originalPtr->next!=originalListFirst) {
      // create the new node
      copiedPtr->next = new Node;
      
      // advance to the next node
      originalPtr = originalPtr->next;
      copiedPtr = copiedPtr->next;
   
      // copy the node data
      copiedPtr->data = originalPtr->data;
   }
   
   // the last node of the copied array should point to the first
   copiedPtr->next = copiedListFirst;
   
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
   
   Node * ptr = firstPtr->next;
   
   while (ptr != firstPtr) {
      Node * tempPtr = ptr;
      ptr = ptr->next;
      delete tempPtr;
   }
   
   delete ptr;
   
   firstPtr = 0;
   
   return true;
}

#endif /*CIRCULAR_LINKED_LIST_H_*/
