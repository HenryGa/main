//
// Created by henry on 21/10/2015.
//

#include "Handler.h"

using namespace std;

//void Handler :: generate_Bonus()
//{
//    v.allocate_Table(d0+d1,1);
//
//    for (int i = 0; i < d0+d1; ++i) {
//        v.insert(i+1,i,0);
//    }
//    result = sylvester.multiply(v,s0+1,s1+1);
//}

/*
 * Synarthsh gia xeirismo kai elegxo ths eisodou apo to xrhsth
 */
void Handler::handle_input(int argc, char *argv[]) {

    srand ( (unsigned int) time(NULL) ); // arxhkopoihsh tou rand , to xreiazomai sth generate

    if( argc == 6 ){

        if(strcmp("-generate",argv[1]) == 0 ) {
            d0 = atoi(argv[3]);
            d1 = atoi(argv[5]);
            generate();
        }
        else {

            cout << "-------Wrong input!-------\n"
                    "Did you mean : equations -generate -d1 X -d2 Y? where X and Y are ints\n";
            cout << " Press Y/N : ";
            char answer;
            cin >> answer;
            if (answer == 'Y' || answer == 'y') {
                char D1[10];
                cout << "Insert d1: ";
                cin >> D1;
                d0 = atoi(D1);
                cout << "Insert d2 : ";
                cin >> D1;
                d1 = atoi(D1);

                generate();
            }
            else
                exit(1);
        }
    }
    else if( argc == 3){

        if ( strcmp("-console",argv[2]) == 0 && strcmp("-read",argv[1]) == 0 )
            consola();
        else {
            cout << "-------Wrong input!-------\nDid you mean : equations -read console?\n";
            cout << " Press Y/N : ";
            char answer;
            cin >> answer;
            if (answer == 'Y' || answer == 'y')
                consola();
            else
                exit(2);
        }

    }
    else if( argc == 4 ) {

        if ( strcmp("-i",argv[2]) == 0 && strcmp("-read",argv[1]) == 0 )
            read(argv[3]);
        else {
            cout << "-------Wrong input!-------\nDid you mean : equations -read -i <file_path>?\n";
            cout << " Press Y/N : ";
            char answer;
            cin >> answer;
            if (answer == 'Y' || answer == 'y') {
                cout << " Insert <file_path>";
                cin >> argv[3];
                read(argv[3]);
            }
            else
                exit(3);
        }
    }
    else{
        cout << " Error input\n";
        cout<<" Expected one of these :\nequations -generate -d1 X -d2 Y? where X and Y are ints\n"
                "equations -read console\nequations -read -i <file_path>\n";

        exit(1);
    }

}


/*
 * Synarthsh pou xeirizetai tis ektypwseis twn pinakwn analoga me tis epiloges tou user
 */
void Handler :: print(){

    char answer[10];

    cout<< " What would you like to see? ^^\nPress : 1 for Sylvester\nPress : 2 for A[i]\n"
                   "Press : 3 for the result of multiply"
                   "Press : 4 for Everything\n"
                   "Press : anything else to EXIT\n";

    cin >> answer;

    int a = atoi(answer);

    if(a == 1)
    {
        if( hidden_variable == 'y')
            sylvester.print_Table( hidden_variable );
        else
            sylvester.print_Table( hidden_variable );
    }
    else if( a == 2 )
    {
        cout << "Please enter which A[i] you would like to see\nOptions are : " << 0 << "...";
        if( m1.get_sthles() > m2.get_sthles() )
            cout << m1.get_sthles()-1 << endl;
        else
            cout << m2.get_sthles()-1 << endl;

        int b;
        cin >> b;

        Polywnymo_Mhtrwwn.print_Table(b);

    }
    else if( a == 4) {

        m1.print_Table();
        cout << endl;
        m2.print_Table();
        cout << endl;

        Polywnymo_Mhtrwwn.print_Table();

        if (hidden_variable == 'y')
            sylvester.print_Table(hidden_variable);
        else
            sylvester.print_Table(hidden_variable);
        cout << endl;
    }
    else
        return;

}

void Handler :: generate_Polywnymo_Mhtrwwn(){

    Polywnymo_Mhtrwwn.generate(m1 , m2);
}

void Handler :: generate_Sylvester(){

    sylvester.allocate_Table(d0 + d1 , d0 + d1 );
    sylvester.make_Sylvester(m1 ,m2 , d0 ,d1);

}

/*
 * Paragei tyxaia syntelestes gia ta 2 polywnyma
*/
 void Handler :: generate() {

    hidden_variable = 'y';
    m1.create_Polywnymo(d0); // paragei to pinaka syntelestwn m1
    m2.create_Polywnymo(d1); // paragei to pinaka syntelestwn m2

}

// diavasma apo consola
void Handler :: consola() {

    char function[200];

    cout << " Enter 1st function : ";

    cin >> function;

    place_function_in_Matrix(function, m1);

    cout << " Enter 2nd function : ";

    cin >> function;

    place_function_in_Matrix(function, m2);

    hidden_variable = find_hidden_variable(m1,m2);

    if( hidden_variable == 'x') {
        m1.reverse();
        m2.reverse();
        d0 = m1.get_maxYpower();
        d1 = m2.get_maxYpower();
    }
    else{ // hidden == 'y'
        d0 = m1.get_maxXpower();
        d1 = m2.get_maxXpower();
    }

}


