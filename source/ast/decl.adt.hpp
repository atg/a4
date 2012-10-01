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

%data Decl

function (
    std::string name,
    std::vector<std::string> parameters,
    Expr body)

constant (
    std::string name,
    Expr body
)

%end
