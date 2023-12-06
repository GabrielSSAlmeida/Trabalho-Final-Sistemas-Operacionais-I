COMPILER := g++
COMPILATION_FLAGS := -Wall -Werror -pthread -std=c++20

all: clean bin bin/timer.o bin/wordManager.o bin/display_content.o\
	bin/pages_manager.o bin/display.o bin/gameController.o bin/controllers.o\
	bin/startController.o bin/guessController.o bin/finalController.o\
	bin/engine.o bin/main.o
	$(COMPILER) $(COMPILATION_FLAGS) -o kermo \
		bin/timer.o bin/wordManager.o bin/display_content.o\
		bin/pages_manager.o bin/display.o bin/gameController.o bin/controllers.o\
		bin/startController.o bin/guessController.o bin/finalController.o\
		bin/engine.o bin/main.o

bin:
	mkdir bin

bin/timer.o: src/timer.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/timer.o src/timer.cpp

bin/wordManager.o: src/wordManager.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/wordManager.o src/wordManager.cpp

bin/display_content.o: src/display_content.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/display_content.o\
		src/display_content.cpp

bin/pages_manager.o: src/pages_manager.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/pages_manager.o\
		src/pages_manager.cpp

bin/display.o: src/display.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/display.o src/display.cpp

bin/gameController.o: src/controllers/gameController.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/gameController.o\
		src/controllers/gameController.cpp

bin/controllers.o: src/controllers/controllers.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/controllers.o\
		src/controllers/controllers.cpp

bin/startController.o: src/controllers/startController.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/startController.o\
		src/controllers/startController.cpp

bin/guessController.o: src/controllers/guessController.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/guessController.o\
		src/controllers/guessController.cpp

bin/finalController.o: src/controllers/finalController.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/finalController.o\
		src/controllers/finalController.cpp

bin/engine.o: src/controllers/engine.cpp
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/engine.o src/controllers/engine.cpp


bin/main.o:
	$(COMPILER) $(COMPILATION_FLAGS) -c -o bin/main.o src/main.cpp

run:
	./kermo

clean:
	rm -rf kermo bin




