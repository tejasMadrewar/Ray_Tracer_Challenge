#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++14 -g
OBJECTS = main.o tick.o canvas.o drawProjectile.o

.PHONY: clean all format

all: main.exe

#projectile.exe: main.cpp projectile.h tick.h env.h
main.exe: $(OBJECTS)
#main.exe: canvas.o main.o
	$(CC) $(CCFLAGS) $^ -o $@

%.o:%.cpp %.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:../%.cpp ../%.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: ../chapter_1/%.cpp ../chapter_1/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

%.o:%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	del *.o *.exe *.ppm *.ilk *.pdb
