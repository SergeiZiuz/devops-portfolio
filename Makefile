CC=clang++
all: solution clean

solution: main.o node.o token.o date.o database.o condition_parser.o
	$(CC) -std=gnu++17 -stdlib=libc++ ./bin/main.o ./bin/node.o ./bin/token.o ./bin/date.o ./bin/database.o ./bin/condition_parser.o -o ./bin/solution

main.o: main.cpp
	$(CC) -std=gnu++17 -stdlib=libc++ -c -Wall main.cpp -o ./bin/main.o

node.o: node.cpp
	$(CC) -std=gnu++17 -stdlib=libc++ -c -Wall node.cpp -o ./bin/node.o

token.o: token.cpp
	$(CC) -std=gnu++17 -stdlib=libc++ -c -Wall token.cpp -o ./bin/token.o

date.o: date.cpp
	$(CC) -std=gnu++17 -stdlib=libc++ -c -Wall date.cpp -o ./bin/date.o

database.o: database.cpp
	$(CC) -std=gnu++17 -stdlib=libc++ -c -Wall database.cpp -o ./bin/database.o

condition_parser.o: condition_parser.cpp
	$(CC) -std=gnu++17 -stdlib=libc++ -c -Wall condition_parser.cpp -o ./bin/condition_parser.o

clean:
	$(RM) ./bin/*.o
