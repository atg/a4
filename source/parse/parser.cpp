#import "parse/parser.hpp"
#import "parse/grammar.hpp"
#import "parse/tokenizer.hpp"

// Parse numbers and strings
Expr* parseNumber(std::string number) {
    return new NumberExpr(number, false, 42, 0);
}
Expr* parseString(std::string str) {
    return new StringExpr(str, "<placeholder>");
}

// Token cleaning. Get rid of consecutive newlines, etc
std::deque<Token> clean(const std::deque<Token>& tokens) {
    std::deque<Token> newTokens(tokens);
    
    // Remove newlines at the end
    while (newTokens.size()) {
        if (newTokens.back().type == NEWLINE)
            newTokens.pop_back();
        else
            break;
    }
    
    return newTokens;
}

ParseTree parse(const std::deque<Token>& tokens) {
    
    //Set up lemon
    void* lemon = ParseAlloc(malloc);
    // ParseTrace(stderr, (char*)"");
    
    //Output
    ParseTree parsetree;
    
    for (Token token : tokens) {
        // printf("    Token %d at %d\n", token.type, token.location);
        parsetree.source_location = token.location;
        Parse(lemon, token.type, token, &parsetree);
    }
    
    //End lemon
    Token eoftoken;
    Parse(lemon, 0, eoftoken, &parsetree);
    ParseFree(lemon, free);
    
    return parsetree;
}
