//
// Created by Jaisal Friedman on 12/8/17.
//

#include "Entry.h"

Entry::Entry() {
    value = NULL;
    key = NULL;
    hash = -1;
}
Entry::Entry(string valueIn) {
    value = valueIn;
    bool foundWhiteSpace = false;
    for (int i = 0; i < valueIn.size(); ++i) {
        if (valueIn.substr(i,1) == " " && !foundWhiteSpace)
            foundWhiteSpace = true;
        else if (valueIn.substr(i,1) == " " && foundWhiteSpace)
            key = valueIn.substr(0,i);
    }
    hash = computeHash();
}
int Entry::computeHash() {
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
int Entry::getHash() {
    return hash;
}
bool Entry::empty() {
    return hash == -1;
}

const string &Entry::getKey() const {
    return key;
}

void Entry::clear(){
    value = NULL;
    key = NULL;
    hash = -1;
}

const string &Entry::getValue() const {
    return value;
}

