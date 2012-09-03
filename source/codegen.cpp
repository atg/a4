#import "codegen.hpp"

void codegen(ParseTree tree, std::ostream& out) {
    for (Decl* decl : tree.decls) {
        codegen(decl, out);
        out << '\n';
    }
}

void codegen(Decl* decl, std::ostream& out) {
    switch (decl->type) {
        case DeclType::Function:
            codegen(static_cast<FunctionDecl*>(decl), out);
            break;
        
        case DeclType::Unspecified: break;
    }
}

void codegen(FunctionDecl* decl, std::ostream& out) {    
    out << "static " << "RETURN_TYPE" << ' ' << decl->name << '(';
    
    // Arguments
    bool isFirst = true;
    for (const std::string& param : decl->parameters) {
        
        if (!isFirst)
            out << ", ";
        else
            isFirst = false;
        
        out << "PARAM_TYPE" << ' ' << param;
    }
    
    out << ") {\n";
    out << "    return ";
    codegen(decl->body, out);
    out << ";\n}";
}


void codegen(Expr* expr, std::ostream& out) {
    switch (expr->type) {
        case ExprType::Call:
            codegen(static_cast<CallExpr*>(expr), out);
            break;
        case ExprType::Subscript:
            codegen(static_cast<SubscriptExpr*>(expr), out);
            break;
        case ExprType::Member:
            codegen(static_cast<MemberExpr*>(expr), out);
            break;
        
        case ExprType::Binary:
            codegen(static_cast<BinaryExpr*>(expr), out);
            break;
        case ExprType::Unary:
            codegen(static_cast<UnaryExpr*>(expr), out);
            break;
        
        case ExprType::Number:
            codegen(static_cast<NumberLiteral*>(expr), out);
            break;
        case ExprType::String:
            codegen(static_cast<StringLiteral*>(expr), out);
            break;
        case ExprType::List:
            codegen(static_cast<ListLiteral*>(expr), out);
            break;
        case ExprType::Dict:
            codegen(static_cast<DictLiteral*>(expr), out);
            break;
        case ExprType::Function:
            codegen(static_cast<FunctionLiteral*>(expr), out);
            break;
        case ExprType::Tuple:
            codegen(static_cast<TupleLiteral*>(expr), out);
            break;
        case ExprType::Bool:
            codegen(static_cast<BoolLiteral*>(expr), out);
            break;
        
        case ExprType::Unspecified: break;
    }
}

void codegen(NumberLiteral* literal, std::ostream& out) {    
    out << (literal->toString());
}

void codegen(BinaryExpr* expr, std::ostream& out) {    
    out << '(';

    if (expr->op == OperatorType::Power || expr->op == OperatorType::In || expr->op == OperatorType::Is || expr->op == OperatorType::Mod) {
        
        if (expr->op == OperatorType::Power)
            out << "std::pow(";
        else if (expr->op == OperatorType::In)
            out << "furrow::contains(";
        else if (expr->op == OperatorType::Is)
            out << "furrow::isa(";
        else if (expr->op == OperatorType::Mod)
            out << "furrow::mod(";
        
        codegen(expr->left, out);
        out << ", ";
        codegen(expr->right, out);
        out << ')';

    }
    else {
        codegen(expr->left, out);
        out << ' ';

        #define CODEGEN_OPERATOR(type_name, opstr) case OperatorType::type_name: out << opstr; break;
        switch (expr->op) {
            CODEGEN_OPERATOR(LogicalAnd, "&&");
            CODEGEN_OPERATOR(LogicalOr, "||");
            
            CODEGEN_OPERATOR(Equals, "==");
            CODEGEN_OPERATOR(NotEqual, "!=");
            CODEGEN_OPERATOR(LessThan, '<');
            CODEGEN_OPERATOR(GreaterThan, '>');
            CODEGEN_OPERATOR(LessOrEqual, "<=");
            CODEGEN_OPERATOR(GreaterOrEqual, ">=");
            
            CODEGEN_OPERATOR(Add, '+');
            CODEGEN_OPERATOR(Subtract, '-');
            
            CODEGEN_OPERATOR(Multiply, '*');
            CODEGEN_OPERATOR(Divide, '/');
            
            CODEGEN_OPERATOR(Negate, '-');
            CODEGEN_OPERATOR(LogicalNot, '!');
            
            case OperatorType::Power: break;
            case OperatorType::In: break;
            case OperatorType::Is: break;
            case OperatorType::Mod: break;
        }
        #undef CODEGEN_OPERATOR

        out << ' ';
        codegen(expr->right, out);
    }

    out << ')';
}

void codegen(UnaryExpr* expr, std::ostream& out) {    
    out << '(';

    codegen(expr->expr, out);
    out << ' ';

    #define CODEGEN_OPERATOR(type_name, opstr) case OperatorType::type_name: out << opstr; break;
    switch (expr->op) {
        CODEGEN_OPERATOR(Negate, '-');
        CODEGEN_OPERATOR(LogicalNot, '!');
        
        default:
            assert(0 && "Invalid unary operator in codegen(UnaryExpr)");
    }
    #undef CODEGEN_OPERATOR
    out << ')';
}

void codegen(MemberExpr* expr, std::ostream& out) {    
    out << '(';
    codegen(expr->target, out);
    out << '.' << expr->field << ")";
}
void codegen(CallExpr* expr, std::ostream& out) {    
    out << '(';
    codegen(expr->target, out);
    out << '(';
    
    // Arguments
    bool isFirst = true;
    for (Expr* arg : expr->arguments) {
        
        if (!isFirst)
            out << ", ";
        else
            isFirst = false;
        
        codegen(arg, out);
    }
    
    out << "))";
}
void codegen(SubscriptExpr* expr, std::ostream& out) {    
    out << '(';
    codegen(expr->target, out);
    out << '[';
    codegen(expr->value, out);
    out << "])";
}
void codegen(StringLiteral* expr, std::ostream& out) {    
    out << "(\"" << expr->escapedValue() << "\")";
}
void codegen(BoolLiteral* expr, std::ostream& out) {    
    if (expr->value) {
        out << "(true)";
    }
    else {
        out << "(false)";
    }
}
