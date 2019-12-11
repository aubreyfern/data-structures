BUILD_FLAGS = -W -Wall -pedantic
CC  = g++
RM = RM
OUT = *out
O = *.o

all: a.out

fileCheck.o: Makefile fileCheck.cpp
	$(CC) $(BUILD_FLAGS) -c fileCheck.cpp -o fileCheck.o 

Student.o: Makefile Student.cpp
	$(CC) $(BUILD_FLAGS) -c Student.cpp -o Student.o 

Simulation.o: Makefile Simulation.cpp
	$(CC) $(BUILD_FLAGS) -c Simulation.cpp -o Simulation.o

a.out: Makefile fileCheck.o Student.o Simulation.o main.cpp
	$(CC) $(BUILD_FLAGS) fileCheck.o Student.o Simulation.o main.cpp -o a.out

clean:
	$(RM) $(OUT) $(O)