%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern Node *g_root; // A way of getting the AST out
  extern FILE *yyin;

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  Node *node;
  double number;
  std::string *string;
}
%define parse.error verbose

%token T_ADD_ASSIGN T_SUB_ASSIGN T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_RSHIFT_ASSIGN T_LSHIFT_ASSIGN T_AND_ASSIGN T_INOR_ASSIGN T_EXOR_ASSIGN
%token T_LBRACKET T_RBRACKET 
%token T_TIMES T_DIVIDE T_MOD
%token T_INV T_NOT
%token T_PLUS T_MINUS 
%token T_LSHIFT T_RSHIFT
%token T_GREATEREQ T_LESSEREQ T_GREATER T_LESSER
%token T_EQUAL T_NOTEQUAL
%token T_BAND
%token T_BXOR
%token T_BOR
%token T_AND 
%token T_OR 
%token T_QUESTION T_COLON T_DOT
%token T_ASSIGN
%token T_INCREMENT T_DECREMENT
%token T_RCBRACKET T_LCBRACKET T_SEMICOLON T_COMMA T_LSBRACKET T_RSBRACKET T_FLOAT
%token SIZEOF WHILE IF ELSE INT VOID RETURN BREAK CONTINUE CASE DEFAULT SWITCH FOR ENUM UNSIGNED FLOAT STRUCT
%token T_NUMBER T_STRING T_LITERAL
%token CHAR T_CHAR

%type <node> STRUCT_INDEX STRUCT_DEC STRUCT_DEF STRING_LITERAL POINTER_ASSIGN POINTER_ASSIGNMENT  ADDRESS DEREFERENCE EMPTY_SCOPE ENUM_LIST ENUM_DECLARE EXTERNAL IF_ONLY FOR_LOOP SWITCH_STAT CASE_SEQ CASE_STAT FUNC_CALL ARGS ARRAY_DEC ARRAY_ASSIGN ARRAY_INDEX PARAMS BREAK_STAT CONTINUE_STAT RETURN_STAT NAME WHILE_LOOP IF_ELSE FUNC BLOCK_SEQ BLOCK SEQ LINE_SEQ LINE DECLARATION  VAR_TYPE ASSIGNMENT MUX OR AND BOR BXOR BAND EQUALITY RELATIONAL SHIFT ADDITIVE MULTIPLICATIVE UNARY FACTOR
%type <number> T_NUMBER T_FLOAT
%type <string> T_LITERAL T_STRING INT VOID RETURN BREAK CONTINUE UNSIGNED FLOAT T_CHAR CHAR

%start ROOT

%%

ROOT :  BLOCK_SEQ { g_root = $1 ;};

/* FUNC_SEQ : FUNC {$$ = $1;}
         | FUNC_SEQ FUNC {$$ = $2;}
         ; */

BLOCK_SEQ : BLOCK {$$ = new BlockSeq($1, NULL);}
          | BLOCK_SEQ BLOCK {$$ = new BlockSeq($1, $2);}
          ;

BLOCK : FUNC {$$ = new Block($1);}
      | EXTERNAL {$$ = new Block($1);}
      | ENUM_DECLARE {$$ = new Block($1);}
      | STRUCT_DEF {$$ = new Block($1);}
      ; 

EXTERNAL : VAR_TYPE NAME T_LBRACKET T_RBRACKET T_SEMICOLON {$$ = new External($1, $2);}
          | VAR_TYPE NAME T_LBRACKET DECLARATION T_RBRACKET T_SEMICOLON {$$ = new External($1, $2, new Params($4));}
          | VAR_TYPE NAME T_LBRACKET PARAMS T_RBRACKET T_SEMICOLON {$$ = new External($1, $2, $4);}
          | VAR_TYPE T_TIMES NAME T_LBRACKET T_RBRACKET T_SEMICOLON {$$ = new External($1, $3);}
          | VAR_TYPE T_TIMES NAME T_LBRACKET DECLARATION T_RBRACKET T_SEMICOLON {$$ = new External($1, $3, new Params($5));}
          | VAR_TYPE T_TIMES NAME T_LBRACKET PARAMS T_RBRACKET T_SEMICOLON {$$ = new External($1, $3, $5);}
          | VAR_TYPE NAME T_SEMICOLON {$$ = new Declaration($1, $2);}
          | VAR_TYPE NAME T_ASSIGN ASSIGNMENT T_SEMICOLON {$$ = new DeclareAssign($1, $2, $4); }
          | VAR_TYPE NAME T_LSBRACKET ASSIGNMENT T_RSBRACKET T_SEMICOLON{$$ = new ArrayDeclare($1, $2, $4);}
          | VAR_TYPE NAME T_LSBRACKET T_RSBRACKET T_ASSIGN T_LCBRACKET ASSIGNMENT T_RCBRACKET T_SEMICOLON{$$ = new ArrayDeclareAssign($1, $2, new Arguments($7));} 
          | VAR_TYPE NAME T_LSBRACKET T_RSBRACKET T_ASSIGN T_LCBRACKET ARGS T_RCBRACKET T_SEMICOLON {$$ = new ArrayDeclareAssign($1, $2, $7);}
          ;
