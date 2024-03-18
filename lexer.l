%{
#include "parser.h"
%}

%%

[0-9]+  { yylval = atoi(yytext); return INTEGER; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULTIPLY; }
"/"     { return DIVIDE; }
"("     { return LPAREN; }
")"     { return RPAREN; }
[ \t\n] ; /* Ignore whitespace */
.       { return UNKNOWN; }

%%
