//
//  node.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef node_h
#define node_h

#include "date.hpp"

#include <string>
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

template<class T, class U>
bool ComparisonValue (const Comparison cmp, const T& t, const U& u) {
    switch (cmp) {
        case Comparison::Less:
            return t < u;
        case Comparison::LessOrEqual:
            return t <= u;
        case Comparison::Greater:
            return t > u;
        case Comparison::GreaterOrEqual:
            return t >= u;
        case Comparison::Equal:
            return t == u;
        case Comparison::NotEqual:
            return t != u;
    }
    throw;
}

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) = 0;
};

class EmptyNode: public Node {
public:
    EmptyNode();
    virtual ~EmptyNode();
    
    bool Evaluate(const Date& date, const std::string& event) override;
};

class DateComparisonNode: public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    virtual ~DateComparisonNode();

    bool Evaluate(const Date& date, const std::string& event) override;
    
private:
    const Comparison _comparison;
    const Date _date;
};

class EventComparisonNode: public Node {
public:
    EventComparisonNode(Comparison cmp, const std::string& value);
    virtual ~EventComparisonNode();

    bool Evaluate(const Date& date, const std::string& event) override;
    
private:
    const Comparison _comparison;
    const std::string _value;
};

class LogicalOperationNode: public Node {
public:
    LogicalOperationNode(const LogicalOperation& logical_operation, const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right);
    virtual ~LogicalOperationNode();

    bool Evaluate(const Date& date, const std::string& event) override;
    
private:
    const LogicalOperation _logical_operation;
    const std::shared_ptr<Node> _left;
    const std::shared_ptr<Node> _right;
    
};

#endif /* node_h */
