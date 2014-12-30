%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1
%}
%union {
char*        literal_value;
char*        string_value;
}
%token <literal_value>  LITERAL
%token LINK_OPEN IMAGE_OPEN CLOSE LEFT_PAR RIGHT_PAR CR
%type <string_value> blocks block link element image
%%
line_list
    : line
    | line_list line
    ;
line
    : blocks CR
    {
        printf("%s\n", $1);
        free($1);
    }
blocks
    : block
    | block blocks
    {
        char* buf;
        int lengths[2];
        lengths[0] = strlen($1);
        lengths[1] = strlen($2);
        int len = 0;
        for (int i=0; i < 2; i++) {
            len += lengths[i];
        }
        buf = calloc(sizeof(char), len + 2);
        sprintf(buf, "%s %s", $1, $2);
        free($1);
        free($2);
        $$ = buf;
    }
    ;
block
    : element
    | link 
    ;
link 
    : LINK_OPEN element CLOSE LEFT_PAR LITERAL RIGHT_PAR
    {
        char* buf;
        int lengths[2];
        lengths[0] = strlen($2);
        lengths[1] = strlen($5);
        int len = 0;
        for (int i=0; i < 2; i++) {
            len += lengths[i];
        }
        buf = calloc(len + 19, sizeof(char));
        sprintf(buf, "<a href=\"%s\" > %s </a>", $5, $2);
        free($2);
        free($5);
        $$ = buf;
    }
    ;
element 
    : image
    | LITERAL
    ;
image
    : IMAGE_OPEN LITERAL CLOSE LEFT_PAR LITERAL RIGHT_PAR
    {
        char* buf;
        int lengths[2];
        lengths[0] = strlen($2);
        lengths[1] = strlen($5);

        int len = 0;
        for (int i = 0; i < 2; i++) {
            len += lengths[i];
        }
        buf = calloc(len + 38, sizeof(char));
        sprintf(buf, "<img src=\"%s\" alt=\"%s\" width=\"320\" ></img>", $5, $2);
        free($2);
        free($5);
        $$ = buf;
    }
    ;
%%
int
yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void);
    extern FILE *yyin;

    //yydebug = 1;
    yyin = stdin;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}
