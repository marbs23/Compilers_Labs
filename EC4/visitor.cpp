#include <iostream>
#include <fstream>
#include <cmath>
#include "ast.h"
#include "visitor.h"


using namespace std;

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

int SqrtExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void PrintStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void AsignStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void WhileStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void DoWhileStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void IfStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

void Vardec::accept(Visitor* visitor) {
    visitor->visit(this);
}

void Body::accept(Visitor* visitor) {
    visitor->visit(this);
}

void BreakStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int FcallExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void IncrementalStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void ReturnStm::accept(Visitor* visitor) {
    return visitor->visit(this);
}

void Fundec::accept(Visitor* visitor) {
    return visitor->visit(this);
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
        case LET_OP:
            result = v1 < v2;
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
        case EQUIV_OP:
            result = (v1 == v2);
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


void EVALVisitor::interprete(Programa* programa){
    if (programa)
    {
        cout << "Interprete:" << endl; 
        programa->accept(this);
        cout <<endl;
    }
    return;
}




void EVALVisitor::visit(PrintStmt *stm) {
    cout << stm->exp->accept(this);
    cout << endl;
}




void PrintVisitor::visit(AsignStmt *stm) {
    cout << stm->variable << " = ";
    stm->exp->accept(this);
    cout << endl;
}
void PrintVisitor::visit(PrintStmt *stm) {
    cout << "print (";
    stm->exp->accept(this);
    cout << ")"<< endl;
}

void PrintVisitor::visit(IncrementalStmt *stm) {
    cout << stm->name;
    cout << "+=";
    stm->e->accept(this);
    cout << endl;
}



int PrintVisitor::visit(IdExp *e) {
    cout << e->value;
    return 0;
}

void PrintVisitor::visit(IfStmt *stm) {
    cout << "if ";
    stm->condicion->accept(this);
    cout << " then" << endl;
    stm->cuerpo_if->accept(this);
    if(stm->hayelse){
        cout << "else" << endl;
        stm->cuerpo_else->accept(this);
    }
    cout << "endif" << endl;
}

void EVALVisitor::visit(IfStmt *stm) {
    if(stm->condicion->accept(this) != 0){
        stm->cuerpo_if->accept(this);
    }
    else if (stm->hayelse){
        stm->cuerpo_else->accept(this);
    }

}

void PrintVisitor::visit(WhileStmt *stm) {
    cout << "while ";
    stm->condicion->accept(this);
    cout << " do" << endl;
    stm->cuerpo->accept(this);
    cout << "endwhile" << endl;
}

void PrintVisitor::visit(DoWhileStmt *stm) {
    cout << "do" << endl;
    stm->cuerpo->accept(this);
    cout << " while" << endl;
    stm->condicion->accept(this);
    cout << "endwhile" << endl;
}
    


void PrintVisitor::visit(Vardec *vd) {
    cout << "var " << vd->tipo << " ";
    for(auto i:vd->variables){
        cout << i << ",";
    }
    cout << endl;
}

void EVALVisitor::visit(Vardec *vd) {
    for(auto& i:vd->variables){
        memoria.add_var(i);
    }
}

int EVALVisitor::visit(IdExp *e) {
    return memoria.lookup(e->value);
}

void EVALVisitor::visit(AsignStmt *stm) {
    memoria.update(stm->variable,stm->exp->accept(this));
}


void EVALVisitor::visit(Body * cuerpo) {
    memoria.add_level();
    for (auto i:cuerpo->vdlist) {
        i->accept(this);
    }
    for (auto i:cuerpo->slist) {
        if(!haybreak){i->accept(this);}
    }
    memoria.remove_level();
}
void PrintVisitor::visit(Body * cuerpo) {
    for (auto i:cuerpo->vdlist) {
        i->accept(this);
    }
    for (auto i:cuerpo->slist) {
        i->accept(this);
    }
}

void PrintVisitor::visit(Programa * p) {
   for(auto i:p->vdlist){
    i->accept(this);
   }
   for(auto i:p->fdlist){
    i->accept(this);
   }
}





void PrintVisitor::visit(ReturnStm* stm) {
    cout << "return " ;
    stm->exp->accept(this);
    cout << endl;
}


void PrintVisitor::visit(Fundec* fd) {
    cout << "def "<< fd->tipo << " " << fd->nombre << "(";
    for(auto i:fd->id_parametros){
        cout << i << "," ;
    }
    cout << "):" << endl;
    fd->cuerpo->accept(this);
    cout << "endfun"<< endl; 




}

int PrintVisitor::visit(FcallExp* exp) {
    cout << exp->nombre << "(" ;
    for (auto i:exp->argumentos){
        i->accept(this);
        cout << ",";
    }
    cout << ")";
    return 0;
}

void EVALVisitor::visit(Programa *p) {
    memoria.clear();
    memoria.add_level();
    for(auto i:p->vdlist){
        i->accept(this);
    }
    for(auto i:p->fdlist){
        fmemoria[i->nombre] = i;
    }
    fmemoria["main"]->accept(this);
}

void EVALVisitor::visit(Fundec* fd) {
    fd->cuerpo->accept(this);
}

int EVALVisitor::visit(FcallExp* exp) {
    hayretorno = false;
    Fundec* fd = fmemoria[exp->nombre];
    memoria.add_level();
    for (int i=0; i<fd->id_parametros.size();i++ ){
        memoria.add_var(fd->id_parametros[i],exp->argumentos[i]->accept(this));
    }
    fd->cuerpo->accept(this);
    memoria.remove_level();
    return retorno;
    }

void EVALVisitor::visit(ReturnStm* stm) {
    if(hayretorno==false){
        hayretorno =true;
        retorno = stm->exp->accept(this);
    }
}

void EVALVisitor::visit(BreakStmt* stm){
    haybreak = true;
}

void EVALVisitor::visit(IncrementalStmt* stm){
    memoria.update(stm->name, memoria.lookup(stm->name) + stm->e->accept(this));
}

void EVALVisitor::visit(WhileStmt *stm) {
    while( (stm->condicion->accept(this)!=0) and (haybreak ==false)  ){
        stm->cuerpo->accept(this);
    }
}

void EVALVisitor::visit(DoWhileStmt *stm) {
    stm->cuerpo->accept(this);
    while( (stm->condicion->accept(this)!=0) and (haybreak ==false)  ){
        stm->cuerpo->accept(this);
    }
}


void PrintVisitor::visit(BreakStmt* stm){
    cout << "break" << endl;
}