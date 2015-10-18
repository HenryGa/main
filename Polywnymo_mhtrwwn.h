//
// Created by henry on 18/10/2015.
//

#ifndef _POLYWNYMO_MHTRWWN_H
#define _POLYWNYMO_MHTRWWN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Matrix.h"

template <typename T>
class Polywnymo_mhtrwwn : public Matrix<T> {

public:

    ~Polywnymo_mhtrwwn();

    virtual void print_Table();

    void generate(Matrix<int> &m1 , Matrix<int> &m2);

};


#endif //FUNCTION_TABLE_POLYWNYMO_MHTRWWN_H
