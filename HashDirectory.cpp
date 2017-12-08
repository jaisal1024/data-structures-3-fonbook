//
// Created by Jaisal Friedman on 12/8/17.
//

#include "HashDirectory.h"

HashDirectory::HashDirectory() {
    hashArray = new list[capacity];
}

HashDirectory::HashDirectory(int capacityIn) {
    if (capacityIn > capacity)
        capacity = capacityIn;
    hashArray = new list[capacity];
    threshold = (int)(capacity*loadFactor);

}

HashDirectory::~HashDirectory() {
    delete [] hashArray;

}
int HashDirectory::computeIndexHash(int entryHash) {}
void HashDirectory::resizeArray(){}
bool HashDirectory::remove(string key) {}
bool HashDirectory::insert(Entry entryIn) {}
string HashDirectory::find(string key) {}
void HashDirectory::printTable() {}
void HashDirectory::printStats() {}