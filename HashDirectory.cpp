//
// Created by Jaisal Friedman on 12/8/17.
//

#include "HashDirectory.h"

HashDirectory::HashDirectory() {
    capacity = 13;
    size = 0, bucketSize = 5;
    loadFactor = 0;
    hashArray = new Buckets[capacity];
}

HashDirectory::HashDirectory(int capacityIn, int bucketSizeIn) {
    size = 0;
    loadFactor = 0;
    if (capacityIn < 10)
        capacity = 13;
    else {
        //compute smallest prime number greater than capacityIn
        while (!is_prime(capacityIn)) {
            capacityIn++;    // you want to find a prime number greater than the argument
        }
        capacity = capacityIn;
    }
    hashArray = new Buckets[capacity];
    bucketSize = bucketSizeIn;

}

bool HashDirectory::is_prime(int num) {
    int sq_root = (int)sqrt(num);
    for (int i = 2; i <= sq_root; i++) {
        if (num % i == 0) {
            return false;
        }
        return true;
    }
}

HashDirectory::~HashDirectory() {
//    for (int i = 0; i < capacity; ++i) {
//        if (hashArray[i].isEmpty())
//            continue;
//        hashArray[i].~Buckets();
//    }
    delete [] hashArray;
}

int HashDirectory::computeHash(string key) {
    int hashCode = 10;
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


int HashDirectory::find_index(string key) {
    int h = computeHash(key) % capacity;
    return h;
}

bool HashDirectory::insert(Entry* entryIn) {
    int index = entryIn->getHash() % capacity;
    if (index == -1) {
        return false;
    }
    bool status = hashArray[index].insert(entryIn);
    if (status) {
        size++;
        return true;
    }
    return false;
}
bool HashDirectory::remove(string key) {
    int index = find_index(key);
    if (index == -1)
        return false;

    return hashArray[index].remove(key);
}
string HashDirectory::find(string key) {
    cout << key << endl;
    int index = find_index(key);
    cout << index << endl;
    hashArray[index].printBucket();
    if (index == -1 || hashArray[index].isEmpty()) {
        cerr << "Search for " << key << " not found" << endl;
        return "";
    }
    return hashArray[index].find(key);
}
void HashDirectory::printTable() {
    if (isEmpty())
        return;
    cout << setw(20) << "\nE-Phonebook Directory: \n " << endl;
    for (int i = 0; i < capacity; ++i) {
        if (hashArray[i].isEmpty())
            continue;
        hashArray[i].printBucket();
    }
}
void HashDirectory::printStats() {}


Buckets::Buckets() {
    bucketArray = new Entry[5];
    nextChain = NULL;
    index = 0;
    isFull = false;
    bucketSize = 5;
}
Buckets::Buckets(int bucketSizeIn) {
    bucketArray = new Entry[bucketSizeIn];
    nextChain = NULL;
    index = 0;
    isFull = false;
    bucketSize = bucketSizeIn;
}
Buckets::~Buckets() {
    delete [] bucketArray;
    Buckets* bucketNext = nextChain;
    while(bucketNext!= NULL){
        Buckets* bucketCurr = nextChain;
        bucketNext = bucketCurr->nextChain;
        delete bucketCurr;
    }
}

bool Buckets::insert(Entry* entryIn){
    if (!isFull) {
        cout << entryIn->getKey()<< " NOT FULL" << endl;
        bucketArray[index++] = *entryIn;
        if (index == bucketSize) {
            Buckets* nextBucket = new Buckets(bucketSize);
            nextChain = nextBucket;
            isFull = true;
        }
        return true;
    }
    else if (nextChain!=NULL) {
       nextChain->insert(entryIn);
    }
    return false;
}
string Buckets::find(string key){
    bool found = false;
    for (int i = 0; i < index && !found; i++) {
        if (bucketArray[index].getKey() == key) {
            found = true;
            cout << bucketArray[index].getValue() << endl;
            return bucketArray[index].getValue();
        }
    }
    if ((found == false && !isFull)) {
        cerr << "Search for " << key << " not found" << endl;
        return "";
    }
    if (isFull){
        return nextChain->find(key);
    }
}
bool Buckets::remove(string key){}
bool Buckets::isEmpty(){ return index ==0;}
int Buckets::getIndex(){ return index;}
void Buckets::printBucket() {
    if (index == 0) {
        return;
    }
    for (int i = 0; i < index; i++) {
        cout << setw(10) << bucketArray[i].getValue()  << endl;
    }
    if (isFull)
        nextChain->printBucket();
}
