//
// Created by Jaisal Friedman on 12/8/17.
//

#ifndef DATA_STRUCTURES_3_FONBOOK_HASHDIRECTORY_H
#define DATA_STRUCTURES_3_FONBOOK_HASHDIRECTORY_H

#include <string>
#include <list>
#include "Entry.h"

using namespace std;

class HashDirectory {
private:
    double loadFactor = 0.75;
    int capacity = 10, size = 0, threshold = (int)(capacity * loadFactor);
    list<Entry> hashArray [];

public:
    HashDirectory();
    HashDirectory(int capacity);
    virtual ~HashDirectory();

private:
    void resizeArray();
    int computeIndexHash(int entryHash);

public:
    bool isEmpty() {return size==0;};
    bool remove(string key);
    bool insert(Entry entryIn);
    string find(string key);
    void printTable();
    void printStats();
};


#endif //DATA_STRUCTURES_3_FONBOOK_HASHDIRECTORY_H
