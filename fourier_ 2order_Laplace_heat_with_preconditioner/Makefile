pr: main.o pde_2d.o fourier.o functions.o bsolver.o
	g++  main.o pde_2d.o fourier.o functions.o bsolver.o -o pr

pr_1: test1.o pde_2d.o fourier.o functions.o
	g++  test1.o pde_2d.o fourier.o functions.o -o pr_1

pr_2: test2.o pde_2d.o fourier.o functions.o bsolver.o
	g++  test2.o pde_2d.o fourier.o functions.o bsolver.o -o pr_2

test1.o: test1.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c test1.cpp

test2.o: test2.cpp functions.h fourier.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c test2.cpp

main.o: main.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp

pde_2d.o: pde_2d.cpp functions.h fourier.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c pde_2d.cpp

bsolver.o: bsolver.cpp functions.h fourier.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c bsolver.cpp

fourier.o: fourier.cpp fourier.h functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c fourier.cpp 

functions.o: functions.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c functions.cpp

clean:
	rm -f *.o *.stackdump pr pr_1 pr_2