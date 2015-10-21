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


/*
 * efarmozetai mono otan o sylveter exei mesa tou pinakes idiou mhkous
 * kai to v exei oses sthles exoun mesa oi pinakes tou sylvester
 * epishs o sylvester prepei na exei mi
 */

template < typename T >
int** Sylvester <T> :: multiply(Matrix<int> & v){

    int vSthles = v.get_sthles();
    int sylv_grammes = this->get_grammes();
    int sylv_sthles = this->get_sthles();

    int ** result = (int **) new int*[sylv_grammes];

    for (int k = 0; k < sylv_grammes; ++k) {
        result[k] = new int[sylv_sthles];
    }

    for (int l = 0; l < sylv_grammes; ++l) {
        for (int k = 0; k < sylv_sthles; ++k) {
            result[l][k] = 0;
        }
    }

    // ftiaxnw prwth grammh
    for (int m = 0; m <sylv_sthles ; ++m) {

        if( this->table[0][m] != NULL )
            for (int i = 0; i < vSthles; ++i) {
                result[0][i] += this->table[0][m][i] * v.get_int_element(0, m);
                cout << this->table[0][m][i] << " " <<  v.get_int_element(0, m);
                getchar();
            }
    }

    //kanw shift()
    for (int n = 1; n < m2grammes-1; ++n) {
        for (int i = 1; i < sylv_sthles; ++i) {
            result [n][i] = result[n-1][i-1];
        }
    }
    //-------------


    // ftiaxnw prwth grammh m2
    for (int m = 0; m < sylv_sthles ; ++m) {

        if( this->table[m2grammes-1][m] != NULL )
            for (int i = 0; i < vSthles; ++i) {
                result[m2grammes-1][i] += this->table[m2grammes-1][m][i] * v.get_int_element(0, m);
            }
    }

    //kanw shift()
    for (int n = m2grammes ; n < sylv_grammes; ++n) {
        for (int i = 1; i < sylv_sthles; ++i) {
            result [n][i] = result[n-1][i-1];
        }
    }
    //-------------


    for (int i = 0; i < sylv_grammes; ++i) {
        for (int  j= 0;  j < sylv_sthles; ++j) {
            cout << result[i][j] << " ";
        }
        putchar('\n');
    }

    return result;
}


template < typename T >
void Sylvester <T> :: make_Sylvester( Matrix<int> &m1, Matrix<int> & m2 ,int d0 , int d1) {

    m1grammes = m1.get_grammes();
    m2grammes = m2.get_grammes();
    m1sthles = m1.get_sthles();
    m2sthles = m2.get_sthles();

    /*
     * 1o orisma = pyknh anaparastash ths ekshswshs pou 8elw na apo8hkeusw
     * 2o orisma= grammh sthn opoia ksekina na topo8etountai oi syntelestes ths ktymenh metavlhts
     * 3o orisma = grammes tou m1
     */
    fill_first_row_of_sylvester(m1, 0, m1grammes );

    shift_rest_first_half(); // gemisei mexri th grammh d1-1

    //------------- 2h eksiswsh ------------------

    fill_first_row_of_sylvester(m2, m2grammes-1 , m2grammes ); // grafw sth grammh d1 mexri th sthlh d1+1->gia akeraious

    shift_rest_second_half();

    //------------------------------------

}

/*
	 * 1o orisma = pyknh anaparastash ths ekshswshs pou 8elw na apo8hkeusw
	 * 2o orisma= grammh sthn opoia ksekina na topo8etountai oi eksiswseis me th ktymenh metavlhts
	 * 3o orisma = grammes tou m1
*/
template <typename T>
void Sylvester<T>::fill_first_row_of_sylvester(Matrix<int> &m1, int first_row_pos, int dimension) {

    /*
     * to dimension0 mou leei oti diavazw mexri th grammh dimensio0 tou pinaka syntelestwn m1
     * kai apo8hkeuw mexri th sthlh dimesnison0 -1  tou sylvester
    */

    int j = 0;
    for (j = 0; j < dimension ; j++ )
    {
        this->table[first_row_pos][j] = m1.get_table_row(dimension-j-1);
    }
    for (int i = dimension ; i < this->sthles; ++i) {
        this->table[first_row_pos][i] = NULL;
    }

}

template <typename T>
void Sylvester<T>::shift_rest_first_half() {

    for( int i  = 1 ; i < m2grammes-1  ; i++  ) {

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
void Sylvester<T>::shift_rest_second_half() {

    for( int i  = m2grammes ; i < this->grammes  ; i++  ) {

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

    cout << "Sylvester needs a variable in order to print\n";

}

template <typename T>
void Sylvester<T>::print_Table(char variable ) {

    for( int i = 0 ; i < this->grammes ; i++ )
    {
        for ( int j  = 0  ; j < this->sthles ; j ++)
        {
            if ( this->table[i][j] == NULL)
                cout << "0 ";
            else
            {
                cout << "( " << this->table[i][j][0] << " ";
                if( i < m2grammes )
                {
                    for (int k = 1; k < m1sthles; ++k)
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
                    for (int k = 1; k < m2sthles; ++k)
                    {
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