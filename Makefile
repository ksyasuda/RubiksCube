CXX = g++

CXXFLAGS = -Wall -Werror -Wextra -pedantic --std=c++11 -Wconversion -O3 -DNDEBUG

DEBUG = -Wall -Werror -Wextra -pedantic --std=c++11 -Wconersion -g3 -DDEBUG

BIN := rcube

all: $(BIN)
	
$(BIN): cube.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


.SUFFIXES:

.PHONY: clean all
clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump rcube *.txt
