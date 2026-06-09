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

int IfStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int WhileStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int DoWhileStm::accept(Visitor* visitor) {
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
        case MINUS_OP:{
            cout << "subq %rcx, %rax" << endl;
            break;
        }
    }
    return 0;
}

int GenCodeVisitor::visit(NumberExp* exp) {
    cout << "movq $" << exp->value << ", %rax" << endl;
    return 0;
}

int GenCodeVisitor::visit(IdExp* exp) {
    cout << "movq " << position[exp->value]*-8 << "(%rbp)" << ", %rax" << endl;
    return 0;
}

void GenCodeVisitor::visit(AssignStm* stm) {
    if (position.find(stm->id)==position.end()){
        position[stm->id] = counter;
        counter++;
    }
    stm->e->accept(this);
    cout << "movq %rax, -" << position[stm->id]*8 << "(%rbp)" << endl;
}

void GenCodeVisitor::visit(IfStm* stm) {
    int id = labelCounter++;
    stm->cond->accept(this);
    cout << "cmpq $0, %rax" << endl;
    cout << "je else" << id << endl;
    for(auto i: stm->bodyIf->slist)
        i->accept(this);    
    cout << "jmp endif" << id << endl;

    cout << "else" << id << ":" << endl;
    for(auto i: stm->bodyElse->slist)
        i->accept(this);
    cout << "endif" << id << ":" << endl;
}

void GenCodeVisitor::visit(WhileStm* stm) {
    int id = labelCounter++;
    cout << "while" << id << ":" << endl;
    stm->cond->accept(this);
    cout << "cmpq $0, %rax" << endl;
    cout << "je endwhile" << id << endl;
    for (auto i : stm->body->slist)
        i->accept(this);
    cout << "jmp while" << id << endl;
    cout << "endwhile" << id << ":" << endl;
}

void GenCodeVisitor::visit(DoWhileStm* stm) {
    int id = labelCounter++;
    cout << "do" << id << ":" << endl;
    for (auto i : stm->body->slist)
        i->accept(this);
    stm->cond->accept(this);
    cout << "cmpq $0, %rax" << endl;
    cout << "jne do" << id << endl;
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
    cout << "subq $16, %rsp" << endl; 
    for (auto i : program->b->slist){
        i->accept(this);
    }
    
    // EPILOGUE
    cout << "movq $0, %rax" << endl;
    cout << "leave" << endl;
    cout << "ret" << endl;
    cout << ".section .note.GNU-stack,\"\",@progbits" << endl;
};