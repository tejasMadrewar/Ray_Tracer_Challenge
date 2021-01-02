CC = clang++
CLANG_FORMAT = clang-format
#CCFLAGS = -std=c++11 -g
CCFLAGS = -std=c++14 -O2
OBJECTS = 

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

OBJECTS = main.o canvas.o intersection.o shape.o sphere.o pattern.o mat.o transform.o

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
