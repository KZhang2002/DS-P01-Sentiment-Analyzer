///Function header for the word.cpp file.
///Documentation on function use is here.

#ifndef PA01_SENTIMENT_WORD_H
#define PA01_SENTIMENT_WORD_H

#include "DSString.h"

class word {
private:
    DSString str;
    int totalSent;
    int uses;

public:
    //constructor
    word();
    word(DSString str);
    word(DSString str, int score);
    word(DSString str, int score, int uses);

    //get functions
    DSString getStr();
    int getTSent();
    int getUses();
    double getPerc();

    //set functions
    DSString setStr(DSString);
    int setTSent(int);
    void addTSent(int);

    //modifiers
    void incUses(); //increases uses by one
};


#endif //PA01_SENTIMENT_WORD_H
