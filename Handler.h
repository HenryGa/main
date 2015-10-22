//
// Created by henry on 21/10/2015.
//

#ifndef FUNCTION_TABLE_HANDLER_H
#define FUNCTION_TABLE_HANDLER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "Matrix.cpp"
#include "Pinakas_syntelestwn.hpp"
#include "Pinakas_syntelestwn.cpp"
#include "Polywnymo_mhtrwwn.h"
#include "Polywnymo_mhtrwwn.cpp"
#include "Pinakas_polywnymou_mhtrwwn.h"
#include "Pinakas_polywnymou_mhtrwwn.cpp"
#include "Sylvester.h"
#include "Sylvester.cpp"

#define BUFFSIZE 1000

class Handler {

private:

    int d0,s0;
    int d1,s1;

    char hidden_variable;


    int *** result;
    Pinakas_syntelestwn<int> m1;
    Pinakas_syntelestwn<int> m2;
    Sylvester <int*> sylvester;
//    Pinakas_syntelestwn<int> v;
    Polywnymo_mhtrwwn< Pinakas_polywnymou_mhtrwwn<int*> *> Polywnymo_Mhtrwwn;

    char Read_synarthsh_from_file(char *filename );

    void place_function_in_Matrix(char * buffer , Matrix<int> &);

    char find_hidden_variable( Matrix<int> & m1 , Matrix<int> & m2);

    void read( char * filename );

    void consola();

    void generate();

public:

    void handle_input(int argc, char * argv[]);

    int getD0() const { return d0; }

    int getD1() const { return d1; }

    int getHidden_Variable() const { return hidden_variable; }

    Pinakas_syntelestwn<int> getM1() const { return m1; }

    Pinakas_syntelestwn<int> getM2() const { return m2; }

    void generate_Sylvester();

    void generate_Polywnymo_Mhtrwwn();

    void print();

    void generate_Bonus();

};


#endif //FUNCTION_TABLE_HANDLER_H
