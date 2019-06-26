CXX = g++

CXXFLAGS = -std=c++11 -O3 -Wall

INCLUDE = -I $(CURDIR)/include

all: run_individual_instance.out

run_individual_instance.out: build/localmin.o build/run_individual_instance.o
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

build/%.o: src/%.cpp include/%.hpp
		$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

build/run_individual_instance.o: src/run_individual_instance.cpp include/localmin.hpp
		$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
		rm -f build/*.o *.out
