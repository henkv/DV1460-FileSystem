CFLAGS=-Wall -O2 -std=c++11

SRCFOLDER=FileSystem
BINFOLDER=bin
TESTFLAG=-I $(SRCFOLDER)/

CPP_FILES = $(filter-out $(SRCFOLDER)/shell.cpp, $(wildcard $(SRCFOLDER)/*.cpp))
OBJ_FILES = $(addprefix $(BINFOLDER)/, $(notdir $(CPP_FILES:.cpp=.o)))

all: bin/shell


# Creates the executable
bin/shell: $(OBJ_FILES) src/shell.cpp
	g++ $(CFLAGS) $^ -o $@

# Compiling all classes into object files
bin/%.o: src/%.cpp
	@mkdir -p bin
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin
