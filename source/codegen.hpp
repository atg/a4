#import "ast.hpp"
#import <ostream>

static void codegen(Expr* expr, std::ostream out) {
    switch (expr.type) {
        case ExprType::Binary:
            codegen(static_cast<BinaryExpr*>(expr), out);
            break;
    }
}

static void codegen(BinaryExpr* expr, std::ostream out) {    
    out << '(';
    
    if (expr.op == OperatorType::Power) {
        
        out << "std::pow(";
        codegen(left);
        out << ", ";
        codegen(right);
        out << ')';
        
    }
    else {
        codegen(left);
        out << ' ';
        
        #define CODEGEN_OPERATOR(type_name, opstr) case OperatorType::type_name; out << opstr; break;
        switch (expr.op) {
            CODEGEN_OPERATOR(Add, '+');
            CODEGEN_OPERATOR(Subtract, '-');
            CODEGEN_OPERATOR(Multiply, '*');
            CODEGEN_OPERATOR(Divide, '/');
        }
        #undef CODEGEN_OPERATOR;
        
        out << ' ';
        codegen(right);
    }
    
    out << ')';
}

