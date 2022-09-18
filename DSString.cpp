//
// Created by mark on 6/2/2021.
//

#include "DSString.h"

//constructors
DSString::DSString() {
    myString = nullptr;
}

DSString::DSString(const char* str) {
    if(str == nullptr) {
        myString = nullptr;
    } else {
        myString = new char[strlen(str) + 1];
        strcpy(myString, str);
    }
}

DSString::DSString(const DSString& str) {
    myString = new char[strlen(str.myString) + 1];
    strcpy(myString, str.myString);
}

DSString::~DSString() {
        delete[] myString;
}

///Operator Overloads

//Assignment Operators
DSString& DSString::operator= (const char* str){
    myString = new char[strlen(str) + 1];
    strcpy(myString, str);
    return *this;
}

DSString& DSString::operator= (const DSString& str){
    if (this != &str) {
        myString = new char[strlen(str.myString) + 1];
        strcpy(myString, str.myString);
    }
    return *this;
}

//Overloaded non-modifying string concat
DSString DSString::operator+ (const DSString& str){
    DSString concat;
    concat.myString = new char[strlen(myString) + strlen(str.myString) + 1];
    concat = strcat(myString, str.myString);
    return concat;
}

DSString DSString::operator+ (const char* ltr){
    DSString concat;
    concat.myString = new char[strlen(myString) + 1];
    concat = strcat(myString, ltr);
    return concat;
}

//Relational Operators
bool DSString::operator== (const char* str){
    return strcmp(myString, str) == 0;
}
bool DSString::operator== (const DSString& str){
    return strcmp(myString, str.myString) == 0;
}

bool DSString::operator> (const char* str){
    return strcmp(myString, str) > 0;
}
bool DSString::operator> (const DSString& str){
    return strcmp(myString, str.myString) > 0;
}
bool DSString::operator< (const char* str){
    return strcmp(myString, str) < 0;
}
bool DSString::operator< (const DSString& str){
    return strcmp(myString, str.myString) < 0;
}

//Subscript Operator
char& DSString::operator[] (const int num){
    return myString[num];
}

//getLength() returns the number (count) of characters in the string.
//does not include null terminator
int DSString::getLength(){
    return strlen(myString);
}

/**
 * The substring method returns a string object that contains a
 * sequence of characters from this string object.
 *
 * param start - the index of where to start
 * param numChars - the number (count) of characters to copy into
 *    the substring
 * @return a DSString object containing the requested substring
 **/
DSString DSString::substring(int start, int numChars) {
    char str[numChars + 1];
    int ltrnum = 0;

    for (int i = start; i < start + numChars; i++) {
        str[ltrnum] = myString[i];
        ltrnum++;
    }

    str[ltrnum] = '\0';
    DSString substr = str;
    return substr;
}

/**
 * the c_str function returns a null-terminated c-string holding the
 * contents of this object.
 **/
char* DSString::c_str(){
    return myString;
}

/**
 * Overloaded stream insertion operator to print the contents of this
 * string to the output stream in the first argument.
 **/
std::ostream& operator<< (std::ostream& os, const DSString& str){
    return os;
}

///My Functions

//Eliminates all non alpha characters from a string
DSString DSString::clean() { //todo fix double space error
    int curLtr = 0;
    int newCurLtr = 0;
    char temp[256];

    while (myString[curLtr])
    {
        if(isalpha(myString[curLtr])) {
            temp[newCurLtr] = tolower(myString[curLtr]);
            newCurLtr++;
        }
        curLtr++;
    }
    temp[newCurLtr] = '\0';

    return DSString(temp);
}


