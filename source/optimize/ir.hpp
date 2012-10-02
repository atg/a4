namespace ir {

struct IR;
struct Literal;
struct Type;

using LetBinding = std::pair<uint64_t, std::shared_ptr<IR>>;

struct IR {
    enum class Kind {
        Var,
        Lit,
        Tuple,
        App,
        Let,
    };
    Kind kind;
    std::shared_ptr<Type> type_ptr;
    Type& type() { return *type_ptr; }
};
struct VarIR : public IR {
    uint64_t id;
    VarIR(Type* _type, uint64_t _id) : type_ptr(_type), id(_id) { }
};
struct LitIR : public IR {
    std::shared_ptr<Literal> value_ptr;
    Literal& value() { return *value_ptr; }
    LitIR(Type* _type, Literal* _value) : type_ptr(_type), value_ptr(_value) { }
};
struct TupleIR : public IR {
    std::vector<std::shared_ptr<IR>> items;
    TupleIR(Type* _type, std::vector<std::shared_ptr<IR>> _items) : type_ptr(_type), items(_items) { }
};
struct AppIR : public IR {
    Exp target;
    Exp arg;
    AppIR(Type* _type, Exp _target, Exp _arg) : type_ptr(_type), target(_target), arg(_arg) { }
};
struct LetIR : public IR {
    std::vector<LetBinding> bindings;
    LetIR(Type* _type, std::vector<LetBinding> _bindings) : type_ptr(_type), bindings(_bindings) { }
};

struct Literal {
    enum class Kind {
        Int,
        Real,
        Bool,
        String,
    };
    Kind kind;
};
struct IntLiteral : public Literal {
    bool sign;
    uint64_t coef;
    IntLiteral(bool _sign, uint64_t _coef) : sign(_sign), coef(_coef) { }
};
struct RealLiteral : public Literal {
    bool sign;
    uint64_t coef;
    uint64_t exponent;
    RealLiteral(bool _sign, uint64_t _coef, uint64_t _exponent) : sign(_sign), coef(_coef), exponent(_exponent) { }
};
struct BoolLiteral : public Literal {
    bool value;
    BoolLiteral(bool _value) : value(_value) { }
};
struct StringLiteral : public Literal {
    std::string value;
    StringLiteral(std::string _value) : value(_value) { }
};

struct Type {
    enum class Kind {
        Named,
        App,
    };
    Kind kind;
};
struct NamedType : public Type {
    std::string name;
    NamedType(std::string _name) : name(_name) { }
};
struct AppType : public Type {
    std::shared_ptr<Type> target_ptr;
    Type& target() { return *target_ptr; }
    std::shared_ptr<Type> arg_ptr;
    Type& arg() { return *arg_ptr; }
    AppType(Type* _target, Type* _arg) : target_ptr(_target), arg_ptr(_arg) { }
};

};

