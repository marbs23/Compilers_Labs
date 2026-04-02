#include <iostream>
#include <cstring>
#include <fstream>
#include "token.h"
#include "scanner.h"

using namespace std;

// -----------------------------
// Constructor
// -----------------------------
Scanner::Scanner(const char* s): input(s), first(0), current(0) { 
    }

// -----------------------------
// Función auxiliar
// -----------------------------

bool is_white_space(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

// -----------------------------
// nextToken: obtiene el siguiente token
// -----------------------------

Token* Scanner::nextToken() {
    Token* token;
    char c;
    state = 0;
    first = current;;

    while (1) {
        switch (state) {
            case 0: 
                c = nextChar();
                if ((c == ' ' || c == '\n' || c == '\r' || c == '\t')) { first = current;; state = 0; }
                else if (c == '\0') return new Token(Token::END);
                else if (c == '(') state = 1;
                else if (c == ')') state = 2;
                else if (c == '+') state = 3;
                else if (c == '-') state = 4;
                else if (c == '*') state = 5;
                else if (c == '/') state = 6;
                else if (c == '^') state = 7;

                else if (c == '<') state = 20;
                else if (c == '>') state = 21;
                else if (c == '=') state = 22;
                else if (c == '!') state = 23;
                else if (isalpha(c)) state = 24;

                else if (c == '0') state = 11;
                else if (isdigit(c)) state = 8;
                else if (c == '#') state = 10;
                else return new Token(Token::ERR, c);
                break;

            case 1: return new Token(Token::LPAREN);
            case 2: return new Token(Token::RPAREN);
            case 3: return new Token(Token::PLUS, c);
            case 4: return new Token(Token::MINUS, c);
            case 5: return new Token(Token::MUL, c);
            case 6: return new Token(Token::DIV, c);
            case 7: return new Token(Token::POW, c);
            case 20: return new Token(Token::LT, '<');
            case 21: return new Token(Token::GT, '>');


            case 8: 
                c = nextChar();
                if (isdigit(c)) state = 8;
                else state = 9;
                break;

            case 9: 
                rollBack();
                return new Token(Token::NUM, input, first, current - first);

            case 10:
                c = nextChar();
                if (c == '\n' || c == '\0' ) {
                    first = current;
                    state = 0;
                } else state = 10;
                break;

            case 11:
                c = nextChar();
                if (c == 'b') {
                    state = 12;
                } else if (isdigit(c)) state = 8;
                else state = 9;
                break;

            case 12:
                c = nextChar();
                if (c == '1' || c == '0') state = 12;
                else state = 13;
                break;

            case 13:
                rollBack();
                return new Token(Token::BIN, input, first, current - first);

            case 22:
                c = nextChar();
                if (c == '=') return new Token(Token::EQEQ, input, first, current - first);
                rollBack();
                return new Token(Token::ERR, '=');

            case 23:
                c = nextChar();
                if (c == '=') return new Token(Token::NOTEQ, input, first, current - first);
                rollBack();
                return new Token(Token::ERR, '!');
            
            case 24:
                c = nextChar();
                if (isalpha(c)) state = 24;
                else state = 25;
                break;

            case 25:
            
                rollBack();
                {
                    string lexema = input.substr(first, current - first);
                    if (lexema == "SIN") return new Token(Token::SIN, input, first, current - first);
                    if (lexema == "COS") return new Token(Token::COS, input, first, current - first);
                    if (lexema == "LOG") return new Token(Token::LOG, input, first, current - first);
                    if (lexema == "True") return new Token(Token::TRUE, input, first, current - first);
                    if (lexema == "False") return new Token(Token::FALSE, input, first, current - first);
                    return new Token(Token::ERR, input, first, current - first);
                }
        }
    }
}

void Scanner::rollBack() {
    if (current > 0)
        current--;
}

char Scanner::nextChar() {
    int c = input[current];
    if (c != '\0') current++;
    return c;
}



// -----------------------------
// Destructor
// -----------------------------
Scanner::~Scanner() { }

// -----------------------------
// Función de prueba
// -----------------------------

void ejecutar_scanner(Scanner* scanner, const string& InputFile) {
    Token* tok;

    // Crear nombre para archivo de salida
    string OutputFileName = InputFile;
    size_t pos = OutputFileName.find_last_of(".");
    if (pos != string::npos) {
        OutputFileName = OutputFileName.substr(0, pos);
    }
    OutputFileName += "_tokens.txt";

    ofstream outFile(OutputFileName);
    if (!outFile.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << OutputFileName << endl;
        return;
    }

    outFile << "Iniciando Scanner para archivo: " << InputFile << endl << endl;

    while (true) {
        tok = scanner->nextToken();

        if (tok->type == Token::END) {
            outFile << *tok << endl;
            delete tok;
            outFile << "\nScanner exitoso" << endl << endl;
            outFile.close();
            return;
        }

        if (tok->type == Token::ERR) {
            outFile << *tok << endl;
            delete tok;
            outFile << "Caracter invalido" << endl << endl;
            outFile << "Scanner no exitoso" << endl << endl;
            outFile.close();
            return;
        }

        outFile << *tok << endl;
        delete tok;
    }
}
