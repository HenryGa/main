all: main generate

main: main.cpp Matrix.o Polywnymo_mhtrwwn.o Pinakas_syntelestwn.o Sylvester.o Pinakas_polywnymou_mhtrwwn.o
	g++ -o main Matrix.o Polywnymo_mhtrwwn.o Pinakas_syntelestwn.o Sylvester.o Pinakas_polywnymou_mhtrwwn.o main.cpp main.hpp  -g3 

Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp Matrix.h

generate: generate_functions.cpp
	g++ -o generate generate_functions.cpp

Pinakas_syntelestwn.o: Pinakas_syntelestwn.cpp
	g++ -c Pinakas_syntelestwn.cpp Pinakas_syntelestwn.hpp

Polywnymo_mhtrwwn.o: Polywnymo_mhtrwwn.cpp
	g++ -c Polywnymo_mhtrwwn.cpp Polywnymo_mhtrwwn.h

Pinakas_polywnymou_mhtrwwn.o:Pinakas_polywnymou_mhtrwwn.cpp
	g++ -c Pinakas_polywnymou_mhtrwwn.cpp Pinakas_polywnymou_mhtrwwn.h

Sylvester.o: Sylvester.cpp
	g++ -c Sylvester.cpp Sylvester.h

clean:
	rm -f *.o main
