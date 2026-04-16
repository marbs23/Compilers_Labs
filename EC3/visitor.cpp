#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include "ast.h"
#include "visitor.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IfExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int MaxExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int SqrtExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NegExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void PrintStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void AsignStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void Programa::accept(Visitor* visitor) {
    visitor->visit(this);
}

///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp* exp) {
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(SqrtExp* exp) {
    cout << "sqrt(";
    exp->value->accept(this);
    cout <<  ")";
    return 0;
}

int PrintVisitor::visit(IfExp* exp) {
    cout << "if(";
    exp->left->accept(this);
    cout << ',';
    exp->mid->accept(this);
    cout << ',';
    exp->right->accept(this);
    cout << ')';
    return 0;
}

int PrintVisitor::visit(MaxExp* exp) {
    cout << "max(";
    bool first = true;
    for (auto exp : exp->args)
    {
        if (!first)cout << ' , ';
        exp->accept(this);
        first = false;
    }
    return 0;
}

int PrintVisitor::visit(NegExp* exp) {
    cout << "-(";
    exp->value->accept(this);
    cout <<  ")";
    return 0;
}

void PrintVisitor::imprimir(Programa* programa){
    if (programa)
    {
        cout << "Codigo:" << endl;
        programa->accept(this);
        cout << endl;
    }
    return ;
}

///////////////////////////////////////////////////////////////////////////////////
int EVALVisitor::visit(BinaryExp* exp) {
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    switch (exp->op) {
        case PLUS_OP:
            result = v1 + v2;
            break;
        case MINUS_OP:
            result = v1 - v2;
            break;
        case MUL_OP:
            result = v1 * v2;
            break;
        case DIV_OP:
            if (v2 != 0)
                result = v1 / v2;
            else {
                cout << "Error: división por cero" << endl;
                result = 0;
            }
            break;
        case POW_OP:
            result = pow(v1,v2);
            break;
        default:
            cout << "Operador desconocido" << endl;
            result = 0;
    }
    return result;
}

int EVALVisitor::visit(NumberExp* exp) {
    return exp->value;
}

int EVALVisitor::visit(SqrtExp* exp) {
    return floor(sqrt( exp->value->accept(this)));
}

int EVALVisitor::visit(NegExp* exp) {
    return -1*( exp->value->accept(this));
}


void EVALVisitor::interprete(Programa* programa){
    if (programa)
    {
        cout << "Interprete:";
        programa->accept(this);
        cout <<endl;
    }
    return;
}

void EVALVisitor::visit(AsignStmt *stm) {
    auto varIt = stm->variables.begin();
    auto expIt = stm->expressions.begin();
    while (varIt != stm->variables.end() && expIt != stm->expressions.end())
    {
        memoria[*varIt] = (*expIt)->accept(this);
        varIt++;
        expIt++;
    }
        
}

int EVALVisitor::visit(IdExp *e) {
    return memoria[e->value];
}

int EVALVisitor::visit(IfExp *e) {
    int l = e->left->accept(this);
    int m = e->mid->accept(this);
    int r = e->right->accept(this);
    if (l) return m;
    return r;
}

int EVALVisitor::visit(MaxExp *e) {
    int result = INT_MIN;
    for (auto e : e->args)
    {
        int value = e->accept(this);
        if (value > result) result = value; 
    }
    return result;
}
 


void EVALVisitor::visit(PrintStmt *stm) {
    cout << stm->exp->accept(this);
}

void EVALVisitor::visit(Programa *p) {
    for (auto i:p->slist) {
        i->accept(this);
    }
}



void PrintVisitor::visit(AsignStmt *stm) {
    bool first = true;
    for (auto var : stm->variables) {
        if (!first) cout << ", ";
        cout << var;
        first = false;
    }
    first = true;
    cout << " = ";
    for (auto exp : stm->expressions) {
        if (!first) cout << ", ";
        cout << exp;
        first = false;
    }
    cout << endl;
}
void PrintVisitor::visit(PrintStmt *stm) {
    cout << "print (";
    stm->exp->accept(this);
    cout << ")"<< endl;
}

void PrintVisitor::visit(Programa * p) {
    for (auto i:p->slist) {
        i->accept(this);
    }
}

int PrintVisitor::visit(IdExp *e) {
    cout << e->value;
    return 0;
}

