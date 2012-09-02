#import <deque>

#import "tokenizer.hpp"
#import "ast.hpp"

ParseTree parse(const std::deque<Token>& tokens);
