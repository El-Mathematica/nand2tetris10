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
    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
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

                CompileClassVarDec();
    
            } else if(tokens->keyWord() == my_enums::keyWord::CONSTRUCTOR || tokens->keyWord() == my_enums::keyWord::FUNCTION || tokens->keyWord() == my_enums::keyWord::METHOD) {
                
                CompileSubroutine();
                
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
    outputFile << indents() << "<classVarDec>" << endl;
    indentValue++;
    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();
    while(tokens->symbol() != ';') {
        if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {
            outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
        } else if(tokens->tokenType() == my_enums::tokenType::SYMBOL) {
            outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        } else {
            outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
        }
        tokens->advance();
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
        tokens->advance();
    }
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    indentValue--;
    outputFile << indents() << "</classVarDec>" << endl;
}

void CompilationEngine::CompileSubroutine() {
    outputFile << indents() << "<subroutineDec>" << endl;
    indentValue++;
    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();
    if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {
        outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    } else {
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
    }
    tokens->advance();
    outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
    tokens->advance();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    compileParameterList();
    
    

    indentValue--;
    outputFile << indents() << "</subroutineDec>" << endl;
}

void CompilationEngine::compileParameterList() {
    outputFile << indents() << "<parameterList>" << endl;
    indentValue++;
    tokens->advance();
    if(tokens->symbol() == ')') {
        indentValue--;
        outputFile << indents() << "</parameterList>" << endl;
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        return;
    }
    do {
        if(tokens->symbol() == ',') {
            tokens->advance();
        }
        if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {
            outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
        } else {
            outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
        }
        tokens->advance();
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
        tokens->advance();
    }
    while(tokens->symbol() == ',');
    

    indentValue--;
    outputFile << indents() << "</parameterList>" << endl;

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
}

void CompilationEngine::compileVarDec() {

}

void CompilationEngine::compileStatements() {

}

void CompilationEngine::compileDo() {

}

void CompilationEngine::compileLet() {

}

void CompilationEngine::compileWhile() {

}

void CompilationEngine::compileReturn() {

}

void CompilationEngine::compileIf() {

}

void CompilationEngine::CompileExpression() {

}

void CompilationEngine::CompileTerm() {

}

void CompilationEngine::CompileExpressionList() {

}

string CompilationEngine::indents() {
    string s(indentValue*2, ' ');
    return s;
}