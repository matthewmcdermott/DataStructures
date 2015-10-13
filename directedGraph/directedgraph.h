#ifndef DIRECTEDGRAPH_H_
#define DIRECTEDGRAPH_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/**
* Universal Constants
*/
int WHITE = 1;
int GRAY = 0;
int BLACK = -1;
int ZERO = 0;

/**
* Class to hold directed graphs
*
*/
template <class T>
class DirectedGraph{

public:
   //constructors
   DirectedGraph();
   DirectedGraph(DirectedGraph&);

   //destructors
   ~DirectedGraph();

   //overloaded assignment operator
   DirectedGraph& operator=(const DirectedGraph&);

   //input and output operator overloading 
   template <class T2>
   friend std::istream& operator>>(std::istream&, DirectedGraph&);
   template <class T2>
   friend std::ostream& operator<<(std::ostream&, DirectedGraph&);

   //functions to build and display the directed graph
   void populateAdjacency();
   void displayAList(ostream&);

   //functions to access private members
   int getDegree() const;
   void setDegree(int);
   int getSquared() const;
   void setSquared(int);
   vector<vector<int> > getAdjacencyList() const;
   void setAdjacencyList(vector<vector<int> >);
   vector<T> getVertices() const;
   void setVertices(vector<T>);

   //searching and traversal functions with any helpers
   void breadthFirstSearch(ostream&) const;
   void depthFirstSearch(ostream&) const;
   void dfsVisit(const int, vector<int>&, vector<int>&) const;
   void outputCompassTranslation(vector<int>&, ostream&) const;

private:
   int graphDegree; //holds the degree of an nxn graph
   int squared; // holds the degree squared (n * n)
   vector<vector <int> > adjacencyList; //adjacency list positions
   vector<T> vertices; //values at the vertices
};

/*****************************************************************************/
/********************** Constructors *****************************************/
/*****************************************************************************/

/**
* Construct a Directed Graph Object
*
* Precondition: None
* Postcondition: An empty graph has been constructed
*
* Worst-Case Time Complexity: O(1)
*/
template<class T>
DirectedGraph<T>::DirectedGraph() {
   graphDegree = 0;
   squared = 0;

}

/**
* Copy consructor for a Directed Graph Object
*
* Precondition: Original is a Directed Graph
* Postcondition: a copy of original has been constructed
*
* Worst-Case Time Complexity: O(N)
*/

template<class T>
DirectedGraph<T>::DirectedGraph(DirectedGraph& original) {

   vertices = original.vertices;
   adjacencyList = original.adjacencyList;
   graphDegree = original.graphDegree;
   squared = graphDegree*graphDegree;
}

/*****************************************************************************/
/********************** Destructor *******************************************/
/*****************************************************************************/

/**
* Destructor for a Directed Graph
*
* Precondition: The life of the directed graph is over
* Postcondition: Memory used by the directed graph is freed
*
* Worst-Case Time Complexity: O(n)
*/
template<class T>
DirectedGraph<T>::~DirectedGraph() {
   //no dynamic memory to deallocate
}

/*****************************************************************************/
/********************** Helper Functions**************************************/
/*****************************************************************************/

/**
* Helper function to fill the adjacency list of a directed graph
*
* Precondition: vertices is filled
* Postcondition: adjacency list is populated
*
* Worst-Case Time Complexity: O(N)
*/
template<class T>
void DirectedGraph<T>::populateAdjacency(){
   int value;
   //populate first half of adjacency list "+" directions
   for (int i = 0; i < squared; ++i)
   {
      value = vertices[i];
      if (value < 0)
      {
         value *= -1;
      }

      //South
      if ((i + (graphDegree * value)) < squared){
         if (value != 0){
            adjacencyList[i].push_back(i + (graphDegree * value));
         }
      }

      //East
      if ((i / graphDegree) == ((i + value) / graphDegree))
      {
         if (value != 0){
            adjacencyList[i].push_back(i + value);
         }
      }

      //North
      if ((i - (graphDegree * value)) >= 0){
         if (value != 0){
            adjacencyList[i].push_back(i - (graphDegree * value));
         }
      }

      //West
      if ((i / graphDegree) == ((i - value) / graphDegree)
         && ((i - value) >= 0))
      {
         if (value != 0){
            adjacencyList[i].push_back(i - value);
         }
      }
   }
   //populate second half of adjacency "X" directions

   for (int j = squared; j < (2 * squared); ++j)
   {
      value = vertices[j];
      if (value < 0){
         value *= -1;
      }

      //NE
      if ((j - (graphDegree * value)) >= squared &&
         (j%graphDegree < ((j + value) % graphDegree)))
      {
         if (value != 0){
            adjacencyList[j].push_back(j + value - (value*graphDegree));
         }
      }
      //NW
      if ((j - (graphDegree * value)) >= squared &&
         (j%graphDegree >((j - value) % graphDegree)))
      {
         if (value != 0){
            adjacencyList[j].push_back(j - value - (value*graphDegree));
         }
      }
      //SE
      if ((j + (graphDegree * value)) < (2 * squared) &&
         (j%graphDegree < ((j + value) % graphDegree)))
      {
         if (value != 0){
            adjacencyList[j].push_back(j + value + (value*graphDegree));
         }
      }
      //SW
      if ((j + (graphDegree * value)) < (2 * squared) &&
         (j%graphDegree >((j - value) % graphDegree)))
      {
         if (value != 0){
            adjacencyList[j].push_back(j - value + (value*graphDegree));
         }
      }
   }
}

