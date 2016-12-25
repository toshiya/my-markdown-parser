%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

%}
%union {
   char* text_value;
   Round* round_value;
   Array rounds_value;
   Lyric* lyric_value;
   Array lyrics_value;
   Array attributes_value;
}

%token <text_value> TEXT
%token SB SR SL CR IGNORE
%type <rounds_value> rounds
%type <lyrics_value> lyrics
%type <round_value> round
%type <lyric_value> lyric
%type <text_value> texts
%type <attributes_value> attributes

%%
battle
    : SB attributes CR white_lines rounds
    {
        Array as = $2;
        Array rs = $5;
        Battle *b = battle_create(as.values[4], as.values[3], as.values[2], as.values[1], as.values[0], rs);
        printf("%s", json_dumps(battle_to_json(b), 0));
    }

rounds
    : rounds round
    {
        Array rs = $1;
        array_push(&rs, $2);
        $$ = rs;
    }
    | round
    {
        Array rs = array_create();
        array_push(&rs, $1);
        $$ = rs;
    }

round
    : SR attributes CR white_lines lyrics
    {
        Array as = $2;
        Array ls = $5;
        Round* r = round_create(as.values[0], ls);
        $$ = r;
    }

lyrics
    : lyrics lyric
    {
       Array ls = $1;
       array_push(&ls, $2);
       $$ = ls;
    }
    | lyric
    {
       Array ls = array_create();
       array_push(&ls, $1);
       $$ = ls;
    }

lyric
    : SL attributes CR texts
    {
        char* content = $4;
        Array as = $2;
        Lyric* l = lyric_create(as.values[0], content);
        $$ = l;
    }

white_lines
    : white_lines CR
    |
    ;

texts
    : texts white_lines
    {
        $$ = $1;
    }
    | texts TEXT
    {
        char* text;
        text = calloc(strlen($1) + strlen($2) + 2, sizeof(char));
        sprintf(text, "%s %s", $1, $2);
        $$ = text;
    }
    | TEXT
    {
        char* text;
        text = calloc(strlen($1) + 1, sizeof(char));
        strcpy(text, $1);
        $$ = text;
    }

attributes
    : TEXT attributes
    {
       char* text;
       text = calloc(strlen($1) + 1, sizeof(char));
       strcpy(text, $1);
       Array as = $2;
       array_push(&as, text);
       $$ = as;
    }
    | TEXT
    {
       char* text;
       text = calloc(strlen($1) + 1, sizeof(char));
       strcpy(text, $1);
       Array as = array_create();
       array_push(&as, text);
       $$ = as;
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
}
