//
//  test_runner.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/test_runner.hpp"

void Assert (bool b, const std::string& hint) {
    return AssertEqual(b, true, hint);
}

TestRunner::~TestRunner() {
    if (failCount > 0) {
        std::cerr << failCount << " tests is failed. Terminate" << std::endl;
        exit(1);
    }
}
