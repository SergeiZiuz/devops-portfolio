all: 
	g++ -std=c++17 -o bin/main.o main.cpp node.cpp token.cpp date.cpp database.cpp condition_parser.cpp

clean:
	$(RM) solution
