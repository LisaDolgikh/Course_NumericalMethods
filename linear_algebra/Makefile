pr: main_1.o main_2.o main_3.o fourier.o functions.o matrix.o
	g++  main_1.o main_2.o main_3.o fourier.o functions.o matrix.o -o pr

pr_1: main_1.o fourier.o functions.o matrix.o
	g++  main_1.o fourier.o functions.o matrix.o -o pr_1

pr_2: main_2.o fourier.o functions.o matrix.o richardson.o
	g++  main_2.o fourier.o functions.o matrix.o richardson.o -o pr_2

pr_3: main_3.o fourier.o functions.o matrix.o bsolver.o
	g++  main_3.o fourier.o functions.o matrix.o bsolver.o -o pr_3


main_1.o: main_1.cpp  fourier.h functions.h matrix.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main_1.cpp


main_2.o: main_2.cpp  fourier.h functions.h matrix.h richardson.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main_2.cpp

main_3.o: main_3.cpp  fourier.h functions.h matrix.h bsolver.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main_3.cpp

matrix.o: matrix.cpp matrix.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c matrix.cpp

fourier.o: fourier.cpp fourier.h functions.h matrix.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c fourier.cpp 

richardson.o: richardson.cpp fourier.h functions.h matrix.h richardson.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c richardson.cpp

bsolver.o: bsolver.cpp fourier.h functions.h matrix.h bsolver.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c bsolver.cpp

functions.o: functions.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c functions.cpp


pic: graph_p.py
	python3 graph.py

clean:
	rm -f *.o *.stackdump pr pr_1 pr_2 pr_3
