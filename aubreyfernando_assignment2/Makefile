BUILD_FLAGS = -W -Wall -pedantic 
CC = g++
RM = rm
OUT = *.out

all: aubreyfernando_assignment2.out

Input.o: Makefile Input.cpp
	$(CC) $(BUILD_FLAGS) -c Input.cpp -o Input.o

Game.o: Makefile Game.cpp
	$(CC) $(BUILD_FLAGS) -c Game.cpp -o Game.o

aubreyfernando_assignment2.out: Makefile Input.o Game.o main.cpp
	$(CC) $(BUILD_FLAGS) Input.o Game.o main.cpp -o aubreyfernando_assignment2.out

clean:
	$(RM) $(OUT)