/**
*  output function, the only way to output a directed graph
adjacency list
*
* Precondition: myGraph is a directed graph
* Postcondition: adjacency list has been output
*
*/
template<class T>
void DirectedGraph<T>::displayAList(ostream& out)
{
   for (int i = 0; i < squared; ++i)
   {
      out << "[" << i << "] -> ";
      for (size_t j = 0; j < adjacencyList[i].size(); ++j)
      {
         out << adjacencyList[i][j] << " ";
      }
      out << endl;
   }
   out << endl;

   for (int i = squared; i < (2 * squared); ++i)
   {
      out << "[" << i << "] -> ";
      for (size_t j = 0; j < adjacencyList[i].size(); ++j)
      {
         out << adjacencyList[i][j] << " ";
      }
      out << endl;
   }

}

/**
* function to retrieve the graphDegree private member variable
*
* Precondition: none
* Postcondition: returns the integer for graphDegree
*/
template <class T>
int DirectedGraph<T>::getDegree() const{
   return graphDegree;
}

/**
* function to set the graphDegree private member variable
*
* Precondition: newDegree is an int
* Postcondition: graphDegree is assigned the value from newDegree
*/
template <class T>
void DirectedGraph<T>::setDegree(int newDegree){
   graphDegree = newDegree;
}

/**
* function to retrieve the squared private member variable
*
* Precondition: none
* Postcondition: returns the integer for squared
*/
template <class T>
int DirectedGraph<T>::getSquared() const{
   return squared;
}

/**
* function to set the squared private member variable
*
* Precondition: newSquared is an int
* Postcondition: squared is assigned the value from newSquared
*/
template <class T>
void DirectedGraph<T>::setSquared(int newSquared){
   squared = newSquared;
}

/**
* function to retrieve the adjacencyList private member variable
*
* Precondition: none
* Postcondition: returns the vector for adjacencyList
*/
template <class T>
vector<vector<int> > DirectedGraph<T>::getAdjacencyList() const{
   return adjacencyList;
}

/**
* function to set the adjacencyList private member variable
*
* Precondition: newList is a vector<T>
* Postcondition: adjacencyList is assigned the value from newList
*/
template <class T>
void DirectedGraph<T>::setAdjacencyList(vector<vector<int> > newList){
   adjacencyList = newList;
}

/**
* function to retrieve the vertices private member variable
*
* Precondition: none
* Postcondition: returns the vector for vertices
*/
template <class T>
vector<T> DirectedGraph<T>::getVertices() const{
   return vertices;
}

/**
* function to set the vertices private member variable
*
* Precondition: newList is a vector<T>
* Postcondition: adjacencyList is assigned the value from newList
*/
template <class T>
void DirectedGraph<T>::setVertices(vector<T> newVertices){
   vertices = newVertices;
}

/*****************************************************************************/
/********************** Overloaded Operators**********************************/
/*****************************************************************************/

