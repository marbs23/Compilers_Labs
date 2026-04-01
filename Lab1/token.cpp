#include <iostream>
#include "token.h"

using namespace std;

// -----------------------------
// Constructores
// -----------------------------

Token::Token(Type type, int _line, int _col) 
    : type(type), text(""), line(_line), col(_col) { }

Token::Token(Type type, char c, int _line, int _col) 
    : type(type), text(string(1, c)), line(_line), col(_col) { }

Token::Token(Type type, const string& string, int _line, int _col)
    : type(type), text(string), line(_line), col(_col) { }

Token::Token(Type type, const string& source, int first, int last, int _line, int _col) 
    : type(type), text(source.substr(first, last)), line(_line), col(_col) { }

// -----------------------------
// Sobrecarga de operador <<
// -----------------------------

// Para Token por referencia
ostream& operator<<(ostream& outs, const Token& tok) {
    switch (tok.type) {
        case Token::PLUS:      outs << "TOKEN(PLUS, \""      << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::MINUS:     outs << "TOKEN(MINUS, \""     << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::MUL:       outs << "TOKEN(MUL, \""       << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::POW:       outs << "TOKEN(POW, \""       << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::DIV:       outs << "TOKEN(DIV, \""       << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::SEMICOLON: outs << "TOKEN(SEMICOLON, \"" << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::NUM:       outs << "TOKEN(NUM, \""       << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::FLOAT:     outs << "TOKEN(FLOAT, \""     << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::ID:        outs << "TOKEN(ID, \""        << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::FUNC:      outs << "TOKEN(FUNC, \""      << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::CONST:     outs << "TOKEN(CONST, \""     << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::ERR:       outs << "TOKEN(ERR, \""       << tok.text << "\", (" << tok.line << "," << tok.col << "))"; break;
        case Token::END:       outs << "TOKEN(END"          << ")"; break;
    }
    return outs;
}

// Para Token puntero
ostream& operator<<(ostream& outs, const Token* tok) {
    if (!tok) return outs << "TOKEN(NULL)";
    return outs << *tok;  // delega al otro
}