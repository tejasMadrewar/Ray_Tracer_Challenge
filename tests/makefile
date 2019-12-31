#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++11 -g
OBJECTS = matTest.o tupleTest.o tuple.o point.o vec.o color.o canvas.o mat.o catchMain.o

.PHONY: clean all test format

all: test

AllTest.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@


# pattern rule for compiling the tests file
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

# pattern rule for compiling the src file
%.o: ..\src\%.cpp ..\src\%.h
	$(CC) $(CCFLAGS) -c $< 

test: AllTest.exe
	AllTest.exe -r console 

format:
	$(CLANG_FORMAT) -i *.cpp
	$(CLANG_FORMAT) -i ..\src\*.*
clean:
	del *.o *.exe *.ilk *.pdb *.ppm
