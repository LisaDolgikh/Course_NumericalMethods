pr: main.o fourier.o
	g++ main.o fourier.o -o pr -O3

main.o: main.cpp fourier.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp -O3

fourier.o: fourier.cpp fourier.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c fourier.cpp -O3


clean:
	rm -f *.o pr
