//
// Created by Jaisal Friedman on 12/8/17.
//

#include "HashDirectory.h"

HashDirectory::HashDirectory() {
    hashArray = new Buckets[capacity];
}

HashDirectory::HashDirectory(int capacityIn, int bucketSizeIn) {
    if (capacityIn > capacity)
        capacity = capacityIn;
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


int HashDirectory::find_index(string key) {
   int h = computeHash(key) % capacity;
    return h;
}

bool HashDirectory::insert(Entry* entryIn) {
    int index = find_index(entryIn->getKey());
    if (index == -1) {
        return false;
    }
    return hashArray[index].insert(entryIn);
}
bool HashDirectory::remove(string key) {
    int index = find_index(key);
    if (index == -1)
        return false;

    return hashArray[index].remove(key);
}
string HashDirectory::find(string key) {
    int index = find_index(key);
    if (index == -1)
        return "";

    return hashArray[index].find(key);

}
void HashDirectory::printTable() {

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
        bucketArray[index++] = *entryIn;
        if (index == bucketSize) {
            Buckets* nextBucket = new Buckets(bucketSize);
            nextChain = nextBucket;
            isFull = true;
        }
        cout << "INSERTED :" << entryIn->getValue() << endl;
        return true;
    }
    else if (nextChain!=NULL) {
       nextChain->insert(entryIn);
    }
    return false;
}
string Buckets::find(string key){}
bool Buckets::remove(string key){}
bool Buckets::isEmpty(){ return index ==0;}
int Buckets::getIndex(){ return index;}
