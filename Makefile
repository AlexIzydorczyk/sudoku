CXXFLAGS=-std=c++11 -Wall
LDFLAGS=-lm
OBJ=solver.o

all: $(OBJ)
	clang++ -std=c++11 -stdlib=libc++ main.cpp -o main $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -std=c++11 -stdlib=libc++ -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) main *.o
