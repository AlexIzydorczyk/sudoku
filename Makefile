CXXFLAGS=-std=c++11 -Wall
LDFLAGS=-lm
OBJ=solver.o

all: $(OBJ)
	g++ main.cpp -o main $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) main *.o
