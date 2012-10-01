#import "ast/ast.hpp"
#import <ostream>

// Decl
void codegen(ParseTree tree, std::ostream& out);

void codegen(Decl* decl, std::ostream& out);
void codegen(FunctionDecl* decl, std::ostream& out);


// Expr
void codegen(Expr* expr, std::ostream& out);
void codegen(BinaryExpr* expr, std::ostream& out);
void codegen(UnaryExpr* expr, std::ostream& out);

void codegen(MemberExpr* expr, std::ostream& out);
void codegen(SubscriptExpr* expr, std::ostream& out);
void codegen(CallExpr* expr, std::ostream& out);

void codegen(NumberLiteral* literal, std::ostream& out);
void codegen(StringLiteral* expr, std::ostream& out);
void codegen(BoolLiteral* expr, std::ostream& out);


// Type
