a.out: HashDirectory.o Entry.o fonbook.o
	g++ -std=c++11 -stdlib=libc++ fonbook.o HashDirectory.o Entry.o
	./a.out -n 100 -b 5 -f file1.txt


HashDirectory.o: HashDirectory.cpp HashDirectory.h
	g++ -std=c++11 -stdlib=libc++ -c HashDirectory.cpp

Entry.o: Entry.cpp Entry.h
	g++ -std=c++11 -stdlib=libc++ -c Entry.cpp

fonbook.o: fonbook.cpp
    g++ -std=c++11 -stdlib=libc++ -c fonbook.cpp

clean:
	rm -f 	fonbook.o \
		Entry.o \
		HashDirectory.o \
		output \
		a.out
