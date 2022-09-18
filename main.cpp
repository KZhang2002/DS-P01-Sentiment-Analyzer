/**
 * Author: Kenny Zhang
 * Github: https://github.com/KZhang2002
 *
 * Project: Tweet Sentiment Trainer and Analyzer
 * Repository: https://github.com/SMUCSE2341/22s-2341-KZhang2002
 *
 * Class: SMU CS 2341 (4649)
 *
 * Desc: Takes in a csv of tweets and creates a word libary that details
 * words seen in the tweets and the percentage of times they've been used positively.
 * This library is later used to judge new tweets and can be scored through a seperate
 * file that contains the sentiment of each tweet.
 *
 * TLDR: Takes in training data. Uses data to predict the sentiment of new tweets.
 *
 * Date Released: 2/11/2022
 */

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "DSString.h"
#include "classifier.h"


using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

//todo:
//  edit DSString::Add html parser, preserve emoticons
//      maybe add functionality for hashtags and usernames?
//  possibly add a perc variable for word.h
//Todo add user input

int main(int argc, char** argv) {
    cout << "You have entered " << argc << " arguments:" << "\n";

    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";

    if(argc == 1) {
        //Runs Catch2 tests from test.cpp
        Catch::Session().run();

    } else if(argc == 5) {
        //Inputs files named in the command line arguments into ifstreams.
        ifstream twtData(argv[1]);

        ifstream sentData(argv[2]);

        ifstream trainData(argv[3]);

        ofstream output(argv[4]);

        classifier cls;

        /**
         * * Sets the threshold for the minimum amount of times a word
         * must have appeared in the training dataset to be considered
         * while calculating the sentiment.
         *
         * If there are no words in the tweet that are on the wordlist
         * or above/equal to the threshold, the program will guess,
         * defaulting to a negative sentiment.
         */
        cls.setUsesThreshold(3);

        /**
            //History of scores before certain features were added. The first number is the uses threshold and the second is the accuracy
        //Scores:
            //minimum viable product: 1: 0.71, 2: 0.72, 3: 0.723, 4: 0.719,  5: 0.719, 7: 0.719, 9: 0.716 (highest: 3: 0.723)
            //implemented guessing, scores: 1: 0.713, 2: 0.723, 3: 0.725, 4: 0.721, 5: 0.722, 6: 0.724. 7: 0.722, 8: 0.72 (highest: 3: 0.725)
            //implemented selective bias: 0: 0.603, 1: 0.71, 2: 0.721, 3: 0.723, 4: 0.72, 5: 0.72, 6: 0.722, 20: 0.708 (highest: 3: 0.723)
            //implemented selective bias and guessing: 2: 0.723 3: 0.726 4: 0.722 (highest: 3: 0.726)
            //implemented better cleaning:
            //implemented word roots:
            //implemented broader word search:
            //implement word search within words
            */

        /**
         * Runs the actual program. Train() accepts training data is
         * formated like this: Sentiment,id,Date,Query,User,Tweet.
         * Test() accepts two files. One with tweets (id,Date,Query,User,Tweet)
         * and one with the sentiment scores (Sentiment,id).
         */

        cls.train(trainData);
        cls.test(twtData, sentData, output);

        twtData.close();
        sentData.close();
        trainData.close();
        output.close();

        /**
         * Note: if you want to format your datasets in a different way,
         * you will have to edit the code.
         */
    }
}
