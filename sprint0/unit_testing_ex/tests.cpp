#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "functions.hpp"

TEST_CASE( "Numbers, 2 and 2 are added", "[numbers::add]") {
    numbers test1;
    test1.number1 = 2;
    test1.number2 = 2;
    REQUIRE( test1.add() == 4);
}

TEST_CASE( "Numbers, 2 and 2 are subtracted", "[numbers::add]") {
    numbers test1;
    test1.number1 = 2;
    test1.number2 = 2;
    REQUIRE( test1.subtract() == 0);
}