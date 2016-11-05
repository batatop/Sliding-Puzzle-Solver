//SearchAlgorithms.h

#ifndef SEARCHALGORITHMS
#define SEARCHALGORITHMS

#include<iostream>
#include <string>
#include "BlockGame.h"

using namespace std;


class Node{
    public:
        string state;
        Node* parent;
};

class SearchAlgorithms {
    public:
        SearchAlgorithms();
        //Gives the solution of 0 element board

        string breadthFirstSearch(BlockGame problem);
        //BFS

        string solution(Node* node);
        //Prints and wites the solution

    private:
        Node* root;
};

#endif
