#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include <list>

class BinaryExp;
class NumberExp;
class IdExp;
class AssignStm;
class PrintStm;
class Program;

class Visitor {
public:
    virtual int visit(BinaryExp* exp) = 0;
    virtual int visit(NumberExp* exp) = 0;
    virtual int visit(IdExp* exp) = 0;
    virtual void visit(AssignStm* stm) = 0;
    virtual void visit(PrintStm* stm) = 0;
    virtual void visit(IfStm* stm) = 0;
    virtual void visit(WhileStm* stm) = 0;
    virtual void visit(DoWhileStm* stm) = 0;
};
class GenCodeVisitor : public Visitor {
public:
    unordered_map<string, int> position;
    int counter = 1;
    void codigo(Program* program);
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(IdExp* exp) override;
    void visit(AssignStm* stm) override;
    void visit(PrintStm* stm) override;
    void visit(IfStm* stm) override;
    void visit(WhileStm* stm) override;
    void visit(DoWhileStm* stm) override;
};
#endif // VISITOR_H