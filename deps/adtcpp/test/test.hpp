struct Expr {
    enum class Kind {
        Add,
        Subtract,
        Multiply,
        Divide,
        Negate,
        Constant,
    };
    Kind kind;
};
struct AddExpr : public Expr {
    std::unique_ptr<Expr> left_ptr;
    Expr& left() { return *left_ptr; }
    std::unique_ptr<Expr> right_ptr;
    Expr& right() { return *right_ptr; }
    AddExpr(Expr* _left, Expr* _right) : left_ptr(_left), right_ptr(_right) { }
};
struct SubtractExpr : public Expr {
    std::unique_ptr<Expr> left_ptr;
    Expr& left() { return *left_ptr; }
    std::unique_ptr<Expr> right_ptr;
    Expr& right() { return *right_ptr; }
    SubtractExpr(Expr* _left, Expr* _right) : left_ptr(_left), right_ptr(_right) { }
};
struct MultiplyExpr : public Expr {
    std::unique_ptr<Expr> left_ptr;
    Expr& left() { return *left_ptr; }
    std::unique_ptr<Expr> right_ptr;
    Expr& right() { return *right_ptr; }
    MultiplyExpr(Expr* _left, Expr* _right) : left_ptr(_left), right_ptr(_right) { }
};
struct DivideExpr : public Expr {
    std::unique_ptr<Expr> left_ptr;
    Expr& left() { return *left_ptr; }
    std::unique_ptr<Expr> right_ptr;
    Expr& right() { return *right_ptr; }
    DivideExpr(Expr* _left, Expr* _right) : left_ptr(_left), right_ptr(_right) { }
};
struct NegateExpr : public Expr {
    std::unique_ptr<Expr> expr_ptr;
    Expr& expr() { return *expr_ptr; }
    NegateExpr(Expr* _expr) : expr_ptr(_expr) { }
};
struct ConstantExpr : public Expr {
    int value;
    ConstantExpr(int _value) : value(_value) { }
};

int evaluate(Expr& expr){
    switch (expr.kind) {
      case Expr::Kind::Add:
        return evaluate(static_cast<AddExpr&>(expr));
      case Expr::Kind::Subtract:
        return evaluate(static_cast<SubtractExpr&>(expr));
      case Expr::Kind::Multiply:
        return evaluate(static_cast<MultiplyExpr&>(expr));
      case Expr::Kind::Divide:
        return evaluate(static_cast<DivideExpr&>(expr));
      case Expr::Kind::Negate:
        return evaluate(static_cast<NegateExpr&>(expr));
      case Expr::Kind::Constant:
        return evaluate(static_cast<ConstantExpr&>(expr));
    }
}
int evaluate(AddExpr& expr){
    return evaluate(expr.left()) + evaluate(expr.right());
}
int evaluate(SubtractExpr& expr){
    return evaluate(expr.left()) - evaluate(expr.right());
}
int evaluate(MultiplyExpr& expr){
    return evaluate(expr.left()) * evaluate(expr.right());
}
int evaluate(DivideExpr& expr){
    return evaluate(expr.left()) / evaluate(expr.right());
}
int evaluate(NegateExpr& expr){
    return - evaluate(expr.expr());
}
int evaluate(ConstantExpr& expr){
    return expr.value;
}

int main() {
    
    
    
switch (expr.kind) {
  case Expr::Kind::Add: {
    Add& expr = static_cast<Add&>(expr);
            return evaluate(expr.left()) + evaluate(expr.right());
    break;
  }
  case Expr::Kind::Subtract: {
    Subtract& expr = static_cast<Subtract&>(expr);
            return evaluate(expr.left()) - evaluate(expr.right());
    break;
  }
  case Expr::Kind::Multiply: {
    Multiply& expr = static_cast<Multiply&>(expr);
            return evaluate(expr.left()) * evaluate(expr.right());
    break;
  }
  case Expr::Kind::Divide: {
    Divide& expr = static_cast<Divide&>(expr);
            return evaluate(expr.left()) / evaluate(expr.right());
    break;
  }
  case Expr::Kind::Negate: {
    Negate& expr = static_cast<Negate&>(expr);
            return - evaluate(expr.expr());
    break;
  }
  case Expr::Kind::Constant: {
    Constant& expr = static_cast<Constant&>(expr);
            return expr.value;
    break;
  }
}

}
