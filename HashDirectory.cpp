//
// Created by Jaisal Friedman on 12/8/17.
//

#include "HashDirectory.h"

HashDirectory::HashDirectory() {
    hashArray = new Entry[capacity];
}

HashDirectory::HashDirectory(int capacityIn) {
    if (capacityIn > capacity)
        capacity = capacityIn;
    hashArray = new Entry[capacity];
    threshold = (int)(capacity*loadFactor);

}

HashDirectory::~HashDirectory() {
    delete [] hashArray;
}

int HashDirectory::computeHash(string key) {
    int hashCode = 5381;
    int c;

    //djb2
//    for (int i = 0; i < key.length(); ++i) {
//        c = (int) key[i];
//        hashCode = ((hashCode << 5) + hashCode) + c;
//    }

    //Simple hashing
    for (int j = 0; j < key.length(); ++j) {
        c = (int) key[j];
        hashCode += (j+1)*c;

    }
    return hashCode;
}

void HashDirectory::resizeArray(){

}

int HashDirectory::find_index_insertion(string key) {
   int h = computeHash(key) % capacity, offset = 0, index;

    while (offset < capacity) {
        index = (h + offset) % capacity;
        // empty index for new entry with key `key`
        if (hashArray[index].empty())
            return index;
        else if (hashArray[index].getKey() == key) //found duplicate
            return -1;
        offset++;
    }
    return -1;
}
int HashDirectory::find_index_search(string key) {
    int h = computeHash(key) % capacity, offset = 0, index;

    while (offset < capacity) {
        index = (h + offset) % capacity;
        // empty index for new entry with key `key`
        if (hashArray[index].getKey() == key) //found duplicate in search
            return index;
        offset++;
    }
    return -1;
}

bool HashDirectory::insert(Entry &entryIn) {
    int index = find_index_insertion(entryIn.getKey());
    if (index == -1) {
        resizeArray();
        return false;
    }
    hashArray[index] = entryIn;
    return true;
}
bool HashDirectory::remove(string key) {
    int index = find_index_search(key);
    if (index == -1)
        return false;

    hashArray[index].clear();
    return true;
}
string HashDirectory::find(string key) {
    int index = find_index_search(key);
    if (index == -1)
        return "";

    return hashArray[index].getValue();

}
void HashDirectory::printTable() {}
void HashDirectory::printStats() {}