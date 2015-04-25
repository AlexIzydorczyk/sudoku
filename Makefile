CXXFLAGS=-std=c++11 -Wall
LDFLAGS=-lm -larmadillo
OBJ=solver.o altproj.o

all: $(OBJ)
	$(CXX) main.cpp -o main $(OBJ) $(CXXFLAGS) $(LDFLAGS)

debug: $(OBJ)
	$(CXX) debug.cpp -o debug $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) main debug

