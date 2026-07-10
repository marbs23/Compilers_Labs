#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>
#include <string>

class Token {
public:
    enum Type {
        // Arithmetic Op
        PLUS, MINUS, MUL, DIV, MOD,          // + - * / %
        
        // Delimiters
        LPAREN, RPAREN,                      // ( )
        LBRACE, RBRACE,                      // { }
        LBRACKET, RBRACKET,                  // [ ]
        SEMICOL, COMA, DOT, ARROW,           // ; , . ->
        
        // Relational / Equality Op
        LT, LE, GT, GE, EQ, NEQ,             // < <= > >= == !=
        
        // Logical Op
        AND, OR, NOT,                        // && || !
        
        // Assign Op
        ASSIGN, PLUSASSIGN, MINUSASSIGN,     // = += -=
        MULASSIGN, DIVASSIGN,                // *= /=
        INC, DEC,                            // ++ --
        
        // Pointers / referencias
        AMP,                                 // &
        
        // Literals
        NUMLIT, CHARLIT, STRINGLIT,          // 123, 'a', "hola"
        TRUE, FALSE,                         // true, false
        NULLPTR,                             // nullptr
        
        // Type keywords
        INT, FLOAT, DOUBLE, CHAR, BOOL, VOID, STRING, AUTO,
        
        // Struct / Templates
        STRUCT, TEMPLATE, TYPENAME,
        
        // Memoria dinámica
        NEW, DELETE,
        
        // Id's - Reserved words
        ID, PRINT, RETURN,
        
        // Flow Control
        IF, ELSE, WHILE, DO, FOR, BREAK, CONTINUE,
        ERR,        // Carácter no reconocido (error léxico)
        END         // Fin de la entrada
    };

    Type        type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string& source, int first, int last);

    static std::string typeName(Type t);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);
};

#endif // TOKEN_H
