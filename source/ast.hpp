#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import "tokenizer.hpp"

struct Expr;
struct Decl;

struct ParseTree {
    std::deque<Decl*> decls;
};

enum class ExprType {
    Unspecified = 0,
    Call,
    Subscript,
    Member,
    Binary,
    Unary,
    Number,
    String,
    List,
    Dict,
    Function,
    Tuple,
    Bool,
};
enum class DeclType {
    Unspecified = 0,
    Function,
};
enum class OperatorType {
    
    LogicalAnd = ANDAND,
    LogicalOr = BARBAR,
    
    In = IN,
    Is = IS,
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
    
    Negate = 1000,
    LogicalNot = EXCLAIM,
    
    Power = STARSTAR,
};

struct Decl {
    DeclType type;
};

struct FunctionDecl : public Decl {
    std::string name;
    std::deque<std::string> parameters;
    Expr* body;

    FunctionDecl(std::string name, std::deque<std::string>* parametersptr, Expr* body) : name(name), body(body), parameters(*parametersptr) {
        type = DeclType::Function;
    }
};


struct Expr {
    ExprType type;
};

// Represent a decimal number as (sign * coefficient * 10 ^ exponent)
struct NumberLiteral : public Expr {
    std::string furrow_class;
    
    bool sign;
    uint64_t coefficient;
    uint64_t exponent;
    
    NumberLiteral(std::string furclass, bool s, uint64_t c, uint64_t e)
      : furrow_class(furclass), sign(s), coefficient(c), exponent(e) {
          type = ExprType::Number;
      }
    
    static NumberLiteral* parse(Token tok) {
        // TODO: Support non-ints (exponent != 0)
        bool s = false;
        if (tok.payloadStart[0] == '-') {
            s = true;
            tok.payloadStart++;
        }
        
        std::string str(tok.payloadStart, tok.payloadEnd);
        uint64_t coef = std::strtoull(str.c_str(), NULL, 10);
        
        return new NumberLiteral("Int", s, coef, 0);
    }
    
    std::string toString() {
        std::string str;
        if (sign) {
            str.push_back('-');
        }
        
        // TODO: Support non-ints (exponent != 0)
        assert(exponent == 0 && "Non-zero exponents in NumberLiteral::toString() are not yet supported.");
        str.resize(100);
        sprintf(&str[1], "%llu", coefficient);
        
        return str;
    }
};

struct BinaryExpr : public Expr {
    Expr* left;
    Expr* right;
    OperatorType op;
    
    BinaryExpr(Expr* a, OperatorType optype, Expr* b) : left(a), op(optype), right(b) {
        type = ExprType::Binary;
    }
};

struct UnaryExpr : public Expr {
    Expr* expr;
    OperatorType op;

    UnaryExpr(Expr* a, OperatorType optype) : expr(a), op(optype) {
        type = ExprType::Unary;
    }
};


struct MemberExpr : public Expr {
    Expr* target;
    std::string field;
    
    MemberExpr(Expr* a, std::string field) : target(a), field(field) {
        type = ExprType::Member;
    }
};

struct CallExpr : public Expr {
    Expr* target;
    std::deque<Expr*> arguments;
    
    CallExpr(Expr* target, std::deque<Expr*> arguments) : target(target), arguments(arguments) {
        type = ExprType::Call;
    }
};

struct SubscriptExpr : public Expr {
    Expr* target;
    Expr* value;

    SubscriptExpr(Expr* target, Expr* value) : target(target), value(value) {
        type = ExprType::Subscript;
    }
};

struct StringLiteral : public Expr {
    std::string value;
    
    StringLiteral(Token tok) {
        type = ExprType::String;
        
        // TODO: Parse tok
        
        /* Allowed escape sequences
            \\    Backslash
            \'    Single quote
            \"    Double quote
            \a    Bell or alert
            \b    Backspace
            \f    Formfeed
            \n    ASCII linefeed (regardless of platform)
            \r    ASCII carriage return (regardless of platform)
            \t    Tab
        */
        
    }
};

struct ListLiteral : public Expr {
    std::deque<Expr*> items;

    ListLiteral(std::deque<Expr*> items) : items(items) {
        type = ExprType::List;
    }
};

struct DictLiteral : public Expr {
    std::deque<std::pair<Expr*, Expr*> > kvpairs;

    DictLiteral(std::deque<std::pair<Expr*, Expr*> > kvpairs) : kvpairs(kvpairs) {
        type = ExprType::Dict;
    }
};

struct FunctionLiteral : public Expr {
    std::deque<std::string> parameters;
    Expr* body;
    
    FunctionLiteral(std::deque<std::string> parameters, Expr* body) : parameters(parameters), body(body) {
        type = ExprType::Function;
    }
};

struct TupleLiteral : public Expr {
    std::deque<Expr*> items;

    TupleLiteral(std::deque<Expr*> items) : items(items) {
        type = ExprType::Tuple;
    }
};

struct BoolLiteral : public Expr {
    bool value;

    BoolLiteral(bool value) : value(value) {
        type = ExprType::Bool;
    }
};


