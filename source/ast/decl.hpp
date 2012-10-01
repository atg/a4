#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import <vector>
#import "parse/tokenizer.hpp"

struct Expr;
struct Decl;

struct ParseTree {
    // For diagnostic reporting
    int source_location;
    
    std::vector<std::shared_ptr<Decl>> decls;
};

struct Decl {
    enum class Kind {
        Function,
        Constant,
    };
    Kind kind;
};
struct FunctionDecl : public Decl {
    std::string name;
    std::vector<std::string> parameters;
    std::unique_ptr<Expr> body_ptr;
    Expr& body() { return *body_ptr; }
    FunctionDecl(std::string _name, std::vector<std::string> _parameters, Expr* _body) : name(_name), parameters(_parameters), body_ptr(_body) { }
};
struct ConstantDecl : public Decl {
    std::string name;
    std::unique_ptr<Expr> body_ptr;
    Expr& body() { return *body_ptr; }
    ConstantDecl(std::string _name, Expr* _body) : name(_name), body_ptr(_body) { }
};
