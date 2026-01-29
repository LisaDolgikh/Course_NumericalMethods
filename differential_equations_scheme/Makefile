pr: main.o solve.o 
	g++  main.o solve.o -o pr

main.o: main.cpp  solve.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp

solve.o: solve.cpp solve.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c solve.cpp

pic: graph_p.py
	python3 graph.py

clean:
	rm -f *.o *.stackdump pr
