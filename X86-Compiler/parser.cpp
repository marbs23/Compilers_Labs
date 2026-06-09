#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "ast.h"
#include "parser.h"

using namespace std;

// =============================
// Métodos de la clase Parser
// =============================

Parser::Parser(Scanner* sc) : scanner(sc) {
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        throw runtime_error("Error léxico");
    }
}

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;

        if (check(Token::ERR)) {
            throw runtime_error("Error lexico");
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}


// =============================
// Reglas gramaticales
// =============================

Program* Parser::parseProgram() {
    Program* p = new Program();
    p->b = parseBody();
    if (!isAtEnd()) {
        throw runtime_error("Error sintáctico");
    }
    
    cout << "Parseo exitoso" << endl;
    return p;
}

Body* Parser::parseBody() {
    Body* b = new Body();
    b->add(parseStm());
    while(match(Token::SEMICOL)){
        b->add(parseStm());
    }
    return b;
}

Stm* Parser::parseStm() {
    Stm* a;
    Exp* e;
    string variable;
    if(match(Token::ID)) {
        variable = previous->text;
        match(Token::ASSIGN);
        e = parseOR();
        return new AssignStm(variable,e);
    }
    else if(match(Token::PRINT)) {
        match(Token::LPAREN);
        e = parseOR();
        match(Token::RPAREN);
        return new PrintStm(e);
    } 
    else if (match(Token::IF)) {
        IfStm* ifstm = new IfStm();
        ifstm->cond = parseOR();
        match(Token::THEN);
        ifstm->bodyIf = parseBody();
        if (match(Token::ELSE))
            ifstm->bodyElse = parseBody();
        else
            ifstm->bodyElse = new Body();
        match(Token::ENDIF);
        return ifstm;
    }
    else if (match(Token::WHILE)) {
        WhileStm* whilestm = new WhileStm();
        whilestm->cond = parseOR();
        match(Token::DO);
        whilestm->body = parseBody();
        match(Token::ENDWHILE);
        return whilestm;
    }
    else if (match(Token::DO)) {
        DoWhileStm* dowhilestm = new DoWhileStm();
        dowhilestm->body = parseBody();
        match(Token::WHILE);
        dowhilestm->cond = parseOR();
        return dowhilestm;
    }    

    else{
        throw runtime_error("Error sintáctico");
    }
    return a;
}

Exp* Parser::parseOR() {
    Exp* l = parseAND();
    while (match(Token::OR)) {
        Exp* r = parseAND();
        l = new BinaryExp(l,r, OR_OP); 
    }
    return l;
}

Exp* Parser::parseAND() {
    Exp* l = parseCE();
    while (match(Token::AND)) {
        Exp* r = parseCE();
        l = new BinaryExp(l, r, AND_OP);
    }
    return l;
}

Exp* Parser::parseCE() {
    Exp* l = parseBE();
    if (match(Token::LT)) {
        Exp* r = parseBE();
        return new BinaryExp(l, r, LT_OP);
    } else if (match(Token::LE)) {
        Exp* r = parseBE();
        return new BinaryExp(l, r, LE_OP);
    } else if (match(Token::GT)) {
        Exp* r = parseBE();
        return new BinaryExp(l, r, GT_OP);
    } else if (match(Token::GE)) {
        Exp* r = parseBE();
        return new BinaryExp(l, r, GE_OP);
    } else if (match(Token::EQ)) {
        Exp* r = parseBE();
        return new BinaryExp(l, r, EQ_OP);
    } else if (match(Token::NE)) {
        Exp* r = parseBE();
        return new BinaryExp(l, r, NE_OP);
    }
    return l;
}

Exp* Parser::parseBE() {
    Exp* l = parseE();
    while (match(Token::PLUS) || match(Token::MINUS)) {
        BinaryOp op;
        if (previous->type == Token::PLUS){
            op = PLUS_OP;
        }
        else{
            op = MINUS_OP;
        }
        Exp* r = parseE();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseE() {
    Exp* l = parseT();
    while (match(Token::MUL) || match(Token::DIV)) {
        BinaryOp op;
        if (previous->type == Token::MUL){
            op = MUL_OP;
        }
        else{
            op = DIV_OP;
        }
        Exp* r = parseT();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseT() {
    Exp* l = parseF();
    if (match(Token::POW)) {
        BinaryOp op = POW_OP;
        Exp* r = parseF();
        l = new BinaryExp(l, r, op);
    }
    return l;
}

Exp* Parser::parseF() {
    Exp* e; 
    if (match(Token::NUM)) {
        return new NumberExp(stoi(previous->text));
    } 
    else if (match(Token::LPAREN))
    {
        e = parseCE();
        match(Token::RPAREN);
        return e;
    }

    else if (match(Token::ID))
    {   
        return new IdExp(previous->text);
    }
    else {
        throw runtime_error("Error sintáctico");
    }
}
