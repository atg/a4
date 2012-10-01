// Untyped semantic analysis
// This stage checks the parse tree for validity, in preparation for type inference
// It finds simple errors that do not require type information, so that the compiler can exit faster if there is an error.
// It also prevents the type checker from crashing if something weird happens

#import "ast/ast.hpp"
#import "analysis/diagnostics.hpp"

%generate Expr
%call precheck($$, scope, diags)
%template void precheck($$, Scope& scope, DiagnosticContext& diags)
Binary expr
    // (nothing to do here)
Unary expr
    // (nothing to do here)
Member expr
    // (nothing to do here)
Is expr
    // (nothing to do here)
Call expr
    // (nothing to do here)
Subscript expr
    // (nothing to do here)
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
    // (nothing to do here)
List expr
    // (nothing to do here)
Dict expr
    // Check for duplicate keys
    std::unordered_multiset<std::string&> keynames;
    for (ExprPair& pair : expr.kvpairs) {
        if (pair.first->kind == Expr::Kind::String) {
            const std::string& k = pair.first->value;
            keynames.insert(k);
            
            if (keynames.count(k) == 2) {
                auto diag = Diagnostic(fmt("Duplicate key '" << k << "' in dictionary."));
                diag.populateFrom(expr);
                diags.push(diag);
            }
        }
    }

Function expr
    // (nothing to do here)
Tuple expr
    // Check that the tuple has at least two values
    if (expr.items.size() < 2) {
        auto diag = Diagnostic(fmt("Tuples must have at least two values."));
        diag.populateFrom(expr);
        diags.push(diag);
    }
    
Bool expr
    // (nothing to do here)
%end
