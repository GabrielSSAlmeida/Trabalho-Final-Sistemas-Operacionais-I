COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror  -pthread

all: clean bin bin/menu.o bin/main.o
	$(COMPILER) $(COMPILATION_FLAGS) -o kermo \
		 bin/menu.o bin/main.o

bin:
	mkdir bin

bin/menu.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/menu.o src/menu.cpp

bin/main.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

run:
	./kermo

clean:
	rm -rf kermo bin