//
//  token.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef token_h
#define token_h

#include <sstream>
#include <vector>
#include <string>
//using namespace std;

enum class TokenType {
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};

struct Token {
    const std::string value;
    const TokenType type;
};

std::vector<Token> Tokenize(std::istream& cl);

#endif /* token_h */
