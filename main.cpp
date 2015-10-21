#include "main.hpp"

void Read_synarthsh_from_file(char *string);

using namespace std;

int main()
{
	srand ( (unsigned int) time(NULL) );
	int d0 ;
	int d1 ;

	Pinakas_syntelestwn<int> m1,m2;

	Sylvester<int *> Sylvester;

	// diavasma apo arxeio

//	char hidden_variable;
//	hidden_variable = Read_synarthsh_from_file((char *) "generated_functions.txt" , m1, m2);
//
//	if ( hidden_variable == 'x' ){
//		m1.reverse();
//		m2.reverse();
//		d0 = m1.get_maxYpower();
//		d1 = m2.get_maxYpower();
//	}
//	else{
//		d0 = m1.get_maxXpower();
//		d1 = m2.get_maxXpower();
//	}

	//------------------------


	//diavasma d1 d2 apo arxeio

	Read_d1_d2_From_File( (char *) "d1d2.txt" , &d0 , &d1);
	char hidden_variable = 'y';
	m1.create_Polywnymo(d0);
	m2.create_Polywnymo(d1);

	//-----------------------


	Sylvester.allocate_Table(d0 + d1 , d0 + d1 );
	Sylvester.make_Sylvester(m1,m2 , d0 ,d1);

	//paragwgh polywnymou mhtrwwn

	Polywnymo_mhtrwwn< Matrix<int*> *> Polywnymo_Mhtrwwn;

	Polywnymo_Mhtrwwn.generate(m1 , m2);

	Polywnymo_Mhtrwwn.print_Table();

	//----------------------------

	/*
	 * 2o orisma = plh8os sthles pou einai grammeno to polywnymo 1
	 * 3o orisma = plh8os sthles pou einai grammeno to polywnymo 2
	 */
	//ektypwseis
	m1.print_Table();
	cout << endl;
	m2.print_Table();
	cout << endl;
	if( hidden_variable == 'y')
		Sylvester.print_Table( hidden_variable);
	else
		Sylvester.print_Table( hidden_variable);
	cout << endl;

	//------------------------------------------------------------

	int ** result;
	Pinakas_syntelestwn <int> v;

	v.allocate_Table(1,d0+1);

	for (int i = 0; i < d0+1; ++i) {
		v.insert(i+1,0,i);
	}


	result = Sylvester.multiply(v);


//	m1.print_Table();
//	cout << endl;
//	m2.print_Table();

}

/*
 * diavazei mia synarthsh apo to filename kai ftiaxnei pyknh anaparastash sto pinaka m
 * epishs gyrnaei ena char gia th metavlhth pou prepei na kryftei
 *
 * Exei thn paradoxh oti h synarthsh sto filename dinetai xwris kena
 */
char Read_synarthsh_from_file(char *filename , Matrix<int> & m1, Matrix<int> & m2) {

	ifstream myfile;
	myfile.open (filename);

	char metavlhth;

	char buffer[BUFFSIZE];

	struct details * details1, *details2;

	if (myfile.is_open()) { // anoikse arxeio

		myfile >> buffer;		// apo8hkeyse th leksh sto buffer	if( (details1->maxXpower > details1->maxYpower) && (details2->maxXpower > details2->maxYpower) )

		details1 = place_function_in_Matrix(buffer , m1 );

		myfile >> buffer;

		details2 = place_function_in_Matrix(buffer , m2 );

	}
	else {
		cerr << " Error while opening file " << filename << endl;
		exit(1);
	}

	myfile.close();

	if( (details1->maxXpower > details1->maxYpower) && (details2->maxXpower > details2->maxYpower) )
		metavlhth =  'y';
	else if ( (details1->maxXpower < details1->maxYpower) && (details2->maxXpower < details2->maxYpower) )
		metavlhth =  'x';
	else
	{
		if( (details1->maxYpower > details2->maxXpower) )
			metavlhth =  'x';
		else
			metavlhth =  'y';
	}

	delete details1, details2;

	return metavlhth;

}

struct details * place_function_in_Matrix( char * buffer , Matrix<int> & m){

	struct details *structdetails = new details();

	char metavlhth;
	int maxXpower=0;
	int maxYpower=0;

