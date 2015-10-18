//
// Created by henry on 13/10/2015.
//

#ifndef FUNCTION_TABLE_MAIN_HPP
#define FUNCTION_TABLE_MAIN_HPP

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
//#include "PyknhAnaparastash.cpp"
//#include "PyknhAnaparastash.hpp"

#define BUFFSIZE 1000

struct details{

    int maxXpower;
    int maxYpower;

};

using namespace std;

void Read_d1_d2_From_File( char * filename , int * , int * );

char Read_synarthsh_from_file(char *filenameint, Matrix<int> & ,Matrix<int> & m2);

struct details * place_function_in_Matrix(char * buffer , Matrix<int> &);

#endif //FUNCTION_TABLE_MAIN_HPP
