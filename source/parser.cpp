#import "parser.hpp"
#import "grammar.hpp"
#import "tokenizer.hpp"

// Token cleaning. Get rid of consecutive newlines, etc
std::deque<Token> clean(const std::deque<Token>& tokens) {
    std::deque<Token> newTokens(tokens);
    // newTokens.resize(tokens.size());
    
    // Get rid of consecutive newlines
    /*
    bool lastWasNewline = false;
    for (Token token : tokens) {
        printf("Is newline? %d (%d) %d\n", token.type == NEWLINE, lastWasNewline, token.type);
        if (token.type == NEWLINE) {
            if (lastWasNewline)
                continue; // Ignore
            lastWasNewline = true;
        }
        else {
            lastWasNewline = false;
        }
        printf("Was newline? %d (%d) %d\n", token.type == NEWLINE, lastWasNewline, token.type);
        newTokens.push_back(token);
    }
    */
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
