///Function implementation for the classifer.h file.
///Documentation on implementation is here too.

#include "classifier.h"

//CONSTRUCTORS:
///These constructors do nothing as they are not necessary as we are testing using one file.
///These definitions are placed here if needed in the future.
classifier::classifier() {

}

classifier::classifier(const classifier &) {

}

classifier::~classifier() {

}

//MAIN FUNCTIONS:

void classifier::train(ifstream& trainData){
    //Creates and sets tweetList using information from trainData.
    setTweetList(genTweetList(trainData));

    //Outputs the tweetList into a csv file. This is not necessary but is good for debugging or data transfer.
    ofstream output ("tweetlist.csv");
    outputTweetList(output);
    output.close();

    //Creates and sets the word library using all the tweets in the tweetList.
    //A word stem/factory function has not been implemented yet.
    genWordLib();

    //Outputs the word list into the wordlist.csv file
    outputWordList();
}

void classifier::test(ifstream& twtData, ifstream& sentData, ofstream& output){
    setTestList(genTweetList(twtData));

    matchSentToTweet(sentData);

    ofstream ttlist ("testtweetlist.csv");
    outputTestList(ttlist);
    ttlist.close();

    score(output);
}

void classifier::score(ofstream& output) {
    decomposeAll();
    judgeAll(usesThreshold);

    //populates the resultsList with all wrongly judged tweets
    for(int i = 0; i < testList.size(); i++) {
        if (testList[i].getSent() != testList[i].getJSent()) {
            resultList.push_back(testList[i]);
        }
    }

    //Compiles an output csv with accuracy and the tweet ids of wrong tweets
    outputResults(output);
}

void classifier::outputResults(ofstream& output) {
    if (output.is_open()) {
        double accuracy = ((double) testList.size() - (double) resultList.size()) / (double) testList.size();

        //Just adds zeroes. (Ex. 0.6 --> 0.600 0.66 --> 0.660)
        if (int(accuracy * 1000) % 100 == 0) {
            output << roundToThousandth(accuracy) << "00" << "\n";
        } else if (int(accuracy * 1000) % 10 == 0) {
            output << roundToThousandth(accuracy) << "0" << "\n";
        } else {
            output << roundToThousandth(accuracy) << "\n";
        }

        //Outputs accuracy and incorrect tweet ids into the output file
        for (int i = 0; i < resultList.size(); i++) {
            output << resultList[i].getID().c_str() << "\n";
        }
    } else {
        cout << "Error has occured: file is not open" << endl;
    }
}

//TWEET FUNCTIONS:
    //getTweetList
    //Opens input file and creates a new vector of tweets
    //Fills this vector with data from the input file
vector<tweet> classifier::genTweetList(ifstream& file){
    vector<tweet> twtLst;

    if (file.is_open()) {
        char temp[2];
        bool isTrain;
        char id[11] = "-1";

        //Checks if the first letter of the file is i.
        //If yes, the tweetList is generated with a sentiment
        //If no, the tweetList is generated with no sentiment
        file.getline(temp, 2, ',');
        char iLtr[2] = "i";

        if(strcmp(temp, iLtr) == 0) {
            isTrain = false;
        } else {
            isTrain = true;
        }

        //Ignores the rest of the header
        file.clear();
        file.ignore(256, '\n');

        //Gets ID, Sentiment, and Tweet message from the file
        //Does not get sentiment if isTrain is false
        while(file.peek() != EOF) {
            char sent[3] = "-1";
            char msg[1024] = "null";
            int numSent; //todo change

            if(isTrain) {
                file.getline(sent, 2, ',');
                file.clear();
            }

            //converts the string sent into an int sent
            numSent = strtol(sent, nullptr, 10);

            if(numSent == 4) {
                numSent = 1;
            }

            //gets id
            file.getline(id, 11, ',');
            file.clear();

            //ignores other elements
            file.ignore(256, ',');
            file.ignore(256, ',');
            file.ignore(256, ',');

            //gets tweet message
            file.getline(msg, 256, '\n');
            file.clear();

            if(isTrain) {
                tweet twt(DSString(id), numSent, DSString(msg));
                twtLst.push_back(twt);
            } else {
                tweet twt((DSString(id)), DSString(msg));
                twtLst.push_back(twt);
            }

            file.clear();
        }
    }
    return twtLst;
}

