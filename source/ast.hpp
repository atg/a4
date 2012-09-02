#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import "tokenizer.hpp"

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
      : furrow_class(furclass), sign(s), coefficient(c), exponent(e) {
          type = ExprType::Number;
      }
    
    static NumberLiteral* parse(Token tok) {
        
        
        bool s = false;
        // TODO: Support non-ints (exponent != 0)
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
