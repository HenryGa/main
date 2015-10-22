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
    delete[] this->table;
}


/*
 * efarmozetai mono otan o sylveter exei mesa tou pinakes idiou mhkous
 * kai to v exei oses sthles exoun mesa oi pinakes tou sylvester
 * epishs o sylvester prepei na exei mi
 */

template < typename T >
int *** Sylvester <T> :: multiply(Matrix<int> & v,int Sthles0,int Sthles1){

    int vGrammes = v.get_grammes();
    int sylv_grammes = this->get_grammes();
    int maxSthles;
    if(Sthles0>Sthles1)
        maxSthles=Sthles0;
    else
        maxSthles=Sthles1;

    int *** result = new int**[sylv_grammes];
    for (int p = 0; p < sylv_grammes; p++) {
        result[p] = new int*[sylv_grammes];
        for (int t= 0; t< sylv_grammes; t++){
            result[p][t]=new int[maxSthles];
            for(int c=0;c<maxSthles;c++)
                result[p][t][c]=0;
        }
    }

    int flag=0;
    // ftiaxnw prwth grammh
    cout <<"result" << endl;
    for (int i = 0; i <sylv_grammes ; ++i) {
        for (int j = 0; j <sylv_grammes ; ++j) {

            if( (i>0) && (this->table[i][0] != NULL) )
                flag=1;

            if(flag==0){
                if( this->table[i][j] != NULL ){
                    for (int m = 0; m < Sthles0; ++m) {
                        result[i][j][m] = this->table[i][j][m] * v.get_int_element(j, 0);
                        cout << result[i][j][m] << " " ;
                 //       getchar();
                    }
                }
               // else{
               //     for (int m = 0; m < Sthles0; ++m)
               //         result[i][j][m]=;
               // }
                    
            }
            else{
                if( this->table[i][j] != NULL ){
                    for (int m = 0; m < Sthles1; ++m) {
                        result[i][j][m] = this->table[i][j][m] * v.get_int_element(j, 0);
                        cout << result[i][j][m] << " ";
                   //     getchar();
                    }               
                }
                else{
                    for (int m = 0; m < Sthles0; ++m)
                        result[i][j][m]=0;
                }
            }   
            cout << "     ";
        }
        cout <<'\n';
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