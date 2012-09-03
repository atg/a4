Type* type_of(Expr*) {
    
}
Type* common_type_of(std::deque<Expr*> exprs) {
    
}

Type* type_of(UnaryExpr* expr) {
    switch (expr.type) {
        case OperatorType::LogicalAnd:
        case OperatorType::LogicalOr:
            return new NamedType("Bool");

        case OperatorType::In:
            // Check that this even makes sense
            return new NamedType("Bool");
        
        case OperatorType::Equals:
        case OperatorType::NotEqual:
            // Check that the objects are of compatiable type
            return new NamedType("Bool");
        
        case OperatorType::LessThan:
        case OperatorType::GreaterThan:
        case OperatorType::LessOrEqual:
        case OperatorType::GreaterOrEqual:
            // Check that the objects are comparable
            return new NamedType("Bool");
        
        case OperatorType::Add:
            // Check that the objects are addable
            return ...;
        case OperatorType::Subtract:
            // Check that the objects are subtractable
            return ...;
        
        case OperatorType::Multiply:
            // Check that the objects can be multiplied
            return ...;
        case OperatorType::Divide:
            // Check that the objects can be divided
            return ...;
        case OperatorType::Mod:
            // Check that the objects can be modulo'd
            return ...;
        
        case OperatorType::Power:
            // Check that the objects can be taken to a power
            return ...;
        
        default:
            assert(0 && "Unknown BinaryExpr type in type_of");
    }
}
Type* type_of(UnaryExpr* expr) {
    if (expr.type == OperatorType::Negate) {
        // Check that the argument is negatable
        
        // This is obviously of the same type
        return type_of(expr.expr);
    }
    else if (expr.type == OperatorType::LogicalNot) {
        // Logical not can be applied to any type
        return new NamedType("Bool");
    }
    else {
        assert(0 && "Unknown UnaryExpr type in type_of");
    }
}
Type* type_of(CallExpr* call, Scope* scope) {
    // Find the relevant call for target
    std::deque<Decl*> candidates;
    
    
    // 1. Find all functions with call->name
    for (Decl* decl : scope.find(call->name)) {
        if (decl.type != DeclType::Function)
            continue;
        
        // 2. Ignore any functions with the wrong number of arguments
        
    }
    
    // 3. Find the types of the arguments given to the call
    // 4. Find functions whose arguments match the call
    // 5. Remove any functions whose argument types differ from another candidate only by being more generic (e.g. (A, B, Int) vs (A, String, Int) )
    // 6. If there is not EXACTLY ONE candidate at this point, then error.
    
}
Type* type_of(SubscriptExpr* subscript) {
    Type* target_type = type_of(target);
    Type* value_type = type_of(value);
    
    // If target_type is a list
    if (type_is_list(target_type)) {
        // Make sure that the value_type is an int
        if (!type_is_int(value_type, true, true)) {
            // Error!
        }
        // If the type is optional or any then mark the SubscriptExpr as needing a test
        // if (type_is_optional(value_type) || type_is_any(value_type)) {
            // subscript->uses_slow_path(true);
        // }
        
        return static_cast<ListType*>(target_type)->
    }
}
Type* type_of(NumberLiteral* num) {
    if (num.exponent == 0)
        return new NamedType("Int");
    else
        return new NamedType("Real");
}
Type* type_of(StringLiteral* unused) {
    return new NamedType("String");
}
Type* type_of(ListLiteral* list) {
    return new ListType(common_type_of(list.items));
}
Type* type_of(DictLiteral* dict) {
    
}
Type* type_of(FunctionLiteral* function) {
    
}
Type* type_of(TupleLiteral* tuple) {
    std::deque types;
    for (Expr* e : tuple.items) {
        types.push_back(copy_pointer(type_of(e)));
    }
    return types;
}
Type* type_of(BoolLiteral* unused) {
    return new NamedType("Bool"); // That was easy
}


bool type_is_list(Type* t, bool allow_optional=true, bool allow_any=true) {
    // Either equal to NamedType("List") or is of TypeType::List
}
bool type_is_generic(Type* t) {
    // Generic types are either variables or Any
}

