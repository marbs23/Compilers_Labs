#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

using namespace std;

class Token {
public:
    // Tipos de token
    enum Type {
        // Aritmetic Operators
        PLUS,    // +
        MINUS,   // -
        MUL,     // *
        DIV,     // /
        POW,     // **

        // Delimitators
        LPAREN,  // (
        RPAREN,  // )
        SEMICOL, // ;  
        COLON,   // :
        COMMA,   // ,
            
        // Literals
        NUM,     // Número
        TRUE,    // true
        FALSE,   // false

        // Reserved Words
        SQRT,    // sqrt
        PRINT,   // print
        ID,      // ID
        
        // Logical Operators
        AND,     // and
        OR,      // or
        
        // Relational Operators
        LT,      // <
        LE,      // <=
        GT,      // >
        GE,      // >=
        EQ,      // ==
        NE,      // !=
        
        // Assign
        ASSIGN,  // =
        
        // Flow Control
        IF,
        THEN,
        ELSE,
        ENDIF,
        WHILE,
        DO,
        ENDWHILE,
        SWITCH,
        CASE,
        ENDSWITCH,
        DEFAULT,
        BREAK,

        // Declarations
        VAR,

        // Functions
        FUN,
        ENDFUN,
        RETURN,

        // Special
        ERR,     // Error
        END      // Fin de entrada
    };

    // Atributos
    Type type;
    string text;

    // Constructores
    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const string& source, int first, int last);

    static std::string typeName(Type t);

    // Sobrecarga de operadores de salida
    friend ostream& operator<<(ostream& outs, const Token& tok);
    friend ostream& operator<<(ostream& outs, const Token* tok);
};

#endif // TOKEN_H