//
//  main.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/database.hpp"
#include "headers/date.hpp"
#include "headers/condition_parser.hpp"
#include "headers/node.hpp"
// #include "test_runner.h"
// #include "databaseTests.hpp"

#include <iostream>
#include <stdexcept>

std::string ParseEvent(std::istream& is);
// void TestAll();
// void TestParseEvent();

static std::shared_ptr<Node> extracted(std::istringstream &is) {
    return ParseCondition(is);
}

int main(int argc, const char* argv[]) {
//	TestAll();

	Database db;

	for (std::string line; getline(std::cin, line); ) {
        std::istringstream is(line);
        
        std::string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(std::cout);
        }
        else if (command == "Del") {
            auto condition = extracted(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            std::cout << "Removed " << count << " entries" << std::endl;
        }
        else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };
            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                std::cout << entry << std::endl;
            }
            std::cout << "Found " << entries.size() << " entries" << std::endl;
        } else if (command == "Last") {
            try {
                std::cout << db.Last(ParseDate(is)) << std::endl;
            } catch (std::invalid_argument&) {
                std::cout << "No entries" << std::endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw std::logic_error("Unknown command: " + command);
        }
    }
    
    return 0;
}

std::string ParseEvent(std::istream& is) {
    while (is.peek() == ' ') {
        is.get();
    }
    std::string event;
    getline(is, event);
    return event;
}