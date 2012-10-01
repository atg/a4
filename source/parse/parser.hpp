#import <deque>

#import "parse/tokenizer.hpp"
#import "ast/ast.hpp"

Expr* parseNumber(std::string number);
Expr* parseString(std::string str);

std::deque<Token> clean(const std::deque<Token>& tokens);
ParseTree parse(const std::deque<Token>& tokens);
