CC = clang++
CLANG_FORMAT = clang-format
#CCFLAGS = -std=c++11 -g
CCFLAGS = -std=c++14 -O2
OBJECTS = 

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
OBJPPM = $(patsubst %.cpp,%.ppm,$(SRC))
OBJEXE = $(patsubst %.cpp,%.exe,$(SRC))

#OBJECTS += $(OBJ)
OBJECTS = camera.o shape.o sphere.o plane.o canvas.o world.o


.PHONY: clean all format

#all: $(OBJPPM) $(OBJEXE)
all: $(OBJPPM)

%.exe: %.o $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@

%.ppm: %.exe
	$^

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
