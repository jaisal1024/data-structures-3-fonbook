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
    for (int i = 0; i < valueIn.size(); i++) {
        if (valueIn.substr(i,1) == " " && !foundWhiteSpaceOne) {
            foundWhiteSpaceOne = true;
            key = valueIn.substr(0,i);
            indexLastName = i+1;
        } else if (valueIn.substr(i,1) == " " && foundWhiteSpaceOne && !foundWhiteSpaceTwo) {
            key = key + valueIn.substr(indexLastName, i - indexLastName);
            foundWhiteSpaceTwo = true;
        } else if (foundWhiteSpaceTwo)
            break;
    }
    hash = computeHash();
}
int Entry::computeHash() {
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
    if (key == "ShanteMark")
        cout << "SHANTE MARK HASH: " << hashCode << endl;
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

