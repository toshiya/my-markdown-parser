%{
#include <stdio.h>
#include "string.h"
#include "node.h"
#include "y.tab.h"
int yywrap(void) {
    return 1; 
}
%}

%%
"# B" return SB;
"## R" return SR;
"### L" return SL;
"\n" return CR;
[^#\n ]+ {
    char* text;
    text = (char*) calloc(sizeof(char), strlen(yytext) + 1);
    strcpy(text, yytext);
    yylval.text_value = text;
    return TEXT;
}
. /* ignore */
%%
