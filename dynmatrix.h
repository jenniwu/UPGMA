#ifndef __DYNMATRIX
#define __DYNMATRIX
#include <string>
#include <iostream>
#include <limits>
using namespace std;

struct DistanceNode {
    double distance;
    DistanceNode* nextInColumn;
    DistanceNode* nextInRow;
    // you can add a constructor
    DistanceNode(double distance, DistanceNode* nextInColumn, DistanceNode* nextInRow){
      this->distance = distance;
      this->nextInColumn = nextInColumn;
      this->nextInRow = nextInRow;
    }
};

struct ClusterNode {
    std::string name;
    // you can add more data members
    ClusterNode* prev;
    ClusterNode* next;
    DistanceNode* row;
    DistanceNode* column;
    // you can add a constructor
    ClusterNode(string name, ClusterNode* prev, ClusterNode* next, DistanceNode* row, DistanceNode* column){
      this->name = name;
      this->prev = prev;
      this->next = next;
      this->row = row;
      this->column = column;
    }
};

void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name);
// adds a cluster (at the tail) and the corresponding row and column to data structure
// distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode

void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved);
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated

void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D);
// finds the minimum distance (between two different clusters) in the data structure 
// and returns the two clusters via C and D

void printDynMatrix(ClusterNode *head);
// prints the matrix

double getDistance(ClusterNode *head, ClusterNode *C, ClusterNode *D);
// gets the distance between ClusterNode C and ClusterNode D

int getNumClusters(string s);
// gets the number of clusters in a cluster name

void updateDistance(ClusterNode *&head, ClusterNode *tail, ClusterNode *&C, ClusterNode *&D);
// updates the DistanceNodes corresponding to ClusterNode with name s

double formula(int c, double cx, int d, double dx);
// apply the formula

int printTree(string input);
// print the tree

#endif
