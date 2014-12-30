%{
#include <stdio.h>
#include "string.h"
#include "y.tab.h"

int
yywrap(void)
{
    return 1;
}
%}
%%
"["      return LINK_OPEN;
"!["     return IMAGE_OPEN;
"]"      return CLOSE;
"("      return LEFT_PAR;
")"      return RIGHT_PAR;
"\n"     return CR;
[0-9A-Za-z_,\-\.:/]+ {
    char* temp;
    int len = strlen(yytext);
    temp = calloc(sizeof(char), len + 1);
    sscanf(yytext, "%s", temp);
    yylval.literal_value = temp;
    return LITERAL;
}
%%

