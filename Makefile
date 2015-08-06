CXXFLAGS += -std=c++14 -pedantic -Wall -O2
GMPLIB = -lgmp -lgmpxx

fib : fib.cpp power.hpp
	$(CXX) $(CXXFLAGS) $(GMPLIB) -o fib fib.cpp

transclos : transclos.cpp power.hpp matrix.hpp
	$(CXX) $(CXXFLAGS) -o transclos transclos.cpp
