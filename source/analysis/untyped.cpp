// Untyped semantic analysis
// This stage checks the parse tree for validity, in preparation for type inference
// It finds simple errors that do not require type information, so that the compiler can exit faster if there is an error.
// It also prevents the type checker from crashing if something weird happens

#import <unordered_set>
#import <sstream>

#import "ast/ast.hpp"
#import "analysis/diagnostics.hpp"
#import "analysis/scope.hpp"

void precheck(Expr& expr, Scope& scope, DiagnosticContext& diags) {
    switch (expr.kind) {
      case Expr::Kind::Binary:
        precheck(static_cast<BinaryExpr&>(expr), scope, diags);
      case Expr::Kind::Unary:
        precheck(static_cast<UnaryExpr&>(expr), scope, diags);
      case Expr::Kind::Member:
        precheck(static_cast<MemberExpr&>(expr), scope, diags);
      case Expr::Kind::Is:
        precheck(static_cast<IsExpr&>(expr), scope, diags);
      case Expr::Kind::Call:
        precheck(static_cast<CallExpr&>(expr), scope, diags);
      case Expr::Kind::Subscript:
        precheck(static_cast<SubscriptExpr&>(expr), scope, diags);
      case Expr::Kind::Variable:
        precheck(static_cast<VariableExpr&>(expr), scope, diags);
      case Expr::Kind::String:
        precheck(static_cast<StringExpr&>(expr), scope, diags);
      case Expr::Kind::Number:
        precheck(static_cast<NumberExpr&>(expr), scope, diags);
      case Expr::Kind::List:
        precheck(static_cast<ListExpr&>(expr), scope, diags);
      case Expr::Kind::Dict:
        precheck(static_cast<DictExpr&>(expr), scope, diags);
      case Expr::Kind::Function:
        precheck(static_cast<FunctionExpr&>(expr), scope, diags);
      case Expr::Kind::Tuple:
        precheck(static_cast<TupleExpr&>(expr), scope, diags);
      case Expr::Kind::Bool:
        precheck(static_cast<BoolExpr&>(expr), scope, diags);
    }
}
void precheck(BinaryExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.left(), scope, diags);
    precheck(expr.right(), scope, diags);
}
void precheck(UnaryExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.expr(), scope, diags);
}
void precheck(MemberExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.target(), scope, diags);
}
void precheck(IsExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.expr(), scope, diags);
}
void precheck(CallExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.target(), scope, diags);
    for (const std::shared_ptr<Expr>& arg : expr.arguments) {
        precheck(*arg, scope, diags);
    }
}
void precheck(SubscriptExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.target(), scope, diags);
    precheck(expr.value(), scope, diags);
}
void precheck(VariableExpr& expr, Scope& scope, DiagnosticContext& diags){
    // Check that the variable actually exists in the scope
    if (!scope.resolve(expr.name)) {
        auto diag = Diagnostic(fmt("There is nothing called '" << expr.name << "'."));
        diag.populateFrom(expr);
        diags.push(diag);
    }
}
void precheck(StringExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
}
void precheck(NumberExpr& expr, Scope& scope, DiagnosticContext& diags){
    // If the number is negative zero, then make it positive
    if (expr.sign && expr.coef == 0)
        expr.sign = false;
    
    // TODO: Check that the number is actually representable using a 64-bit integer (as either signed or unsigned)
    
}
void precheck(ListExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    for (const std::shared_ptr<Expr>& item : expr.items) {
        precheck(*item, scope, diags);
    }
}
void precheck(DictExpr& expr, Scope& scope, DiagnosticContext& diags){
    // Check for duplicate keys
    std::unordered_multiset<std::string> keynames;
    for (ExprPair& pair : expr.kvpairs) {
        if (pair.first->kind == Expr::Kind::String) {
            const std::string& k = static_cast<StringExpr&>(*pair.first).value;
            keynames.insert(k);
            
            if (keynames.count(k) == 2) {
                auto diag = Diagnostic(fmt("Duplicate key '" << k << "' in dictionary."));
                diag.populateFrom(expr);
                diags.push(diag);
            }
        }
    }
    
    for (const ExprPair& pair : expr.kvpairs) {
        precheck(pair.*first, scope, diags);
        precheck(pair.*second, scope, diags);
    }
    
}
void precheck(FunctionExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    precheck(expr.body(), scope, diags);
    
}
void precheck(TupleExpr& expr, Scope& scope, DiagnosticContext& diags){
    // Check that the tuple has at least two values
    if (expr.items.size() < 2) {
        auto diag = Diagnostic(fmt("Tuples must have at least two values."));
        diag.populateFrom(expr);
        diags.push(diag);
    }
    
    for (const std::shared_ptr<Expr>& item : expr.items) {
        precheck(*item, scope, diags);
    }
}
void precheck(BoolExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
}
