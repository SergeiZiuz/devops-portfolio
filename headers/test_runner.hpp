//
//  test_runner.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef test_runner_h
#define test_runner_h

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <memory>

// Interface
template <class T> std::ostream& operator << (std::ostream& os, const std::set<T>& s);
template <class T> std::ostream& operator << (std::ostream& os, const std::vector<T>& v);
template <class K, class V> std::ostream& operator << (std::ostream& os, const std::map<K, V>& m);
template <class T, class U> void AssertEqual (const T& t, const U& u, const std::string& hint);
void Assert (bool b, const std::string& hint);

class TestRunner {
public:
    template <class TestFunc>
    void RunTest (TestFunc func, const std::string& test_name);
    
    ~TestRunner();
private:
    int failCount = 0;
};

// Implementation

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
    os << "{";
    bool first = true;
    for (const std::string& item: s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << item;
    }
    return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << "{";
    bool first = true;
    for (const std::string& item: v) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << item;
    }
    return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& item: m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << item.first << ": "<< item.second;
    }
    
    return os << "}";
}

template <class TestFunc>
void TestRunner::RunTest (TestFunc func, const std::string& test_name) {
    try {
        func();
        std::cerr << test_name << " OK" << std::endl;
    } catch (std::runtime_error& e) {
        failCount++;
        std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
}

template <class T, class U>
void AssertEqual (const T& t, const U& u, const std::string& hint) {
    // значения двуз разных типов для удобства For usefull volumes is different type
    if (t != u) {
        std::ostringstream os;
        os << "Assertin faild: " << t << "!=" << u;
        throw std::runtime_error(os.str());
    }
}

#endif /* test_runner_h */
