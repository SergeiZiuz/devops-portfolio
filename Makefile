all: solution clean

solution: main.o node.o token.o date.o database.o condition_parser.o
	g++ -std=c++17 ./bin/main.o ./bin/node.o ./bin/token.o ./bin/date.o ./bin/database.o ./bin/condition_parser.o -o ./bin/solution

main.o: main.cpp
	g++ -std=c++17 -c -Wall main.cpp -o ./bin/main.o

node.o: node.cpp
	g++ -std=c++17 -c -Wall node.cpp -o ./bin/node.o

token.o: token.cpp
	g++ -std=c++17 -c -Wall token.cpp -o ./bin/token.o

date.o: date.cpp
	g++ -std=c++17 -c -Wall date.cpp -o ./bin/date.o

database.o: database.cpp
	g++ -std=c++17 -c -Wall database.cpp -o ./bin/database.o

condition_parser.o: condition_parser.cpp
	g++ -std=c++17 -c -Wall condition_parser.cpp -o ./bin/condition_parser.o

clean:
	$(RM) ./bin/*.o
