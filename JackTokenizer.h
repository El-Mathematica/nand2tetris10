#ifndef JACKTOKENIZER_H
#define JACKTOKENIZER_H

#include <iostream>
#include <string>
#include <fstream>

#include "enum.h"

using namespace std;

class JackTokenizer {
    private:
        string currentToken;
        ifstream myFile;
    public:
        JackTokenizer(string fileName);
        bool hasMoreTokens();
        void advance();
        my_enums::tokenType tokenType();
        my_enums::keyWord keyWord();
        char symbol();
        string identifier();
        int intVal();
        string stringVal();
};



#endif