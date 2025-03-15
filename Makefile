CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: lad_main d_main

lad_main: src/ladder_main.cpp ladder.o 
	g++ $(CXXFLAGS) src/ladder_main.cpp -o lad_main ladder.o


ladder.o: src/ladder.cpp src/ladder.h
	g++ $(CXXFLAGS) -c src/ladder.cpp -o ladder.o


d_main: src/dijkstras_main.cpp d.o
	g++ $(CXXFLAGS) src/dijkstras_main.cpp -o d_main d.o

d.o: src/dijkstras.cpp src/dijkstras.h
	g++ $(CXXFLAGS) -c src/dijkstras.cpp -o d.o

clean:
	/bin/rm main