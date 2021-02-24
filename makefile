main.o: main.cpp Collection.h Stress_ball.h
	g++ -std=c++17 -c main.cpp
	
Collection.o: Collection.cpp Collection.h Stress_ball.h
	g++ -std=c++17 -c Collection.cpp

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	g++ -std=c++17 -c Stress_ball.cpp

all: main.o Collection.o Stress_ball.o 
	g++ -std=c++17 main.o Collection.o Stress_ball.o -o test

clean:
	rm -f *.o test

run: test
	./test