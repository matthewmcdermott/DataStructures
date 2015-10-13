// circularLinkedList.h
// (Some functions provided by Dr. Tina Kouri)
// Contains the header information for a circular
// linked list. This linked list is implemented using a head node.

#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <iostream>

using namespace std;

template <typename T> class List;
template <typename T> ostream& operator<<(ostream&, const List<T>&);

/**
* The following constants are used to set default values
*/
const int HEAD = 0;


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
   bool copyList(Node *, Node * &);
   int getSize() const;
   int getCapacity() const;
   bool isEmpty() const;
   bool insert(const T&, const int&);
   bool remove(const int&);
   bool deleteList(Node*);
   T runJosephusAlgorithm();
   const List& operator=(const List&);
   void display(ostream&) const;
   friend ostream& operator<< <T>(ostream&, const List<T>&);
private:
   Node * _first; // pointer to the first element of the linked list 
};

/**
* Default constructor
*
* Precondition:  n/a
* Postcondition: Creates an empty singly-linked list
*/
template <class T>
List<T>::List() 
{
   Node * headNode = new Node;
   _first = headNode;
   headNode->next = _first; //head node points to itself
}

/**
* Copy Constructor
*
* Precondition: There exists a circularLinkedList object 
* Postcondition: The exisiting object is copied
*/
template <class T>
List<T>::List(const List& originalList)
{
   _first = 0; //copyList function handles creating the new head node
   
   copyList(originalList._first, _first);
}

/**
* Destructor
*
* Preconditions:  A circularLinkedList object has come to the end of its life.
* Postconditions: The memory is returned to the heap and the object is deleted.
*/
template <class T>
List<T>::~List()
{
   deleteList(_first);
}

/**
* copyList function
*
* Precondition:   A list exists and needs to be copied
* Postcondition:  copyList points to a copy of the original list
*/
template <class T>
bool List<T>::copyList(Node * originalListFirst, Node * &copiedListFirst)
{
   //check for an empty original list, then delete the copied list
   if (originalListFirst == 0)
   {
      deleteList(copiedListFirst);
      return true;
   }

   //initialize the copied List to be empty
   deleteList(copiedListFirst);

   //create a new head node for copiedList and initialize list
   Node* copiedListHeadNode = new Node;
   copiedListFirst = copiedListHeadNode;
   copiedListHeadNode->next = copiedListFirst;

   //copy the data from the original list to the copied list
   Node * originalPtr = originalListFirst;
   Node * copiedPtr = copiedListFirst;

   while (originalPtr->next != originalListFirst)
   {
      copiedPtr->next = new Node;
      originalPtr = originalPtr->next;
      copiedPtr = copiedPtr->next;

      copiedPtr->data = originalPtr->data;
      copiedPtr->next = copiedListFirst;
   }

   copiedPtr->next = copiedListFirst;
   return true;
}

/**
* deleteList function
*
* Preconditions:  There exists a list that must be deleted
* Postconditions: The list is deleted and the memory is freed.
*/
template <class T>
bool List<T>::deleteList(Node * firstPtr)
{
   if (firstPtr == 0)
      return true;

   Node * currentPtr = firstPtr;

   while (currentPtr != firstPtr)
   {
      Node * tempPtr = currentPtr;
      currentPtr = currentPtr->next;
      delete tempPtr;
   }

   firstPtr = 0;

   return true;
}


/**
* Function to check whether the circular linked list is empty
*
* Preconditions:  n/a
* Postconditions: True will be returned if the list is empty.
*                 False will be returned if the list contains data.
*/
template <class T>
bool List<T>::isEmpty() const 
{   
   if (_first->next != _first)
   {
      return false;
   }
   return true;
}

/**
* Function to calculate the size of a circular linked list
*
* Preconditions:  A circular linked list exists, but the size is unknown.
* Postconditions: the size of the linked list is returned.
*/
template <class T>
int List<T>::getSize() const 
{
   int size = 0;
   Node* ptr = _first->next;

   
   while (ptr != _first)
   {
      ptr = ptr->next;
      ++size; 
   }

   return size;
}

/**
* getCapacity function that returns a -1 capacity
*
* Preconditions:  none
* Postconditions: returns a -1 since a pointer based linked list has no
*                 predefined capacity
*/
template <class T>
int List<T>::getCapacity() const
{
   return -1;
}

