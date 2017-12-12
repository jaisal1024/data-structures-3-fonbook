//
// Created by Jaisal Friedman on 12/8/17.
//
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include "Entry.h"
#include "HashDirectory.h"

HashDirectory* init(int entrySize, int bucketSize){
    HashDirectory* hashPtr = new HashDirectory(entrySize, bucketSize);
    return hashPtr;
}
bool add(string value, HashDirectory* hashDirectory) {
    Entry* entry = new Entry(value);
    return hashDirectory->insert(entry);
}
string find(string key, HashDirectory* hashDirectory) {
    return hashDirectory->find(key);
}
bool deleteE(string key, HashDirectory* hashDirectory) {
    return hashDirectory->remove(key);
}
bool load(const char* file, HashDirectory* hashDirectory) {
    string input;
    bool opened = false;
    //Define and open input stream
    ifstream textFile(file);
    if (textFile.is_open()) {
        opened = true;
        while (getline(textFile, input)) { //get each line of the txt file
            cout << input << endl;
            Entry* entry = new Entry(input);
            hashDirectory->insert(entry);
        }
    }
    textFile.close();
    if (opened)
        return true;
    cerr << "Error: " << strerror(errno);
    return false;
}
bool dump(const char* file, HashDirectory* hashDirectory) {
    return true;
}


int main(int argc, char* argv[]) {
//Read Command Line Prompt
//input flags & variable
    int entryIndex = -1;
    int bucketIndex = -1;
    int fileIndex = -1;
    bool fileGiven = false;
    const char* fileName;

    //check if you are given at least 4 terminal inputs
    if (argc < 4) {
        cout << "Please invoke the program in the following form ./fonbook -n <numberofentries> -b <bucketsize> -f <filename>, where -f <filename> is optional" << endl;
        return -1;
    }
    //check inputs to get entry, bucket, and filename indexes in the array argv
    for (int i = 0; i < argc; i++) {
        if (*argv[i] == '-' && *(argv[i]+1)== 'n')
            entryIndex= i+1;
        if (*argv[i] == '-' && *(argv[i]+1) == 'b')
            bucketIndex= i+1;
        if (*argv[i] == '-' && *(argv[i] + 1) == 'f')
            fileIndex = i + 1;
    }
    if (entryIndex != -1)
        int entrySize = (int)*(argv[entryIndex]);
    else {
        cout << "Please include the number of entries by invoking the program in the following form ./fonbook -n <numberofentries> -b <bucketsize> -f <filename>, where -f <filename> is optional" << endl;
        return -1;
    }
    if (bucketIndex != -1)
        int entrySize = (int)*(argv[bucketIndex]);
    else {
        cout << "Please include the size of buckets by invoking the program in the following form ./fonbook -n <numberofentries> -b <bucketsize> -f <filename>, where -f <filename> is optional" << endl;
        return -1;
    }
    if (fileIndex != -1) {
        fileName = argv[fileIndex];
        fileGiven = true;
        cout << fileName << endl;
    }



//Handle Program running
    bool run = true, initRun = false;
    HashDirectory* hashDirectory;
    if (fileGiven) { //initialize data structure and load fileName.
        hashDirectory = init(entryIndex, bucketIndex);
        initRun = true;
        if ((load(fileName, hashDirectory)))
            cout << "Load file successfully" << endl;
    }

    while (run) {
        string input;
        cin >> input;
        if (input == "init" ) {
            if (!initRun) {
                hashDirectory = init(entryIndex, bucketIndex);
            }
            cout << "Main Memory Hash Directory already initialized" << endl;
            initRun = true;
        } else if (initRun) {
            if (input.substr(0,3) == "add") {
                if (add(input.substr(4,input.length() -3), hashDirectory))
                    cout << "Add successful" << endl;
            } else if (input.substr(0,4) == "find") {
                cout << (find(input.substr(5,input.length() -4), hashDirectory)) << endl;
            } else if (input.substr(0,4) == "dele") {
                if (deleteE(input.substr(6,input.length() -5), hashDirectory))
                    cout << "Delete successful" << endl;
            } else if (input.substr(0,4) == "load") {
                //if (load(input.substr(5,input.length() -4), hashDirectory))
                    cout << "Load successful" << endl;
            } else if (input.substr(0,4) == "dump") {
                //if (dump(input.substr(5,input.length() -4), hashDirectory))
                    cout << "Dump successful" << endl;
            } else if (input.substr(0,4) == "prin") {

                if (input.substr(5, 3) == "tab") {

                } else if (input.substr(5, 3) == "sta") {

                } else {
                    cout << "Input command not found" << endl;
                }

            } else if (input.substr(0,4) == "quit") {
                run = false;
            } else  {
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

