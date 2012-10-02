// Untyped semantic analysis
// This stage checks the parse tree for validity, in preparation for type inference
// It finds simple errors that do not require type information, so that the compiler can exit faster if there is an error.
// It also prevents the type checker from crashing if something weird happens

#import <unordered_set>
#import <sstream>

#import "ast/ast.hpp"
#import "analysis/diagnostics.hpp"
#import "analysis/scope.hpp"

%generate Expr
%call precheck($$, scope, diags)
%template void precheck($$, Scope& scope, DiagnosticContext& diags)
Binary expr
    // (nothing to do here)
    precheck(expr.left(), scope, diags);
    precheck(expr.right(), scope, diags);
Unary expr
    // (nothing to do here)
    precheck(expr.expr(), scope, diags);
Member expr
    // (nothing to do here)
    precheck(expr.target(), scope, diags);
Is expr
    // (nothing to do here)
    precheck(expr.expr(), scope, diags);
Call expr
    // (nothing to do here)
    precheck(expr.target(), scope, diags);
    for (const std::shared_ptr<Expr>& arg : expr.arguments) {
        precheck(*arg, scope, diags);
    }
Subscript expr
    // (nothing to do here)
    precheck(expr.target(), scope, diags);
    precheck(expr.value(), scope, diags);
Variable expr
    // Check that the variable actually exists in the scope
    if (!scope.resolve(expr.name)) {
        auto diag = Diagnostic(fmt("There is nothing called '" << expr.name << "'."));
        diag.populateFrom(expr);
        diags.push(diag);
    }
String expr
    // (nothing to do here)
Number expr
    // If the number is negative zero, then make it positive
    if (expr.sign && expr.coef == 0)
        expr.sign = false;
    
    // TODO: Check that the number is actually representable using a 64-bit integer (as either signed or unsigned)
    
List expr
    // (nothing to do here)
    for (const std::shared_ptr<Expr>& item : expr.items) {
        precheck(*item, scope, diags);
    }
Dict expr
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
    
Function expr
    // (nothing to do here)
    precheck(expr.body(), scope, diags);
    
Tuple expr
    // Check that the tuple has at least two values
    if (expr.items.size() < 2) {
        auto diag = Diagnostic(fmt("Tuples must have at least two values."));
        diag.populateFrom(expr);
        diags.push(diag);
    }
    
    for (const std::shared_ptr<Expr>& item : expr.items) {
        precheck(*item, scope, diags);
    }
Bool expr
    // (nothing to do here)
%end
