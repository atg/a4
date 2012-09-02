#import "ast.hpp"
#import <ostream>

void codegen(Expr* expr, std::ostream& out);
void codegen(NumberLiteral* literal, std::ostream& out);
void codegen(BinaryExpr* expr, std::ostream& out);
void codegen(ParseTree tree, std::ostream& out);
