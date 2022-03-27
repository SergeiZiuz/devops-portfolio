//
//  test.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/test_runner.hpp"
#include "headers/databaseTests.hpp"

#include <iostream>

void TestAll();
void TestParseEvent();
std::string ParseEvent(std::istream& is);

int main(int argc, const char* argv[]) {
    // TestAll();

    return 0;
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestAdd, "Database test Add");
    tr.RunTest(TestFind, "Database test Find");
    tr.RunTest(TestLast, "Database test Last");
    tr.RunTest(TestDel, "Database test Delete");
}

void TestParseEvent() {
    {
        std::istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        std::istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        std::istringstream is("  first event  \n  second event");
        std::vector<std::string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
    }
}