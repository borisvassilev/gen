CXXFLAGS += -std=c++14 -pedantic -Wall -O2
GMPLIB = -lgmp -lgmpxx

fib : fib.cpp power.hpp
	$(CXX) $(CXXFLAGS) $(GMPLIB) -o fib fib.cpp
