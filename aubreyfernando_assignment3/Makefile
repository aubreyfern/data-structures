BUILD_FLAGS = -W -Wall -pedantic 
CC = g++
RM = rm
OUT = *.out
O = *.o 

all: a.out

checkFile.o: Makefile checkFile.cpp
	$(CC) $(BUILD_FLAGS) -c checkFile.cpp -o checkFile.o

checkDelimiters.o: Makefile checkDelimiters.cpp
	$(CC) $(BUILD_FLAGS) -c checkDelimiters.cpp -o checkDelimiters.o

a.out: Makefile checkFile.o checkDelimiters.o main.cpp
	$(CC) $(BUILD_FLAGS) checkFile.o checkDelimiters.o  main.cpp -o a.out

clean:
	$(RM) $(OUT) $(O)