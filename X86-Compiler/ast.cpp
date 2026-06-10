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
        case LE_OP:   return "<";
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


// ------------------idExp ------------------
IdExp::IdExp(string v) : value(v) {}

IdExp::~IdExp() {}

// ------------------ Stm ------------------
Stm::~Stm(){}

// ------------------ PrintStm ------------------
PrintStm::PrintStm(Exp* expresion){
    e=expresion;
}
PrintStm::~PrintStm(){}

// ------------------ AssignStm ------------------
AssignStm::AssignStm(string variable,Exp* expresion){
    id = variable;
    e = expresion;
}
AssignStm::~AssignStm(){}

// ------------------ IfStm ------------------
IfStm::IfStm(){}
IfStm::~IfStm(){}

// ------------------ WhileStm ------------------
WhileStm::WhileStm(){}
WhileStm::~WhileStm(){}

// ------------------ SwitchStm ------------------
SwitchStm::SwitchStm(){}
SwitchStm::~SwitchStm(){}

// ------------------ DoWhileStm ------------------
DoWhileStm::DoWhileStm(){}
DoWhileStm::~DoWhileStm(){}

// ------------------ Body ------------------
Body::Body(){}
void Body::add(Stm* a){
    slist.push_back(a);
}
Body::~Body(){}


// ------------------ Program ------------------
Program::Program(){}
Program::~Program(){}