#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(CompilationEngine& compilationEng) {
    this->outputFile = nullptr;
    
}

CompilationEngine::CompilationEngine(string inputFileName, string outputFileName) {

    tokens = new JackTokenizer(inputFileName);

    outputFile.open(outputFileName);
    if(!outputFile.is_open()) {
        cout << "cant open output file" << endl;
    }

    indentValue = 0;

    CompileClass();
};

void CompilationEngine::CompileClass() {
    tokens->advance();
    if(tokens->keyWord() != my_enums::keyWord::CLASS) {
        cout << "broken input" << endl;
        return;
    }
    outputFile << indents() << "<class>" << endl;
    indentValue++;
    tokens->advance();
    if(tokens->tokenType() != my_enums::tokenType::IDENTIFIER) {
        cout << "unexpected input" << endl;
        return;
    }
    outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;

    tokens->advance();

    if(tokens->tokenType() != my_enums::tokenType::SYMBOL) {
        cout << "unexpected item" << endl;
        return;
    }

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;

    while(tokens->symbol() != '}' && tokens->hasMoreTokens()) {
    
        tokens->advance();
        
        

        if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {

            if(tokens->keyWord() == my_enums::keyWord::STATIC || tokens->keyWord() == my_enums::keyWord::FIELD) {
                outputFile << indents() << "<classVarDec>" << endl;
                indentValue++;
                outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
                CompileClassVarDec();
                indentValue--;
                outputFile << indents() << "</classVarDec>" << endl;
            
            } else if(tokens->keyWord() == my_enums::keyWord::CONSTRUCTOR || tokens->keyWord() == my_enums::keyWord::FUNCTION || tokens->keyWord() == my_enums::keyWord::METHOD) {
                
                outputFile << indents() << "<subroutineDec>" << endl;
                indentValue++;
                outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
                CompileSubroutine();
                indentValue--;
                outputFile << indents() << "</subroutineDec>" << endl;
            }
        }


    }




    if(tokens->tokenType() != my_enums::tokenType::SYMBOL) {
        cout << "unexpected item" << endl;
        return;
    }

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;

    indentValue--;
    outputFile << indents() << "</class>" << endl;
        
}

void CompilationEngine::CompileClassVarDec() {
    
}

void CompilationEngine::CompileSubroutine() {

}

string CompilationEngine::indents() {
    string s(indentValue, '\t');
    return s;
}