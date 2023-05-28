#include <iostream>
#include <fstream>

#include "JackTokenizer.h"

using namespace std;

int main() {
    JackTokenizer tokens = JackTokenizer("simpleTest.jack");
    if(tokens.hasMoreTokens()) { //if more tokens exist in the stream
        
    }
    return 0;
}