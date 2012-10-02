#if 0
void inference(Expr& expr, Scope& scope, DiagnosticContext& diags) {
    switch (expr.kind) {
      case Expr::Kind::Binary:
        inference(static_cast<BinaryExpr&>(expr), scope, diags);
      case Expr::Kind::Unary:
        inference(static_cast<UnaryExpr&>(expr), scope, diags);
      case Expr::Kind::Member:
        inference(static_cast<MemberExpr&>(expr), scope, diags);
      case Expr::Kind::Is:
        inference(static_cast<IsExpr&>(expr), scope, diags);
      case Expr::Kind::Call:
        inference(static_cast<CallExpr&>(expr), scope, diags);
      case Expr::Kind::Subscript:
        inference(static_cast<SubscriptExpr&>(expr), scope, diags);
      case Expr::Kind::Variable:
        inference(static_cast<VariableExpr&>(expr), scope, diags);
      case Expr::Kind::String:
        inference(static_cast<StringExpr&>(expr), scope, diags);
      case Expr::Kind::Number:
        inference(static_cast<NumberExpr&>(expr), scope, diags);
      case Expr::Kind::List:
        inference(static_cast<ListExpr&>(expr), scope, diags);
      case Expr::Kind::Dict:
        inference(static_cast<DictExpr&>(expr), scope, diags);
      case Expr::Kind::Function:
        inference(static_cast<FunctionExpr&>(expr), scope, diags);
      case Expr::Kind::Tuple:
        inference(static_cast<TupleExpr&>(expr), scope, diags);
      case Expr::Kind::Bool:
        inference(static_cast<BoolExpr&>(expr), scope, diags);
    }
}
void inference(BinaryExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.left, scope, diags);
    inference(expr.right, scope, diags);
}
void inference(UnaryExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.expr, scope, diags);
}
void inference(MemberExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.target, scope, diags);
}
void inference(IsExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.expr, scope, diags);
    inference(expr.oftype, scope, diags);
}
void inference(CallExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.target, scope, diags);
    for (const std::shared_ptr<Expr>& arg : expr.arguments) {
        inference(*arg, scope, diags);
    }
}
void inference(SubscriptExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.target, scope, diags);
    inference(expr.value, scope, diags);
}
void inference(VariableExpr& expr, Scope& scope, DiagnosticContext& diags){
    // Check that the variable actually exists in the scope
    if (!scope.resolve(expr.name)) {
        auto diag = Diagnostic(fmt("There is nothing called '" << expr.name << "'."));
        diag.populateFrom(expr);
        diags.push(diag);
    }
}
void inference(StringExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
}
void inference(NumberExpr& expr, Scope& scope, DiagnosticContext& diags){
    // If the number is negative zero, then make it positive
    if (expr.sign && expr.coef == 0)
        expr.sign = false;

    // TODO: Check that the number is actually representable using a 64-bit integer (as either signed or unsigned)

}
void inference(ListExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    for (const std::shared_ptr<Expr>& item : expr.items) {
        inference(*item, scope, diags);
    }
}
void inference(DictExpr& expr, Scope& scope, DiagnosticContext& diags){
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

}
void inference(FunctionExpr& expr, Scope& scope, DiagnosticContext& diags){
    // (nothing to do here)
    inference(expr.body, scope, diags);

}
void inference(TupleExpr& expr, Scope& scope, DiagnosticContext& diags){
    expr.type.reset(new TupleType());
    for (const std::shared_ptr<Expr>& item : expr.items) {
        inference(*item, scope, diags);
        expr.type->push_back(std::shared_ptr(item->type));
    }
}
void inference(BoolExpr& expr, Scope& scope, DiagnosticContext& diags){
    expr.type.reset(new NamedType("Bool"));
}

#endif