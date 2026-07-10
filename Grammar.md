# Gramática EBNF — Lenguaje "MiniCpp"

Diseñada para el Proyecto 3 (CS3402 - Compiladores): compilador completo x86 con
lexer, parser, análisis semántico, generación de código y optimización.

Notación (misma que usa la gramática de funciones del curso):
- `::=`  definición
- `|`    alternativa
- `[ ]`  opcional (0 o 1)
- `( )*` cero o más repeticiones
- `( )+` una o más repeticiones
- literales en `negrita`/código, no terminales en *Cursiva/Mayúscula*

---

## 1. Programa y declaraciones globales

```
Program        ::= (TopDecl)+

TopDecl        ::= StructDecl
                  | TemplateFunDecl
                  | FunDecl
                  | VarDecl

StructDecl     ::= struct id { (FieldDecl)+ } ;

FieldDecl      ::= Type VarInitList ;
```

## 2. Sistema de tipos

```
Type           ::= PrimType
                  | id                          (* tipo definido por el usuario / struct *)
                  | Type *                      (* puntero: T*, T**, ... *)
                  | Type [ [IntLiteral] ]        (* arreglo, posiblemente multidimensional
                                                     al encadenar esta regla: T[][3] *)
                  | id < TypeArgList >           (* instanciación de template: Stack<int> *)
                  | auto                          (* inferencia de tipos *)

PrimType       ::= int | float | double | char | bool | void | string

TypeArgList    ::= Type ( , Type )*
```

## 3. Declaraciones de variables

```
VarDecl        ::= Type VarInitList ;

VarInitList    ::= VarInit ( , VarInit )*

VarInit        ::= id [ ArraySuffix ] [ = Expr ]

ArraySuffix    ::= ( [ [IntLiteral] ] )+          (* soporta T v[5]; T m[3][4]; *)
```

## 4. Funciones (incluye plantillas / templates)

```
TemplateFunDecl ::= template < TemplateParamList > FunDecl

TemplateParamList ::= typename id ( , typename id )*

FunDecl        ::= Type id ( [ParamDecList] ) Block

ParamDecList   ::= ParamDec ( , ParamDec )*

ParamDec       ::= Type id [ ArraySuffix ]
```

## 5. Bloques y sentencias

```
Block          ::= { (Stmt)* }

Stmt           ::= VarDecl
                  | ExprStmt
                  | IfStmt
                  | WhileStmt
                  | DoWhileStmt
                  | ForStmt
                  | ReturnStmt
                  | BreakStmt ;
                  | ContinueStmt ;
                  | DeleteStmt
                  | Block

ExprStmt       ::= Expr ;

IfStmt         ::= if ( Expr ) Block [ else (IfStmt | Block) ]

WhileStmt      ::= while ( Expr ) Block

DoWhileStmt    ::= do Block while ( Expr ) ;

ForStmt        ::= for ( [ForInit] ; [Expr] ; [Expr] ) Block

ForInit        ::= VarDecl | Expr

ReturnStmt     ::= return [Expr] ;

DeleteStmt     ::= delete [ [ ] ] Expr ;      (* delete p;  |  delete[] arr; *)
```

## 6. Expresiones (de menor a mayor precedencia)

```
Expr           ::= Assignment

Assignment     ::= LogicalOr [ (= | += | -= | *= | /=) Assignment ]

LogicalOr      ::= LogicalAnd ( || LogicalAnd )*

LogicalAnd     ::= Equality ( && Equality )*

Equality       ::= Relational ( (== | !=) Relational )*

Relational     ::= Additive ( (< | <= | > | >=) Additive )*

Additive       ::= Term ( (+ | -) Term )*

Term           ::= Unary ( (* | / | %) Unary )*

Unary          ::= (! | - | * | & | ++ | --) Unary
                  | Postfix

Postfix        ::= Primary ( PostfixOp )*

PostfixOp      ::= . id                        (* acceso a miembro:      p.x        *)
                  | -> id                       (* acceso vía puntero:    p->x       *)
                  | [ Expr ]                    (* indexación (multidim encadenada):
                                                    m[i][j] *)
                  | ( [ArgList] )               (* llamada a función *)
                  | ++ | --                     (* post incremento/decremento *)

Primary        ::= id
                  | IntLiteral
                  | FloatLiteral
                  | CharLiteral
                  | StringLiteral
                  | true | false
                  | nullptr
                  | ( Expr )
                  | ( Type ) Expr               (* cast explícito de tipo: (int) x *)
                  | new Type [ [ Expr ] ]        (* new T;   |   new T[n];         *)
                  | Lambda

ArgList        ::= Expr ( , Expr )*
```

## 7. Funciones lambda

```
Lambda         ::= [ CaptureList ] ( [ParamDecList] ) [ -> Type ] Block

CaptureList    ::= = | &
                  | CaptureItem ( , CaptureItem )*

CaptureItem    ::= [&] id
```

---

## Notas de diseño (para tu análisis semántico / type checker)

- **Inferencia de tipos (`auto`)**: al declarar `auto x = expr;`, el *type checker*
  debe resolver el tipo de `expr` y propagarlo a la entrada de la tabla de símbolos
  antes de continuar el chequeo del bloque.
- **Conversión/promoción automática**: define una tabla de compatibilidad, p. ej.
  `int → float → double` es promoción implícita permitida; `bool ↔ numérico`
  requiere conversión explícita (cast) — igual que en las reglas de tu profesor
  para el lenguaje simple (`No se permite asignar valores booleanos a variables
  numéricas, ni viceversa`), pero aquí la relajas solo para tipos numéricos.
- **Punteros y memoria**: `Type*` se resuelve recursivamente (un puntero a puntero
  es válido). `new`/`delete` deben verificar que el operando de `delete` sea de
  tipo puntero.
- **Templates**: al instanciar `id<TypeArgList>`, sustituye los parámetros de tipo
  en la declaración genérica y vuelve a tipar el cuerpo (monomorphization simple),
  o mantenlo genérico si prefieres chequeo estructural — decide esto explícitamente
  en tu reporte técnico, es un punto de diseño que te van a preguntar en la
  exposición.
- **Arreglos multidimensionales**: representarlos como tipos anidados
  (`Type [] []`) hace que la regla de `ArraySuffix`/`Type` sea uniforme tanto en
  declaración (`int m[3][4]`) como en indexación (`m[i][j]`), sin reglas
  especiales extra.
- **Lambdas**: trátalas como azúcar sintáctico que genera un struct anónimo con
  operator() en tu AST, así reutilizas toda la infraestructura de `FunDecl` para
  chequeo de tipos y generación de código.

## Siguiente paso sugerido

Con esta gramática ya puedes:
1. Definir tokens del lexer (palabras clave, operadores, literales).
2. Construir el AST (una clase/struct por cada no-terminal con hijos).
3. Escribir el parser (recursivo descendente funciona bien para esta gramática,
   ya que es LL(1) salvo el caso `Postfix`/`new`, que se resuelve con lookahead
   simple).

Si quieres, en el siguiente paso te ayudo a definir las clases del AST en C++
(o el lenguaje que uses para implementar el compilador) a partir de esta
gramática.