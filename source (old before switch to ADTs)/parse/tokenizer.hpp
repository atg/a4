#import <deque>
#import <string>
#import "parse/tokentypes.hpp"

struct Token {
    int type;
    int location;
    const char* payloadStart;
    const char* payloadEnd;
};

std::deque<Token> tokenize(const std::string& content);
