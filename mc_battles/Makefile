JANSSON_LIB=/usr/local/lib
GTEST_ROOT=/usr/local/googletest/googletest/

all: bin/battle_md

y.tab.c: battle_md.y
	yacc -dv battle_md.y

y.tab.h: battle_md.y
	yacc -dv battle_md.y

lex.yy.c: token.l y.tab.h
	lex token.l

battle_md: y.tab.c lex.yy.c node.c
	mkdir -p bin
	yacc -dv battle_md.y
	clang -o bin/$@ $^ -L$(JANSSON_LIB) -ljansson

example: bin/battle_md
	echo "execute the following command!!!"
	echo "cat example/example.md | ./bin/battle_md | jsonlint"

test:
	mkdir -p bin
	clang++ -std=c++11 -o bin/test_node unit_test/test_node.cc node.c -I$(GTEST_ROOT)/include -L$(JANSSON_LIB) -L$(GTEST_ROOT)/build -ljansson -lgtest_main -lgtest
	./bin/test_node

clean:
	rm lex.yy.c y.output y.tab.c y.tab.h bin/*
