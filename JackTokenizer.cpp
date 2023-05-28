#include <iostream>

#include "JackTokenizer.h"

using namespace std;

JackTokenizer::JackTokenizer(string fileName) {
    myFile.open(fileName);
    if(!myFile.is_open()) {
        cout << "Can't Open File!" << endl;
    } 
}


bool JackTokenizer::hasMoreTokens() {
    char c = myFile.get();
    while(!myFile.eof()) {
        
        if(c == ' ' || c == '\n') {
            c = myFile.get();
            continue;
        } else if(c == '/') {
            c = myFile.get();
            if(c == '/') {
                while(!myFile.eof() && c != '\n') {
                    c = myFile.get();
                }
                continue;
            } else {
                return true;
            }
            
        } else {
            return true;
        }
        
    }
    return false;
}




