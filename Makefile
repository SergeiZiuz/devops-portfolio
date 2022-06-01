obj_files = main.o node.o token.o date.o database.o condition_parser.o
src_files = main.cpp node.cpp token.cpp date.cpp database.cpp condition_parser.cpp
all: solution clean

solution: main.o node.o token.o date.o database.o condition_parser.o
	# $(CXX) -std=c++17 $^ -o  $(CFLAGS) $(LDFLAGS)
	$(CXX) -std=c++17 ./bin/main.o ./bin/node.o ./bin/token.o ./bin/date.o ./bin/database.o ./bin/condition_parser.o -o ./bin/solution $(CFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) -std=c++17 -c -Wall main.cpp -o ./bin/main.o

node.o: node.cpp
	$(CXX) -std=c++17 -c -Wall node.cpp -o ./bin/node.o

token.o: token.cpp
	$(CXX) -std=c++17 -c -Wall token.cpp -o ./bin/token.o

date.o: date.cpp
	$(CXX) -std=c++17 -c -Wall date.cpp -o ./bin/date.o

database.o: database.cpp
	$(CXX) -std=c++17 -c -Wall database.cpp -o ./bin/database.o

condition_parser.o: condition_parser.cpp
	$(CXX) -std=c++17 -c -Wall condition_parser.cpp -o ./bin/condition_parser.o

test: test.cpp
	$(CXX) -std=c++17 -Wall test.cpp -o ./bin/test.o $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS)

clean:
	$(RM) ./bin/*.o
