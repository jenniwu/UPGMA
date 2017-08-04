#include <iostream>
#include <fstream>
#include <algorithm>
#include "dynmatrix.h"

using namespace std;

// construct a string representation 

void usage() {
    cerr << "Usage: upgma species.txt" << endl;
}

int main( int argc, char *argv[] ) {
    if( argc != 2 ) {
        usage();
        return 0;
    }

    // let's start with empty DynMatrix:
    ClusterNode* head = NULL;
    ClusterNode* tail = NULL;

    int n = 0; // number of species
    ifstream fin( argv[1] );
    if( fin.is_open() ) {
        // read species:
        string species;
        while ((fin.peek() != '\n') && (fin >> species)) {
            n++;
            addCluster(head, tail, species);
        }
        // read distances:
        DistanceNode *column = head->column;
        DistanceNode *row = head->row;
        for (int i=0; i < n && fin; i++) {
            for (int j = 0; j < n && fin; j++) {
                double d;
                fin >> d;
                column->distance = d;
                column = column->nextInRow;
            }
            row = row->nextInColumn;
            column = row;
        }

//        cout << "Printing input..." << endl;
//        printDynMatrix(head);
        fin.close();
    }

    cout << "Entering UPGMA..." << endl;
    // UPGMA Method
    while(head != tail){
        ClusterNode *C;
        ClusterNode *D;
        findMinimum(head, C, D);
        string name = "(" + C->name + "," + D->name + ")";

        addCluster(*&head, *&tail, name);
        updateDistance(head, tail, C, D);
//        printDynMatrix(head);

        removeCluster(*&head, *&tail, *&C);
        removeCluster(*&head, *&tail, *&D);
//        printDynMatrix(head);
    }
    // print the name of the last remaining cluster
    if (head) {
        cout << "The last remaining cluster:" << endl;
        cout << head->name << endl;
    }
    cout << endl;
    // BONUS (optional): print the tree in a nice way
    cout << "Printing Tree..." << endl;
    printTree(head->name);
    cout << endl;
    removeCluster(head, tail, head);
    cout << "Finished UPGMA!" << endl;

    return 0;
}
