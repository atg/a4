#import <vector>

#define EMIT(t) \
  Token token; \
  token.type = t; \
  token.payloadStart = ts; \
  token.payloadEnd = te; \

%%{

machine Tokenizer;
write data;

main := |*
    
    "+" { EMIT(PLUS); };
    "-" { EMIT(MINUS); };
    "*" { EMIT(STAR); };
    "/" { EMIT(SLASH); };
    "**" { EMIT(STARSTAR); };
    
    # Ignore whitespace
    space+ { };
*|;

}%%


std::deque<Token> tokenize(const std::string& content)
{
    //Get string data
    char* data = &(content[0]);
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
    return output;
}
