#include <iostream>
#include "ast.h"
#include "visitor.h"
#include <unordered_map>
using namespace std;
unordered_map<std::string, int> memoria;
///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AssignStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int PrintStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////

int GenCodeVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << "pushq %rax" << endl;
    exp->right->accept(this);
    cout << "movq %rax, %rcx" << endl;
    cout << "popq %rax" << endl;
    switch(exp->op) {
        case PLUS_OP:{
            cout << "addq %rcx, %rax" << endl;
            break;
        }
        default:
            cout << "Operador desconocido" << endl;
    }
    return 0;
}

int GenCodeVisitor::visit(NumberExp* exp) {
    cout << "movq $" << exp->value << ", %rax" << endl;
    return 0;
}

int GenCodeVisitor::visit(IdExp* exp) {
    return 0;
}

void GenCodeVisitor::visit(AssignStm* stm) {
}

void GenCodeVisitor::visit(PrintStm* stm) {
    stm->e->accept(this);
    cout << "movq %rax, %rsi" << endl;
    cout << "leaq print_fmt(%rip), %rdi" << endl;
    cout << "call printf@PLT" << endl;
}

void GenCodeVisitor::codigo(Program* program){
    // PROLOGUE
    cout << ".data" << endl;
    cout << "print_fmt: .string \"%ld\\n\" " << endl;
    cout << ".text" << endl;
    cout << ".globl main" << endl;
    cout << "main:" << endl;
    cout << "pushq %rbp" << endl;
    cout << "movq %rsp, %rbp" << endl;

    for (auto i : program->slist){
        i->accept(this);
    }
    
    // EPILOGUE
    cout << "movq $0, %rax" << endl;
    cout << "leave" << endl;
    cout << "ret" << endl;
    cout << ".section .note.GNU-stack,\"\",@progbits  " << endl;
};

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

int PrintVisitor::visit(IdExp* exp) {
    cout << exp->value;
    return 0;
}

void PrintVisitor::visit(AssignStm* stm) {
    cout << stm->id << " = ";
    stm->e->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStm* stm) {
    cout << "print(";
    stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::imprimir(Program* program){
    for (Stm* s : program->slist) {
        s->accept(this);
        cout << endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////
int EVALVisitor::visit(BinaryExp* exp) {
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    switch(exp->op) {
        case PLUS_OP: result = v1 + v2; break;
        case MINUS_OP: result = v1 - v2; break;
        case MUL_OP: result = v1 * v2; break;
        case DIV_OP:
            if(v2 != 0) result = v1 / v2;
            else {
                cout << "Error: división por cero" << endl;
                result = 0;
            }
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

int EVALVisitor::visit(IdExp* exp) {
    return memoria[exp->value];
}

void EVALVisitor::visit(AssignStm* stm) {
    memoria[stm->id] = stm->e->accept(this);
}

void EVALVisitor::visit(PrintStm* stm) {
    cout << stm->e->accept(this);
}
void EVALVisitor::interprete(Program* program){
    for (Stm* s : program->slist) {
        s->accept(this);
    }
};