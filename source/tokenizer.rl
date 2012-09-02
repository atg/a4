#import <deque>
#import "tokenizer.hpp"

#define EMIT(t) \
  Token tok; \
  tok.type = t; \
  tok.payloadStart = ts; \
  tok.payloadEnd = te; \
  tokens.push_back(tok);

%%{

machine Tokenizer;
write data;

main := |*
    
    "+" { EMIT(ADD); };
    "-" { EMIT(MINUS); };
    "*" { EMIT(STAR); };
    "/" { EMIT(SLASH); };
    "**" { EMIT(STARSTAR); };
    
    "-"? digit+ { EMIT(NUMBER); };
    
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
