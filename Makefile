COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror  -pthread -std=c++20

all: clean bin bin/main.o bin/menu.o bin/timer.o bin/input.o bin/palavra.o bin/display.o
	$(COMPILER) $(COMPILATION_FLAGS) -o kermo \
		 bin/main.o bin/menu.o bin/timer.o bin/input.o bin/palavra.o bin/display.o

bin:
	mkdir bin

bin/palavra.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/palavra.o src/palavra.cpp

bin/menu.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/menu.o src/menu.cpp

bin/timer.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/timer.o src/timer.cpp

bin/input.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/input.o src/input.cpp

bin/display.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/display.o src/display.cpp

bin/main.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

run:
	./kermo

clean:
	rm -rf kermo bin