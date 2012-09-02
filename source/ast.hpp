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
struct BinaryExpr : Expr {
    Expr* left;
    Expr* right;
    OperatorType op;
    
    BinaryExpr(Expr* a, OperatorType optype, Expr* b) : type(Binary), left(a), op(optype), right(b) { }
};
