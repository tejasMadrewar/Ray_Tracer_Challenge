#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++11 -g
OBJECTS = main.o tick.o canvas.o drawProjectile.o

.PHONY: clean all format

all: projectile_ppm

#projectile.exe: main.cpp projectile.h tick.h env.h
projectile_ppm.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@
#$(CC) $(CCFLAGS) $< -o $@

projectile_ppm: projectile_ppm.exe
	projectile_ppm.exe

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
