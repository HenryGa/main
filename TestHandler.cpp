//
// Created by henry on 22/10/2015.
//

#include "cppunit/config/SourcePrefix.h"
#include "TestHandler.h"

#include "Handler.h"


void TestHandler::setUp() {



}

void TestHandler::tearDown() {

}

void TestHandler::testArea() {

}

void TestHandler::testHandle_input() {

    Handler *handler = new Handler();

    char * argv[] = {(char*)"main",(char*)"-read",(char*)"-console"};

    handler->handle_input(3,argv);

//    CPPUNIT_ASSERT_EQUAL("-read",argv[1]);
//    CPPUNIT_ASSERT_EQUAL("-generate" ,argv[1]);

}
