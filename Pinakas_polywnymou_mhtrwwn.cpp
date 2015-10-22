//
// Created by henry on 18/10/2015.
//

#include "Pinakas_polywnymou_mhtrwwn.h"

using namespace std;

template <typename T>
void Pinakas_polywnymou_mhtrwwn<T>::print_Table(){

    for (int i = 0; i < this->grammes ; ++i) {
        for (int j = 0; j < this->sthles ; ++j) {

            if( this->table[i][j] != NULL )
                cout << *( this->table[i][j] ) << " ";
            else
                cout << "0 ";

        }
        cout << endl;
    }

}

/*
 * Paragei to mhtrwo me ari8mo yPower
 * 1o orisma = pinakas Sylvester
 * 2o orisma = dynamh tou y me thn opoia pollaplasiazw to paragwmeno pinaka
 */
template <typename T>
void Pinakas_polywnymou_mhtrwwn<T>::generate_Mhtrwo( Matrix<int > & m1 , Matrix<int> & m2, int column){

    int m1sthles = m1.get_sthles();
    int m2sthles = m2.get_sthles();
    int m1grammes = m1.get_grammes();
    int m2grammes = m2.get_grammes();

    int a;

    for (int i = 0; i < this->grammes; ++i)
    {
        for (int j = 0; j < this->sthles; ++j)
        {
            this->table[i][j] = NULL;
        }
    }

    if( m1sthles-1 - column >=0 ){
        a = m1grammes-1;
        for (int i = 0; i < m1grammes ; ++i)
        {
            this->table[0][i] = m1.get_element(a-i,column);
        }

        

        //fill
        for (int j = m1grammes; j < this->sthles ; ++j)
        {
            this->table[0][j] = NULL;
        }
        //-----

        //shift
        for (int i = 1; i < m2grammes-1; ++i)
        {
            this->table[i][0] = NULL;
            for (int j = 1; j < this->sthles; ++j)
            {
                this->table[i][j] = this->table[i-1][j-1];
            }
            
            /* code */
        }
        //------
    }

    if( m2sthles-1 - column >= 0 ){
        //make 1rst row
        a = m2grammes-1;
        for (int j = 0 ; j < m2grammes ; ++j)
        {
            this->table[m2grammes-1][j] = m2.get_element(a-j,column);
        }

        //fill
        for (int i = m2grammes; i < this->grammes ; ++i)
        {
            this->table[m2grammes-1][i] = NULL;
        }
        //-----

        //shift
        for (int i = m2grammes; i < this->grammes; ++i)
        {
            this->table[i][0] = NULL;
            for (int j = 1; j < this->sthles; ++j)
            {
                this->table[i][j] = this->table[i-1][j-1];
            }
        }
        //------
    }

}

template <typename T>
Pinakas_polywnymou_mhtrwwn<T>::~Pinakas_polywnymou_mhtrwwn() {


    for (int i = 0; i < this->grammes; ++i) {
        delete[] this->table[i];
    }
    delete[] this->table;


}
