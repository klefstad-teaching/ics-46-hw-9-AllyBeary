F = -std=c++20 -Wall -Wextra -Wpedantic -Wfatal-errors
P = ladder
def: $P
main: src/dijkstras_main.cpp src/dijkstras.cpp
	g++ $F src/dijkstras_main.cpp src/dijkstras.cpp -o main

ladder: src/ladder_main.cpp src/ladder.cpp 
	g++ $F src/ladder_main.cpp src/ladder.cpp -o ladder

clean: 
	/bin/rm -f main $P