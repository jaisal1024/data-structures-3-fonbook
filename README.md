# data-structures-3-fonbook
## E Phone Directory for Data Structures CS-105
Repository for our final data structures project implementing a directory of E-Phone Directory called Fonbook using Hash tables

### Program Implementation: 
The program loops continuously taking commands through the terminal from the user. It can initialize the main memory data structures needed, load file of entries, dump the hash directory into a file, add, delete, find, print the table, and the print the statistics. 
#### Program Flow:
##### Command Line Parsing
1. Argv, argc command line input parsing to make sure the given inputs are proper
2. If the file is found initialize and add the contents 
##### Loop for User Commands
1. Read the first word and check if init has been called 
2. Check if quit is inputted
3. Check if printtable, printstats is inputted. If add, delete, remove, load, dump is called wait for subsequent inputs. 
#### Functions:
##### Init
1. Initializes Hash Directory and subsequent Arrays of Bucket class and Entry class
##### Add, Delete, Find k 
1. Add - adds a file k to the hash directory by creating an Entry and computing its hash code. It then adds it to the correct hashArray bucket
2. Delete - deletes an entry based on key. Searches through the hashArray bucket to find a match and then shifts the current index within the array to accommodate the delete
3. Find - finds an entry based on key. Returns the information of the entry in O(1) time if overflow chaining is not utilized. 
##### Load, dump file
1. Load - loads a given file into a function and adds all valid elements to the Hash Directory
2. Dump - adds all Hash Directory entries to given file
##### Print table, print statistics
1. Print table - prints the current E-directory 
2. Prints the statistics - the current load factor and the individual utilization of each bucket and the number of times accessed in the program so far
##### Quit
1. Releases all the pointers and exits the loop, ending the program.

### Data Structures:
#### Hash Directory:
Hash Directory is the class used to store the Hash Directory. It includes a pointer to an array of bucket objects. It also includes all the public functions which the main file calls upon inputs 
It also stores the current size (capacity used) and the total capacity. 
Upon initialization it calculates the smallest prime number greater than the given number of entries to use as the capacity of the array for the hash function.
#### Bucket:
Bucket is the class used to store the Buckets of the Hash Directory. Indexes within the buckets are returned by the hash function. The program then searches through the bucket to find, delete, remove, etc. 
Buckets contain a pointer to an array of entry objects. They also contain pointers to the next and prev buckets in the chain. This is for separate chaining purposes in case a bucket is full. 
Buckets is all protected or private variables and functions. It is only accessed by the Hash Directory. 
#### Entry: 
Entry is the class used to store actual Entries and the neccesary information. This caches the hash function value upon construction. It also stores the key and value of the Entry. 
### Invokation:
To invoke the file, cd into the proper directory. Then ~$ make. The program will run with the invocation -n 100 -b 5 -f file.txt, you can invoke again upon quitting using the command using ./a.out -n <#ofentries> -b <bucketsize> -f <filename>

### Remaining Bugs:
If the number of entries given at invocation is significantly less than the number of entries read into the program. The program is not fully functional as there are pointer errors in the overflow bucket chaining functionality when quitting the program. Segmentation Error 11
If an entry is deleted, then re-inserted. It is not found by the program. 
If a duplicate entry is inserted, it's not flagged. 
Jaisal Friedman - NYU Abu Dhabi