vector<tweet> classifier::matchSentToTweet(ifstream& file){
    vector<tweet> twtLst;

    if (file.is_open()) {
        char id[11] = "-1";
        char tempSent[2] = "n";
        int sent = 0;

        file.ignore(256, '\n');

        int curTwtInd = 0;

        while(file.peek() != EOF) {
            file.getline(tempSent, 2, ','); //gets the sentiment of the file
            file.clear();

            sent = strtol(tempSent, nullptr, 10); //converts sentiment to an int

            if(sent == 4) { //Changes sentiment system from a 0 to 4 system to a 0 to 1 system
                sent = 1;
            }

            file.getline(id, 11, '\n'); //Gets id
            file.clear();

            int twtInd = searchTweetList(id); //Gets the index of a tweet with inputted id

            if (twtInd == -1) {
                cout << "ID not found" << endl;
            } else {
                testList[twtInd].setSent(sent); //Sets tweet with the appropriate sentiment
            }

            curTwtInd++;
        }
    }
    return twtLst;
}

int classifier::searchTweetList(DSString id) {
    int curTwtInd = 0;
    while(curTwtInd < testList.size()) { //Runs through the testList entries sequentially until the ids match
        if(testList[curTwtInd].getID() == id) {
            return curTwtInd;
        }
        curTwtInd++;
    }
    cout << "Tweet Not Found" << endl;
    return -1;
}

void classifier::outputTweetList(ofstream& output) {
    if(output.is_open()) {
        for(int i = 0; i < tweetList.size(); ++i) {
            output << tweetList[i].getID().c_str() << ", ";
            output << tweetList[i].getSent() << ", ";
            output << tweetList[i].getTweet().c_str() << "\n";
        }
    }
    output.close();
}

void classifier::outputTestList(ofstream& output) {
    if(output.is_open()) {
        for(int i = 0; i < testList.size(); ++i) {
            output << testList[i].getID().c_str() << ", ";
            output << testList[i].getSent() << ", ";
            output << testList[i].getTweet().c_str() << "\n";
        }
    }
    output.close();
}

vector<tweet>& classifier::getTweetList() { return tweetList; }

void classifier::setTweetList(vector<tweet> twtLst) { tweetList = twtLst; }

void classifier::setTestList(vector<tweet> twtLst) { testList = twtLst; }

void classifier::setUsesThreshold(int i) { usesThreshold = i; }

//WORDLIB FUNCTIONS:

//WordList results are formatted word, times used positively (total sentiment), times used
void classifier::outputWordList() {
    ofstream output("wordlist.csv");
    if(output.is_open()) {
        int i = 0;

        while (wordLib[i].getUses() >= usesThreshold && i < wordLib.size()) {
            output << wordLib[i].getStr().c_str() << ", ";
            output << wordLib[i].getTSent() << ", ";
            output << wordLib[i].getUses() << ", ";
            output << ((double) wordLib[i].getTSent()) / ((double) wordLib[i].getUses()) << "\n";
            i++;
        }
    }
    output.close();
}

//Used in genWordLib as a comparison function for sort()
bool isLessThan(word i, word j) { return i.getUses() < j.getUses(); }

//Adds all words into a list. Then it is sorted from most uses to least uses.
void classifier::genWordLib() {
    int i = 0;
    while (i < tweetList.size()) {
        getTweetList()[i].decompose();
        addToWordLib(getTweetList()[i].getWordList());
        i++;
    }
    std::sort(wordLib.begin(), wordLib.end(), isLessThan);
    std::reverse(wordLib.begin(), wordLib.end());
}

//Executes the decompose function for all tweets
void classifier::decomposeAll() {
    int i = 0;
    while (i < testList.size()) {
        testList[i].decompose();
        i++;
    }
}

vector<word> classifier::getWordLib() { return wordLib; }

//Given a word list, a new entry for wordlib is made if the word is not already there
//If there is a matching word, it will increment the total sentiment var.
void classifier::addToWordLib(vector<word> list) {
    int i = 0;
    while(i < list.size()) {
        int wordInd = searchWordLib(list[i].getStr());
        if (wordInd == -1) {
            wordLib.push_back(list[i]);
        } else {
            wordLib[wordInd].addTSent(list[i].getTSent());
            wordLib[wordInd].incUses();
        }
        i++;
    }
}

//MISC:

//Returns true if str has been found in WordLib.
int classifier::searchWordLib(DSString str) {
    int i = 0;
    while(i < wordLib.size()) {
        if(wordLib[i].getStr() == str) {
            return i;
        }
        i++;
    }
    return -1;
}

//Runs the judge function on all tweet in the testList.
void classifier::judgeAll(int usesThreshold) {
    for (int i = 0; i < testList.size(); i++) {
        testList[i].judge(wordLib, usesThreshold);
        if (testList[i].getJSent() == -1) {
            //if there are no words in the tweet that are on wordLib, the sentiment is guessed to be false
            testList[i].judge(wordLib, 0);
            if (testList[i].getJSent() == -1) {
                testList[i].setJSent(0);
            }
        }
    }
}

double classifier::roundToThousandth(double num) {
    return round(num * 1000.0) / 1000.0;
}
