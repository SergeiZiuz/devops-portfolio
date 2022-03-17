all: 
	g++ -std=c++17 -o main.o main.cpp node.cpp token.cpp date.cpp database.cpp condition_parser.cpp supportedFunctionsForTestDatabase.cpp test_runner.cpp 

clean:
	$(RM) solution
