FLAGS=-W -Wall -fmax-errors=1

main : p4.o
	g++ p4.o -o main	

p4.o : p4.cpp
	g++ -c $(FLAGS) p4.cpp