#ifndef AST_H
#define AST_H

#include <string>
#include <unordered_map>
#include <list>
#include <ostream>

using namespace std;

class Visitor;
class Body;

// Operadores binarios soportados
enum BinaryOp { 
    PLUS_OP, 
    MINUS_OP, 
    MUL_OP, 
    DIV_OP,
    POW_OP,
    AND_OP,
    OR_OP,
    LT_OP,
    LE_OP,
    GT_OP,
    GE_OP,
    EQ_OP,
    NE_OP
};

// Clase abstracta Exp
class Exp {
public:
    virtual int  accept(Visitor* visitor) = 0;
    virtual ~Exp() = 0;  // Destructor puro → clase abstracta
    static string binopToChar(BinaryOp op);  // Conversión operador → string
};

// Expresión binaria
class BinaryExp : public Exp {
public:
    Exp* left;
    Exp* right;
    BinaryOp op;
    int accept(Visitor* visitor);
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    ~BinaryExp();

};

// Expresión numérica
class NumberExp : public Exp {
public:
    int value;
    int accept(Visitor* visitor);
    NumberExp(int v);
    ~NumberExp();
};

// Expresión numérica
class IdExp : public Exp {
public:
    string value;
    int accept(Visitor* visitor);
    IdExp(string v);
    ~IdExp();
};


class Stm{
public:
    virtual int accept(Visitor* visitor) = 0;
    virtual ~Stm() = 0;
};

class AssignStm: public Stm {
public:
    string id;
    Exp* e;
    AssignStm(string, Exp*);
    ~AssignStm();
    int accept(Visitor* visitor);
};
class PrintStm: public Stm {
public:
    Exp* e;
    PrintStm(Exp*);
    ~PrintStm();
    int accept(Visitor* visitor);
};
class IfStm: public Stm {
public:
    Exp* cond;
    Body* bodyIf;
    Body* bodyElse;
    IfStm();
    ~IfStm();
    int accept(Visitor* visitor);
};
class WhileStm: public Stm {
public:
    Exp* cond;
    Body* body;
    WhileStm();
    ~WhileStm();
    int accept(Visitor* visitor);
};
class DoWhileStm: public Stm {
public:
    Exp* cond;
    Body* body;
    DoWhileStm();
    ~DoWhileStm();
    int accept(Visitor* visitor);
};
class SwitchStm: public Stm {
public:
    Exp* cond;
    unordered_map<int,Body*> options;
    Body* defaultBody;
    SwitchStm();
    ~SwitchStm();
    int accept(Visitor* visitor);
};
class BreakStm: public Stm {
public:
    BreakStm();
    ~BreakStm();
    int accept(Visitor* visitor);
};

class Body {
public:
    list<Stm*> slist;
    void add(Stm*);
    int accept(Visitor* visitor);
    Body();
    ~Body();
};

class Program {
public:
    Body* b;
    Program();
    ~Program();
    int accept(Visitor* visitor);
};

#endif // AST_H
