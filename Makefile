#CXX=clang++
CXX=g++
CXXFLAGS=-std=c++11 -stdlib=libc++ -Wall
LDFLAGS=-lm -larmadillo
OBJ=solver.o altproj.o

all: $(OBJ)
	$(CXX) main.cpp -o main $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) main *.o
