#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++14 -g
OBJECTS = 

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

#OBJECTS += $(OBJ)
OBJECTS = canvas.o main.o

.PHONY: clean all format

all: main

main.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@

main: main.exe
	main.exe

%.o:%.cpp %.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:../%.cpp ../%.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

format:
	$(CLANG_FORMAT) -i *.cpp

clean:
	del *.o *.exe *.ppm *.ilk *.pdb
