pr: main.o fourier.o functions.o matrix.o
	g++  main.o fourier.o functions.o matrix.o -o pr

main.o: main.cpp  fourier.h functions.h matrix.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp

matrix.o: matrix.cpp matrix.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c matrix.cpp

fourier.o: fourier.cpp fourier.h functions.h matrix.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c fourier.cpp 

functions.o: functions.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c functions.cpp

pic: graph_p.py
	python3 graph.py

clean:
	rm -f *.o *.stackdump pr
