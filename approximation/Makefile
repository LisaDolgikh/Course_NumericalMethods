pr: main.o approximation.o Ln.o Pn.o gauss.o
	g++ main.o approximation.o Ln.o Pn.o gauss.o -o pr -O3

main.o: main.cpp approximation.h Ln.h Pn.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp -O3

approximation.o: approximation.cpp approximation.h Ln.h Pn.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c approximation.cpp -O3

Ln.o: Ln.cpp approximation.h Ln.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c Ln.cpp -O3

Pn.o: Pn.cpp approximation.h Pn.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c Pn.cpp -O3

gauss.o: gauss.cpp approximation.h Pn.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c gauss.cpp -O3

clean:
	rm -f *.o *.stackdump pr

