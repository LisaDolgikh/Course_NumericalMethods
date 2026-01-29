pr: main.o explicit_scheme.o functions.o
	g++  main.o explicit_scheme.o functions.o -o pr

main.o: main.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp

explicit_scheme.o: explicit_scheme.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c explicit_scheme.cpp 

functions.o: functions.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c functions.cpp

clean:
	rm -f *.o *.stackdump pr