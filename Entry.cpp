//
// Created by Jaisal Friedman on 12/8/17.
//

#include "Entry.h"

Entry::Entry() {
    value = "";
    key = "";
    hash = -1;
}
Entry::Entry(string valueIn) {
    value = valueIn;
    bool foundWhiteSpaceOne = false, foundWhiteSpaceTwo = false;
    int indexLastName = -1;
    for (int i = 0;
         i < valueIn.size() && !foundWhiteSpaceTwo; i++) { //look for first and second white space to find key
        if (valueIn.substr(i, 1) == " " && !foundWhiteSpaceOne) {
            foundWhiteSpaceOne = true;
            key = valueIn.substr(0, i); //key is equal to first name
            indexLastName = i + 1; //store index for start of last name
        } else if (valueIn.substr(i, 1) == " " && foundWhiteSpaceOne && !foundWhiteSpaceTwo) {
            key = key +
                  valueIn.substr(indexLastName, i - indexLastName); //key is equal to the first name + last name found
            foundWhiteSpaceTwo = true;
        }
        hash = computeHash();
    }
}
int Entry::computeHash() {
    int hashCode = 10;
    int c;

    //Simple hashing function
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
    value = "";
    key = "";
    hash = -1;
}

const string &Entry::getValue() const {
    return value;
}

