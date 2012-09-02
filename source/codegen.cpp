#import "codegen.hpp"

void codegen(ParseTree tree, std::ostream& out) {
    codegen(tree.expr, out);
    out << '\n';
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
            CODEGEN_OPERATOR(Add, '+');
            CODEGEN_OPERATOR(Subtract, '-');
            CODEGEN_OPERATOR(Multiply, '*');
            CODEGEN_OPERATOR(Divide, '/');
            
            case OperatorType::Power: break;
        }
        #undef CODEGEN_OPERATOR

        out << ' ';
        codegen(expr->right, out);
    }

    out << ')';
}