STRUCT_DEF : STRUCT NAME T_LCBRACKET LINE_SEQ T_RCBRACKET T_SEMICOLON {$$ = new StructDefinition($2, $4);}
           | STRUCT NAME T_LCBRACKET T_RCBRACKET T_SEMICOLON {$$ = new StructDefinition($2, NULL);}
           ;

FUNC : VAR_TYPE NAME T_LBRACKET T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new FunctionDeclaration($1, $2, $6) ;}
     | VAR_TYPE NAME T_LBRACKET DECLARATION T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new FunctionDeclaration($1, $2, $7, new Params($4));}
     | VAR_TYPE NAME T_LBRACKET PARAMS T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new FunctionDeclaration($1, $2, $7, $4);}
     | VAR_TYPE T_TIMES NAME T_LBRACKET T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new FunctionDeclaration($1, $3, $7) ;}
     | VAR_TYPE T_TIMES NAME T_LBRACKET DECLARATION T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new FunctionDeclaration($1, $3, $8, new Params($5));}
     | VAR_TYPE T_TIMES NAME T_LBRACKET PARAMS T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new FunctionDeclaration($1, $3, $8, $5);}
     ;

ENUM_DECLARE: ENUM NAME T_LCBRACKET ARGS T_RCBRACKET T_SEMICOLON {$$ = new EnumDeclare($2, $4);}
            | ENUM NAME T_LCBRACKET NAME T_RCBRACKET T_SEMICOLON {$$ = new EnumDeclare($2, new Arguments($4));}
            | ENUM NAME T_LCBRACKET ASSIGNMENT T_RCBRACKET T_SEMICOLON {$$ = new EnumDeclare($2, new Arguments($4));}
            ;


PARAMS : DECLARATION T_COMMA DECLARATION{$$ = new Params($1, $3); }
       | PARAMS T_COMMA DECLARATION {$$ = new Params($1, $3); }
       ;


      
FOR_LOOP  : FOR T_LBRACKET DECLARATION T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new ForLoop($3, $5, $7, $10);}
          | FOR T_LBRACKET DECLARATION T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET LINE {$$ = new ForLoop($3, $5, $7, $9);}
          | FOR T_LBRACKET DECLARATION T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET T_SEMICOLON {$$ = new ForLoop($3, $5, $7);}
          | FOR T_LBRACKET DECLARATION T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET T_LCBRACKET T_RCBRACKET {$$ = new ForLoop($3, $5, $7);}
          | FOR T_LBRACKET ASSIGNMENT T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new ForLoop($3, $5, $7, $10);}
          | FOR T_LBRACKET ASSIGNMENT T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET LINE {$$ = new ForLoop($3, $5, $7, $9);}
          | FOR T_LBRACKET ASSIGNMENT T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET T_SEMICOLON {$$ = new ForLoop($3, $5, $7);}
          | FOR T_LBRACKET ASSIGNMENT T_SEMICOLON ASSIGNMENT T_SEMICOLON ASSIGNMENT T_RBRACKET T_LCBRACKET T_RCBRACKET {$$ = new ForLoop($3, $5, $7);}
          ;
WHILE_LOOP : WHILE T_LBRACKET ASSIGNMENT T_RBRACKET LINE {$$ = new WhileLoop($3, $5);}
           | WHILE T_LBRACKET ASSIGNMENT T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new WhileLoop($3, $6);}
           | WHILE T_LBRACKET ASSIGNMENT T_RBRACKET T_SEMICOLON {$$ = new WhileLoop($3, NULL);}
           | WHILE T_LBRACKET ASSIGNMENT T_RBRACKET T_LCBRACKET T_RCBRACKET {$$ = new WhileLoop($3, NULL);}
           ;
           
