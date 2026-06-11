#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include <list>

class BinaryExp;
class Body;
class FunDec;
class FcallExp;
class IdExp;
class IfStm;
class NumberExp;
class PrintStm;
class Program;
class ReturnStm;
class Stm;
class VarDec;
class WhileStm;

class Visitor {
public:
    virtual int visit(BinaryExp* exp)  = 0;
    virtual int visit(NumberExp* exp)  = 0;
    virtual int visit(IdExp* exp)      = 0;
    virtual int visit(PrintStm* stm)   = 0;
    virtual int visit(WhileStm* stm)   = 0;
    virtual int visit(DoWhileStm* stm) = 0;
    virtual int visit(SwitchStm* stm)  = 0;
    virtual int visit(IfStm* stm)      = 0;
    virtual int visit(AssignStm* stm)  = 0;
    virtual int visit(Body* body)      = 0;
    virtual int visit(VarDec* vd)      = 0;
    virtual int visit(FcallExp* fc)    = 0;
    virtual int visit(BreakStm* r)     = 0;
    virtual int visit(ReturnStm* r)    = 0;
    virtual int visit(FunDec* fd)      = 0;
};
class GenCodeVisitor : public Visitor {
public:
    unordered_map<string, int> position;

    int counter = 1;
    int labelCounter = 0;

    int codigo(Program* program);
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(IdExp* exp) override;
    int visit(AssignStm* stm) override;
    int visit(PrintStm* stm) override;
    int visit(IfStm* stm) override;
    int visit(WhileStm* stm) override;
    int visit(DoWhileStm* stm) override;
    int visit(SwitchStm* stm) override;
    int visit(ReturnStm* stm) override;
    int visit(BreakStm* stm) override;
    int visit(Body* body)     override;
    int visit(VarDec* vd)     override;
    int visit(FcallExp* fc)   override;
    int visit(FunDec* fd)     override;
};
#endif // VISITOR_H