/**
* Insert function to insert a node into the list
*
* Precondition:   a value needs to be inserted into the list. const
*                 parameters for data and position.
* Postcondition:  the value is inserted in a new node at the given position
*/
template <class T>
bool List<T>::insert(const T& data, const int& position) 
{
   Node * newNode = new Node;
   newNode->data = data;
   newNode->next = newNode;
   Node* predPtr = _first;

   if (position == HEAD) //checks if position is front
   {
      newNode->next = _first->next;
      _first->next = newNode;
      return true;
   }
   
   int testPosition = 0;
   for (int i = 0; i < position; ++i) //traverses to correct position
   {
      predPtr = predPtr->next;
      testPosition++;
   }
   
   //inserting node into place
   newNode->next = predPtr->next;
   predPtr->next = newNode;

   return true;
}

/**
* Remove function
*
* Preconditions:  The list is not empty and HEAD <= position < end
* Postconditions: The element at the given positions is removed
*/
template <class T>
bool List<T>::remove(const int& position)
{
   if (isEmpty() == true)
      return false;

   //check if the given position is at the head
   if (position == HEAD)
   {
      Node * currentPtr = _first->next;
      _first->next = _first->next->next;
      delete currentPtr;
      return true;
   }

   //Find the correct given position and delete it
   Node * currentPtr = _first->next;
   Node * predPtr = 0;

   for (int i = 0; i < position; ++i)
   {
      predPtr = currentPtr;
      currentPtr = currentPtr->next;
   }

   predPtr->next = currentPtr->next;
   delete currentPtr;

   return true;
}

/**
* Display Function to display the elements of the linked list in order
*
* Preconditions:  A circular linked list contains elements that must be printed
* Postconditions: The elements are displayed on screen with a space between
*/
template <class T>
void List<T>::display(ostream& out) const
{
   Node* currentPtr = _first;

   if (isEmpty() == true)
   {
      out << "This list is empty. " << endl;
   }

   currentPtr = currentPtr->next;
   while (currentPtr != _first)
   {
      out << currentPtr->data << " ";
      currentPtr = currentPtr->next;
   }
}

/**
* Overloaded Assignment operator
*
* Preconditions:  N/A
* Postconditions: A copy of the rhs has been assigned to this object.  A const
*                 reference to this list is returned
*/
template <class T>
const List<T>& List<T>::operator=(const List& rhs)
{
   if (this == &rhs)
      return *this;

   copyList(rhs._first, _first);
   return *this;
}

/**
* Overloaded output operator
*
* Preconditions:  The ostream, out, is open
* Postconditions: The list represented by the list object has been inserted
*                 into  out
*/
template <class T>
ostream& operator<<(ostream& out, const List<T>& list)
{
   list.display(out);

   return out;
}

/**
* Josephus Algorithm
*
* Preconditions:  A circular linked list exists, and we are to select one item.
* Postconditions: One item is selected and returned using Josephus Algorithm.
*/
template <class T>
T List<T>::runJosephusAlgorithm()
{
   //check for an empty list.  If empty, return a garbage value of type T
   if (isEmpty()==true)
   {
      return T();
   }

   List copiedList;  //copy the list so as not to modify the original
   copyList(_first, copiedList._first);
   Node * currentPtr = copiedList._first->next;
   int n = -1;
   int count = 0;
   int startNode = 0;
   int positionTracker = 0;

   while((copiedList.getSize())>1)
   {
      currentPtr = copiedList._first->next;
      count = 0;
      positionTracker = 0;
      n = rand()%(copiedList.getSize()*2);
      startNode = rand()%(copiedList.getSize());
      for(int i = 0; i < startNode; ++i)  //move pointer to startNode
      {
         currentPtr = currentPtr->next;
         ++positionTracker;
      }

      while(count <= n)//count up to N 
      {         
         currentPtr = currentPtr->next;
         if (currentPtr != copiedList._first)
         {
            ++positionTracker;
            ++count;
         }
      }
      
      copiedList.remove(positionTracker%(copiedList.getSize()));
   }
   return copiedList._first->next->data;
}

#endif /* CIRCULARLINKEDLIST_H */
