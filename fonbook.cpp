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
//input flags & variable
    int dictIndex = -1;
    int limitIndex = -1;
    const char* dictionaryPath;
    int limit = 1;
    //check if you are given 5 terminal inputs
    if (argc != 5) {
        cout << "Please include 2 inputs, the path to the dictionary file and the limit to the number of words you want found in your command line input: in the form of -d $/path/file.txt -l limit " << endl;
        return -1;
    }
    //check inputs to get dictionary and length variable indexes in the array argv
    for (int i = 0; i < argc; i++) {
        if (*argv[i] == '-' && *(argv[i]+1)== 'd')
            dictIndex = i+1;
        if (*argv[i] == '-' && *(argv[i]+1) == 'l')
            limitIndex= i+1;
        cout << argv[i] << endl;
    }


//Handle Program running
    bool run = true, init = false;
    while (run) {
        string input;
        cin >> input;
        if (input == "init" && !init) {

        } else if (input.substr(0,3) == "add ") {

        } else if (input.substr(0,4) == "find") {

        } else if (input.substr(0,4) == "dele") {

        } else if (input.substr(0,4) == "load") {

        } else if (input.substr(0,4) == "dump") {

        } else if (input.substr(0,4) == "prin") {
            if (input.substr(5,3) == "tab") {

            } else if (input.substr(5,3) == "sta") {

            } else {
                cout << "Input command not found" << endl;
            }

        } else if (input.substr(0,4) == "quit") {
            run = false;
        } else {
            cout << "Input command not found" << endl;
        }
    }


    return EXIT_SUCCESS;
}

