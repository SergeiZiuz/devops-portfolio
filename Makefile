all: 
	g++ -std=c++17 -o main.o main.cpp node.cpp token.cpp date.cpp database.cpp condition_parser.cpp 
	g++ -std=c++17 -o test.o test.cpp supportedFunctionsForTestDatabase.cpp test_runner.cpp condition_parser_test.cpp


clean:
	$(RM) solution
