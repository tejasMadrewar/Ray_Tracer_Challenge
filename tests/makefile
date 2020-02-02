CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++11 -g

TESTS = $(wildcard *.cpp)
OBJTESTS = $(TESTS:.cpp=.o)

SRCFILES = $(notdir $(wildcard ../src/*.cpp))
OBJSRCFILES = $(SRCFILES:.cpp=.o)

OBJECTS = $(OBJTESTS) $(OBJSRCFILES)

.PHONY: clean all test format

all: test

AllTests.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@

point.o: tuple.o
vec.o: tuple.o
color.o: tuple.o
mat.o: tuple.o
canvas.o: color.o
transform.o: mat.o
ray.o: point.o vec.o mat.o
sphere.o: ray.o object.o intersection.o mat.o material.o
intersection.o: object.o
light.o: color.o point.o
material.o: color.o light.o
world.o: light.o material.o object.o
transformation.o: point.o vec.o transform.o
camera.o: canvas.o mat.o ray.o transformation.o world.o

tupleTest.o: tuple.o vec.o point.o color.o canvas.o
matTest.o: mat.o
transformTest.o: transform.o
sphereTest.o: sphere.o
intersectionTest.o: sphere.o intersection.o
lightTest.o: light.o
materialTest.o: material.o
worldTest.o: world.o
transformationTest.o:transformation.o
cameraTest.o: camera.o

# pattern rule for compiling the tests file
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@ 

# pattern rule for compiling the src file
%.o: ..\src\%.cpp ..\src\%.h
	$(CC) $(CCFLAGS) -c $< -o $@ 

test: AllTests.exe
	AllTests.exe -r console 

format:
	$(CLANG_FORMAT) -i *.cpp
	$(CLANG_FORMAT) -i ../src/*.cpp
	$(CLANG_FORMAT) -i ../src/*.h

clean:
	del *.o *.exe *.ilk *.pdb *.ppm
