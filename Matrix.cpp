//
// Created by henry on 13/10/2015.
//

#include "Matrix.h"

using namespace std;

template <typename T>
void Matrix<T> :: allocate_Table(int plh8osGrammes , int plh8osSthles ) {

	table = new T * [plh8osGrammes];

    for ( int i = 0 ; i < plh8osGrammes ; i ++)
        table[i] = new T[plh8osSthles];
	
	grammes = plh8osGrammes;
	sthles = plh8osSthles;
	
}

template <typename T>
void Matrix<T> :: print_Table()
{
	cout<< "edw mama\n";
	
}

/*
 * topo8etei sth 8esh i,j tou pinaka to item
 */
template <typename T>
void Matrix<T> :: insert( T item ,int  i ,int j ) {

	this->table[i][j] = item;

}

template <typename T>
Matrix<T>::~Matrix() {


}

template <typename T>
void Matrix<T>::reverse() {

	int ** newTable = new int*[sthles];
	for (int k = 0; k < sthles; ++k) {
		newTable[k] = new int[grammes];
	}

	for (int i = 0; i < grammes ; ++i) {
		for (int j = 0; j < sthles; ++j) {
			newTable[j][i] = table[i][j];
		}
	}

	int ** p = table;
	table = newTable;
	delete[] p;

	int temp;
	temp = grammes;
	grammes = sthles;
	sthles = temp;
}

template <typename T>
int Matrix<T>::get_vathmos() {

	if ( grammes == sthles)
		return grammes;

	int firstI = 0,firstJ= 0,secondI= 0,secondJ= 0;

	for (int i = grammes-1; i >= 0; --i) {
		for (int j = sthles-1; j >= 0; --j) {

			if( table[i][j] != 0){
				firstI = i;
				firstJ = j;
				break;
			}
		}
		if ( firstI != -1 )
			break;
	}

	for (int j = sthles-1; j >= 0; --j) {
		for (int i = grammes-1; i >= 0; --i) {
			if( table[i][j] != 0){
				secondI = i;
				secondJ = j;
				break;
			}
		}
		if ( firstJ != -1 )
			break;
	}

	firstI;
	firstJ;
	secondI;
	secondJ;

	if( (firstI + firstJ) > (secondI+secondJ) )
		return firstI + firstJ;
	else
		return secondI+secondJ;

}
