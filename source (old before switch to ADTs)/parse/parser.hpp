#import <deque>

#import "parse/tokenizer.hpp"
#import "ast/ast.hpp"

std::deque<Token> clean(const std::deque<Token>& tokens);
ParseTree parse(const std::deque<Token>& tokens);
