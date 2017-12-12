//
// Created by Jaisal Friedman on 12/8/17.
//


#ifndef DATA_STRUCTURES_3_FONBOOK_ENTRY_H
#define DATA_STRUCTURES_3_FONBOOK_ENTRY_H

#include <string>
using namespace std;


class Entry {
private:
    string key;
    string value;
    int hash;
    int computeHash();
public:
    Entry();
    Entry(string value);
    const string &getKey() const;
    const string &getValue() const;
    int getHash();
    bool empty();
    void clear();

    friend class HashDirectory;

};


#endif //DATA_STRUCTURES_3_FONBOOK_ENTRY_H
