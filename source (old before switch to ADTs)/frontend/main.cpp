#import <deque>
#import <string>

#import <fstream>
#import <cstdlib>
#import <cstdio>

#import "ast/ast.hpp"
#import "parse/tokenizer.hpp"
#import "parse/parser.hpp"
#import "codegen/codegen.hpp"

// It pains me to do this
#import <iostream>

const char * const FURROW_VERSION = "0.1";

void help() {
    fprintf(stderr, "Furrow. A minimalist language. Version %s\n", FURROW_VERSION);
    fprintf(stderr, "  fur <inputfile.fur>\n");
}

int main(int argc, char *argv[]) {
    
    std::ios_base::sync_with_stdio(false);
    
    if (argc < 2) {
        help();
        return 0;
    }
    
    // Read a file from argv[1]
    std::ifstream f(argv[1], std::ifstream::in);
    std::string content((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    
    // Tokenize it
    std::deque<Token> tokens = tokenize(content);
    
    // Parse it
    ParseTree parsetree = parse(clean(tokens));
    
    // Codegen
    codegen(parsetree, std::cout);
    
    return 0;
}