IF_ONLY : IF T_LBRACKET ASSIGNMENT T_RBRACKET T_SEMICOLON {$$ = new IfStatment($3, NULL);}
          |IF T_LBRACKET ASSIGNMENT T_RBRACKET LINE {$$ = new IfStatment($3, $5);}
          |IF T_LBRACKET ASSIGNMENT T_RBRACKET T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new IfStatment($3, $6);}
          |IF T_LBRACKET ASSIGNMENT T_RBRACKET T_LCBRACKET T_RCBRACKET {$$ = new IfStatment($3, NULL);}
          ;

IF_ELSE : IF_ONLY ELSE LINE  {$$ = new IfElse($1, $3);}
        | IF_ONLY ELSE T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new IfElse($1, $4);}
        | IF_ONLY ELSE T_LCBRACKET T_RCBRACKET {$$ = new IfElse($1, NULL);}
        | IF_ONLY {$$ = new IfElse($1);}
        ;
        
ARRAY_DEC : VAR_TYPE NAME T_LSBRACKET ASSIGNMENT T_RSBRACKET {$$ = new ArrayDeclare($1, $2, $4);}
          | VAR_TYPE NAME T_LSBRACKET T_RSBRACKET T_ASSIGN T_LCBRACKET ASSIGNMENT T_RCBRACKET{$$ = new ArrayDeclareAssign($1, $2, new Arguments($7));} 
          | VAR_TYPE NAME T_LSBRACKET T_RSBRACKET T_ASSIGN T_LCBRACKET ARGS T_RCBRACKET{$$ = new ArrayDeclareAssign($1, $2, $7);}
          | VAR_TYPE NAME T_LSBRACKET T_RSBRACKET T_ASSIGN  STRING_LITERAL {$$ = new ArrayDeclareAssign($1, $2, $6);} 
          ;
ARRAY_ASSIGN : NAME T_LSBRACKET ASSIGNMENT T_RSBRACKET T_ASSIGN ASSIGNMENT {$$ = new ArrayAssign($1, $3, $6);}
             ;

ARRAY_INDEX : NAME T_LSBRACKET ASSIGNMENT T_RSBRACKET {$$ = new ArrayCall($1, $3);}
            ;
CASE_SEQ  : CASE_STAT {$$ = new CaseSeq($1); }
          | CASE_SEQ CASE_STAT {$$ = new CaseSeq($1, $2); }
          | CASE_SEQ DEFAULT T_COLON  LINE_SEQ  {$$ = new CaseSeq($1, new Case(NULL, $4) );}
          | CASE_SEQ DEFAULT T_COLON T_SEMICOLON {$$ = $1;}
          ;
SWITCH_STAT : SWITCH T_LBRACKET ASSIGNMENT T_RBRACKET T_LCBRACKET CASE_SEQ T_RCBRACKET {$$ = new Switch($3, $6);}
            | SWITCH T_LBRACKET ASSIGNMENT T_RBRACKET T_SEMICOLON {$$ = new Switch($3, NULL);}
            | SWITCH T_LBRACKET ASSIGNMENT T_RBRACKET T_LCBRACKET T_RCBRACKET {$$ = new Switch($3, NULL);}
            ;

CASE_STAT : CASE MUX T_COLON  LINE_SEQ  {$$ = new Case($2, $4);}
          | CASE MUX T_COLON T_SEMICOLON {$$ = new Case($2, NULL);}
          ;
LINE_SEQ : LINE {$$ = new LineSeq($1); }
         | EMPTY_SCOPE {$$ = new LineSeq($1); }
         | LINE_SEQ LINE {$$ = new LineSeq($1, $2);}
         | LINE_SEQ EMPTY_SCOPE {$$ = new LineSeq($1, $2); }
         ;
EMPTY_SCOPE : T_LCBRACKET LINE_SEQ T_RCBRACKET {$$ = new EmptyScope($2);}
            ;
LINE : DECLARATION T_SEMICOLON {$$ = new Line($1); }
     | ASSIGNMENT T_SEMICOLON {$$ = new Line($1); }
     | RETURN_STAT T_SEMICOLON {$$ = new Line($1); }
     | BREAK_STAT T_SEMICOLON {$$ = new Line($1);}
     | CONTINUE_STAT T_SEMICOLON {$$ = new Line($1); }
     | ARRAY_ASSIGN T_SEMICOLON {$$ = new Line($1); }
     | ARRAY_DEC T_SEMICOLON {$$ = new Line($1); }
     | IF_ELSE {$$ = new Line($1);}
     | WHILE_LOOP {$$ = new Line($1);}
     | SWITCH_STAT {$$ = new Line($1);}
     | FOR_LOOP {$$ = new Line($1);}
     | POINTER_ASSIGN T_SEMICOLON {$$ = new Line($1);}
     | STRUCT_DEC {$$ = new Line($1);}
     ;

