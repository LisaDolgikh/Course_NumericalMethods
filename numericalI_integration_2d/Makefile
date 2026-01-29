pr: main.o integration.o functions.o splitting.o
	g++ main.o integration.o functions.o splitting.o -o pr -O3

split: main_split.o functions.o splitting.o
	g++ main_split.o functions.o splitting.o -o pr_split -O3

integ: main_integ.o functions.o integration.o
	g++ main_integ.o functions.o integration.o -o pr_integ -O3

main.o: main.cpp splitting.h functions.h integration.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp -O3

main_split.o: main_split.cpp splitting.h functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main_split.cpp -O3

main_integ.o: main_integ.cpp integration.h functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main_integ.cpp -O3


integration.o: integration.cpp integration.h functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c integration.cpp -O3

functions.o: functions.cpp functions.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c functions.cpp -O3

splitting.o: splitting.cpp splitting.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c splitting.cpp -O3

pic: graph_p.py
	python3 graph_p.py

clean:
	rm -f *.o *.stackdump pr pr_integ pr_split
