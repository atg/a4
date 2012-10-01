#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import "parse/tokenizer.hpp"

struct Decl;
struct Expr;
struct FunctionType;

struct ParseTree {
    // For diagnostic reporting
    int source_location;
    
    std::deque<Decl*> decls;
};

enum class DeclType {
    Unspecified = 0,
    Function,
};
struct Decl {
    DeclType type;
};

struct FunctionDecl : public Decl {
    // FunctionType* signature;
    std::string name;
    std::deque<std::string> parameters;
    Expr* body;

    FunctionDecl(std::string name, std::deque<std::string>* parametersptr, Expr* body) : name(name), body(body), parameters(*parametersptr) {
        type = DeclType::Function;
    }
};
