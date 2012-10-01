#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import <vector>
#import "parse/tokenizer.hpp"

struct Type;
using ExprPair = std::pair<std::shared_ptr<Expr>, std::shared_ptr<Expr>>;

enum class BinaryOperator {
    LogicalAnd = ANDAND,
    LogicalOr = BARBAR,
    
    In = IN,
    Equals = EQ,
    NotEqual = EXCLAIMEQ,
    LessThan = LT,
    GreaterThan = GT,
    LessOrEqual = LTEQ,
    GreaterOrEqual = GTEQ,
    
    Add = ADD,
    Subtract = MINUS,
    
    Multiply = STAR,
    Divide = SLASH,
    Mod = MOD,
    
    Power = STARSTAR,
};
enum class UnaryOperator {
    Negate = 1000,
    LogicalNot = EXCLAIM,
};

%data Expr

binary    (BinaryOperator op,    Expr left,    Expr right)
unary     (UnaryOperator op,     Expr body)
member    (Expr target,          std::string field)
is        (Expr expr,            Type oftype)
call      (Expr target,          std::vector<std::shared_ptr<Expr>> arguments)
subscript (Expr target,          Expr value)
variable  (std::string name)
string    (std::string value)
list      (std::vector<std::shared_ptr<Expr>> items)
dict      (std::vector<ExprPair> kvpairs)
function  (std::vector<std::string> parameters)
tuple     (std::vector<std::shared_ptr<Expr>> items)
bool      (bool value)

%end
