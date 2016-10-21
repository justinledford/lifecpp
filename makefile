CXX=g++
FLAGS=--std=c++11 -lncurses

all: life

clean:
	rm -f *.o life

life: GameOfLife.o Grid.o life.cpp
	$(CXX) $(FLAGS) $^ -o $@

life.o: life.cpp
	$(CXX) $(FLAGS) -c $^

GameOfLife.o: GameOfLife.cpp
	$(CXX) $(FLAGS) -c $^

Grid.o: Grid.cpp
	$(CXX) $(FLAGS) -c $^
