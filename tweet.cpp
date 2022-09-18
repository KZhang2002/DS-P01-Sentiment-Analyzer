///Function implementation for the classifer.h file.
///Documentation on implementation is here too.

#include "tweet.h"

//constructors
tweet::tweet() {
    sent = -1;
    id = "";
    date = "";
    msg = "";
}

tweet::tweet(int sent, DSString id, DSString date, DSString msg) {
    this->sent = sent;
    this->id = id.c_str();
    this->date = date.c_str();
    this->msg = msg.c_str();
}

tweet::tweet(DSString id, int sent, DSString msg) {
    this->sent = sent;
    this->id = id;
    this->date = "-1";
    this->msg = msg;
}

tweet::tweet(DSString id, DSString msg) {
    sent = 0;
    this->id = id;
    this->date = "-1";
    this->msg = msg;
}

tweet::~tweet(){

}

//get functions
int tweet::getSent(){ return sent; }

int tweet::getJSent(){ return judgeSent; }

DSString tweet::getID(){ return id; }

DSString tweet::getDate(){ return date; }

DSString& tweet::getTweet(){ return msg; }

vector<word>& tweet::getWordList(){ return wordList; }

//set functions
void tweet::setSent(int sent){ this->sent  = sent; }

void tweet::setID(DSString id) { this->id = id; }

void tweet::setDate(DSString date) { this->date = date; }

void tweet::setTweet(DSString tweet) { msg = tweet; }

void tweet::setJSent(int sent){ judgeSent  = sent; }

//actual functions
void tweet::decompose() {
    int curLtr = 0;
    int wordStart = 0;
    int wordLen = 0;
    char buffer = msg[0];
    int i = 1;

    //Continually reads characters until a space is encountered
    //If the next character is not also a space and the substring
    //does not have a length of 0, the word is added to the wordList
    //wordLen increases with every letter and resets to 0 after a word is found
    //wordStart is set to curLtr after the end of a word is found
    while(buffer != '\0') {
        if(buffer == ' ' && msg[curLtr + 1] != ' ') {
            if (msg.substring(wordStart, wordLen).clean().getLength() != 0) {
                wordList.emplace_back(word(msg.substring(wordStart, wordLen).clean(), sent));
                i++;
            }
            wordStart = curLtr + 1;
            wordLen = 0;
        }
        curLtr++;
        wordLen++;
        buffer = msg[curLtr];
    }
}

//Judge gets all the words in a word list and adds their probability of being positive (times used positively/times used)
//into totalSent. Then totalSent is divided by the total number of words in the tweet. If a word's uses is below usesThreshold,
//the word is not counted, either in the totalSent or the wordcount.
void tweet::judge(vector<word> wordLib, int usesThreshold) {
    double totalSent = 0;
    double score;
    int numWords = wordList.size();
    for(int i = 0; i < wordList.size(); i++) {
        int wordIndex = searchWordLib(wordList[i].getStr(), wordLib);
        if ((wordIndex != -1 && wordLib[wordIndex].getUses() >= usesThreshold)) {
            totalSent += wordLib[wordIndex].getPerc();
        } else if (wordLib[wordIndex].getUses() < usesThreshold) {
            numWords--;
        }
    }

    //If no words in the tweet are recognizable, judgeSent becomes -1
    if (totalSent == 0) {
        judgeSent = -1;
        return;
    }

    //The sentiment is then averaged and checked if it is more positve than negative
    score = totalSent/numWords;

    if (score >= 0.5) {
        judgeSent = 1;
    } else {
        judgeSent = 0;
    }
}

//Searches sequentially though wordLib until a given string is found.
int tweet::searchWordLib(DSString str, vector<word> wordLib) {
    int i = 0;
    while(i < wordLib.size()) {
        if(wordLib[i].getStr() == str) {
            return i;
        }
        i++;
    }
    return -1;
}