// diavasma apo arxeio
void Handler :: read( char * filename) {

    hidden_variable = Read_synarthsh_from_file( filename );

    if (hidden_variable == 'x') {
        m1.reverse();
        m2.reverse();
        d0 = m1.get_maxYpower();
        d1 = m2.get_maxYpower();
    }
    else {
        d0 = m1.get_maxXpower();
        d1 = m2.get_maxXpower();
    }
}

/*
 * diavazei mia synarthsh apo to filename kai ftiaxnei pyknh anaparastash sto pinaka m
 * epishs gyrnaei ena char gia th metavlhth pou prepei na kryftei
 *
 * Exei thn paradoxh oti h synarthsh sto filename dinetai xwris kena
 */
char Handler :: Read_synarthsh_from_file(char *filename ) {

    ifstream myfile;
    myfile.open (filename);

    char buffer[BUFFSIZE];


    if (myfile.is_open()) { // anoikse arxeio

        myfile >> buffer;		// apo8hkeyse th leksh sto buffer	if( (details1->maxXpower > details1->maxYpower) && (details2->maxXpower > details2->maxYpower) )

        place_function_in_Matrix(buffer , m1 );

        myfile >> buffer;

        place_function_in_Matrix(buffer , m2 );

    }
    else {
        cerr << " Error while opening file " << filename << endl;
        exit(1);
    }

    myfile.close();

    return find_hidden_variable(m1,m2);

}

char Handler::find_hidden_variable( Matrix<int> & m1 , Matrix<int> & m2){

    int m1MaxXpower = m1.get_maxXpower();
    int m1MaxYpower = m1.get_maxYpower();
    int m2MaxXpower = m2.get_maxXpower();
    int m2MaxYpower = m2.get_maxYpower();

    if( ( m1MaxXpower > m1MaxYpower) && (m2MaxXpower > m2MaxYpower) )
        return 'y';
    else if ( (m1MaxXpower < m1MaxYpower) && (m2MaxXpower < m2MaxYpower) )
        return 'x';
    else
    {
        if( m1MaxYpower > m2MaxXpower )
            return 'x';
        else
            return 'y';
    }

}

/*
 * Dhmiourgei ton pinaka syntelestwn m mesw ths eksiswshs sto buffer
 */
void Handler::place_function_in_Matrix( char * buffer , Matrix<int> & m){

    char metavlhth;
    int maxXpower=0;
    int maxYpower=0;

    int xPowers[100]; // pinakas me tis dynameis tou x pou vlepw
    int yPowers[100]; // pinakas me tis dynameis tou y pou vlepw
    int syntelestes[100]; // pinakas me tous syntelestes ka8e orou
    char syntelesthsBuffer[BUFFSIZE]; // pinakas gia na me voh8aei na diavazw tous syntelestes

    int pos = 0;

    //mhdenizw tous pinakes
    for (int i1 = 0; i1 < 100 ; ++i1) {
        xPowers[i1] = 0;
        yPowers[i1] = 0;
    }

    size_t bufferSize = strlen(buffer);

    //diavasma sta8erou orou
    int j = 0;
    int proshmo;
    if ( buffer[0] == '-') {
        proshmo = -1;
        j++;
    }
    else{
        proshmo = 1;
        if(buffer[0] == '+')
            j++;
    }

    int z = 0; // krataw th 8esh pou ksekinaei o sta8eros oros ston buffer
    while( buffer[j] != '+' && buffer[j] != '-'  ) { // mexri na dw + h' -
        syntelesthsBuffer[z] = buffer[j]; // antigrafw ta grammata
        j++;
        z++;
    }
    syntelesthsBuffer[z] = '\0'; // dhlwnw pou teleiwnei h symvoloseira pou diavasa
    syntelestes[pos] = proshmo*atoi(syntelesthsBuffer); // kai o pinakas syntelestwn[0] = auto pou diavasa
    //--------------------

    for (int k = j; k < bufferSize ; ++k) { // gia ta ypoloipa grammata tou buffer

        if (buffer[k] == '+' || buffer[k] == '-') { // ean dw + h' - shmainei oti ksekinaei kainourgios oros
            pos++; // to pos deixnei gia poion oro milaw
        }

        //diavasma syntelesth
        int c=0;
        if((buffer[k]=='+') && ((buffer[k+1]=='x') || (buffer[k+1]=='y'))) // edw apla anagnwrizw eisodous ths morfhs xy
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

    //mhdenizw to pinaka syntelestwn giati 8a gemisw mono merika kommatia tou
    for (int l = 0; l <= maxXpower ; ++l)
        for (int i = 0; i <= maxYpower; ++i)
            m.insert(0,l,i);
    //------------------------------

    //topo8etshsh syntelestwn se pinaka syntlestwn
    for (int i = 0; i <= pos ; ++i) {
        m.insert(syntelestes[i],xPowers[i],yPowers[i]);
    }
    //-------------------------------------------

    m.set_maxXpower(maxXpower);
    m.set_maxYpower(maxYpower);

}
