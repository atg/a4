#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import <vector>
#import "parse/tokenizer.hpp"

struct Type;
struct Expr;
using ExprPair = std::pair<std::shared_ptr<Expr>, std::shared_ptr<Expr>>;

Expr* parseNumber(std::string number);
Expr* parseString(std::string str);

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
        Number,
        List,
        Dict,
        Function,
        Tuple,
        Bool,
    };
    Kind kind;
};
struct BinaryExpr : public Expr {
    std::shared_ptr<Expr> left_ptr;
    Expr& left() { return *left_ptr; }
    BinaryOperator op;
    std::shared_ptr<Expr> right_ptr;
    Expr& right() { return *right_ptr; }
    BinaryExpr(Expr* _left, BinaryOperator _op, Expr* _right) : left_ptr(_left), op(_op), right_ptr(_right) { }
};
struct UnaryExpr : public Expr {
    std::shared_ptr<Expr> expr_ptr;
    Expr& expr() { return *expr_ptr; }
    UnaryOperator op;
    UnaryExpr(Expr* _expr, UnaryOperator _op) : expr_ptr(_expr), op(_op) { }
};
struct MemberExpr : public Expr {
    std::shared_ptr<Expr> target_ptr;
    Expr& target() { return *target_ptr; }
    std::string field;
    MemberExpr(Expr* _target, std::string _field) : target_ptr(_target), field(_field) { }
};
struct IsExpr : public Expr {
    std::shared_ptr<Expr> expr_ptr;
    Expr& expr() { return *expr_ptr; }
    std::shared_ptr<Type> oftype_ptr;
    Type& oftype() { return *oftype_ptr; }
    IsExpr(Expr* _expr, Type* _oftype) : expr_ptr(_expr), oftype_ptr(_oftype) { }
};
struct CallExpr : public Expr {
    std::shared_ptr<Expr> target_ptr;
    Expr& target() { return *target_ptr; }
    std::vector<std::shared_ptr<Expr>> arguments;
    CallExpr(Expr* _target, std::vector<std::shared_ptr<Expr>> _arguments) : target_ptr(_target), arguments(_arguments) { }
};
struct SubscriptExpr : public Expr {
    std::shared_ptr<Expr> target_ptr;
    Expr& target() { return *target_ptr; }
    std::shared_ptr<Expr> value_ptr;
    Expr& value() { return *value_ptr; }
    SubscriptExpr(Expr* _target, Expr* _value) : target_ptr(_target), value_ptr(_value) { }
};
struct VariableExpr : public Expr {
    std::string name;
    VariableExpr(std::string _name) : name(_name) { }
};
struct StringExpr : public Expr {
    std::string src;
    std::string value;
    StringExpr(std::string _src, std::string _value) : src(_src), value(_value) { }
};
struct NumberExpr : public Expr {
    std::string src;
    bool sign;
    uint64_t coef;
    uint64_t exponent;
    NumberExpr(std::string _src, bool _sign, uint64_t _coef, uint64_t _exponent) : src(_src), sign(_sign), coef(_coef), exponent(_exponent) { }
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
    std::shared_ptr<Expr> body_ptr;
    Expr& body() { return *body_ptr; }
    FunctionExpr(std::vector<std::string> _parameters, Expr* _body) : parameters(_parameters), body_ptr(_body) { }
};
struct TupleExpr : public Expr {
    std::vector<std::shared_ptr<Expr>> items;
    TupleExpr(std::vector<std::shared_ptr<Expr>> _items) : items(_items) { }
};
struct BoolExpr : public Expr {
    bool value;
    BoolExpr(bool _value) : value(_value) { }
};