/**
* overloaded input operator, the only way to input a directed graph
*
* Precondition: filestream is open, myGraph is a directed graph
* Postcondition:myGraph has been populated with input
*
*/
template<class T>
istream& operator>>(istream& in, DirectedGraph<T>& myGraph){

   //assign temporary variables
   vector<vector<int> > tempAdjacencyList;
   tempAdjacencyList = myGraph.getAdjacencyList();
   tempAdjacencyList.clear();
   vector<T> tempVertices;
   tempVertices = myGraph.getVertices();
   tempVertices.clear();

   int n;
   in >> n;
   myGraph.setDegree(n);
   myGraph.setSquared(n*n);
   for (int i = 0; i < (myGraph.getSquared()); ++i)
   {
      in >> n;
      tempVertices.push_back(n);
   }

   for (int i = 0; i < (myGraph.getSquared()); ++i)
   {
      tempVertices.push_back(tempVertices[i]);
   }

   tempAdjacencyList = vector<vector<int> >(2 * myGraph.getSquared());

   //assign temporary variables to real variables
   myGraph.setAdjacencyList(tempAdjacencyList);
   myGraph.setVertices(tempVertices);

   myGraph.populateAdjacency();

   return in;
}

/**
* overloaded output operator, the only way to output a directed graph
*
* Precondition: filestream is open, myGraph is a directed graph
* Postcondition: vertices has been output
*
*/
template<class T>
ostream& operator<<(ostream& out, DirectedGraph<T>& myGraph){

   vector<T> tempVertices;
   tempVertices = myGraph.getVertices();

   for (int i = 0; i < (myGraph.getSquared()); ++i)
   {
      if (i%myGraph.getDegree() == 0)
      {
         out << endl;
      }
      out << tempVertices[i] << " ";
   }
   out << endl;

   return out;
}

/**
*overloaded assignment operator
*
*Precondition: both left and right are Directed Graphs
*Postcondition: left is a copy of right
*
*/
template<class T>
DirectedGraph<T>& DirectedGraph<T>::operator=(const DirectedGraph<T>& rhs){

   if (this == &rhs){
      return *this;
   }
   else
   {
      vertices = rhs.vertices;
      adjacencyList = rhs.adjacencyList;
      graphDegree = rhs.graphDegree;
      squared = graphDegree * graphDegree;
      return *this;
   }
}

/*****************************************************************************/
/********************** Search Functions *************************************/
/*****************************************************************************/

/**
* Breadth-First Search to find shortest path through the maze
* Written by: Sam Suddath
*
* Precondition: There is a nonempty nxn directed graph
* Postcondition: Returns a path from the top left starting position to th
* 		bottom right finish position.
*/
template <class T>
void DirectedGraph<T>::breadthFirstSearch(ostream& out) const {

   //vectors to hold color state, parent, and distance
   vector<int> color(2 * squared, WHITE);
   vector<int> parent(2 * squared, ZERO);
   vector<int> distance(2 * squared, ZERO);

   int currentPosition = ZERO; //first position of maze
   int neighborPosition = ZERO;
   if (vertices[currentPosition] <0){
      currentPosition += squared;
   }
   
   //set first positions values
   color[currentPosition] = GRAY;
   parent[currentPosition] = ZERO;
   distance[currentPosition] = ZERO;

   queue<int> toDo;//create queue for search
   
   toDo.push(currentPosition);//push first position

   while (toDo.size() != 0){//begin overarching loop
      currentPosition = toDo.front();
      neighborPosition = 0;
      toDo.pop();

      //loop to add all non gray neighbors to queue
      for (size_t i = 0; i < adjacencyList[currentPosition].size(); ++i){
         neighborPosition = adjacencyList[currentPosition][i];


         if (color[neighborPosition] == WHITE){

            if (vertices[neighborPosition] < ZERO){ //checks for negative
               if (neighborPosition < squared){ //checks if lower half

                  color[neighborPosition] = GRAY;
                  neighborPosition = neighborPosition + squared;
                  parent[neighborPosition] = currentPosition;
                  distance[neighborPosition] = distance[currentPosition] + 1;
                  toDo.push(neighborPosition); // enqueue

               }
               else if (neighborPosition >= squared){ //check if top half

                  color[neighborPosition] = GRAY;
                  neighborPosition = neighborPosition - squared;
                  parent[neighborPosition] = currentPosition;
                  distance[neighborPosition] = distance[currentPosition] + 1;
                  toDo.push(neighborPosition); // enqueue

               }
            }
            else{//non red circle number

               parent[neighborPosition] = currentPosition;
               color[neighborPosition] = GRAY;
               distance[neighborPosition] = distance[currentPosition] + 1;
               toDo.push(neighborPosition); // enqueue

            }

         }
      }
   }

   vector<int> trace; //trace from finish to start
   int toAdd;//location to add to trace

   (currentPosition<squared) ? toAdd = (squared - 1) : toAdd = (2 * squared - 1);
   while (toAdd != 0 && toAdd != squared){
      trace.push_back(toAdd);
      toAdd = parent[toAdd];
   }
   trace.push_back(toAdd);

   outputCompassTranslation(trace, out);

}

