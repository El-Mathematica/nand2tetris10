#ifndef COMPILATIONENGINE_H
#define COMPILATIONENGINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "enum.h"
#include "JackTokenizer.h"

using namespace std;

class CompilationEngine {
    private:
        ofstream outputFile;
        
        JackTokenizer* tokens;
        int indentValue;
    public:
        CompilationEngine(CompilationEngine& compilationEng);
        CompilationEngine(string inputFileName, string outputFileName);
        void CompileClass();
        void CompileClassVarDec();
        void CompileSubroutine();
        void compileParameterList();
        void compileVarDec();
        void compileStatements();
        void compileDo();
        void compileLet();
        void compileWhile();
        void compileReturn();
        void compileIf();
        void CompileExpression();
        void CompileTerm();
        void CompileExpressionList();
        string indents();
};

#endif
