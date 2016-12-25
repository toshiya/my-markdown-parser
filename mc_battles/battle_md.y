%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}
%union {
   char* text_value;
}

%token <text_value> TEXT
%token SB SR SL CR IGNORE

%%
battle
    : SB attributes CR white_lines rounds
    ;

rounds
    : rounds round
    | round
    ;

round
    : SR attributes CR white_lines lyrics
    ;

lyrics
    : lyrics lyric
    | lyric
    ;

lyric
    : SL attributes CR texts
    ;

white_lines
    : white_lines CR
    |
    ;

texts
    : texts white_lines
    | texts TEXT
    | TEXT
    ;

attributes
    : TEXT attributes
    | TEXT
    ;

%%

int
yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "%s\n", str);
    fprintf(stderr, "near %s!\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void);
    extern FILE *yyin;
    yyin = stdin;

    if (yyparse()) {
        fprintf(stderr, "Error!\n");
        exit(1);
    }

    printf("syntax ok:\n");
}
