%{
#include <stdio.h>
#include "string.h"
#include "y.tab.h"
int yywrap(void) {
    return 1; 
}
%}

%%
"#B" return SB;
"#R" return SR;
"#L" return SL;
"\n" return CR;
[^#\n ]+ {
    char* text;
    text = calloc(sizeof(char), strlen(yytext) + 1);
    strcpy(text, yytext);
    yylval.text_value = text;
    return TEXT;
}
. /* ignore */
%%

// For Debug token.l
//int main(void) {
//    int ret = IGNORE;
//    while(ret != END) {
//        ret = yylex();
//    }
//    return 0;
//}
