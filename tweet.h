///Function header for the tweet.cpp file.
///Documentation on function use is here.

#ifndef PA01_SENTIMENT_TWEET_H
#define PA01_SENTIMENT_TWEET_H

#include "DSString.h"
#include <vector>
#include "word.h"

//Namespace declarations
using std::vector;
using std::cout;
using std::endl;

class tweet {

private:

    int sent; //actual sentiment
    int judgeSent; //judged sentiment
    DSString id;
    DSString date;
    DSString msg;
    vector<word> wordList; //All the words in a tweet

public:

    //constructors
    tweet();
    tweet(int sent, DSString id, DSString date, DSString msg);
    tweet(DSString id, int sent, DSString msg);
    tweet(DSString id, DSString msg);
    ~tweet();

    //get functions
    int getSent();
    int getJSent();
    DSString getID();
    DSString getDate();
    DSString& getTweet();
    vector<word>& getWordList();

    //set functions
    void setSent(int);
    void setID(DSString);
    void setDate(DSString);
    void setTweet(DSString);
    void setJSent(int sent);

    //Actual Functions
    void judge(vector<word> wordLib, int usesThreshold); //Uses the word library to judge a tweets sentiment
    void decompose(); //Breaks down a tweet into seperate words and puts them into the wordList variable
    int searchWordLib(DSString str, vector<word> wordLib); //Returns the index of DSString str in wordLib. Returns -1 if not found.
};


#endif //PA01_SENTIMENT_TWEET_H
