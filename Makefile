magma: gost.o main.o
	g++ gost.o main.o -o magma -std=c++11

gost.o: gost.cpp
	g++ -c gost.cpp -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

clean:
	rm *.o
