#import "parser.hpp"
#import "grammar.hpp"

ParseTree parse(const std::deque<Token>& tokens) {
    
    //Set up lemon
    void* lemon = ParseAlloc(malloc);
    
    //Output
    ParseTree parsetree;
    
    for (Token token : tokens) {
        Parse(lemon, token.type, token, &parsetree);
    }
    
    //End lemon
    Token eoftoken;
    Parse(lemon, 0, eoftoken, &parsetree);
    ParseFree(lemon, free);
    
    return parsetree;
}
