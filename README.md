my-markdown-parser
==================

Parsing markdown by using lex and yacc.

[Article On Qiita (In Japanese)](http://qiita.com/toshiya/items/7fa39bd9c06fc1c0a44c)

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
cd image_link
yacc -dv my_markdown.y 
lex token.l
gcc -o my_markdown_parser y.tab.c lex.yy.c
```

## Execution

```
cd image_link
cat sample/sample.md | ./my_markdown_parser
```
