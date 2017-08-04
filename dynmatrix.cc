#include "dynmatrix.h"

void addCluster(ClusterNode *&head, ClusterNode *&tail, const std::string& name)
// adds a cluster (at the tail) and the corresponding row and column to data structure
// distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode
{
    if (head == NULL) {
        ClusterNode *newClusterNode = new ClusterNode(name, tail, NULL, NULL, NULL);
        head = newClusterNode;
        tail = newClusterNode;
        head->next = NULL;
        head->row = new DistanceNode(0.0, NULL, NULL);
        head->column = head->row;
    } else {
//        cout << "adding new ClusterNode" << endl;
        ClusterNode *newClusterNode = new ClusterNode(name, tail, NULL, NULL, NULL);
        tail->next = newClusterNode;
        newClusterNode->prev = tail;
        newClusterNode->next = NULL;

//        cout << "adding RIGHT COLUMN distanceNode" << endl;
        DistanceNode *newDistanceNode1 = new DistanceNode(0.0, NULL, NULL);
        tail->column->nextInRow = newDistanceNode1;
        newClusterNode->column = newDistanceNode1;
        DistanceNode *iterator1 = tail->column;
        DistanceNode *iterator2 = newDistanceNode1;

        //using while-loop to add a column of new node
        while (iterator1->nextInColumn) {
//            cout << "iterating distanceNode" << endl;
            iterator2->nextInColumn = new DistanceNode(0.0, NULL, NULL);
            iterator1->nextInColumn->nextInRow = iterator2->nextInColumn;
            iterator1 = iterator1->nextInColumn;
            iterator2 = iterator2->nextInColumn;
//            cout << "finished iterating distanceNode" << endl;
        }

//        cout << "adding BOTTOM ROW distanceNode" << endl;
        DistanceNode *newDistanceNode2 = new DistanceNode(0.0, NULL, NULL);
        newClusterNode->row = newDistanceNode2;
        tail->row->nextInColumn = newDistanceNode2;
        DistanceNode *iterator3 = tail->row;
        DistanceNode *iterator4 = newDistanceNode2;
        //using while-loop to add a row of new node
        while (iterator3->nextInRow) {
//            cout << "iterating distanceNode" << endl;
            iterator4->nextInRow = new DistanceNode(0.0, NULL, NULL);
            iterator3->nextInRow->nextInColumn = iterator4->nextInRow;
            iterator3 = iterator3->nextInRow;
            iterator4 = iterator4->nextInRow;
        }

        //updating tail
        tail = tail->next;
    }
}


void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved)
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated
{
    ClusterNode *tempHead = head;
    ClusterNode *tempTail = tail;

    if (head == tail) {
        delete head->column;
        delete head;
    } else if(toBeRemoved == head) {
        ClusterNode *refHead = head;
        DistanceNode *deleter = toBeRemoved->column;
        DistanceNode *deletec = toBeRemoved->row->nextInRow;
        DistanceNode *temp = deleter;
        deleter = deleter->nextInColumn;
        delete temp;
        DistanceNode *iterator1 = toBeRemoved->row->nextInColumn;
        DistanceNode *iterator2 = toBeRemoved->row->nextInRow;

        while(tempHead->next){
            //remvoe first column, chanigng correspoding row  3 links
            tempHead->next->row = iterator1->nextInRow;
            iterator1 = iterator1->nextInColumn;
            temp = deleter;
            deleter = deleter->nextInColumn;
            delete temp;
            //remove first row, changing correspoing column 3 links
            tempHead->next->column = iterator2->nextInColumn;
            iterator2= iterator2->nextInRow;
            temp = deletec;
            deletec = deletec->nextInRow;
            delete temp;
            //update tempHead;
            tempHead = tempHead->next;
        }
        delete deleter;
        delete deletec;
        head = head->next;
        head->prev = NULL;
        delete refHead;

    } else if(toBeRemoved == tail){
        ClusterNode *refTail = tail;
        DistanceNode *iterator1 = tempTail->prev->row;
        DistanceNode *iterator2 = tempTail->prev->column;
        DistanceNode *last = tail->row;
        while(tempTail->prev){
            //remove last row, changing corresponding 3 column
            delete iterator1->nextInColumn;
            iterator1->nextInColumn = NULL;
            iterator1 = iterator1->nextInRow;
            //remove last column, changing corresponding 3 row
            last = last->nextInRow;
            delete iterator2->nextInRow;
            iterator2->nextInRow = NULL;
            iterator2 = iterator2->nextInColumn;
            //update tempHead2
            tempTail = tempTail->prev;
        }
        delete last;
        tail = tail->prev;
        tail->next = NULL;
        delete refTail;
    } else {  //tobeRemoved == middle clusterNode
        //left->right row link = left->right->right link
        DistanceNode *iterator3 = toBeRemoved->prev->column;
        DistanceNode *toDelete = NULL;
        while(iterator3){
            toDelete = iterator3->nextInRow;
            delete toDelete;
            iterator3->nextInRow = iterator3->nextInRow->nextInRow;
            iterator3 = iterator3->nextInColumn;
        }

        //up->bottom link = up->bottom-<bottom link
        DistanceNode *iterator4 = toBeRemoved->prev->row;
        while(iterator4){
            toDelete = iterator4->nextInColumn;
            delete toDelete;
            iterator4->nextInColumn = iterator4->nextInColumn->nextInColumn;
            iterator4 = iterator4->nextInRow;
        }
        //UPDATING CLUSTERNODE left and right links
        toBeRemoved->prev->next = toBeRemoved->next;
        toBeRemoved->next->prev = toBeRemoved->prev;
        delete toBeRemoved;
    }
}


