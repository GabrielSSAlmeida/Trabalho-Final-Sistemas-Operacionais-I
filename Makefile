COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror -pthread -std=c++20 -lncurses -ltinfo

all: clean bin bin/main.o
	$(COMPILER) $(COMPILATION_FLAGS) -o kermo \
		 bin/main.o

bin:
	mkdir bin

bin/main.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

run:
	./kermo

clean:
	rm -rf kermo bin