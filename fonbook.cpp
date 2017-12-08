//
// Created by Jaisal Friedman on 12/8/17.
//
#include <cstdlib>
#include <string>
#include <iostream>
#include "Entry.h"
#include "HashDirectory.h";


int main(int argc, char* argv[]) {
    //Read Command Line Prompt

//Handle Program running
    bool run = true, init = false;
    while (run) {
        string input;
        cin >> input;
        if (input == "init" && !init) {

        } else if (input.substr(0,3) == "add") {

        }
    }
    return EXIT_SUCCESS;
}

