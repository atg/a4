void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  Token yyminor,               /* The value for the token */
  ParseTree* parsetree         /* Optional %extra_argument parameter */
);

void *ParseAlloc(void *(*mallocProc)(size_t));

void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
);

void ParseTrace(FILE *TraceFILE, char *zTracePrompt);
