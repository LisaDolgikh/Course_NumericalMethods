pr: main.o integration.o functions.o
	g++ main.o integration.o functions.o -o pr -O3

main.o: main.cpp integration.h functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp -O3

integration.o: integration.cpp integration.h functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c integration.cpp -O3

functions.o: functions.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c functions.cpp -O3

pic: graph_p.py
	python3 graph_p.py

clean:
	rm -f *.o *.stackdump pr