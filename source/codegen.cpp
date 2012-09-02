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
        case ExprType::Binary:
            codegen(static_cast<BinaryExpr*>(expr), out);
            break;
        
        case ExprType::Number:
            codegen(static_cast<NumberLiteral*>(expr), out);
            break;
        
        case ExprType::Unspecified: break;
    }
}

void codegen(NumberLiteral* literal, std::ostream& out) {    
    out << (literal->toString());
}

void codegen(BinaryExpr* expr, std::ostream& out) {    
    out << '(';

    if (expr->op == OperatorType::Power) {

        out << "std::pow(";
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
