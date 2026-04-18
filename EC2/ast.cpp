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
        case MOD_OP:   return "%";
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

// ------------------ IfExp ------------------
IfExp::IfExp(Exp* l, Exp* m, Exp* r)
    : left(l), mid(m), right(r) {}

    
IfExp::~IfExp() {
    delete left;
    delete mid;
    delete right;
}



// ------------------ NumberExp ------------------
NumberExp::NumberExp(int v) : value(v) {}

NumberExp::~NumberExp() {}

// ------------------ FloatExp ------------------
FloatExp::FloatExp(float v) : value(v) {}

FloatExp::~FloatExp() {}

// ------------------idExp ------------------
IdExp::IdExp(string v) : value(v) {}

IdExp::~IdExp() {}

// ------------------EExp ------------------
EExp::EExp(string v) : value(v) {}

EExp::~EExp() {}

// ------------------PiExp ------------------
PiExp::PiExp(string v) : value(v) {}

PiExp::~PiExp() {}

// ------------------ SqrtExp ------------------
SqrtExp::SqrtExp(Exp* v) : value(v) {}

SqrtExp::~SqrtExp() {}

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



void NumberExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << value << "\"];\n";
}

void SqrtExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"sqrt\"];\n";

    if (value) {
        int childId = id;
        value->toDot(out, id);
        out << "  node" << myId << " -> node" << childId << ";\n";
    }
}

void IdExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << value << "\"];\n";
}

void FloatExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << value << "\"];\n";
}

void EExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << value << "\"];\n";
}

void PiExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\"" << value << "\"];\n";
}

void IfExp::toDot(ostream& out, int& id) const {
    int myId = id++;
    out << "  node" << myId << " [label=\""
        << "IF" << "\"];\n";

    if (left) {
        int leftId = id;
        left->toDot(out, id);
        out << "  node" << myId << " -> node" << leftId << ";\n";
    }
    if (mid) {
        int midId = id;
        mid->toDot(out, id);
        out << "  node" << myId << " -> node" << midId << ";\n";
    }
    
    if (right) {
        int rightId = id;
        right->toDot(out, id);
        out << "  node" << myId << " -> node" << rightId << ";\n";
    }
}