.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Bag.o Board.o Tile.o Node.o LinkedList.o qwirkle.o Game.o Player.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
