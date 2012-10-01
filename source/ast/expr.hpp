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

struct Expr {
    enum class Kind {
        Binary,
        Unary,
        Member,
        Is,
        Call,
        Subscript,
        Variable,
        String,
        List,
        Dict,
        Function,
        Tuple,
        Bool,
    };
    Kind kind;
};
struct BinaryExpr : public Expr {
    BinaryOperator op;
    std::unique_ptr<Expr> left_ptr;
    Expr& left() { return *left_ptr; }
    std::unique_ptr<Expr> right_ptr;
    Expr& right() { return *right_ptr; }
    BinaryExpr(BinaryOperator _op, Expr* _left, Expr* _right) : op(_op), left_ptr(_left), right_ptr(_right) { }
};
struct UnaryExpr : public Expr {
    UnaryOperator op;
    std::unique_ptr<Expr> body_ptr;
    Expr& body() { return *body_ptr; }
    UnaryExpr(UnaryOperator _op, Expr* _body) : op(_op), body_ptr(_body) { }
};
struct MemberExpr : public Expr {
    std::unique_ptr<Expr> target_ptr;
    Expr& target() { return *target_ptr; }
    std::string field;
    MemberExpr(Expr* _target, std::string _field) : target_ptr(_target), field(_field) { }
};
struct IsExpr : public Expr {
    std::unique_ptr<Expr> expr_ptr;
    Expr& expr() { return *expr_ptr; }
    std::unique_ptr<Type> oftype_ptr;
    Type& oftype() { return *oftype_ptr; }
    IsExpr(Expr* _expr, Type* _oftype) : expr_ptr(_expr), oftype_ptr(_oftype) { }
};
struct CallExpr : public Expr {
    std::unique_ptr<Expr> target_ptr;
    Expr& target() { return *target_ptr; }
    std::vector<std::shared_ptr<Expr>> arguments;
    CallExpr(Expr* _target, std::vector<std::shared_ptr<Expr>> _arguments) : target_ptr(_target), arguments(_arguments) { }
};
struct SubscriptExpr : public Expr {
    std::unique_ptr<Expr> target_ptr;
    Expr& target() { return *target_ptr; }
    std::unique_ptr<Expr> value_ptr;
    Expr& value() { return *value_ptr; }
    SubscriptExpr(Expr* _target, Expr* _value) : target_ptr(_target), value_ptr(_value) { }
};
struct VariableExpr : public Expr {
    std::string name;
    VariableExpr(std::string _name) : name(_name) { }
};
struct StringExpr : public Expr {
    std::string value;
    StringExpr(std::string _value) : value(_value) { }
};
struct ListExpr : public Expr {
    std::vector<std::shared_ptr<Expr>> items;
    ListExpr(std::vector<std::shared_ptr<Expr>> _items) : items(_items) { }
};
struct DictExpr : public Expr {
    std::vector<ExprPair> kvpairs;
    DictExpr(std::vector<ExprPair> _kvpairs) : kvpairs(_kvpairs) { }
};
struct FunctionExpr : public Expr {
    std::vector<std::string> parameters;
    FunctionExpr(std::vector<std::string> _parameters) : parameters(_parameters) { }
};
struct TupleExpr : public Expr {
    std::vector<std::shared_ptr<Expr>> items;
    TupleExpr(std::vector<std::shared_ptr<Expr>> _items) : items(_items) { }
};
struct BoolExpr : public Expr {
    bool value;
    BoolExpr(bool _value) : value(_value) { }
};
