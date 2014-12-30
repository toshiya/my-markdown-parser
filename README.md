my-markdown-parser
==================

Parsing markdown by using lex and yacc.

# Requirement

You need to install yacc and lex.

# Currently Supported Markdown

* Embedded Image

```
  ![AltText](http://img.example.com/100)
```

* Link

```
  [LinkText](http://example.com)
```

# Example

## Build

```bash
yacc -dv my_markdown.y 
lex token.l
gcc -o my_markdown_parser y.tab.c lex.yy.c
```

## Execution

```
cat sample/sample.md | ./my_markdown_parser
```