	int xPowers[BUFFSIZE];
	int yPowers[BUFFSIZE];
	int syntelestes[BUFFSIZE];
	char syntelesthsBuffer[BUFFSIZE];

	int pos = 0;

	for (int i1 = 0; i1 < BUFFSIZE ; ++i1) {
		xPowers[i1] = 0;
		yPowers[i1] = 0;
	}

	size_t bufferSize = strlen(buffer);

	//diavasma sta8erou orou
	int j = 0;
	int proshmo = 1;
	if ( buffer[0] == '-') {
		proshmo = -1;
		j++;
	}
	else{
		proshmo = 1;
		if(buffer[0] == '+')
			j++;
	}

	int z = 0;
	while( buffer[j] != '+' && buffer[j] != '-'  ) {
		syntelesthsBuffer[z] = buffer[j];
		j++;
		z++;
	}
	syntelesthsBuffer[z] = '\0';
	syntelestes[pos] = proshmo*atoi(syntelesthsBuffer);
	//--------------------

	for (int k = j; k < bufferSize ; ++k) {

		if (buffer[k] == '+' || buffer[k] == '-') {
			pos++;
		}

		//diavasma syntelesth
		int c=0;
		if((buffer[k]=='+') && ((buffer[k+1]=='x') || (buffer[k+1]=='y')))
			syntelestes[pos]=1;
		else if((buffer[k]=='-') && ((buffer[k+1]=='x') || (buffer[k+1]=='y')))
			syntelestes[pos]=-1;
		else{
			//diavasma syntelesth
			while (buffer[k] != '*' && k < bufferSize) {
				syntelesthsBuffer[c] = buffer[k];
				c++;
				k++;
			}
		}
		//--------------------

		if (c != 0){ // ean diavasa syntelesth

			syntelesthsBuffer[c] = '\0';
			syntelestes[pos] = atoi(syntelesthsBuffer);
		}

		k++; // goto metavlhth
		metavlhth = buffer[k];
		if(buffer[k+1] != '^')
		{

			if(metavlhth == 'x'){

				xPowers[pos]=1;

			}
			else{

				yPowers[pos]=1;
			}

			++k; //goto + or - or *
		}
		else
		{
			k = k + 2; // goto dynamh ths metavlhths


			//diavasma dynamhs ths metavlhths
			int z = 0;
			while( (buffer[k] != '+') && (buffer[k] != '-') && (buffer[k] != '*') && (k < bufferSize) ) {

				syntelesthsBuffer[z] = buffer[k];
				++k;
				++z;
			}
			syntelesthsBuffer[z] = '\0';
			//------------------------------

			if (metavlhth == 'x' ){

				xPowers[pos] = atoi(syntelesthsBuffer);

				if(maxXpower < xPowers[pos] )
					maxXpower = xPowers[pos];
			}
			if (metavlhth == 'y' ){

				yPowers[pos] = atoi(syntelesthsBuffer);

				if(maxYpower < yPowers[pos] )
					maxYpower = yPowers[pos];

			}
		}

		if( buffer[k] == '*' || buffer[k] == '+' || buffer[k] == '-' )
			--k;

	}

	m.allocate_Table(maxXpower + 1, maxYpower + 1);

	//mhdenizw to pinaka syntelestwn
	for (int l = 0; l <= maxXpower ; ++l)
		for (int i = 0; i <= maxYpower; ++i)
			m.insert(0,l,i);
	//------------------------------

	//topo8etshsh syntelestwn se pinaka syntlestwn
	for (int i = 0; i <= pos ; ++i) {
		m.insert(syntelestes[i],xPowers[i],yPowers[i]);
	}
	//-------------------------------------------

	structdetails->maxXpower = maxXpower;
	structdetails->maxYpower = maxYpower;

	m.set_maxXpower(maxXpower);
	m.set_maxYpower(maxYpower);

	return structdetails;
}

void Read_d1_d2_From_File( char * filename , int * d1 , int * d2 )
{
	ifstream myfile;
	myfile.open (filename);

	string wordRead;

	if (myfile.is_open()) { // anoikse arxeio

		myfile >> wordRead;		// apo8hkeyse th leksh sto wordRead

		*d1 = atoi(wordRead.c_str()); // metatroph lekshs se ari8mo

		myfile >> wordRead;

		*d2 = atoi(wordRead.c_str());

	}

	myfile.close();

}
