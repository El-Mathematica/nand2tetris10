#ifndef JACKTOKENIZER_H
#define JACKTOKENIZER_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include "enum.h"

using namespace std;

class JackTokenizer {
    private:
        string currentToken;
        string currentLookForwardToken;
        ifstream myFile;
        ifstream lookForwardFile;
        unordered_map<string, my_enums::keyWord> tokenMap;
    public:
        JackTokenizer(string fileName);
        bool hasMoreTokens();
        void advance();
        void advancePeek();
        my_enums::tokenType tokenType();
        my_enums::keyWord keyWord();
        string stringKeyWord();
        char symbol();
        string identifier();
        int intVal();
        string stringVal();
};



#endif