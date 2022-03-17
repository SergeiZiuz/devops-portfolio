//
//  supportedFunctionsForTestDatabase.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2019 Sergei Ziuzev. All rights reserved.
//

#include "headers/supportedFunctionsForTestDatabase.hpp"

static std::shared_ptr<Node> extr(std::istringstream &is) {
    return ParseCondition(is);
}

std::string DoPrint(const Database& database) {
    std::stringstream ss;
    database.Print(ss);
    std::string resalt;
    resalt = ss.str();
    return resalt;
}

std::vector<std::string> DoFind(const Database& database, std::istringstream& is) {
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const std::string& event) {
        return condition->Evaluate(date, event);
    };
    const auto entries = database.FindIf(predicate);
    
    return entries;
}

std::string DoLast(const Database& database, const Date& data) {
    return database.Last(data);
}

int DoDelete(Database& database, std::istringstream& is) {
    auto condition = extr(is);
    auto predicate = [condition](const Date& date, const std::string& event) {
        return condition->Evaluate(date, event);
    };
    
    return database.RemoveIf(predicate);
}
