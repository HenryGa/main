//
// Created by henry on 18/10/2015.
//

#ifndef FUNCTION_TABLE_SYLVESTER_H
#define FUNCTION_TABLE_SYLVESTER_H

#include "Matrix.h"

template <typename T>
class Sylvester : public Matrix<T> {

    int m1grammes;
    int m2grammes;
    int m1sthles;
    int m2sthles;

public:

    ~Sylvester();

    void print_Table();
    void print_Table(char variable);

    void make_Sylvester(Matrix<int> &m1, Matrix<int> &m2, int d0, int d1);

    void fill_first_row_of_sylvester(Matrix<int> &m1, int first_row_pos, int dimension0);

    void shift_rest_first_half();

    void shift_rest_second_half();

    int get_vathmos(){return this->grammes;}

    int** multiply(Matrix<int> &v);
};


#endif //FUNCTION_TABLE_SYLVESTER_H
