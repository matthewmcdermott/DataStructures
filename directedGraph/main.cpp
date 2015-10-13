#include <iostream>
#include <fstream>
#include <iomanip>
#include "directedgraph.h"

using namespace std;

int main()
{
   ofstream mattOutput;
   mattOutput.open("mcdermott.txt");
   if (!mattOutput)
   {
      cerr << "The output file did not open" << endl;
   }


   ofstream samOutput;
   samOutput.open("suddath.txt");
   if (!samOutput)
   {
      cerr << "The output file did not open" << endl;
   }


   fstream inputFile;
   inputFile.open("InputFile.txt");
   if (!inputFile)
   {
      cerr << "The input file did not open" << endl;
   }

   DirectedGraph<int> tempGraph;
   int numOfGraphs = 0;
   inputFile >> numOfGraphs;
   for (int i = 0; i < numOfGraphs; ++i)
   {

      inputFile >> tempGraph;

      tempGraph.breadthFirstSearch(samOutput);
      samOutput << endl << endl;

      tempGraph.depthFirstSearch(mattOutput);
      mattOutput << endl << endl;

   }

   return true;
}
