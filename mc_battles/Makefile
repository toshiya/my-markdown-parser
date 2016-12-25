all: battle_md


y.tab.c: battle_md.y
	yacc -dv battle_md.y

y.tab.h: battle_md.y
	yacc -dv battle_md.y

lex.yy.c: token.l y.tab.h
	lex token.l

battle_md: y.tab.c lex.yy.c node.c
	yacc -dv battle_md.y
	gcc -o $@ y.tab.c lex.yy.c node.c -ljansson

test: battle_md
	cat example/example.md | ./battle_md

clean:
	rm battle_md lex.yy.c y.output y.tab.c y.tab.h 
