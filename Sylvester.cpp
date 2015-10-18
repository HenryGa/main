//
// Created by henry on 18/10/2015.
//

#include "Sylvester.h"

using namespace std;

template < typename T >
Sylvester<T>::~Sylvester(){

    for (int i = 0; i < this->grammes; ++i) {
        delete[] this->table[i];
    }
}



template < typename T >
void Sylvester <T> :: make_Sylvester( Matrix<int> &m1, Matrix<int> & m2 ,int d0 , int d1) {

    /*
     * 1o orisma = pyknh anaparastash ths ekshswshs pou 8elw na apo8hkeusw
     * 2o orisma= grammh sthn opoia ksekina na topo8etountai oi syntelestes ths ktymenh metavlhts
     * 3o orisma = grammes tou m1
     */
    fill_first_row_of_sylvester(m1, 0, d0 + 1 );

    shift_rest_first_half( d1 ); // gemisei mexri th grammh d1-1

    //------------- 2h eksiswsh ------------------

    fill_first_row_of_sylvester(m2, d1 , d1 + 1 ); // grafw sth grammh d1 mexri th sthlh d1+1->gia akeraious

    shift_rest_second_half( d1 + 1 );

    //------------------------------------

}

/*
	 * 1o orisma = pyknh anaparastash ths ekshswshs pou 8elw na apo8hkeusw
	 * 2o orisma= grammh sthn opoia ksekina na topo8etountai oi eksiswseis me th ktymenh metavlhts
	 * 3o orisma = grammes tou m1
*/
template <typename T>
void Sylvester<T>::fill_first_row_of_sylvester(Matrix<int> &m1, int first_row_pos, int dimension0) {

    /*
     * to dimension0 mou leei oti diavazw mexri th grammh dimensio0 tou pinaka syntelestwn m1
     * kai apo8hkeuw mexri th sthlh dimesnison0 -1  tou sylvester
    */

    int j = 0;
    for (j = 0; j < dimension0 ; j++ )
    {
        this->table[first_row_pos][j] = m1.get_table_row(dimension0-j-1);
    }
    for (int i = dimension0 ; i < this->sthles; ++i) {
        this->table[first_row_pos][i] = NULL;
    }

}

template <typename T>
void Sylvester<T>::shift_rest_first_half(int dimension1) {

    for( int i  = 1 ; i < dimension1  ; i++  ) {

        this->table[i][0] = NULL;

        int j=1;
        while(j < this->sthles)
        {
            this->table[i][j]=this->table[i-1][j-1];
            j++;
        }
    }

}

template <typename T>
void Sylvester<T>::shift_rest_second_half( int dimension1) {

    for( int i  = dimension1 ; i < this->grammes  ; i++  ) {

        this->table[i][0] = NULL;

        int j=1;
        while( j < this->sthles)
        {
            this->table[i][j]=this->table[i-1][j-1];
            j++;
        }
    }

}

template <typename T>
void Sylvester<T>::print_Table(){

    cout << "Sylvester needs a variable m1Columns , m2Columns in order to print\n";

}

template <typename T>
void Sylvester<T>::print_Table(char variable, int m1Sthles, int m2Sthles , int d1  ) {

    for( int i = 0 ; i < this->grammes ; i++ )
    {
        for ( int j  = 0  ; j < this->sthles ; j ++)
        {
            if ( this->table[i][j] == NULL)
                cout << "0 ";
            else
            {
                cout << "( " << this->table[i][j][0] << " ";
                if( i < d1 )
                {
                    for (int k = 1; k < m1Sthles; ++k)
                    {
                        if( this->table[i][j][k] == 0) {
                            continue;
                        }

                        if (this->table[i][j][k] > 0)
                            cout << "+ " << this->table[i][j][k] << variable<< "^" << k << " ";
                        else
                            cout << this->table[i][j][k] <<variable << "^" << k << " ";

                    }
                }
                else
                {
                    for (int k = 1; k < m2Sthles; ++k)
                    {
//                        cout << "k = " << k << "---";
                        if( this->table[i][j][k] == 0) {
                            continue;
                        }

                        if (this->table[i][j][k] > 0 )
                            cout << "+" << this->table[i][j][k] << variable <<"^" << k << " ";
                        else
                            cout << this->table[i][j][k] << variable << "^" << k << " ";

                    }
                }

                cout << ") ";
            }
        }
        cout << endl;
    }

}