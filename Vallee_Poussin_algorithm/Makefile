pr: main.o interpolation.o Pm.o gauss.o
	g++ main.o interpolation.o Pm.o gauss.o -o pr -O3

main.o: main.cpp interpolation.h Pm.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp -O3

interpolation.o: interpolation.cpp interpolation.h Pm.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c interpolation.cpp -O3

Pm.o: Pm.cpp interpolation.h Pm.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c Pm.cpp -O3

gauss.o: gauss.cpp interpolation.h Pm.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c gauss.cpp -O3

pic: graph.py
	python3 graph.py

clean:
	rm -f *.o *.stackdump pr

