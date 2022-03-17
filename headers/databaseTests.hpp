//
//  databaseTests.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef databaseTests_hpp
#define databaseTests_hpp

#include "database.hpp"
#include "date.hpp"
#include "condition_parser.hpp"
#include "node.hpp"
#include "test_runner.hpp"
#include "supportedFunctionsForTestDatabase.hpp"

#include <sstream>
#include <iostream>

void TestAdd();
void TestFind();
void TestLast();
void TestDel();

#endif /* databaseTests_hpp */
