//SearchAlgorithms.h

#ifndef SEARCHALGORITHMS
#define SEARCHALGORITHMS

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include "BlockGame.h"

using namespace std;


class Node{
    public:
        string state;
        int f;
        Node* parent;
};

class SearchAlgorithms {
    public:
        SearchAlgorithms();
        //Initilizes root to NULL and nodeCounter to 0

        string breadthFirstSearch(BlockGame problem);
        //BFS algorithm. Returns the solution or "failure"

        string depthLimitedSearch(BlockGame problem, int limit);
        //DLS algorithm. Returns the solution "cutoff" or "failure"

        string recursiveDLS(Node* node, BlockGame problem, int limit);
        //Recursive function for DLS

        string aStarAlgorithm(BlockGame problem);
        //A* algorithm. Returns the solution "failure"

        string bestFirstSearch(BlockGame problem, Node* node);
        //Best first search for the A* algorithm

        string solution(Node* node);
        //Returns the solution states in one string and prints the step number

    private:
        Node* root;
        int fLimit;
        long int nodeCounter;
};

#endif
