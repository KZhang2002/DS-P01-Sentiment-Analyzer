///Function implementation for the classifer.h file.
///Documentation on implementation is here too.

#include "word.h"

//constructors
word::word() {
    this->str = "";
    totalSent = 0;
    uses = 1;
}
word::word(DSString str) {
    this->str = str;
    totalSent = 0;
    uses = 1;
}
word::word(DSString str, int score) {
    this->str = str;
    totalSent = score;
    uses = 1;
}
word::word(DSString str, int score, int uses) {
    this->str = str;
    totalSent = score;
    this-> uses = uses;
}

//get functions
double word::getPerc() { return (double) totalSent/uses; }
DSString word::getStr() { return str; }
int word::getTSent() { return totalSent; }
int word::getUses() { return uses; }

//set functions
DSString word::setStr(DSString str) { this->str = str; }
int word::setTSent(int tSent) { totalSent = tSent; }
void word::addTSent(int num) { totalSent += num; }

//modifiers
void word::incUses() { uses++; };