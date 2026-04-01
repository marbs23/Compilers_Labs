#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

using namespace std;

class Token {
public:
    // Tipos de token
    enum Type {
        PLUS,    // +
        MINUS,   // -
        MUL,     // *
        DIV,     // /
        POW,     // ^
        LPAREN,  // (
        RPAREN,  // )
        NUM,     // Número
        SEMICOLON, // Punto y coma
        ERR,     // Error
        END,     // Fin de entrada
        ID,      // Id
        FLOAT,   // Float
        FUNC,
        CONST,
    };

    // Atributos
    Type type;
    string text;
    int line;
    int col;

    // Constructores
    Token(Type type, int _line, int _col);
    Token(Type type, char c, int _line, int _col);
    Token(Type type, const string& string, int _line, int _col);
    Token(Type type, const string& source, int first, int last, int _line, int _col);

    // Sobrecarga de operadores de salida
    friend ostream& operator<<(ostream& outs, const Token& tok);
    friend ostream& operator<<(ostream& outs, const Token* tok);
};

#endif // TOKEN_H