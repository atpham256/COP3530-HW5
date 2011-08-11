all:
	make hw5prob1 hw5prob2
hw5prob1: hw5prob1.o
	g++ -g -Wall -o hw5prob1 hw5prob1.o
hw5prob1.o: hw5prob1.cpp
	g++ -g -Wall -c hw5prob1.cpp
hw5prob2: hw5prob2.o
	g++ -g -Wall -o hw5prob2 hw5prob2.o
hw5prob2.o: hw5prob2.cpp
	g++ -g -Wall -c hw5prob2.cpp
clean:
	rm *.o hw5prob1 hw5prob2
