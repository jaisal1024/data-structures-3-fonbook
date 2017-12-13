output: fonbook.o HashDirectory.o Entry.o
	g++ fonbook.o HashDirectory.o Entry.o
	./output -n 20 -b 5 -f file1.txt

fonbook.o: fonbook.cpp
	g++ -c fonbook.cpp

HashDirectory.o:  HashDirectory.cpp HashDirectory.h
	g++ -c HashDirectory.cpp

Entry.o: Entry.cpp Entry.h
	g++ -c Entry.cpp


clean:
	rm -f 	fonbook.o \
		Entry.o \
		HashDirectory.o \
		output
