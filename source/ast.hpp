#import <cassert>
#import "tokentypes.hpp"

struct Expr;

struct ParseTree {
    Expr* expr;
};

enum class ExprType {
    Unspecified = 0,
    Binary,
    Number,
};
enum class OperatorType {
    Add = ADD,
    Subtract = MINUS,
    Multiply = STAR,
    Divide = SLASH,
    Power = STARSTAR,
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
      : furrow_class(furclass), sign(s), coefficient(c), exponent(e) { }
    
    static NumberLiteral parse(Token tok) {
        
        // TODO: Support non-ints (exponent != 0)
        // TODO: Use something other than strtoul so that it does 64-bit always
        if (tok.payloadStart[0] == '-') {
            sign = true;
            tok.payloadStart++;
        }
        coefficient = strtoul(tok.payloadStart, tok.payloadEnd, 10);
    }
    
    std::string toString() {
        std::string str;
        if (sign) {
            str.push_back('-');
        }
        
        // TODO: Support non-ints (exponent != 0)
        assert(exponent == 0 && "Non-zero exponents in NumberLiteral::toString() are not yet supported.");
        
        str.reserve(100);
        sprintf(&str[1], "%llu", coefficient);
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
