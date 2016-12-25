%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYDEBUG 1

char* battle_attrs[128];
char* round_attrs[128];
char* lyric_attrs[128];
int bai = 0;
int rai = 0;
int lai = 0;
%}
%union {
   char* text_value;
}

%token <text_value> TEXT
%token SB SR SL CR IGNORE

%%
battle
    : SB battle_attributes CR white_lines rounds
    ;

rounds
    : rounds round
    | round
    ;

round
    : SR round_attributes CR white_lines lyrics
    ;

lyrics
    : lyrics lyric
    | lyric
    ;

lyric
    : SL lyric_attributes CR texts
    ;

white_lines
    : white_lines CR
    |
    ;

texts
    : texts white_lines
    {
        printf("lyric:CR\n");
    }
    | texts TEXT
    {
        printf("lyric:%s\n", $2);
    }
    | TEXT
    {
        printf("lyric:%s\n", $1);
    }
    ;

battle_attributes
    : TEXT battle_attributes
    {
       battle_attrs[bai++] = $1;
    }
    | TEXT
    {
       battle_attrs[bai++] = $1;
    }

round_attributes
    : TEXT round_attributes
    {
       round_attrs[rai++] = $1;
    }
    | TEXT
    {
       round_attrs[rai++] = $1;
    }

lyric_attributes
    : TEXT lyric_attributes
    {
       lyric_attrs[lai++] = $1;
    }
    | TEXT
    {
       lyric_attrs[lai++] = $1;
    }


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

    printf("battle attrs:\n");
    for (int i=0; i < bai; i++) {
       printf("%s, ", battle_attrs[i]);
    }
    printf("\n");

    printf("round attrs:\n");
    for (int i=0; i < rai; i++) {
       printf("%s,", round_attrs[i]);
    }
    printf("\n");

    printf("lyric attrs:\n");
    for (int i=0; i < lai; i++) {
       printf("%s,", lyric_attrs[i]);
    }
    printf("\n");
}
