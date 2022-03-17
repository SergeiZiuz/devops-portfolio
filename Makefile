all: 
	g++ -std=c++20 -o main.o main.cpp node.cpp token.cpp date.cpp database.cpp condition_parser.cpp supportedFunctionsForTestDatabase.cpp test_runner.cpp condition_parser_test.cpp

clean:
	$(RM) solution
