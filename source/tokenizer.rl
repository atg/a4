#import <deque>
#import "tokenizer.hpp"

#define EMIT(t) \
  Token tok; \
  tok.type = t; \
  tok.payloadStart = ts; \
  tok.payloadEnd = te; \
  tok.location = ts - data; \
  tokens.push_back(tok);

%%{

machine Tokenizer;
write data;

main := |*
    
    ("\r\n" | "\n" | "\r")+ { EMIT(NEWLINE); };
    
    "+" { EMIT(ADD); };
    "-" { EMIT(MINUS); };
    "*" { EMIT(STAR); };
    "/" { EMIT(SLASH); };
    "**" { EMIT(STARSTAR); };
    
    "==" { EMIT(EQEQ); };
    "!=" { EMIT(EXCLAIMEQ); };
    "<" { EMIT(LT); };
    ">" { EMIT(LT); };
    "<=" { EMIT(LTEQ); };
    ">=" { EMIT(GTEQ); };
    
    "&&" { EMIT(ANDAND); };
    "||" { EMIT(BARBAR); };
    
    "(" { EMIT(LPAREN); };
    ")" { EMIT(RPAREN); };
    "[" { EMIT(LSQUARE); };
    "]" { EMIT(RSQUARE); };
    "{" { EMIT(LCURLY); };
    "}" { EMIT(RCURLY); };
    "=" { EMIT(EQ); };
    "," { EMIT(COMMA); };
    "." { EMIT(DOT); };
    ":" { EMIT(COLON); };
        
    "mod" { EMIT(MOD); };
    "is" { EMIT(IS); };
    "in" { EMIT(IN); };
    
    "!" { EMIT(EXCLAIM); };
    
    "yes" | "true" { EMIT(YES); };
    "no" | "false" { EMIT(NO); };
    
    "=>" { EMIT(FATARROW); };
    "->" { EMIT(ARROW); };
    "?" { EMIT(QUESTIONMARK); };
    
    "-"? digit+ { EMIT(NUMBER); };
    
    # [A-Z_][A-Z0-9_]* { EMIT(UPPERIDENT); };
    [a-z_][a-zA-Z0-9_]* { EMIT(IDENT); };
    [A-Z_][a-zA-Z0-9_]* { EMIT(TITLEIDENT); };    
    
    # Ignore whitespace
    space+ { };
*|;

}%%

std::deque<Token> tokenize(const std::string& content) {
    
    std::deque<Token> tokens;
    
    //Get string data
    char* data = const_cast<char*>(&(content[0]));
    size_t len = content.size();
    
    //Start
    char* p = data;
    
    //End
    char* pe = p + len;
    char* eof = pe;
    
    //State
    int cs = 0, act = 0, have = 0, curline = 1;
    char *ts, *te = 0;
    int done = 0;
    
    //Run the machine
    %% write init;
    %% write exec;
    
    //Return the output
    return tokens;
}
