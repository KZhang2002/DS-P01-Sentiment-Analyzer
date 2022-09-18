///Function implementation for the classifer.h file.
///Documentation on implementation is here too.

#include "catch.hpp"
#include "DSString.h"
#include "classifier.h"
#include <iostream>
#include <fstream>

//Namespace declarations
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;


TEST_CASE( "DSString Class Functions", "[DSString]" ) {
    DSString str1;
    char const *test = "test";
    char const *alph = "abcdefghijklmnopqrstuvwxyz";
    char const *empty = "";

    SECTION("Constructor Testing") {
        DSString str2(test);
        REQUIRE(strcmp(str2.c_str(), test) == 0); //Should Pass

        DSString str3(str2);
        REQUIRE(strcmp(str3.c_str(), str2.c_str()) == 0); //Should Pass
    }

    SECTION("Assignment Operator Testing") {
        DSString str2;

        str2 = test;
        REQUIRE(strcmp(str2.c_str(), test) == 0); //Should Pass

        str1 = str2;
        REQUIRE(strcmp(str1.c_str(), str2.c_str()) == 0); //Should Pass
    }

    SECTION("Concat Operator Testing") {
        DSString str2 = test;
        str1 = test;
        DSString str3 = str2 + str1;
        char testtest[9] = "testtest";

        cout << (str3).c_str() << endl;
        cout << testtest << endl;
        cout << (str3).getLength() << endl;
        cout << strlen(testtest) << endl;

        REQUIRE(strcmp(str3.c_str(), testtest) == 0); //Should pass
    }

    SECTION("Relational Operator Testing") {
        str1 = "a";
        DSString str2("b");
        REQUIRE((strcmp(str1.c_str(), str2.c_str()) < 0) == str1 < str2); //Should pass
        REQUIRE((strcmp(str2.c_str(), str1.c_str()) < 0) == str1 > str2); //Should pass
    }

    SECTION("Subscript Operator Testing") {
        str1 = test;
        REQUIRE(str1[0] == 't'); //Should pass
        REQUIRE(str1[1] != 't'); //Should pass
    }

    SECTION("Get Function Testing") {
        str1 = test;
        DSString str2(alph);

        //getLength() test
        REQUIRE(str1.getLength() == strlen(test)); //Should pass

        //substring() tests
        char temp1[5] = "abcd";
        DSString str3 = str2.substring(0, 4);
        cout << str2.substring(0, 4) << " = " << temp1 << endl;
        cout << str3 <<  " = " << temp1 << endl;
        REQUIRE(strcmp(str3.c_str(), temp1) == 0); //Should pass

        char temp2[4] = "xyz";
        str3 = str2.substring(23, 3);
        cout << str3 << " = " << temp2 << endl;
        REQUIRE(strcmp(str3.c_str(), temp2) == 0); //Should pass

        //c_str() test
        REQUIRE(strcmp(str1.c_str(), test) == 0); //Should pass
    }

    SECTION("Stream Insertion Operator Testing") {
        DSString message("Stream Insertion Operator Works");
        cout << message << endl;
    }

    SECTION("Oversized String Testing") {
        str1 = alph;
        //cout << str1 << endl;
        //cout << str1[10] << str1[11] << str1[12] << endl;
        REQUIRE(strcmp(str1.c_str(), alph) == 0); //Should pass
    }

    SECTION("Clean Function Testing") {
        DSString emptyStr("");
        DSString nonalph1("!@#$%^");
        DSString nonalph2("!test");
        DSString nonalph3("test!");
        DSString nonalph4("!te!st!");
        DSString nonalph5("!te!!!st!");
        DSString testStr(test);

        REQUIRE(strcmp(nonalph2.clean().c_str(), testStr.c_str()) == 0);
        REQUIRE(strcmp(nonalph3.clean().c_str(), testStr.c_str()) == 0);
        REQUIRE(strcmp(nonalph4.clean().c_str(), testStr.c_str()) == 0);
        REQUIRE(strcmp(nonalph4.clean().c_str(), testStr.c_str()) == 0);
    }
}
