//
// Created by henry on 22/10/2015.
//

#ifndef FUNCTION_TABLE_TESTHANDLER_H
#define FUNCTION_TABLE_TESTHANDLER_H

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"

using namespace CPPUNIT_NS;

class TestHandler : public TestFixture {

    CPPUNIT_TEST_SUITE( TestHandler );

        CPPUNIT_TEST( testArea );

        CPPUNIT_TEST( testHandle_input );

    CPPUNIT_TEST_SUITE_END();

public:

    void setUp();

    void tearDown();

    void testArea();

    void testHandle_input();

};


#endif //FUNCTION_TABLE_TESTHANDLER_H
