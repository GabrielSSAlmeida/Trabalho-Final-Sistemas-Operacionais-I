COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror  -pthread

all: clean bin bin/globals.o bin/main.o bin/palavra.o bin/file.o bin/printer.o
	$(COMPILER) $(COMPILATION_FLAGS) -o kermo \
		 bin/globals.o bin/main.o bin/palavra.o bin/file.o bin/printer.o

bin:
	mkdir bin

bin/printer.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/printer.o src/printer.cpp

bin/file.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/file.o src/file.cpp

bin/palavra.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/palavra.o src/palavra.cpp

bin/main.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

bin/globals.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/globals.o src/globals.cpp

run:
	./kermo

clean:
	rm -rf kermo bin