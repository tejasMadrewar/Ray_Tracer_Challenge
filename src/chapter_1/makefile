#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++11 
#OBJECTS = main.o tick.o
SRCFILES = $(wildcard *.cpp)
OBJECTS = $(SRCFILES:.cpp=.o)

.PHONY: clean all format

all: format main

#main.exe: main.cpp projectile.h tick.h env.h
main.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@
#$(CC) $(CCFLAGS) $< -o $@

main: main.exe
	main.exe

%.o:%.cpp %.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

format:
	$(CLANG_FORMAT) -i *.cpp *.h
clean:
	del *.o *.exe
