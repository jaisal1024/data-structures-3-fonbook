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
    if (index == -1 || hashArray[index].isEmpty()) {
        cerr << "Search for " << key << " not found - Remove not possible" << endl;
        return false;
    }
    return hashArray[index].remove(key);
}
string HashDirectory::find(string key) {
    int index = find_index(key);
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

bool HashDirectory::dump(const char* fileName) {
    if (isEmpty()){
        cout << "Hash Directory is empty, there is nothing to dump to the file " << fileName  << endl;
        return false;
    }
    bool opened = false;
    ofstream textFile;
    textFile.open(fileName, ios::out);
    if (textFile.is_open()){
        opened = true;
        for (int i = 0; i < capacity; ++i) {
            if (hashArray[i].isEmpty())
                continue;
            else {
                vector<string> bucketContents;
                hashArray[i].getBucketContents(bucketContents);
                for (int j = 0; j < bucketContents.size(); ++j) {
                    textFile << bucketContents.at(j) << endl;
                }
            }

        }

    }
    textFile.close();
    return opened;
}


Buckets::Buckets() {
    bucketArray = new Entry[5];
    nextChain = NULL;
    prevChain = NULL;
    index = 0;
    isFull = false;
    bucketSize = 5;
}
Buckets::Buckets(int bucketSizeIn) {
    bucketArray = new Entry[bucketSizeIn];
    nextChain = NULL;
    prevChain = NULL;
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
    delete prevChain;
}

bool Buckets::insert(Entry* entryIn){
    //check it's not defined within the bucket already
    for (int i = 0; i < index; i++) {
        if (bucketArray[i].getValue().compare(entryIn->getValue()) == 0){
            cerr << "Warning: Cannot insert already defined entry" << endl;
            return false;

        }
    }
    if (!isFull) {
        bucketArray[index++] = *entryIn;
        if (index == bucketSize) {
            cout << "Create: bucket chain " << endl;
            Buckets* nextBucket = new Buckets(bucketSize);
            nextChain = nextBucket;
            nextBucket->prevChain = this;
            isFull = true;
        }
        return true;
    }
    else if (nextChain!=NULL) {
       nextChain->insert(entryIn);
    } else
        return false;
}
string Buckets::find(string key){
    bool found = false;
    for (int i = 0; i < index && !found; i++) {
        if (bucketArray[i].getKey().compare(key)==0) {
            found = true;
            return bucketArray[i].getValue();
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
bool Buckets::remove(string key){
    for (int i = 0; i < index; i++) {
        if (bucketArray[i].getKey().compare(key)==0) {
            cout << "Removed successfully : " << bucketArray[i].getValue() << endl;
            return refactorOnRemove(i);
        }
    }
    if (!isFull) {
        cerr << "Search for " << key << " not found - Remove not possible" << endl;
        return false;
    } else {
        return nextChain->remove(key);
    }
}
bool Buckets::refactorOnRemove(int i) {
    if (i < bucketSize -1){
        if (i == index-1) //if the found element is the last in the bucketArray
            index--;
        else { //shift bucketArray to accommodate remove function
            for (int j = i; j < bucketSize - 1; ++j) {
                if (bucketArray[j + 1].getKey().length() != 0) {
                    bucketArray[j] = bucketArray[j + 1];
                } else {
                    break;
                }
            }
            index--;
        }
        return true;
    } else if (i == bucketSize -1){
        index--;
        isFull = false;
        return true;
    } else
        return false;
}
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
void Buckets::getBucketContents(vector<string> & bucketContents) {
    if (index == 0) {
        return;
    }
    for (int i = 0; i < index; i++) {
        bucketContents.push_back(bucketArray[i].getValue());
    }
    if (isFull)
        nextChain->printBucket();
}

