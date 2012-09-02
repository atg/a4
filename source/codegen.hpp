#import "ast.hpp"
#import <ostream>

void codegen(ParseTree tree, std::ostream& out);

void codegen(Decl* decl, std::ostream& out);
void codegen(FunctionDecl* decl, std::ostream& out);

void codegen(Expr* expr, std::ostream& out);
void codegen(NumberLiteral* literal, std::ostream& out);
void codegen(BinaryExpr* expr, std::ostream& out);
