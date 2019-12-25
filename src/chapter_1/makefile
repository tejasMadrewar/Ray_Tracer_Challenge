#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++11 
OBJECTS = main.o tick.o

.PHONY: clean all format

all: format projectile

#projectile.exe: main.cpp projectile.h tick.h env.h
projectile.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@
#$(CC) $(CCFLAGS) $< -o $@

projectile: projectile.exe
	projectile.exe

%.o:%.cpp %.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

format:
	$(CLANG_FORMAT) -i *.cpp *.h
clean:
	del *.o *.exe
