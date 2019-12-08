CC = g++
CCFLAGS = -s -std=c++11 
OBJECTS = tupleTest.o tuple.o point.o vec.o catchMain.o

.PHONY: clean all test

all: test

tupleTest: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@


# pattern rule for compiling the tests file
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

# pattern rule for compiling the src file
%.o: ..\src\%.cpp ..\src\%.h
	$(CC) $(CCFLAGS) -c $< 

test: tupleTest
	tupleTest.exe -r console 

clean:
	del *.o *.exe
