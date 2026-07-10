#include "token.h"

Token::Token(Type type)
    : type(type), text("") {}

Token::Token(Type type, char c)
    : type(type), text(std::string(1, c)) {}

Token::Token(Type type, const std::string& source, int first, int last)
    : type(type), text(source.substr(first, last)) {}

std::string Token::typeName(Type t) {
    switch (t) {
        // Arithmetic Op
        case PLUS:        return "'+'";
        case MINUS:       return "'-'";
        case MUL:         return "'*'";
        case DIV:         return "'/'";
        case MOD:         return "'%'";
        // Delimiters
        case LPAREN:      return "'('";
        case RPAREN:      return "')'";
        case LBRACE:      return "'{'";
        case RBRACE:      return "'}'";
        case LBRACKET:    return "'['";
        case RBRACKET:    return "']'";
        case SEMICOL:     return "';'";
        case COMA:        return "','";
        case DOT:         return "'.'";
        case ARROW:       return "'->'";
        // Relational / Equality Op
        case LT:          return "'<'";
        case LE:          return "'<='";
        case GT:          return "'>'";
        case GE:          return "'>='";
        case EQ:          return "'=='";
        case NEQ:         return "'!='";
        // Logical Op
        case AND:         return "'&&'";
        case OR:          return "'||'";
        case NOT:         return "'!'";
        // Assign Op
        case ASSIGN:      return "'='";
        case PLUSASSIGN:  return "'+='";
        case MINUSASSIGN: return "'-='";
        case MULASSIGN:   return "'*='";
        case DIVASSIGN:   return "'/='";
        case INC:         return "'++'";
        case DEC:         return "'--'";
        // Pointers / referencias
        case AMP:         return "'&'";
        // Literals
        case NUMLIT:      return "número";
        case CHARLIT:     return "carácter";
        case STRINGLIT:   return "cadena";
        case TRUE:        return "'true'";
        case FALSE:       return "'false'";
        case NULLPTR:     return "'nullptr'";
        // Type keywords
        case INT:         return "'int'";
        case FLOAT:       return "'float'";
        case DOUBLE:      return "'double'";
        case CHAR:        return "'char'";
        case BOOL:        return "'bool'";
        case VOID:        return "'void'";
        case STRING:      return "'string'";
        case AUTO:        return "'auto'";
        // Struct / Templates
        case STRUCT:      return "'struct'";
        case TEMPLATE:    return "'template'";
        case TYPENAME:    return "'typename'";
        // Memoria dinámica
        case NEW:         return "'new'";
        case DELETE:      return "'delete'";
        // Id's - Reserved words
        case ID:          return "identificador";
        case PRINT:       return "'print'";
        case RETURN:      return "'return'";
        // Flow Control
        case IF:          return "'if'";
        case ELSE:        return "'else'";
        case WHILE:       return "'while'";
        case DO:          return "'do'";
        case FOR:         return "'for'";
        case BREAK:       return "'break'";
        case CONTINUE:    return "'continue'";
        case ERR:         return "<error léxico>";
        case END:         return "fin de entrada";
        default:          return "<desconocido>";
    }
}

std::ostream& operator<<(std::ostream& outs, const Token& tok) {
    outs << "TOKEN(" << Token::typeName(tok.type);
    if (tok.type != Token::END) {
        outs << ", \"" << tok.text << "\"";
    }
    outs << ")";
    return outs;
}

std::ostream& operator<<(std::ostream& outs, const Token* tok) {
    if (!tok) return outs << "TOKEN(NULL)";
    return outs << *tok;
}