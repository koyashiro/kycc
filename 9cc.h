#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// parse.c
//

typedef enum {
  TK_RESERVED,
  TK_IDENT,
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Token Token;
struct Token {
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len;
};

extern char *user_input;

extern Token *token;

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

bool consume(char *op);
Token *consume_ident(void);
void expect(char *op);
int expect_number(void);

bool at_eol(void);

Token *new_token(TokenKind kind, Token *cur, char *str, int len);

bool startswith(char *p, char *q);

Token *tokenize(void);

typedef enum {
  ND_ADD,    // +
  ND_SUB,    // -
  ND_MUL,    // *
  ND_DIV,    // /
  ND_ASSIGN, // =
  ND_LVAR,   // local variable
  ND_EQ,     // ==
  ND_NE,     // !=
  ND_LT,     // <
  ND_LE,     // <=
  ND_NUM,    // Integer
} NodeKind;

typedef struct Node Node;
struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
  int offset;
};

Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);

extern Node *code[100];

void program(void);
Node *stmt(void);
Node *expr(void);
Node *assign(void);
Node *equality(void);
Node *relational(void);
Node *add(void);
Node *mul(void);
Node *unary(void);
Node *primary(void);

//
// codegen.c
//

void gen_lval(Node *node); 

void gen(Node *node);
