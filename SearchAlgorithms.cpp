//SearchAlgorithms.cpp

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include "SearchAlgorithms.h"

using namespace std;

SearchAlgorithms::SearchAlgorithms(){
    root= NULL;
    nodeCounter= 0;
}

string SearchAlgorithms::breadthFirstSearch(BlockGame problem){
    Node* node= new Node();
    nodeCounter++;
    node->state= problem.getInitialState();
    node->parent= NULL;
    root= node;
    if(problem.checkWin(node->state)){
        return solution(node);
    }
    queue<Node*> frontier;
    queue<Node*> tempQueue;
    frontier.push(node);
    set<string> explored;
    bool checkExplored;
    bool reached= false;
    string action="";
    int i=0;
    while(!reached){
        if(frontier.empty()){
            return "failure";
        }
        node= frontier.front();
        frontier.pop();
        explored.insert(node->state);
        action= problem.actions(node->state);
        while(i<action.length()){
            Node* child= new Node();
            nodeCounter++;
            child->state= action.substr(i, 36);
            child->parent= node;
            checkExplored= explored.find(child->state) != explored.end();

            int tempSize= frontier.size();
            tempQueue= frontier;
            while(!tempQueue.empty() && !checkExplored){
                if(tempQueue.front()->state == child->state){
                    checkExplored= true;
                }
                tempQueue.pop();
            }

            if(!checkExplored){
                if(problem.checkWin(child->state)){
                    return solution(child);
                }
                frontier.push(child);
                action= action.substr(i, action.length()-36);
            }
            i+=36;
        }
        i=0;
        action="";
    }
}

string SearchAlgorithms::depthLimitedSearch(BlockGame problem, int limit){
    Node* node= new Node();
    nodeCounter++;
    node->state= problem.getInitialState();
    node->parent= NULL;
    root= node;
    return recursiveDLS(node, problem, limit);
}

string SearchAlgorithms::recursiveDLS(Node* node, BlockGame problem, int limit){
    string result= "", action="";
    int i= 0;
    bool cutoff_occured= false;
    if(problem.checkWin(node->state)){
        return solution(node);
    }
    else if(limit==0){
        return "cutoff";
    }
    else{
        if(!cutoff_occured){
            action= problem.actions(node->state);
            while(i<action.length()){
                Node* child= new Node();
                nodeCounter++;
                child->state= action.substr(i, 36);
                child->parent= node;
                result= recursiveDLS(child, problem, limit-1);
                if(result=="cutoff"){
                    cutoff_occured= true;
                }
                else if(result!="failure"){
                    return result;
                }
                i+= 36;
            }
        }
    }

    if(cutoff_occured){
        return "cutoff";
    }
    else{
        return "failure";
    }
}


string SearchAlgorithms::aStarAlgorithm(BlockGame problem){
    Node* node= new Node();
    node->state= problem.getInitialState();
    node->parent= NULL;
    int g= problem.distanceToStart(node->state);
    int h= problem.distanceToFinish(node->state);
    node->f= g+h;

    fLimit= 11;

    return bestFirstSearch(problem, node);
}


string SearchAlgorithms::bestFirstSearch(BlockGame problem, Node* node){
    string result= "";
    if(problem.checkWin(node->state)){
        return solution(node);
    }

    string action= problem.actions(node->state);
    Node* successors[action.length()/36];
    for(int j=0; j<action.length()/36; j++){
        successors[j]= NULL;
    }

    int i= 0;
    while(i<action.length()){
        Node* child= new Node();
        child->state= action.substr(i, 36);
        child->parent= node;
        successors[i/36]= child;
        i+= 36;
    }

    bool isNull= true;
    for(int j=0; j<action.length()/36; j++){
        if(successors[j]!= NULL){
            isNull= false;
        }
    }
    if(isNull){
        fLimit= 11;
        return "failure";
    }

    for(int j=0; j<action.length()/36; j++){
        if(successors[j]!=NULL){
            successors[j]->f= max(problem.distanceToStart(successors[j]->state)+problem.distanceToFinish(successors[j]->state), node->f);
        }
    }

    bool reached= false;
    Node* best;
    Node* alternative;
    while (!reached) {
        for(int j=0; j<action.length()/36; j++){
            if(successors[j]!=NULL){
                if(j==0){
                    best= successors[j];
                    alternative= best;
                }
                else{
                    if(alternative==best){
                        alternative= successors[j];
                    }
                    if(successors[j]->f<best->f){
                        alternative= best;
                        best= successors[j];
                    }
                }
            }
        }

        if(best->f>fLimit){
            fLimit= best->f;
            return "failure";
        }
        fLimit= min(fLimit, alternative->f);
        result= bestFirstSearch(problem, best);

        if(result!="failure"){
            return result;
        }
    }
}

string SearchAlgorithms::solution(Node* node){
    Node* tempNode= node;
    int index= 0;
    int steps= 0;
    string solution="";
    while(tempNode->state!= root->state){
        steps++;
        tempNode= tempNode->parent;
    }
    cout<<"Solved with "<<steps<<" steps. You can find the steps in the 'solution.txt' file."<<endl;

    string stepStates[steps];
    tempNode= node;
    index= steps-1;
    while(tempNode->state!= root->state){
        stepStates[index]= tempNode->state;
        tempNode= tempNode->parent;
        index--;
    }

    for(int i=0; i<steps; i++){
            solution+= stepStates[i];
    }

    return solution;
}