FUNC_CALL : NAME T_LBRACKET T_RBRACKET {$$ = new FunctionCall($1); }
          | NAME T_LBRACKET ASSIGNMENT T_RBRACKET {$$ = new FunctionCall($1, new Arguments($3));}
          | NAME T_LBRACKET ARGS T_RBRACKET {$$ = new FunctionCall($1, $3);}
          ;



ARGS : ASSIGNMENT T_COMMA ASSIGNMENT {$$ = new Arguments($1, $3); }
     | ARGS T_COMMA ASSIGNMENT {$$ = new Arguments($1, $3); }
     ;


DECLARATION : VAR_TYPE NAME {$$ = new Declaration($1, $2); }
            | VAR_TYPE NAME T_ASSIGN ASSIGNMENT {$$ = new DeclareAssign($1, $2, $4);} // $1 as well?
            | VAR_TYPE T_TIMES NAME {$$ = new PointerDeclare($1, $3);}
            | VAR_TYPE T_TIMES NAME T_ASSIGN POINTER_ASSIGNMENT {$$ = new PointerDeclareAssign($1, $3, $5);}
            ;
STRUCT_DEC : STRUCT NAME NAME T_SEMICOLON {$$ = new StructDeclare($2, $3);};
STRUCT_INDEX : NAME T_DOT NAME {$$ = new StructIndex($1, $3);};

POINTER_ASSIGN : NAME T_EQUAL POINTER_ASSIGNMENT {$$ = new PointerAssign($1, $3);};

POINTER_ASSIGNMENT :  ADDRESS {$$ = $1;}
                    | POINTER_ASSIGNMENT T_PLUS MUX {$$ = new PointerAdd($1, $3);}
                    | MUX T_PLUS POINTER_ASSIGNMENT  {$$ = new PointerAdd($3, $1);}
                    | POINTER_ASSIGNMENT T_MINUS MUX  {$$ = new PointerSub($1, $3);}
                    ;

DEREFERENCE : T_TIMES NAME {$$ = new Dereference($2);};

ADDRESS : T_BAND NAME {$$ = new Address($2);};


ASSIGNMENT : MUX {$$ = $1;}
           | VAR_TYPE T_TIMES NAME T_ASSIGN STRING_LITERAL {$$ = new CharArrey($3, $5);}
           | NAME T_ASSIGN ASSIGNMENT{$$ = new Assign($1, $3);} //Will have to deal with this the same way we T_STRING in T_FACTOR cause assignment returns the variable
           | T_INCREMENT NAME {$$ = new PreIncrement($2);}
           | NAME T_INCREMENT {$$ = new PostIncrement($1);}
           | STRUCT_INDEX T_ASSIGN ASSIGNMENT {$$ = new StructAssign($1, $3);}
           | T_DECREMENT NAME {$$ = new PreDecrement($2);}
           | NAME T_DECREMENT {$$ = new PostDecrement($1);}
           | NAME T_ADD_ASSIGN ASSIGNMENT {$$ = new Assign($1, new AddOperator($1, $3));}
           | NAME T_SUB_ASSIGN ASSIGNMENT {$$ = new Assign($1, new SubOperator($1, $3));}
           | NAME T_MUL_ASSIGN ASSIGNMENT {$$ = new Assign($1, new MulOperator($1, $3));}
           | NAME T_DIV_ASSIGN ASSIGNMENT {$$ = new Assign($1, new DivOperator($1, $3));}
           | NAME T_MOD_ASSIGN ASSIGNMENT {$$ = new Assign($1, new ModOperator($1, $3));}
           | NAME T_LSHIFT_ASSIGN ASSIGNMENT {$$ = new Assign($1, new LShiftOperator($1, $3));}
           | NAME T_RSHIFT_ASSIGN ASSIGNMENT {$$ = new Assign($1, new RShiftOperator($1, $3));}
           | NAME T_AND_ASSIGN ASSIGNMENT {$$ = new Assign($1, new BAndOperator($1, $3));}
           | NAME T_EXOR_ASSIGN ASSIGNMENT {$$ = new Assign($1, new BXorOperator($1, $3));}
           | NAME T_INOR_ASSIGN ASSIGNMENT {$$ = new Assign($1, new BOrOperator($1, $3));}
           | DEREFERENCE T_ASSIGN ASSIGNMENT {$$ = new DereferenceAssign($1, $3);}
           ;

BREAK_STAT : BREAK {$$ = new Break();}
           ;

CONTINUE_STAT : CONTINUE {$$ = new Continue();}
              ;