void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D)
// finds the minimum distance (between two different clusters) in the data structure 
// and returns the two clusters via C and D
{
    ClusterNode *tempC = head;
    ClusterNode *tempD = head;
    DistanceNode *temp;
    double globalMin = std::numeric_limits<double>::max();
    while(tempC){
        temp = tempC->row;
        while(tempD) {
            if(tempC != tempD && temp->distance != 0.0 && temp->distance < globalMin){
                globalMin = temp->distance;
                C = tempC;
                D = tempD;
            }
            temp = temp->nextInRow;
            tempD = tempD->next;
        }
        tempC = tempC->next;
        tempD = head;
    }
}

void printDynMatrix(ClusterNode *head)
// prints the matrix
{
    cout << "-------------------------------------" << endl;
    ClusterNode *temp = head;
    while (temp) {
        cout << temp->name << " ";
        temp = temp->next;
    }
    cout << endl;

    DistanceNode *row = head->row;
    DistanceNode *column = head->column;

    while (column) {
        while (row) {
            cout << row->distance << "\t";
            row = row->nextInRow;
        }
        cout << endl;
        column = column->nextInColumn;
        row = column;
    }
    cout << "-------------------------------------" << endl;
    cout << endl;
}

double getDistance(ClusterNode *head, ClusterNode *C, ClusterNode *D)
// gets the distance between ClusterNode C and ClusterNode D
{
    double d;
    ClusterNode *row = head;
    ClusterNode *col = head;
    DistanceNode *temp = head->row;

    while(row != C) {
        temp = temp->nextInColumn;
        row = row->next;
    }

    while(col != D) {
        temp = temp->nextInRow;
        col = col->next;
    }

    d = temp->distance;
    return d;
}

int getNumClusters(string s) {
    int n = 1;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == ',') {
            ++n;
        }
    }

    return n;
}

void updateDistance(ClusterNode *&head, ClusterNode *tail, ClusterNode *&C, ClusterNode *&D)
// updates the DistanceNodes corresponding to ClusterNode with name s
{
    ClusterNode *temp = head;
    DistanceNode *row = tail->row;
    DistanceNode *col = tail->column;

    int clustersC = getNumClusters(C->name);
    int clustersD = getNumClusters(D->name);

    while (col) {
        col->distance = formula(clustersC, getDistance(head, C, temp), clustersD, getDistance(head, D, temp));
        temp = temp->next;
        col = col->nextInColumn;
    }

    temp = head;
    while (row) {
        row->distance = formula(clustersC, getDistance(head, C, temp), clustersD, getDistance(head, D, temp));
        temp = temp->next;
        row = row->nextInRow;
    }

    col = tail->column;
    while (col->nextInColumn) {
        col = col->nextInColumn;
    }
    col->distance = 0.0;
}

double formula(int c, double cx, int d, double dx)
// apply the formula
{
    double res;
    res = ((c*cx)+(d*dx))/(c+d);
    return res;
}

int printTree(string input)
// print the tree
{
    int offset = 0;
    if(input.find_last_of(')')==string::npos) {
        cout << input << endl;
    }
    for (int i = input.size()-1; i >= 0; i--) {
        // cout<<input[i];
        if (input[i] == ')') {
            // cout<<input[i];
            offset += 3;
        } else if(input[i] == '(') {
            offset -= 3;
        } else if (input[i] == ',') {
            if (offset <= 3) {
                cout << "*" << endl;
            } else {
                int s = (offset-3)/3;
                if (s < 2) {
                    cout << "|--*" << endl;
                } else {
                    cout << "|  " << string((s-2)*3, ' ') << "|--*" << endl;
                }
            }
        } else if(input[i] != ',') {
            int s = (offset-3)/3;
            if(input[i+1] == ',') {
                int pos = input.find_last_of('(', i);
               for (int n = 0; n < s; n++) {
                        cout << "|  ";
                    }
                cout << "|--" << input.substr(pos+1, i-pos) << endl;
                i = pos+1;
            } else if (input[i+1] == ')') {
                int pos = input.find_last_of(',', i);
                cout << "|  "<< string((s-1)*3, ' ') << "|--" << input.substr(pos+1, i-pos) << endl;
                i = pos+1;
            }
        }
    }
    return 0;
}