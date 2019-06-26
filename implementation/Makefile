CXX = g++

CXXFLAGS = -std=c++11 -O3 -Wall

INCLUDE = -I $(CURDIR)/include

all: localmin.out

localmin.out: build/localmin.o build/main.o
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

build/%.o: src/%.cpp include/%.hpp
		$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

build/main.o: src/main.cpp include/localmin.hpp
		$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
		rm -f build/*.o *.out
