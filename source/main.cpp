#import <fstream>
#import <cstdlib>
#import <cstdio>
#import "ast.hpp"

// It pains me to do this
#import <iostream>

const char * const FURROW_VERSION = "0.1";

void help() {
    fprintf(stderr, "Furrow. A minimalist language. Version %s", FURROW_VERSION);
    fprintf(stderr, "  fur <inputfile.fur>");
}

int main(int argc, char *argv[]) {
    
    std::ios_base::sync_with_stdio(false);
    
    if (argc < 2) {
        help();
        return 0;
    }
    
    // Read a file from argv[1]
    std::ifstream f(argv[1], std::ifstream::in);
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    
    // Tokenize it
    std::vector<Token> tokens = tokenize(content);
    
    // Parse it
    ParseTree parsetree = parse(tokens);
    
    // Codegen
    codegen(parsetree, std::cout);
    
    return 0;
}

