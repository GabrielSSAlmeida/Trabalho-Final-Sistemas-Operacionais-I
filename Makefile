COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror  -pthread -std=c++20

all: clean bin bin/menu.o bin/main.o bin/palavra.o
	$(COMPILER) $(COMPILATION_FLAGS) -o kermo \
		 bin/menu.o bin/main.o bin/palavra.o

bin:
	mkdir bin

bin/palavra.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/palavra.o src/palavra.cpp

bin/menu.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/menu.o src/menu.cpp

bin/main.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

run:
	./kermo

clean:
	rm -rf kermo bin