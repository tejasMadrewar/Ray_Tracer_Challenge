#CC = g++
CC = clang++
CLANG_FORMAT = clang-format
CCFLAGS = -std=c++11 
OBJECTS = tupleTest.o tuple.o point.o vec.o color.o canvas.o catchMain.o

.PHONY: clean all test format

all: test

tupleTest.exe: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@


# pattern rule for compiling the tests file
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

# pattern rule for compiling the src file
%.o: ..\src\%.cpp ..\src\%.h
	$(CC) $(CCFLAGS) -c $< 

test: tupleTest.exe
	tupleTest.exe -r console 

format:
	$(CLANG_FORMAT) -i *.cpp
	$(CLANG_FORMAT) -i ..\src\*.*
clean:
	del *.o *.exe
