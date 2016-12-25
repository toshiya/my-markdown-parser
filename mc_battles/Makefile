all:
	yacc -dv battle_md.y
	lex token.l
	gcc y.tab.c lex.yy.c node.c -ljansson

clean:
	rm a.out lex.yy.c y.output y.tab.c y.tab.h 
