# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -I/usr/include
LDFLAGS = -lm -larmadillo

# Object files
OBJ = solver.o altproj.o game.o tests.o

# Default target
all: sudoku

# Linking the executable for the main build
sudoku: $(OBJ) main.o
	$(CXX) main.o $(OBJ) -o sudoku $(CXXFLAGS) $(LDFLAGS)

# Linking the executable for the debug build
debug: $(OBJ) debug.o
	$(CXX) debug.o $(OBJ) -o debug $(CXXFLAGS) $(LDFLAGS)

# Rule for compiling .cpp files to .o files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean target
clean:
	rm -f $(OBJ) main.o debug.o sudoku debug

