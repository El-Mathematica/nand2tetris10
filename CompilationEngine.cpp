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

    while(tokens->hasMoreTokens()) {
    
        tokens->advance();
        
 

        if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {

            if(tokens->keyWord() == my_enums::keyWord::STATIC || tokens->keyWord() == my_enums::keyWord::FIELD) {

                CompileClassVarDec();
    
            } else if(tokens->keyWord() == my_enums::keyWord::CONSTRUCTOR || tokens->keyWord() == my_enums::keyWord::FUNCTION || tokens->keyWord() == my_enums::keyWord::METHOD) {

                CompileSubroutine();
                
            }
        }

        


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
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    

    // '{'
    tokens->advance();
    
    outputFile << indents() << "<subroutineBody>" << endl;
    indentValue++;
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    while(tokens->tokenType() == my_enums::tokenType::KEYWORD && tokens->stringKeyWord() == "var") {
        compileVarDec();
        tokens->advance();
    }

    compileStatements();
        
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;



    indentValue--;
    outputFile << indents() << "</subroutineBody>" << endl;

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
        return;
    }
    do {
        if(tokens->symbol() == ',') {
            outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
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

    
}

void CompilationEngine::compileVarDec() {
    //var
    outputFile << indents() << "<varDec>" << endl;
    indentValue++;
    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();

    if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {
        outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    } else {
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
    }

    do {
        if(tokens->symbol() == ',') {
            outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        }
        tokens->advance();
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
        tokens->advance();
    }
    while(tokens->symbol() == ',');

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;

    indentValue--;
    outputFile << indents() << "</varDec>" << endl;
    
}

void CompilationEngine::compileStatements() {

    outputFile << indents() << "<statements>" << endl;
    indentValue++;
    while(tokens->tokenType() == my_enums::tokenType::KEYWORD && (tokens->keyWord() == my_enums::keyWord::LET || tokens->keyWord() == my_enums::keyWord::IF || tokens->keyWord() == my_enums::keyWord::WHILE || tokens->keyWord() == my_enums::keyWord::DO || tokens->keyWord() == my_enums::keyWord::RETURN)) {
        switch(tokens->keyWord()) {
            case my_enums::keyWord::LET:
                compileLet();
                break;
            case my_enums::keyWord::IF:
                compileIf();
                break;
            case my_enums::keyWord::WHILE:
                compileWhile();
                break;
            case my_enums::keyWord::DO:
                compileDo();
                break;
            case my_enums::keyWord::RETURN:
                compileReturn();
                break;
        }
        
        if(tokens->symbol() == '}') {
            break;
        }
        

        //tokens->advance();
    }

    indentValue--;
    outputFile << indents() << "</statements>" << endl;
}

void CompilationEngine::compileDo() {
    outputFile << indents() << "<doStatement>" << endl;
    indentValue++;

    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();

    outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
    tokens->advance();

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    if(tokens->symbol() == '(') {
        tokens->advance();

        CompileExpressionList();
        
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    } else if(tokens->symbol() == '.') {
        tokens->advance();
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
        tokens->advance();
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        tokens->advance(); // temp
        CompileExpressionList();

        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    }
    
    tokens->advance();

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    indentValue--;
    outputFile << indents() << "</doStatement>" << endl;
}

void CompilationEngine::compileLet() {
    outputFile << indents() << "<letStatement>" << endl;
    indentValue++;
    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();

    outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
    tokens->advance();

    if(tokens->symbol() == '[') {
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        tokens->advance();
        CompileExpression();
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        tokens->advance();
    }

    //'='
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();

    CompileExpression();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    
    indentValue--;
    outputFile << indents() << "</letStatement>" << endl;
}

void CompilationEngine::compileWhile() {
    outputFile << indents() << "<whileStatement>" << endl;
    indentValue++;

    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    CompileExpression();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    compileStatements();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();


    indentValue--;
    outputFile << indents() << "</whileStatement>" << endl;
}

void CompilationEngine::compileReturn() {
    outputFile << indents() << "<returnStatement>" << endl;
    indentValue++;

    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();

    if(tokens->symbol() == ';') {
        
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        tokens->advance();
        indentValue--;
        outputFile << indents() << "</returnStatement>" << endl;
        return;
    }

    CompileExpression();

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    indentValue--;
    outputFile << indents() << "</returnStatement>" << endl;
}

void CompilationEngine::compileIf() {
    outputFile << indents() << "<ifStatement>" << endl;
    indentValue++;

    outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    tokens->advance();

    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    CompileExpression();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();
    compileStatements();
    outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
    tokens->advance();

    if(tokens->keyWord() == my_enums::keyWord::ELSE) {
        outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
        tokens->advance();
        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        tokens->advance();
        compileStatements();

        outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
        tokens->advance();
    }
    //cout << tokens->stringKeyWord() << endl;
    
    indentValue--;
    outputFile << indents() << "</ifStatement>" << endl;
}

void CompilationEngine::CompileExpression() {

    outputFile << indents() << "<expression>" << endl;
    indentValue++;

    

    if(tokens->tokenType() == my_enums::tokenType::SYMBOL) {
        tokens->advance();
        indentValue--;
        outputFile << indents() << "</expression>" << endl;
        return;
    }

    

    outputFile << indents() << "<term>" << endl;
    indentValue++;


    if(tokens->tokenType() == my_enums::tokenType::KEYWORD) {
        outputFile << indents() << "<keyword> " << tokens->stringKeyWord() << " </keyword>" << endl;
    } else {
        outputFile << indents() << "<identifier> " << tokens->identifier() << " </identifier>" << endl;
    }
    


    tokens->advance(); // check for token out of expression

    indentValue--;
    outputFile << indents() << "</term>" << endl;

    indentValue--;
    outputFile << indents() << "</expression>" << endl;
    
    
}

void CompilationEngine::CompileTerm() {

}

void CompilationEngine::CompileExpressionList() {
    outputFile << indents() << "<expressionList>" << endl;
    indentValue++;
    
    
    
    while(tokens->stringKeyWord() != ")") {
        
        if(tokens->stringKeyWord() == ",") {
            outputFile << indents() << "<symbol> " << tokens->symbol() << " </symbol>" << endl;
            tokens->advance();
        }
        CompileExpression();

    }

    
    


    indentValue--;
    outputFile << indents() << "</expressionList>" << endl;
}

string CompilationEngine::indents() {
    string s(indentValue*2, ' ');
    return s;
}