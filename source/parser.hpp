#import <deque>

#import "tokenizer.hpp"
#import "ast.hpp"

std::deque<Token> clean(const std::deque<Token>& tokens);
ParseTree parse(const std::deque<Token>& tokens);
