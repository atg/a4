// Untyped semantic analysis
// This stage checks the parse tree for validity, in preparation for type inference
// It finds simple errors that do not require type information, so that the compiler can exit faster if there is an error.
// It also prevents the type checker from crashing if something weird happens

#import "ast/ast.hpp"
#import "analysis/diagnostics.hpp"

void precheck(Expr& expr, DiagnosticContext diags) {
    switch (expr.kind) {
      case Expr::Kind::Binary:
        precheck(static_cast<BinaryExpr&>(expr));
      case Expr::Kind::Unary:
        precheck(static_cast<UnaryExpr&>(expr));
      case Expr::Kind::Member:
        precheck(static_cast<MemberExpr&>(expr));
      case Expr::Kind::Is:
        precheck(static_cast<IsExpr&>(expr));
      case Expr::Kind::Call:
        precheck(static_cast<CallExpr&>(expr));
      case Expr::Kind::Subscript:
        precheck(static_cast<SubscriptExpr&>(expr));
      case Expr::Kind::Variable:
        precheck(static_cast<VariableExpr&>(expr));
      case Expr::Kind::String:
        precheck(static_cast<StringExpr&>(expr));
      case Expr::Kind::Number:
        precheck(static_cast<NumberExpr&>(expr));
      case Expr::Kind::List:
        precheck(static_cast<ListExpr&>(expr));
      case Expr::Kind::Dict:
        precheck(static_cast<DictExpr&>(expr));
      case Expr::Kind::Function:
        precheck(static_cast<FunctionExpr&>(expr));
      case Expr::Kind::Tuple:
        precheck(static_cast<TupleExpr&>(expr));
      case Expr::Kind::Bool:
        precheck(static_cast<BoolExpr&>(expr));
    }
}
void precheck(BinaryExpr& expr, DiagnosticContext diags){
}
void precheck(UnaryExpr& expr, DiagnosticContext diags){
}
void precheck(MemberExpr& expr, DiagnosticContext diags){
}
void precheck(IsExpr& expr, DiagnosticContext diags){
}
void precheck(CallExpr& expr, DiagnosticContext diags){
}
void precheck(SubscriptExpr& expr, DiagnosticContext diags){
}
void precheck(VariableExpr& expr, DiagnosticContext diags){
}
void precheck(StringExpr& expr, DiagnosticContext diags){
}
void precheck(NumberExpr& expr, DiagnosticContext diags){
}
void precheck(ListExpr& expr, DiagnosticContext diags){
}
void precheck(DictExpr& expr, DiagnosticContext diags){
}
void precheck(FunctionExpr& expr, DiagnosticContext diags){
}
void precheck(TupleExpr& expr, DiagnosticContext diags){
}
void precheck(BoolExpr& expr, DiagnosticContext diags){
}
