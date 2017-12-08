//
// Created by Jaisal Friedman on 12/8/17.
//

#include "Entry.h"


Entry::Entry(string keyIn, string valueIn) {
    key = keyIn;
    value = valueIn;
    hash = computeHash();
}
int Entry::computeHash() {

}
