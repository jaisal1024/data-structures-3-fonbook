//
// Created by Jaisal Friedman on 12/8/17.
//

#ifndef DATA_STRUCTURES_3_FONBOOK_HASHDIRECTORY_H
#define DATA_STRUCTURES_3_FONBOOK_HASHDIRECTORY_H

#include <string>
#include "Entry.h"
#include "cmath"
#include <iostream>
#include <iomanip>

using namespace std;

class Buckets {
protected:
    Entry *bucketArray;
    Buckets* nextChain;
    Buckets* prevChain;
    int index;
    bool isFull;
    int bucketSize;

public:
    Buckets();
    Buckets(int bucketSize);
    ~Buckets();

protected:
    string find(string key);
    bool remove(string key);
    bool insert(Entry* entryIn);
    bool isEmpty();
    int getIndex();
    void printBucket();

private:
    bool refactorOnRemove(int i);

    friend class HashDirectory;
};

class HashDirectory {
private:
    double loadFactor;
    int capacity, size, bucketSize;
    Buckets* hashArray;

public:
    HashDirectory();
    HashDirectory(int capacity, int bucketSize);
    virtual ~HashDirectory();

private:
    int find_index(string key);
    int computeHash(string key);
    bool is_prime(int num);

public:
    bool isEmpty() {return size==0;};
    bool remove(string key);
    bool insert(Entry* entryIn);
    string find(string key);
    void printTable();
    void printStats();
};




#endif //DATA_STRUCTURES_3_FONBOOK_HASHDIRECTORY_H
