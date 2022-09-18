///Function header for the classifer.cpp file.
///Documentation on function use is here.

#ifndef PA01_SENTIMENT_CLASSIFIER_H
#define PA01_SENTIMENT_CLASSIFIER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "word.h"
#include "tweet.h"
#include <cmath>
#include <algorithm>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

class classifier {

private:
    /**
     *  Stores all words used in tweets, along with number of uses,
     *  times it was used positively, and percentage of times it
     *  was used positively. Used to predict sentiment.
     */
    vector<word> wordLib;

    ///Various vectors used to store raw tweet data from csvs.
    vector<tweet> tweetList; //Stores training data
    vector<tweet> testList; //Stores tweets from the testing data
    vector<tweet> resultList; //Stores sentiments from the scoring data

    /**
     *  Sets the threshold for the minimum amount of times a word
     * must have appeared in the training dataset to be considered
     * while calculating the sentiment.
     *
     *  If there are no words in the tweet that are on the wordlist
     * or above/equal to the threshold, the program will guess,
     * defaulting to a negative sentiment.
     */
    int usesThreshold;

public:

    ///Constructors
    ///These are all empty as all variables are created and set within the gen/set functions
    classifier();
    classifier(const classifier&);
    ~classifier();

    ///Main Functions - All other functions will be called from these ones.
    void train(ifstream&);
    void test(ifstream& twtData, ifstream& sentData, ofstream& output);
    void score(ofstream& output);
    void outputResults(ofstream& output);

    ///Configuration Functions
    void setUsesThreshold(int i); //Sets the min amount of uses a word must have before being used in sentiment analysis. Recommended value is 3.

    ///Training/Testing Tweetlist Functions
    vector<tweet> genTweetList(ifstream&); //Generates a tweet list from an input file, used for both testlist and tweetlist

    void setTweetList(vector<tweet>); //Sets the classifier's training data list
    int searchTweetList(DSString); //Returns the vector index of a given DSString
    vector<tweet>& getTweetList(); //Gets tweetlist
    void outputTweetList(ofstream& output); //Outputs the tweet list into the given ofstream, formatted as (id,sentiment,message)

    void setTestList(vector<tweet>); //Sets the classifier's test data list
    void outputTestList(ofstream& output); //Outputs the test list into the given ofstream, formatted as (id,sentiment,message)

    ///WordLib Functions
    void genWordLib(); //Generates a word library from the classifer's tweetList.
    void outputWordList(); //Outputs the word library into "wordlist.csv", formatted (word, times used positively, total times used, percent of positive tweets) and sorted from most uses to least uses.
    void addToWordLib(vector<word>); //Addes a word into the word library
    int searchWordLib(DSString str); //Returns the index of a given string in word library, returns -1 if not found
    vector<word> getWordLib(); //Returns the word library

    ///Scoring Functions
    void judgeAll(int usesThreshold); //Gives all the tweets in the test library a calculated sentiment. For details on usesThreshold look at the setUsesThreshold function.
    void decomposeAll(); //Decomposes all tweets into individual words and adds them to the word library.
    vector<tweet> matchSentToTweet(ifstream&); //Sets the test tweet list's sentiments from the sentiment data file.
    double roundToThousandth(double num); //Rounds a given double to the third digit. Will add zeroes if necessary. (Ex. 0.6 --> 0.600, 0.66 --> 0.660)
};

#endif //PA01_SENTIMENT_CLASSIFIER_H
