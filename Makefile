CC=clang++
all: solution clean

solution: main.o node.o token.o date.o database.o condition_parser.o
	$(CC) -std=c++17 ./bin/main.o ./bin/node.o ./bin/token.o ./bin/date.o ./bin/database.o ./bin/condition_parser.o -o ./bin/solution

main.o: main.cpp
	$(CC) -std=c++17 -c -Wall main.cpp -o ./bin/main.o

node.o: node.cpp
	$(CC) -std=c++17 -c -Wall node.cpp -o ./bin/node.o

token.o: token.cpp
	$(CC) -std=c++17 -c -Wall token.cpp -o ./bin/token.o

date.o: date.cpp
	$(CC) -std=c++17 -c -Wall date.cpp -o ./bin/date.o

database.o: database.cpp
	$(CC) -std=c++17 -c -Wall database.cpp -o ./bin/database.o

condition_parser.o: condition_parser.cpp
	$(CC) -std=c++17 -c -Wall condition_parser.cpp -o ./bin/condition_parser.o

test: test.cpp
	$(CC) -target x86_64-apple-darwin20.6.0 -arch x86_64 -std=c++17 -Wall test.cpp -o ./bin/test.o

clean:
	$(RM) ./bin/*.o
