/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "source/grammar.lemon"

    #import <string>
    #import <cassert>
    
    #import "ast.hpp"
    #import "tokenizer.hpp"
    
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-parameter"
    
    static std::string ident2string(Token tok) {
        return std::string(tok.payloadStart, tok.payloadEnd);
    }
    
    template <typename T>
    static T unpointer(T* ptr) {
        T val(*ptr);
        delete ptr;
        return val;
    }
    
    template <typename T>
    static std::deque<T> singular(T val) {
        std::deque<T> xs;
        xs.push_back(val);
        return xs;
    }
#line 36 "source/grammar.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 57
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE  Token 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  Type* yy29;
  std::deque<Decl*>* yy34;
  Expr* yy35;
  std::deque<Types*>* yy51;
  std::deque<std::string>* yy62;
  Decl* yy87;
  std::deque<Expr*>* yy101;
  std::deque<std::pair<Expr*, Expr*> >* yy103;
  std::pair<Expr*, Expr*>* yy106;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParseTree* parsetree ;
#define ParseARG_PDECL , ParseTree* parsetree 
#define ParseARG_FETCH  ParseTree* parsetree  = yypParser->parsetree 
#define ParseARG_STORE yypParser->parsetree  = parsetree 
#define YYNSTATE 100
#define YYNRULE 52
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    23,   22,   19,   29,    7,   27,    6,   26,   25,   24,
 /*    10 */    17,   18,   13,   14,   15,   85,    3,   12,   71,   17,
 /*    20 */    18,   13,   14,   15,   99,   94,   12,   71,   16,   98,
 /*    30 */    30,   28,   81,   23,   22,   19,   29,    7,   27,    6,
 /*    40 */    26,   25,   24,   17,   18,   13,   14,   15,   12,   71,
 /*    50 */    12,   71,   13,   14,   15,   41,   31,   12,   71,   42,
 /*    60 */    35,   65,   79,   68,   89,   11,   23,   22,   19,   29,
 /*    70 */     7,   27,    6,   26,   25,   24,   17,   18,   13,   14,
 /*    80 */    15,   35,   44,   12,   71,   87,   36,   23,   22,   19,
 /*    90 */    29,    7,   27,    6,   26,   25,   24,   17,   18,   13,
 /*   100 */    14,   15,   67,   46,   12,   71,   19,   29,    7,   27,
 /*   110 */     6,   26,   25,   24,   17,   18,   13,   14,   15,   21,
 /*   120 */    10,   12,   71,   20,  153,   77,   76,   84,   30,   28,
 /*   130 */    81,   39,   63,   21,   91,   72,    4,   20,   43,   95,
 /*   140 */    93,    2,   66,    1,   88,   61,   82,   83,   21,   72,
 /*   150 */     4,    8,   20,   95,   93,    2,   90,    1,   73,   54,
 /*   160 */    82,   83,    5,   70,   72,    4,   69,   32,   95,   93,
 /*   170 */     2,   74,    1,   33,   96,   82,   83,   30,   28,   81,
 /*   180 */    30,   28,   81,   34,  100,   37,   86,   75,   97,   49,
 /*   190 */    40,   78,   64,   50,   48,   52,   62,   51,   47,   38,
 /*   200 */    80,   58,    9,  154,   59,  154,   55,   57,   56,   60,
 /*   210 */    92,  154,  154,   53,   45,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    10 */    13,   14,   15,   16,   17,   39,   40,   20,   21,   13,
 /*    20 */    14,   15,   16,   17,   30,   37,   20,   21,   40,   32,
 /*    30 */    26,   27,   28,    3,    4,    5,    6,    7,    8,    9,
 /*    40 */    10,   11,   12,   13,   14,   15,   16,   17,   20,   21,
 /*    50 */    20,   21,   15,   16,   17,   50,   40,   20,   21,   50,
 /*    60 */    50,   52,   32,   53,   54,    2,    3,    4,    5,    6,
 /*    70 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    80 */    17,   50,   50,   20,   21,   54,   50,    3,    4,    5,
 /*    90 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   100 */    16,   17,   50,   50,   20,   21,    5,    6,    7,    8,
 /*   110 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   14,
 /*   120 */    33,   20,   21,   18,   45,   46,   47,   48,   26,   27,
 /*   130 */    28,   50,   50,   14,   32,   30,   31,   18,   50,   34,
 /*   140 */    35,   36,   50,   38,   39,   50,   41,   42,   14,   30,
 /*   150 */    31,   40,   18,   34,   35,   36,   37,   38,   32,   51,
 /*   160 */    41,   42,   31,   55,   30,   31,   40,   36,   34,   35,
 /*   170 */    36,   30,   38,    1,   43,   41,   42,   26,   27,   28,
 /*   180 */    26,   27,   28,   31,    0,   50,   32,   52,   37,   50,
 /*   190 */    50,   30,   50,   50,   50,   50,   50,   50,   50,   50,
 /*   200 */    30,   51,    2,   56,   51,   56,   51,   51,   51,   49,
 /*   210 */    48,   56,   56,   50,   50,
};
#define YY_SHIFT_USE_DFLT (-25)
#define YY_SHIFT_MAX 77
static const short yy_shift_ofst[] = {
 /*     0 */   141,  105,  119,  134,  134,  131,  134,  134,  134,  134,
 /*    10 */   134,  134,  134,  134,  134,  134,  134,  134,  134,  134,
 /*    20 */   134,  134,  134,  134,  134,  134,  134,  134,  131,  131,
 /*    30 */   131,  131,  131,  141,  170,   63,   30,   -3,   84,   84,
 /*    40 */    84,   84,   84,  101,  101,    6,    6,    6,    6,    6,
 /*    50 */     6,    6,   37,   37,  154,  102,  151,    4,    4,    4,
 /*    60 */   126,   28,   28,   28,   28,  -12,   28,   28,  -24,   -6,
 /*    70 */    16,  161,  200,   87,  152,  111,  172,  184,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_MAX 34
static const short yy_reduce_ofst[] = {
 /*     0 */    79,   10,    9,   31,  135,  108,  144,  148,   36,  140,
 /*    10 */   149,   81,  146,   95,   82,   52,    5,  163,  145,   53,
 /*    20 */    92,  142,   88,   32,  147,  143,  139,  164,  156,  153,
 /*    30 */   150,  155,  157,  162,  160,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   102,  152,  152,  152,  152,  152,  152,  152,  152,  152,
 /*    10 */   152,  152,  152,  152,  152,  152,  152,  152,  152,  152,
 /*    20 */   152,  152,  152,  152,  152,  152,  152,  152,  152,  152,
 /*    30 */   152,  152,  152,  152,  152,  152,  136,  137,  105,  140,
 /*    40 */   132,  136,  137,  125,  124,  119,  116,  118,  120,  121,
 /*    50 */   122,  123,  115,  114,  151,  150,  152,  146,  145,  117,
 /*    60 */   152,  111,  108,  112,  109,  152,  110,  113,  152,  152,
 /*    70 */   152,  152,  152,  152,  152,  152,  101,  152,  107,  133,
 /*    80 */   142,  148,  134,  135,  104,  130,  149,  138,  131,  139,
 /*    90 */   129,  147,  103,  127,  128,  126,  143,  144,  106,  141,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "NEWLINE",       "COLON",         "ANDAND",      
  "BARBAR",        "IN",            "IS",            "EQEQ",        
  "EXCLAIMEQ",     "LT",            "GT",            "LTEQ",        
  "GTEQ",          "ADD",           "MINUS",         "STAR",        
  "SLASH",         "MOD",           "EXCLAIM",       "UNARYMINUS",  
  "STARSTAR",      "DOT",           "SUBSCRIPT",     "CALL",        
  "GROUPING",      "LAMBDA",        "FATARROW",      "ARROW",       
  "QUESTIONMARK",  "TYPE_GROUPING",  "IDENT",         "LPAREN",      
  "RPAREN",        "EQ",            "NUMBER",        "STRING",      
  "LSQUARE",       "RSQUARE",       "LCURLY",        "RCURLY",      
  "COMMA",         "YES",           "NO",            "TITLEIDENT",  
  "error",         "root",          "decls0",        "decls",       
  "decl",          "idents",        "expr",          "type",        
  "exprs",         "kvpairs",       "kvpair",        "types",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "root ::= decls0",
 /*   1 */ "decls0 ::= decls",
 /*   2 */ "decls0 ::=",
 /*   3 */ "decls ::= decls NEWLINE decl",
 /*   4 */ "decls ::= decl",
 /*   5 */ "decl ::= IDENT LPAREN idents RPAREN EQ expr",
 /*   6 */ "expr ::= LPAREN expr RPAREN",
 /*   7 */ "expr ::= expr DOT IDENT",
 /*   8 */ "expr ::= expr STARSTAR expr",
 /*   9 */ "expr ::= MINUS expr",
 /*  10 */ "expr ::= EXCLAIM expr",
 /*  11 */ "expr ::= expr STAR expr",
 /*  12 */ "expr ::= expr SLASH expr",
 /*  13 */ "expr ::= expr MOD expr",
 /*  14 */ "expr ::= expr ADD expr",
 /*  15 */ "expr ::= expr MINUS expr",
 /*  16 */ "expr ::= expr IN expr",
 /*  17 */ "expr ::= expr IS type",
 /*  18 */ "expr ::= expr EQEQ expr",
 /*  19 */ "expr ::= expr EXCLAIMEQ expr",
 /*  20 */ "expr ::= expr LT expr",
 /*  21 */ "expr ::= expr GT expr",
 /*  22 */ "expr ::= expr LTEQ expr",
 /*  23 */ "expr ::= expr GTEQ expr",
 /*  24 */ "expr ::= expr ANDAND expr",
 /*  25 */ "expr ::= expr BARBAR expr",
 /*  26 */ "expr ::= NUMBER",
 /*  27 */ "expr ::= STRING",
 /*  28 */ "expr ::= LSQUARE exprs RSQUARE",
 /*  29 */ "expr ::= LSQUARE RSQUARE",
 /*  30 */ "expr ::= LCURLY kvpairs RCURLY",
 /*  31 */ "expr ::= LCURLY RCURLY",
 /*  32 */ "expr ::= IDENT COLON expr",
 /*  33 */ "expr ::= LPAREN exprs COMMA expr RPAREN",
 /*  34 */ "expr ::= YES",
 /*  35 */ "expr ::= NO",
 /*  36 */ "exprs ::= exprs COMMA expr",
 /*  37 */ "exprs ::= expr",
 /*  38 */ "kvpairs ::= kvpairs COMMA kvpair",
 /*  39 */ "kvpairs ::= kvpair",
 /*  40 */ "kvpair ::= expr COLON expr",
 /*  41 */ "idents ::= idents COMMA IDENT",
 /*  42 */ "idents ::= IDENT",
 /*  43 */ "type ::= TITLEIDENT",
 /*  44 */ "type ::= LSQUARE type RSQUARE",
 /*  45 */ "type ::= type FATARROW type",
 /*  46 */ "type ::= type ARROW type",
 /*  47 */ "type ::= LPAREN types COMMA type RPAREN",
 /*  48 */ "type ::= type QUESTIONMARK",
 /*  49 */ "type ::= LPAREN type RPAREN",
 /*  50 */ "types ::= types COMMA type",
 /*  51 */ "types ::= type",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_MAX ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_MAX );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_SZ_ACTTAB );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 45, 1 },
  { 46, 1 },
  { 46, 0 },
  { 47, 3 },
  { 47, 1 },
  { 48, 6 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 2 },
  { 50, 2 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 3 },
  { 50, 1 },
  { 50, 1 },
  { 50, 3 },
  { 50, 2 },
  { 50, 3 },
  { 50, 2 },
  { 50, 3 },
  { 50, 5 },
  { 50, 1 },
  { 50, 1 },
  { 52, 3 },
  { 52, 1 },
  { 53, 3 },
  { 53, 1 },
  { 54, 3 },
  { 49, 3 },
  { 49, 1 },
  { 51, 1 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 5 },
  { 51, 2 },
  { 51, 3 },
  { 55, 3 },
  { 55, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* root ::= decls0 */
#line 53 "source/grammar.lemon"
{ parsetree->decls = *yymsp[0].minor.yy34; }
#line 838 "source/grammar.c"
        break;
      case 1: /* decls0 ::= decls */
#line 56 "source/grammar.lemon"
{ yygotominor.yy34 = yymsp[0].minor.yy34; }
#line 843 "source/grammar.c"
        break;
      case 2: /* decls0 ::= */
#line 57 "source/grammar.lemon"
{ yygotominor.yy34 = new std::deque<Decl*>(); }
#line 848 "source/grammar.c"
        break;
      case 3: /* decls ::= decls NEWLINE decl */
#line 60 "source/grammar.lemon"
{ yygotominor.yy34 = yymsp[-2].minor.yy34; yymsp[-2].minor.yy34->push_back(yymsp[0].minor.yy87); }
#line 853 "source/grammar.c"
        break;
      case 4: /* decls ::= decl */
#line 61 "source/grammar.lemon"
{ yygotominor.yy34 = new std::deque<Decl*>(); yygotominor.yy34->push_back(yymsp[0].minor.yy87); }
#line 858 "source/grammar.c"
        break;
      case 5: /* decl ::= IDENT LPAREN idents RPAREN EQ expr */
#line 66 "source/grammar.lemon"
{ yygotominor.yy87 = new FunctionDecl(ident2string(yymsp[-5].minor.yy0), yymsp[-3].minor.yy62, yymsp[0].minor.yy35); }
#line 863 "source/grammar.c"
        break;
      case 6: /* expr ::= LPAREN expr RPAREN */
#line 72 "source/grammar.lemon"
{ yygotominor.yy35 = yymsp[-1].minor.yy35; }
#line 868 "source/grammar.c"
        break;
      case 7: /* expr ::= expr DOT IDENT */
#line 81 "source/grammar.lemon"
{ yygotominor.yy35 = new MemberExpr(yymsp[-2].minor.yy35, ident2string(yymsp[0].minor.yy0)); }
#line 873 "source/grammar.c"
        break;
      case 8: /* expr ::= expr STARSTAR expr */
#line 84 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Power, yymsp[0].minor.yy35); }
#line 878 "source/grammar.c"
        break;
      case 9: /* expr ::= MINUS expr */
#line 87 "source/grammar.lemon"
{ yygotominor.yy35 = new UnaryExpr(yymsp[0].minor.yy35, OperatorType::Negate); }
#line 883 "source/grammar.c"
        break;
      case 10: /* expr ::= EXCLAIM expr */
#line 88 "source/grammar.lemon"
{ yygotominor.yy35 = new UnaryExpr(yymsp[0].minor.yy35, OperatorType::LogicalNot); }
#line 888 "source/grammar.c"
        break;
      case 11: /* expr ::= expr STAR expr */
#line 91 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Multiply, yymsp[0].minor.yy35); }
#line 893 "source/grammar.c"
        break;
      case 12: /* expr ::= expr SLASH expr */
#line 92 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Divide, yymsp[0].minor.yy35); }
#line 898 "source/grammar.c"
        break;
      case 13: /* expr ::= expr MOD expr */
#line 93 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Mod, yymsp[0].minor.yy35); }
#line 903 "source/grammar.c"
        break;
      case 14: /* expr ::= expr ADD expr */
#line 96 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Add, yymsp[0].minor.yy35); }
#line 908 "source/grammar.c"
        break;
      case 15: /* expr ::= expr MINUS expr */
#line 97 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Subtract, yymsp[0].minor.yy35); }
#line 913 "source/grammar.c"
        break;
      case 16: /* expr ::= expr IN expr */
#line 103 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::In, yymsp[0].minor.yy35); }
#line 918 "source/grammar.c"
        break;
      case 17: /* expr ::= expr IS type */
#line 104 "source/grammar.lemon"
{ yygotominor.yy35 = new IsExpr(yymsp[-2].minor.yy35, OperatorType::Is, yymsp[0].minor.yy29); }
#line 923 "source/grammar.c"
        break;
      case 18: /* expr ::= expr EQEQ expr */
#line 105 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::Equals, yymsp[0].minor.yy35); }
#line 928 "source/grammar.c"
        break;
      case 19: /* expr ::= expr EXCLAIMEQ expr */
#line 106 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::NotEqual, yymsp[0].minor.yy35); }
#line 933 "source/grammar.c"
        break;
      case 20: /* expr ::= expr LT expr */
#line 107 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::LessThan, yymsp[0].minor.yy35); }
#line 938 "source/grammar.c"
        break;
      case 21: /* expr ::= expr GT expr */
#line 108 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::GreaterThan, yymsp[0].minor.yy35); }
#line 943 "source/grammar.c"
        break;
      case 22: /* expr ::= expr LTEQ expr */
#line 109 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::LessOrEqual, yymsp[0].minor.yy35); }
#line 948 "source/grammar.c"
        break;
      case 23: /* expr ::= expr GTEQ expr */
#line 110 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::GreaterOrEqual, yymsp[0].minor.yy35); }
#line 953 "source/grammar.c"
        break;
      case 24: /* expr ::= expr ANDAND expr */
#line 113 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::LogicalAnd, yymsp[0].minor.yy35); }
#line 958 "source/grammar.c"
        break;
      case 25: /* expr ::= expr BARBAR expr */
#line 114 "source/grammar.lemon"
{ yygotominor.yy35 = new BinaryExpr(yymsp[-2].minor.yy35, OperatorType::LogicalOr, yymsp[0].minor.yy35); }
#line 963 "source/grammar.c"
        break;
      case 26: /* expr ::= NUMBER */
#line 117 "source/grammar.lemon"
{ yygotominor.yy35 = static_cast<Expr*>(NumberLiteral::parse(yymsp[0].minor.yy0)); }
#line 968 "source/grammar.c"
        break;
      case 27: /* expr ::= STRING */
#line 118 "source/grammar.lemon"
{ yygotominor.yy35 = new StringLiteral(yymsp[0].minor.yy0); }
#line 973 "source/grammar.c"
        break;
      case 28: /* expr ::= LSQUARE exprs RSQUARE */
#line 119 "source/grammar.lemon"
{ yygotominor.yy35 = new ListLiteral(unpointer(yymsp[-1].minor.yy101)); }
#line 978 "source/grammar.c"
        break;
      case 29: /* expr ::= LSQUARE RSQUARE */
#line 120 "source/grammar.lemon"
{ yygotominor.yy35 = new ListLiteral(std::deque<Expr*>()); }
#line 983 "source/grammar.c"
        break;
      case 30: /* expr ::= LCURLY kvpairs RCURLY */
#line 121 "source/grammar.lemon"
{ yygotominor.yy35 = new DictLiteral(unpointer(yymsp[-1].minor.yy103)); }
#line 988 "source/grammar.c"
        break;
      case 31: /* expr ::= LCURLY RCURLY */
#line 122 "source/grammar.lemon"
{ yygotominor.yy35 = new DictLiteral(std::deque<std::pair<Expr*, Expr*> >()); }
#line 993 "source/grammar.c"
        break;
      case 32: /* expr ::= IDENT COLON expr */
#line 123 "source/grammar.lemon"
{ yygotominor.yy35 = new FunctionLiteral(singular(ident2string(yymsp[-2].minor.yy0)), yymsp[0].minor.yy35); }
#line 998 "source/grammar.c"
        break;
      case 33: /* expr ::= LPAREN exprs COMMA expr RPAREN */
#line 125 "source/grammar.lemon"
{ yymsp[-3].minor.yy101->push_back(yymsp[-1].minor.yy35); yygotominor.yy35 = new TupleLiteral(unpointer(yymsp[-3].minor.yy101)); }
#line 1003 "source/grammar.c"
        break;
      case 34: /* expr ::= YES */
#line 127 "source/grammar.lemon"
{ yygotominor.yy35 = new BoolLiteral(true); }
#line 1008 "source/grammar.c"
        break;
      case 35: /* expr ::= NO */
#line 128 "source/grammar.lemon"
{ yygotominor.yy35 = new BoolLiteral(false); }
#line 1013 "source/grammar.c"
        break;
      case 36: /* exprs ::= exprs COMMA expr */
#line 131 "source/grammar.lemon"
{ yygotominor.yy101 = yymsp[-2].minor.yy101; yymsp[-2].minor.yy101->push_back(yymsp[0].minor.yy35); }
#line 1018 "source/grammar.c"
        break;
      case 37: /* exprs ::= expr */
#line 132 "source/grammar.lemon"
{ yygotominor.yy101 = new std::deque<Expr*>; yygotominor.yy101->push_back(yymsp[0].minor.yy35); }
#line 1023 "source/grammar.c"
        break;
      case 38: /* kvpairs ::= kvpairs COMMA kvpair */
#line 137 "source/grammar.lemon"
{ yygotominor.yy103 = yymsp[-2].minor.yy103; yymsp[-2].minor.yy103->push_back(unpointer(yymsp[0].minor.yy106)); }
#line 1028 "source/grammar.c"
        break;
      case 39: /* kvpairs ::= kvpair */
#line 138 "source/grammar.lemon"
{ yygotominor.yy103 = new std::deque<std::pair<Expr*, Expr*> >; yygotominor.yy103->push_back(unpointer(yymsp[0].minor.yy106)); }
#line 1033 "source/grammar.c"
        break;
      case 40: /* kvpair ::= expr COLON expr */
#line 141 "source/grammar.lemon"
{ yygotominor.yy106 = new std::pair<Expr*, Expr*>(yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 1038 "source/grammar.c"
        break;
      case 41: /* idents ::= idents COMMA IDENT */
#line 145 "source/grammar.lemon"
{ yygotominor.yy62 = yymsp[-2].minor.yy62; yymsp[-2].minor.yy62->push_back(ident2string(yymsp[0].minor.yy0)); }
#line 1043 "source/grammar.c"
        break;
      case 42: /* idents ::= IDENT */
#line 146 "source/grammar.lemon"
{ yygotominor.yy62 = new std::deque<std::string>; yygotominor.yy62->push_back(ident2string(yymsp[0].minor.yy0)); }
#line 1048 "source/grammar.c"
        break;
      case 43: /* type ::= TITLEIDENT */
#line 151 "source/grammar.lemon"
{ yygotominor.yy29 = new NamedType(ident2string(yymsp[0].minor.yy0)); }
#line 1053 "source/grammar.c"
        break;
      case 44: /* type ::= LSQUARE type RSQUARE */
#line 152 "source/grammar.lemon"
{ yygotominor.yy29 = new ListType(yymsp[-1].minor.yy29); }
#line 1058 "source/grammar.c"
        break;
      case 45: /* type ::= type FATARROW type */
#line 153 "source/grammar.lemon"
{ yygotominor.yy29 = new DictType(yymsp[-2].minor.yy29, yymsp[0].minor.yy29); }
#line 1063 "source/grammar.c"
        break;
      case 46: /* type ::= type ARROW type */
#line 154 "source/grammar.lemon"
{ yygotominor.yy29 = new FunctionType(yymsp[-2].minor.yy29, yymsp[0].minor.yy29); }
#line 1068 "source/grammar.c"
        break;
      case 47: /* type ::= LPAREN types COMMA type RPAREN */
#line 155 "source/grammar.lemon"
{ yymsp[-3].minor.yy51.push_back(yymsp[-1].minor.yy29); yygotominor.yy29 = new TupleType(yymsp[-3].minor.yy51); }
#line 1073 "source/grammar.c"
        break;
      case 48: /* type ::= type QUESTIONMARK */
#line 156 "source/grammar.lemon"
{ yygotominor.yy29 = new OptionalType(yymsp[-1].minor.yy29); }
#line 1078 "source/grammar.c"
        break;
      case 49: /* type ::= LPAREN type RPAREN */
#line 157 "source/grammar.lemon"
{ yygotominor.yy29 = yymsp[-1].minor.yy29; }
#line 1083 "source/grammar.c"
        break;
      case 50: /* types ::= types COMMA type */
#line 160 "source/grammar.lemon"
{ yygotominor.yy51 = yymsp[-2].minor.yy51; yymsp[-2].minor.yy51->push_back(yymsp[0].minor.yy29); }
#line 1088 "source/grammar.c"
        break;
      case 51: /* types ::= type */
#line 161 "source/grammar.lemon"
{ yygotominor.yy51 = new std::deque<Type*>; yygotominor.yy51->push_back(yymsp[0].minor.yy29); }
#line 1093 "source/grammar.c"
        break;
      default:
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 34 "source/grammar.lemon"
 fprintf(stderr, "Parser is lost.\n"); 
#line 1143 "source/grammar.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 33 "source/grammar.lemon"
 fprintf(stderr, "Syntax error at char #%d.\n", parsetree->source_location); 
#line 1160 "source/grammar.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