/**
* Depth-First Search
* Written by: Matt McDermott
*
* Precondition: There is a nonempty nxn directed graph
* Postcondition: Returns a path from the top left starting position to th
* 		bottom right finish position.
*/
template <class T>
void DirectedGraph<T>::depthFirstSearch(ostream& out) const{
   vector<int> color(2 * squared, WHITE); //tracks color indicator
   vector<int> parent(2 * squared, ZERO); //tracks parent of each vertext

   int first = 0;

   if (vertices[first] < 0){
      first = first + squared;
   }

   //First vertex initialization
   parent[first] = ZERO;

   if (color[first] == WHITE){
      color[first] = GRAY;
      dfsVisit(first, color, parent);
   }

   vector<int> path; //holds path from end to starting point in maze
   int temp;

   if (parent[2 * squared - 1] != 0){
      temp = 2 * squared - 1;
   }
   else{
      temp = squared - 1;
   }

   while (temp != squared && temp != ZERO){
      path.push_back(temp);
      temp = parent[temp];
   }
   path.push_back(temp);

   outputCompassTranslation(path, out);

}

/**
* dfsVisit helper function for Depth First Search
* Written by: Matt McDermott
*
* Precondition: u is a vertext in the directed graph
* Postcondition: The node is visited and all steps are performed
*/
template <class T>
void DirectedGraph<T>::dfsVisit(const int position, vector<int> &color,
   vector<int> &parent) const{
   int neighbor; // hold the neighbor of position

   for (size_t i = 0; i < adjacencyList[position].size(); ++i){
      neighbor = adjacencyList[position][i];
      if (color[neighbor] == WHITE){

         if (vertices[neighbor] < 0 && neighbor<squared){
            color[neighbor] = GRAY;
            neighbor = neighbor + squared;
            parent[neighbor] = position;
            dfsVisit(neighbor, color, parent);
         }
         else if (vertices[neighbor] < 0 && neighbor >= squared){

            color[neighbor] = GRAY;
            neighbor = neighbor - squared;
            parent[neighbor] = position;
            dfsVisit(neighbor, color, parent);
         }

         else{
            parent[neighbor] = position;
            color[neighbor] = GRAY;
            dfsVisit(neighbor, color, parent);
         }
      }
   }
}

/**
* helper function to print compass directions for maze navigation
* Written by: Sam Suddath
*
* Precondition: currentPath is the path to from start to finish in the maze
* Precondition out is an open outstream
* Postcondition: the compass directions have been printed.
*/
template<class T>
void DirectedGraph<T>::outputCompassTranslation(vector<int>& currentPath, ostream& out) const{


   //variables to compute locations
   int current;
   int parent;

   int currentRow;
   int currentColumn;

   int parentRow;
   int parentColumn;

   //step through input path
   for (size_t i = currentPath.size()-1; i > 0; --i){


      //compute locations using rows and columns
      current = currentPath[i-1];
      parent = currentPath[i];

      if (current >= getSquared()){
         current -= getSquared();
      }

      if (parent >= getSquared()){
         parent -= getSquared();
      }

      currentRow = current / getDegree();
      currentColumn = current % getDegree();

      parentRow = parent / getDegree();
      parentColumn = parent % getDegree();

      //based off rows and columns output a transition
      if (currentRow == parentRow)
      {

         if (currentColumn > parentColumn){
            out << "E ";
         }
         else if (currentColumn < parentColumn){
            out << "W ";
         }
      }

      else if (currentRow < parentRow){

         if (currentColumn == parentColumn){
            out << "N ";
         }
         else if (currentColumn > parentColumn){
            out << "NE ";
         }
         else if (currentColumn < parentColumn){
            out << "NW ";
         }
      }

      else if (currentRow > parentRow){

         if (currentColumn == parentColumn){
            out << "S ";
         }
         else if (currentColumn > parentColumn){
            out << "SE ";
         }
         else if (currentColumn < parentColumn){
            out << "SW ";
         }
      }
   }
}

#endif /* DIRECTEDGRAPH_H_ */
