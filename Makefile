CXXFLAGS=-std=c++11 -Wall
LDFLAGS=-lm -larmadillo
OBJ=solver.o altproj.o

all: $(OBJ)
	$(CXX) -std=c++11 -stdlib=libc++ main.cpp -o main $(OBJ) $(CXXFLAGS) $(LDFLAGS)

debug: $(OBJ)
	$(CXX) altproj.cpp -o debug $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -std=c++11 -stdlib=libc++ -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) main *.o