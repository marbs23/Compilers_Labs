#ifndef AST_H
#define AST_H

#include <string>
#include <unordered_map>
#include <list>
#include <ostream>

using namespace std;


// Operadores binarios soportados
enum BinaryOp { 
    PLUS_OP, 
    MINUS_OP, 
    MUL_OP, 
    DIV_OP,
    POW_OP
};

// Clase abstracta Exp
class Exp {
public:
    virtual ~Exp() = 0;  // Destructor puro → clase abstracta
    static string binopToChar(BinaryOp op);  // Conversión operador → string
    virtual void toDot(std::ostream& out, int& id) const = 0;  // Visualización en DOT
};

// Expresión binaria
class BinaryExp : public Exp {
public:
    Exp* left;
    Exp* right;
    BinaryOp op;
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    ~BinaryExp();
    void toDot(std::ostream& out, int& id) const override; 

};

// Expresión numérica
class NumberExp : public Exp {
public:
    int value;
    NumberExp(int v);
    ~NumberExp();
    void toDot(std::ostream& out, int& id) const override; 
};

// Expresión numérica
class IdExp : public Exp {
public:
    string value;
    IdExp(string v);
    ~IdExp();
    void toDot(std::ostream& out, int& id) const override; 
};

// Raiz cuadrada
class SqrtExp : public Exp {
public:
    Exp* value;
    SqrtExp(Exp* v);
    ~SqrtExp();
    void toDot(std::ostream& out, int& id) const override; 
}
;

// Operador ternario IF
class IfExp : public Exp {
public:
    Exp* left;
    Exp* mid;
    Exp* right;
    IfExp(Exp* l, Exp* m, Exp* r);
    ~IfExp();
    void toDot(std::ostream& out, int& id) const override;
};

#endif // AST_H
