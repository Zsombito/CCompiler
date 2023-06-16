%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%
[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }

[!]             { return T_NOT;}
[~]             { return T_INV; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[%]             { return T_MOD; }

[+]             { return T_PLUS; }
[-]             { return T_MINUS; }

"<<"            { return T_LSHIFT; }
">>"            { return T_RSHIFT; }

[>]             { return T_GREATER; }
[<]             { return T_LESSER; }
">="            { return T_GREATEREQ;}
"<="            { return T_LESSEREQ;}

"=="            { return T_EQUAL; }
"!="            { return T_NOTEQUAL;}

[&]             { return T_BAND; }

[\^]            { return T_BXOR;}

[|]             { return T_BOR; }

"&&"            { return T_AND; }

"||"            { return T_OR; }

[?]             { return T_QUESTION; }
[:]             { return T_COLON; }

\.             {return T_DOT;}

[=]             { return T_ASSIGN; }

"{"             { return T_LCBRACKET; }
"}"             { return T_RCBRACKET; }
","             { return T_COMMA; }
"["             { return T_LSBRACKET; }
"]"             { return T_RSBRACKET; }
"++"            { return T_INCREMENT; }
"--"            { return T_DECREMENT; }

"+="            { return T_ADD_ASSIGN; }
"-="            { return T_SUB_ASSIGN; }
"*="            { return T_MUL_ASSIGN; }
"/="            { return T_DIV_ASSIGN; }
"%="            { return T_MOD_ASSIGN; }
">>="           { return T_RSHIFT_ASSIGN; }
"<<="           { return T_LSHIFT_ASSIGN; }
"&="            { return T_AND_ASSIGN; }
"^="            { return T_INOR_ASSIGN; }
"|="            { return T_EXOR_ASSIGN; }

";"             { return T_SEMICOLON; }
"if"            {return IF;}
"else"          {return ELSE;}
"int"           {yylval.string=new std::string(yytext); return INT;}
"void"          {yylval.string=new std::string(yytext); return VOID; }
"unsigned"      {yylval.string=new std::string(yytext); return UNSIGNED; }
"float"         {yylval.string=new std::string(yytext); return FLOAT; }
"char"         {yylval.string=new std::string(yytext); return CHAR; }
"while"         {return WHILE;}
"return"        {return RETURN;}
"continue"      {return CONTINUE; }
"break"         {return BREAK; }
"switch"        {return SWITCH;}
"case"        {return CASE;}
"for"         {return FOR;}
"default"     {return DEFAULT;}
"enum"        {return ENUM;}
"sizeof"      {return SIZEOF;}
"struct"      {return STRUCT;}



[0-9]+ { yylval.number=strtod(yytext, 0); return T_NUMBER; }
[0-9]+.?[0-9]*[f|F] { yylval.number=strtod(yytext, 0); return T_FLOAT; }
([a-z]|[A-Z]|_)([a-z]|[A-Z]|_|[0-9])*         { yylval.string=new std::string(yytext); return T_STRING; }
'.'                 { yylval.string=new std::string(yytext); return T_CHAR; }
\".*\"              { yylval.string=new std::string(yytext); return T_LITERAL; }
[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
