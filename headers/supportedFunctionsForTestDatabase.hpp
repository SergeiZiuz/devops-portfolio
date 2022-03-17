//
//  supportedFunctionsForTestDatabase.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2019 Sergei Ziuzev. All rights reserved.
//

#ifndef supportedFunctionsForTestDatabase_hpp
#define supportedFunctionsForTestDatabase_hpp

#include "database.hpp"
#include "date.hpp"
#include "condition_parser.hpp"

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

std::string DoPrint(const Database& database);
int DoDelete(Database& database, std::istringstream& is);
std::string DoLast(const Database& database, const Date& date);
std::vector<std::string> DoFind(const Database& database, std::istringstream& is);



#endif /* supportedFunctionsForTestDatabase_hpp */
