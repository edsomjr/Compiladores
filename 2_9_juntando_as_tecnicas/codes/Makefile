SOURCES=${shell find . -type f -name "*.cpp"}
OBJECTS=$(SOURCES:.cpp=.o)

.cpp.o:
	g++ -c $< -Wall -std=c++20

all: prog

prog: $(OBJECTS)
	g++ -o $@ $(OBJECTS)

clean:
	@rm -f *.o prog
