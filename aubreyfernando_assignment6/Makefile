BUILD_FLAGS = -W -Wall -pedantic 
CC = g++
RM = rm
OUT = *.out
O = *.o 

all: a.out

checkFile.o: Makefile checkFile.cpp
	$(CC) $(BUILD_FLAGS) -c checkFile.cpp -o checkFile.o

BubbleSort.o: Makefile BubbleSort.cpp
	$(CC) $(BUILD_FLAGS) -c BubbleSort.cpp -o BubbleSort.o

InsertionSort.o: Makefile InsertionSort.cpp
	$(CC) $(BUILD_FLAGS) -c InsertionSort.cpp -o InsertionSort.o

QuickSort.o: Makefile QuickSort.cpp
	$(CC) $(BUILD_FLAGS) -c QuickSort.cpp -o QuickSort.o

ShellSort.o: Makefile ShellSort.cpp
	$(CC) $(BUILD_FLAGS) -c ShellSort.cpp -o ShellSort.o

a.out: Makefile checkFile.o BubbleSort.o InsertionSort.o QuickSort.o ShellSort.o main.cpp
	$(CC) $(BUILD_FLAGS) checkFile.o BubbleSort.o InsertionSort.o QuickSort.o ShellSort.o main.cpp -o a.out

clean:
	$(RM) $(OUT) $(O)