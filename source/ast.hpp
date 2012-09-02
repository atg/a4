#import "tokentypes.hpp"

struct Expr;

struct ParseTree {
    Expr* expr;
};

enum class ExprType {
    Unspecified = 0,
    Binary,
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
struct BinaryExpr : public Expr {
    Expr* left;
    Expr* right;
    OperatorType op;
    
    BinaryExpr(Expr* a, OperatorType optype, Expr* b) : left(a), op(optype), right(b) {
        type = ExprType::Binary;
    }
};
