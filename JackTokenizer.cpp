#include <iostream>

#include "JackTokenizer.h"

using namespace std;

JackTokenizer::JackTokenizer(string fileName) {
    
    tokenMap = {{"class", my_enums::keyWord::CLASS}, {"method", my_enums::keyWord::METHOD}, {"function", my_enums::keyWord::FUNCTION}, {"constructor", my_enums::keyWord::CONSTRUCTOR}, {"int", my_enums::keyWord::INT}, {"boolean", my_enums::keyWord::BOOLEAN}, {"char", my_enums::keyWord::CHAR}, {"void", my_enums::keyWord::VOID}, {"var", my_enums::VAR}, {"static", my_enums::STATIC}, {"field", my_enums::FIELD}, {"let", my_enums::LET}, {"do", my_enums::DO}, {"if", my_enums::IF}, {"else", my_enums::ELSE}, {"while", my_enums::WHILE}, {"return", my_enums::RETURN}, {"true", my_enums::TRUE}, {"false", my_enums::FALSE}, {"null", my_enums::NULLSPECIAL}, {"this", my_enums::THIS}};

    myFile.open(fileName);
    if(!myFile.is_open()) {
        cout << "Can't Open File!" << endl;
    } 

    
}


bool JackTokenizer::hasMoreTokens() {
    int getCount = 1;
    char c = myFile.get();
    while(!myFile.eof()) {
        if(isspace(c)) {
            c = myFile.get();
            getCount++;
            continue;
        } else if(c == '/') {
            char d = myFile.get();
            getCount++;

            if(d == '/') {
                while(!myFile.eof() && c != '\n') {
                    c = myFile.get();
                    getCount++;
                }
                
            }

            if(d == '*') {
                c = myFile.get();
                d = myFile.get();
                getCount+=2;
                while(!myFile.eof() && (c != '*' || d != '/')) {
                    c = d;
                    d = myFile.get();
                    getCount++;
                }

            }  else {
                for(int i = 0; i < getCount; i++) myFile.unget();
                return true;
            }
            
        } else {
            for(int i = 0; i < getCount; i++) myFile.unget();
            return true;
        } 
    }
    for(int i = 0; i < getCount; i++) myFile.unget();
    return false;
}



void JackTokenizer::advance() {
    currentToken = "";
    char c = myFile.get();
    while(!myFile.eof()) {
        if(isspace(c)) {
            c = myFile.get();
            continue;
        } else if(c == '/') {
            char d = myFile.get();
            if(d == '/') {
                while(!myFile.eof() && c != '\n') {
                    c = myFile.get();
                }
                

            } else if(d == '*') {
                c = myFile.get();
                d = myFile.get();

                while(!myFile.eof() && (c != '*' || d != '/')) {
                    c = d;
                    d = myFile.get();
                }
                
                c = myFile.get();

            }  else {
                break;
            }
        } else {
            break;
        }
    }
    currentToken.push_back(c);
    if(isalnum(currentToken[0])) {
        while(isalnum(myFile.peek())) {
            currentToken.push_back(myFile.get());
        }
    } else if(currentToken[0] == '\"') {
        while(myFile.peek() != '\"') {
            currentToken.push_back(myFile.get());
        }
        currentToken.push_back(myFile.get());

    } 
}

/*
void JackTokenizer::advancePeek() {
    int ungetter = 0;
    currentLookForwardToken = currentToken;
    if(isalnum(currentToken[0])) {

    }
}
*/

my_enums::tokenType JackTokenizer::tokenType() {
    if(currentToken[0] == '\"') {
        return my_enums::tokenType::STRING_CONST;
    } else if(isdigit(currentToken[0])) {
        return my_enums::tokenType::INT_CONST;
    } else if(!isalnum(currentToken[0])) {
        return my_enums::tokenType::SYMBOL;
    } else {
        if(tokenMap.find(currentToken) != tokenMap.end()) {
            return my_enums::tokenType::KEYWORD;
        } else {
            return my_enums::tokenType::IDENTIFIER;
        }
    }
}

my_enums::keyWord JackTokenizer::keyWord() {
    return tokenMap.find(currentToken)->second;
}

string JackTokenizer::stringKeyWord() {
    return currentToken;
}

char JackTokenizer::symbol() {
    
    return currentToken[0];
}

string JackTokenizer::identifier() {
    return currentToken;
}

int JackTokenizer::intVal() {
    return stoi(currentToken);
}

string JackTokenizer::stringVal() {
    string temp = currentToken.substr(1);
    return temp.substr(0, temp.size()-1);
}


