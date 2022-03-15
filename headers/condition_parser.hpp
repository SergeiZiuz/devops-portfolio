//
//  condition_parser.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef condition_parser_h
#define condition_parser_h

#include "node.hpp"
#include "date.hpp"
#include "token.hpp"

#include <memory>
#include <iostream>
#include <map>

//using namespace std;

std::shared_ptr<Node> ParseCondition(std::istream& is);

void TestParseCondition();

#endif /* condition_parser_h */
