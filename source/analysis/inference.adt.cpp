#if 0
%generate Expr
%call inference($$, scope, diags)
%template void inference($$, Scope& scope, DiagnosticContext& diags)
Binary expr
    // (nothing to do here)
    inference(expr.left, scope, diags);
    inference(expr.right, scope, diags);
Unary expr
    // (nothing to do here)
    inference(expr.expr, scope, diags);
Member expr
    // (nothing to do here)
    inference(expr.target, scope, diags);
Is expr
    // (nothing to do here)
    inference(expr.expr, scope, diags);
    inference(expr.oftype, scope, diags);
Call expr
    // (nothing to do here)
    inference(expr.target, scope, diags);
    for (const std::shared_ptr<Expr>& arg : expr.arguments) {
        inference(*arg, scope, diags);
    }
Subscript expr
    // (nothing to do here)
    inference(expr.target, scope, diags);
    inference(expr.value, scope, diags);
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
        inference(*item, scope, diags);
    }
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

    for (const ExprPair& pair : expr.kvpairs) {
        inference(pair.*first, scope, diags);
        inference(pair.*second, scope, diags);
    }

Function expr
    // (nothing to do here)
    inference(expr.body, scope, diags);

Tuple expr
    expr.type.reset(new TupleType());
    for (const std::shared_ptr<Expr>& item : expr.items) {
        inference(*item, scope, diags);
        expr.type->push_back(std::shared_ptr(item->type));
    }
Bool expr
    expr.type.reset(new NamedType("Bool"));
%end

#endif