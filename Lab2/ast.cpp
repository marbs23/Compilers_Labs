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

void BinaryExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\""
        << Exp::binopToChar(op) << "\"];\n";

    if (left) {
        int leftId = id;
        left->toDot(out, id);
        out << "  node" << myId << " -> node" << leftId << ";\n";
    }
    if (right) {
        int rightId = id;
        right->toDot(out, id);
        out << "  node" << myId << " -> node" << rightId << ";\n";
    }
}

// ------------------ NumberExp ------------------
NumberExp::NumberExp(int v) : value(v) {}

NumberExp::~NumberExp() {}

void NumberExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << value << "\"];\n";
}