RETURN_STAT : RETURN ASSIGNMENT {$$ = new Return($2);}
            ;

VAR_TYPE :  INT {$$ = new Type(*$1);}
          | UNSIGNED {$$ = new Type(*$1);}
          | FLOAT {$$ = new Type(*$1);}
          | CHAR {$$ = new Type(*$1);}
          | VOID {$$ = new Type(*$1);}
          ;

MUX : OR {$$ = $1;}
    | OR T_QUESTION MUX T_COLON MUX {$$ = new MuxOperator($1, $3, $5); }
     ;
OR : AND { $$ = $1;}
   | OR T_OR AND {$$ = new OrOperator($1, $3);}
   ;

AND : BOR { $$ = $1;}
    | AND T_AND BOR {$$ = new AndOperator($1, $3);}
    ;

BOR : BXOR { $$ = $1;}
    | BOR T_BOR BXOR {$$ = new BOrOperator($1, $3);}
    ;

BXOR : BAND { $$ = $1;}
     | BXOR T_BXOR BAND {$$ = new BXorOperator($1, $3);}
     ;

BAND : EQUALITY { $$ = $1;}
     | BAND T_BAND EQUALITY {$$ = new BAndOperator($1, $3);}
     ;

EQUALITY : RELATIONAL { $$ = $1;}
         | EQUALITY T_EQUAL RELATIONAL {$$ = new EqualOperator($1, $3);}
         | EQUALITY T_NOTEQUAL RELATIONAL {$$ = new NotEqualOperator($1, $3);}
         ;

RELATIONAL : SHIFT { $$ = $1; }
           | RELATIONAL T_GREATEREQ SHIFT {$$ = new GreaterEqOperator($1, $3);}
           | RELATIONAL T_GREATER SHIFT {$$ = new GreaterOperator($1, $3);}
           | RELATIONAL T_LESSEREQ SHIFT {$$ = new LesserEqOperator($1, $3);}
           | RELATIONAL T_LESSER SHIFT {$$ = new LesserOperator($1, $3);}
           ;

SHIFT : ADDITIVE { $$ = $1; }
      | SHIFT T_LSHIFT ADDITIVE {$$ = new LShiftOperator($1, $3);}
      | SHIFT T_RSHIFT ADDITIVE {$$ = new RShiftOperator($1, $3);}
      ;

ADDITIVE : MULTIPLICATIVE           { $$ = $1; }
         | ADDITIVE T_PLUS MULTIPLICATIVE {$$ = new AddOperator($1, $3);}
         | ADDITIVE T_MINUS MULTIPLICATIVE {$$ = new SubOperator($1, $3);}
         ;

MULTIPLICATIVE : UNARY          { $$ = $1; }
               | MULTIPLICATIVE T_TIMES UNARY {$$ = new MulOperator($1, $3);} 
               | MULTIPLICATIVE T_DIVIDE UNARY {$$ = new DivOperator($1, $3);}
               | MULTIPLICATIVE T_MOD UNARY {$$ = new ModOperator($1, $3);}
               ;

UNARY : FACTOR        { $$ = $1; }
      | T_MINUS UNARY {$$ = new NegOperator($2);}
      | T_INV UNARY {$$ = new InvOperator($2);}
      | T_NOT UNARY {$$ = new NotOperator($2); }
      ;

FACTOR : T_NUMBER     { $$ = new Number($1); }
       | T_FLOAT      { $$ = new Float($1);}
       | T_CHAR       { $$ = new Char(*$1);}
       | T_LBRACKET MUX T_RBRACKET { $$ = $2; }
       | NAME {$$ = $1; } //Note for Krish: This can be a function name as well, so variable was not the best name
       | FUNC_CALL {$$ = $1;}
       | ARRAY_INDEX {$$ = $1;}
       | DEREFERENCE {$$ = $1;}
       | STRUCT_INDEX {$$ = $1;}
       | SIZEOF T_LBRACKET VAR_TYPE T_RBRACKET {$$ = new Sizeof($3);}
       | SIZEOF T_LBRACKET NAME T_RBRACKET {$$ = new Sizeof($3);}
       ;
STRING_LITERAL : T_LITERAL {$$ = new String(*$1);};
NAME : T_STRING {$$ = new Identifier(*$1);}
     ;


%%

Node *g_root; // Definition of variable (to match declaration earlier)

Node *parseAST(std::string filename)
{
  yyin = fopen(filename.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << filename << std::endl;
    exit(1);
  }
  g_root = NULL;
  yyparse();
  return g_root;
}
