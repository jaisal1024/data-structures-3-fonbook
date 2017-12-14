//
// Created by Jaisal Friedman on 12/8/17.
//
#include <cstdlib>
#include <fstream>
#include "Entry.h"
#include "HashDirectory.h"

using namespace std;


HashDirectory* init(int entrySize, int bucketSize){
    HashDirectory* hashPtr = new HashDirectory(entrySize, bucketSize);
    return hashPtr;
}
void add(string value, HashDirectory* hashDirectory) {
    Entry* entry = new Entry(value);
    if(hashDirectory->insert(entry))
        cout << "Add successful" << endl;
    else
        cout << "Add unsuccessful" << endl;
}
void find(string key, HashDirectory* hashDirectory) {
    cout << hashDirectory->find(key);
}
void deleteE(string key, HashDirectory* hashDirectory) {
    hashDirectory->remove(key);
}
void load(const char* fileName, HashDirectory* hashDirectory) {
    string input;
    bool opened = false;
    //Define and open input stream
    ifstream textFile;
    textFile.open(fileName);
    if (textFile.is_open()) {
        opened = true;
        while (getline(textFile, input)) { //get each line of the txt file
            Entry* entry = new Entry(input);
            if (!hashDirectory->insert(entry))
                cout << input << " : could not be inserted" << endl;
        }
    }
    textFile.close();
    if (opened)
        cout << "File loaded successfully" << endl;
    else
        cerr << "Error: " << strerror(errno);
}
void dump(const char* file, HashDirectory* hashDirectory) {
    ofstream textFile;
    textFile.open(file);
    if (textFile.is_open()) {
    }
}


int main(int argc, char* argv[]) {
//Read Command Line Prompt
//input flags & variable
    int entryIndex = -1;
    int entrySize;
    int bucketSize;
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
        else if (*argv[i] == '-' && *(argv[i]+1) == 'b')
            bucketIndex= i+1;
        else if (*argv[i] == '-' && *(argv[i] + 1) == 'f')
            fileIndex = i+1;
    }
    if (entryIndex != -1) {
        entrySize = atoi(argv[entryIndex]);
    } else {
        cout << "Please include the number of entries by invoking the program in the following form ./fonbook -n <numberofentries> -b <bucketsize> -f <filename>, where -f <filename> is optional" << endl;
        return -1;
    }
    if (bucketIndex != -1)
        bucketSize = atoi(argv[bucketIndex]);
    else {
        cout << "Please include the size of buckets by invoking the program in the following form ./fonbook -n <numberofentries> -b <bucketsize> -f <filename>, where -f <filename> is optional" << endl;
        return -1;
    }
    if (fileIndex != -1) {
        fileName = argv[fileIndex];
        fileGiven = true;
        cout << "\'" << fileName << "\'"<< endl;
    }



//Handle Program running
    bool run = true, initRun = false;
    HashDirectory* hashDirectory;
    if (fileGiven) { //initialize data structure and load fileName.
        hashDirectory = init(entrySize, bucketSize);
        initRun = true;
        load(fileName, hashDirectory);
    }

    while (run) {
        string input, classifier;
        cin >> input;
        if (input == "init" ) {
            if (!initRun) {
                hashDirectory = init(entryIndex, bucketIndex);
                initRun = true;
                cout << "Hash Directory Initialized" << endl;
            } else {
                cout << "Main Memory Hash Directory already initialized" << endl;
            }
        } else if (input == "quit") {
            hashDirectory->~HashDirectory();
            run = false;
        } else if (initRun) {
            if(input == "printtable") {
                hashDirectory->printTable();
                continue;
            } else if (input == "printstats") {
                hashDirectory->printStats();
                continue;
            }
            cin >> classifier;
            if (input == "add" && classifier.length() > 0) {
                string temp;
                for (int i = 0; i < 6; ++i) {
                    cin >> temp;
                    classifier = classifier + " " + temp;
                }
                add(classifier, hashDirectory);
            } else if (input == "find" && classifier.length() > 0) {
                find(classifier, hashDirectory);
            } else if (input == "delete" && classifier.length() > 0) {
                deleteE(classifier, hashDirectory);
            } else if (input == "load" && classifier.length() > 0) {
                load(classifier.c_str(), hashDirectory);
            } else if (input == "dump" && classifier.length() > 0) {
                dump(classifier.c_str(), hashDirectory);
            }  else  {
                cout << "Input command not found" << endl;
            }
        } else {
            cout << "Input command not found" << endl;
            if (!initRun)
                cout << "Warning: You may need to initialize the program first using init" << endl;
        }
    }


    return EXIT_SUCCESS;
}

