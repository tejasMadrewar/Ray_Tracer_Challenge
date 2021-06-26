CXX = clang++

CLANG_FORMAT = clang-format

DEBUG_ARGS = -g
DEP_ARGS = -MMD -MP
CXX_STD = -std=c++14

CCFLAGS = $(CXX_STD) $(DEBUG_ARGS) $(DEP_ARGS)
LINKERFLAGS =

TESTS = $(wildcard *.cpp)
OBJTESTS = $(TESTS:.cpp=.o)

SRCFILES = $(notdir $(wildcard ../src/*.cpp))
OBJSRCFILES = $(SRCFILES:.cpp=.o)

OBJECTS = $(OBJTESTS) $(OBJSRCFILES)

CHAPFOLDERS = $(dir $(wildcard ../src/chap*/))
CHAPFILESH = $(wildcard ../src/chap*/*.h)
CHAPFILESCPP = $(wildcard ../src/chap*/*.cpp)

.PHONY: clean all test format

all: format test

# include dep files
-include $(OBJECTS:.o=.d)

AllTests.exe: $(OBJECTS)
	@echo Linking $@
	@$(CXX) $(CCFLAGS) $^ -o $@

# pattern rule for compiling the tests file
%.o: %.cpp
	@echo Compiling $*.o
	@$(CXX) $(CCFLAGS) -c $< -o $@ 

# pattern rule for compiling the src file
%.o: ..\src\%.cpp ..\src\%.h
	@echo Compiling $*.o
	@$(CXX) $(CCFLAGS) -c $< -o $@ 

test: AllTests.exe
	AllTests.exe -r console 

format:
	@echo Formatting code
	@$(CLANG_FORMAT) -i *.cpp
	@$(CLANG_FORMAT) -i ../src/*.cpp
	@$(CLANG_FORMAT) -i ../src/*.h
	@$(CLANG_FORMAT) -i $(CHAPFILESCPP)
	@$(CLANG_FORMAT) -i $(CHAPFILESH)

clean:
	del *.o *.exe *.ilk *.pdb *.ppm *.d
