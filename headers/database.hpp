//
//  database.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef database_h
#define database_h

#include "date.hpp"
#include "node.hpp"

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <iterator>

class Database {
public:
    void Add(const Date& date, const std::string& event);
    
    std::vector<std::string> FindIf(std::function<bool (const Date& date, const std::string& event)> evaluate) const;
    
    int RemoveIf(std::function<bool (const Date& date, const std::string& event)> evaluate);
    
    std::string Last(Date date) const;

    void Print(std::ostream &cout) const;
    
    int SizeDaties() const;
    
    int SizeEvents() const;
    
private:
    std::map<Date, std::vector<std::string>> storage;
    std::map<Date, std::set<std::string>> checkRepeat;
};

#endif /* database_h */

