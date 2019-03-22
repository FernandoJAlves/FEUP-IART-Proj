SRC = main.cpp menus.cpp map.cpp game.cpp


all:
	g++ $(SRC) -Wall -o run

debug:
	g++ -g $(SRC) -Wall -o run

clean:
	rm run