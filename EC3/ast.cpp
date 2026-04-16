#include "ast.h"
#include <iostream>

using namespace std;

// ------------------ Exp ------------------
Exp::~Exp() {}

string Exp::binopToChar(BinaryOp op) {
    switch (op) {
        case PLUS_OP:  return "+";
        case MINUS_OP: return "-";
        case MUL_OP:   return "*";
        case DIV_OP:   return "/";
        case POW_OP:   return "**";
        default:       return "?";
    }
}

// ------------------ BinaryExp ------------------
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp o)
    : left(l), right(r), op(o) {}

    
BinaryExp::~BinaryExp() {
    delete left;
    delete right;
}



// ------------------ NumberExp ------------------
NumberExp::NumberExp(int v) : value(v) {}

NumberExp::~NumberExp() {}

// ------------------ IfExp ------------------
IfExp::IfExp(Exp* l, Exp* m, Exp* r) : left(l), mid(m), right(r) {}

IfExp::~IfExp() {
    delete left;
    delete mid;
    delete right;
}

// ------------------ SqrtExp ------------------
SqrtExp::SqrtExp(Exp* v) : value(v) {}

SqrtExp::~SqrtExp() {}

// ------------------ NegExp ------------------
NegExp::NegExp(Exp* v) : value(v) {}

NegExp::~NegExp() {}

// ------------------ MaxExp ------------------
MaxExp::MaxExp(list<Exp*> a) : args(a) {}

MaxExp::~MaxExp() {}

//
Programa::Programa() {}
Programa::~Programa(){}

Stmt::~Stmt(){}

PrintStmt::PrintStmt(Exp* e) {
    exp=e;
}

PrintStmt::~PrintStmt() {

}

AsignStmt::AsignStmt(list<string> v, list<Exp*> e): variables(v), expressions(e) {

}

AsignStmt::~AsignStmt() {

}

// ------------------ IdExp ------------------
IdExp::IdExp(string v) : value(v) {}

IdExp::~IdExp() {}
